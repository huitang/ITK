#
#  Program:   Insight Segmentation & Registration Toolkit
#  Module:    itkutils.tcl
#  Language:  C++
#  Date:      $Date$
#  Version:   $Revision$
#
#  Copyright (c) 2002 Insight Consortium. All rights reserved.
#  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.
#
#     This software is distributed WITHOUT ANY WARRANTY; without even 
#     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
#     PURPOSE.  See the above copyright notices for more information.
#

# Define ITK Tcl utilities.
namespace eval itk {
  
  # Allow code like "$obj Print [itk::result]
  proc result {} {
    return [itk::TclStringStream [cable::Interpreter]]
  }
  
  # Create an object of the given type.  Return a pointer to it.  A
  # smart pointer to the object is kept in a list that is destroyed at
  # program exit.
  proc create {type} {
    global itk::_ObjectList_
    set ptr [itk::$type New]
    set p [$ptr ->]
    lappend _ObjectList_ $ptr
    return $p
  }

  # Start with an empty object list.
  set _ObjectList_ {}
  
  # Create an image viewing window.
  proc createImageViewer2D {name image} {
    # Create the display window.
    toplevel $name
    frame $name.xy
    pack $name.xy -expand 1 -fill both -side left
    canvas $name.xy.canvas -scrollregion "1 1 32 32" \
                           -xscrollcommand "$name.xy.scrollx set" \
                           -yscrollcommand "$name.xy.scrolly set"
    scrollbar $name.xy.scrollx -orient horizontal \
                               -command "$name.xy.canvas xview"
    scrollbar $name.xy.scrolly -orient vertical \
                               -command "$name.xy.canvas yview"
    pack $name.xy.scrollx -side bottom -fill x
    pack $name.xy.scrolly -side right -fill y
    pack $name.xy.canvas -expand 1 -fill both
    
    # Create a Tk image on the canvas.
    set i [image create photo]
    $name.xy.canvas create image 0 0 -image $i -anchor nw
    
    # Setup the TkImageViewer2D instance.
    set viewer [itk::create TkImageViewer2D]
    $viewer SetInput $image
    $viewer SetInterpreter [cable::Interpreter]
    $viewer SetImageName $i
    $viewer SetCanvasName $name.xy.canvas
    return $viewer
  }
  
  # Create a Tcl callback event.
  proc createTclCommand { cmd } {
    set command [itk::create TclCommand]
    $command SetInterpreter [cable::Interpreter]
    $command SetCommandString $cmd
    return $command
  } 

  namespace export create result createImageViewer2D
}

# Define ITK Tcl interactor.
namespace eval itk::interact {

  set Bold "-background #43ce80 -foreground #221133 -relief raised -borderwidth 1"
  set Normal "-background #dddddd -foreground #221133 -relief flat"
  set Tagcount 1
  set CommandList ""
  set CommandIndex 0

  proc createInteractor {} {
    global itk::interact::CommandList
    global itk::interact::CommandIndex
    global itk::interact::Tagcount
    
    proc doitk {s w} {
      global itk::interact::Bold
      global itk::interact::Normal
      global itk::interact::Tagcount 
      global itk::interact::CommandList
      global itk::interact::CommandIndex
      
      set tag [append tagnum $Tagcount]
      set CommandIndex $Tagcount
      incr Tagcount 1
      .itkInteract.display.text configure -state normal
      .itkInteract.display.text insert end $s $tag
      set CommandList [linsert $CommandList end $s]
      eval .itkInteract.display.text tag configure $tag $Normal
      .itkInteract.display.text tag bind $tag <Any-Enter> \
      	".itkInteract.display.text tag configure $tag $Bold"
      .itkInteract.display.text tag bind $tag <Any-Leave> \
      	".itkInteract.display.text tag configure $tag $Normal"
      .itkInteract.display.text tag bind $tag <1> "itk::interact::doitk [list $s] .itkInteract"
      .itkInteract.display.text insert end \n;
      .itkInteract.display.text insert end [uplevel 1 $s]
      .itkInteract.display.text insert end \n\n
      .itkInteract.display.text configure -state disabled
      .itkInteract.display.text yview end
    }
    
    catch {destroy .itkInteract}
    toplevel .itkInteract -bg #bbbbbb
    wm title .itkInteract "itk Interactor"
    wm iconname .itkInteract "itk"
    
    frame .itkInteract.buttons -bg #bbbbbb
    pack  .itkInteract.buttons -side bottom -fill both -expand 0 -pady 2m
    button .itkInteract.buttons.dismiss -text Dismiss \
	    -command "wm withdraw .itkInteract" \
	    -bg #bbbbbb -fg #221133 -activebackground #cccccc -activeforeground #221133
    pack .itkInteract.buttons.dismiss -side left -expand 1 -fill x
    
    frame .itkInteract.file -bg #bbbbbb
    label .itkInteract.file.label -text "Command:" -width 10 -anchor w \
	    -bg #bbbbbb -fg #221133
    entry .itkInteract.file.entry -width 40 \
	    -bg #dddddd -fg #221133 -highlightthickness 1 -highlightcolor #221133
    bind .itkInteract.file.entry <Return> {
        itk::interact::doitk [%W get] .itkInteract; %W delete 0 end
    }
    pack .itkInteract.file.label -side left
    pack .itkInteract.file.entry -side left -expand 1 -fill x
    
    frame .itkInteract.display -bg #bbbbbb
    text .itkInteract.display.text -yscrollcommand ".itkInteract.display.scroll set" \
	    -setgrid true -width 60 -height 8 -wrap word -bg #dddddd -fg #331144 \
	    -state disabled
    scrollbar .itkInteract.display.scroll \
	    -command ".itkInteract.display.text yview" -bg #bbbbbb \
	    -troughcolor #bbbbbb -activebackground #cccccc -highlightthickness 0 
    pack .itkInteract.display.text -side left -expand 1 -fill both
    pack .itkInteract.display.scroll -side left -expand 0 -fill y
    
    pack .itkInteract.display -side bottom -expand 1 -fill both
    pack .itkInteract.file -pady 3m -padx 2m -side bottom -fill x 
    
    set CommandIndex 0
    
    bind .itkInteract <Down> {
      global itk::interact::CommandIndex
      global itk::interact::CommandList

      if { $CommandIndex < [expr $Tagcount - 1] } {
	incr CommandIndex
	set command_string [lindex $CommandList $CommandIndex]
	.itkInteract.file.entry delete 0 end
	.itkInteract.file.entry insert end $command_string
      } elseif { $CommandIndex == [expr $Tagcount - 1] } {
	.itkInteract.file.entry delete 0 end
      }
    }
	
    bind .itkInteract <Up> {
      global itk::interact::CommandIndex
      global itk::interact::CommandList

      if { $CommandIndex > 0 } { 
	set CommandIndex [expr $CommandIndex - 1]
	set command_string [lindex $CommandList $CommandIndex]
	.itkInteract.file.entry delete 0 end
	.itkInteract.file.entry insert end $command_string
      }
    }
    
    wm withdraw .itkInteract
  }
  
  # Create the interactor.
  createInteractor
}
