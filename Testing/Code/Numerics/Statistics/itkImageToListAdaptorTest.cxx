/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageToListAdaptorTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkImageToListAdaptor.h"
#include "itkRandomImageSource.h"
#include "itkImageRegionIterator.h"

int itkImageToListAdaptorTest(int, char**) 
{
  std::cout << "ImageToListAdaptor Test \n \n"; 
  bool pass = true;
  std::string whereFail = "" ;

  typedef itk::Image< float, 3 > FloatImage ;

  // Now generate a random image
  typedef itk::RandomImageSource<FloatImage> SourceType;
  SourceType::Pointer source = SourceType::New();
  unsigned long size[3] = {17, 8, 20} ;
  unsigned long totalSize = size[0] * size[1] * size[2] ;

  source->SetSize(size);
  float minValue = -100.0;
  float maxValue = 1000.0;

  source->SetMin( static_cast< FloatImage::PixelType >( minValue ) );
  source->SetMax( static_cast< FloatImage::PixelType >( maxValue ) );
  source->Update() ;

  typedef  itk::Statistics::ImageToListAdaptor< FloatImage,
    itk::Statistics::ScalarImageAccessor< FloatImage > >
    ImageToListAdaptorType ;

  ImageToListAdaptorType::Pointer sample = ImageToListAdaptorType::New() ;
  sample->SetImage(source->GetOutput()) ;

  // tests begin

  if (totalSize != sample->Size())
    {
      pass = false ;
      whereFail = "Size()" ;
    }

  if (totalSize != sample->Size(0))
    {
      pass = false ;
      whereFail = "Size(0)" ;
    }

  if (totalSize != sample->GetNumberOfInstances())
    {
      pass = false ;
      whereFail = "GetNumberOfInstances()" ;
    }

  FloatImage::IndexType index ;
  index.Fill(2) ;// index {2, 2, 2} = instance identifier (offset from image) 
  FloatImage::PixelType pixel = sample->GetImage()->GetPixel(index) ;
  ImageToListAdaptorType::InstanceIdentifier id = 
    static_cast< FloatImage::OffsetValueType >(sample->GetImage()
                                               ->ComputeOffset(index)) ;

  if (pixel != sample->GetMeasurementVector(id)[0])
    {
      pass = false ;
      whereFail = "GetMeasurementVector()" ;
    }

  // iterator test
  typedef itk::ImageRegionIterator< FloatImage > ImageIterator ;
  ImageIterator i_iter(sample->GetImage(),
                       sample->GetImage()->GetLargestPossibleRegion()) ;

  ImageToListAdaptorType::Iterator s_iter = sample->Begin() ;

  while (!i_iter.IsAtEnd())
    {
      if (i_iter.Get() != s_iter.GetMeasurementVector()[0])
        {
          pass = false ;
          whereFail = "Iterator: GetMeasurementVecto()" ;
        }
      ++i_iter ;
      ++s_iter ;
    }

  if (s_iter != sample->End())
    {
      pass = false ;
      whereFail = "Iterator: End()" ;
    }

  if( !pass )
    {
      std::cout << "Test failed in " << whereFail << "." << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "Test passed." << std::endl;
  return EXIT_SUCCESS;


}



