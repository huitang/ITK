/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkAnchorOpenCloseLine_h
#define __itkAnchorOpenCloseLine_h

#include "itkAnchorHistogram.h"

//#define RAWHIST

namespace itk
{
/**
 * \class AnchorOpenCloseLine
 * \brief class to implement openings and closings using anchor
 * methods. This is the base class that must be instantiated with
 * appropriate definitions of greater, less and so on
 */
template< class TInputPix, class TCompare >
class ITK_EXPORT AnchorOpenCloseLine
{
public:
  /** Some convenient typedefs. */
  typedef TInputPix InputImagePixelType;
  AnchorOpenCloseLine();
  ~AnchorOpenCloseLine()
  {
    delete m_Histo;
  }

  void PrintSelf(std::ostream & os, Indent indent) const;

  /** Single-threaded version of GenerateData.  This filter delegates
   * to GrayscaleGeodesicErodeImageFilter. */
  void DoLine(std::vector<InputImagePixelType> & buffer, unsigned bufflength);

  void SetSize(unsigned int size)
  {
    m_Size = size;
  }

private:
  unsigned int m_Size;

  typedef MorphologyHistogram< InputImagePixelType >              Histogram;
  typedef MorphologyHistogramVec< InputImagePixelType, TCompare > VHistogram;
  typedef MorphologyHistogramMap< InputImagePixelType, TCompare > MHistogram;

  bool StartLine(std::vector<InputImagePixelType> & buffer,
                 InputImagePixelType & Extreme,
                 Histogram & histo,
                 unsigned & outLeftP,
                 unsigned & outRightP);

  void FinishLine(std::vector<InputImagePixelType> & buffer,
                  InputImagePixelType & Extreme,
                  unsigned & outLeftP,
                  unsigned & outRightP);

  bool UseVectorBasedHistogram()
  {
    // bool, short and char are acceptable for vector based algorithm: they do
    // not require
    // too much memory. Other types are not usable with that algorithm
    return typeid( InputImagePixelType ) == typeid( unsigned char )
           || typeid( InputImagePixelType ) == typeid( signed char )
           || typeid( InputImagePixelType ) == typeid( unsigned short )
           || typeid( InputImagePixelType ) == typeid( signed short )
           || typeid( InputImagePixelType ) == typeid( bool );
  }

  Histogram *m_Histo;

  inline bool Compare1( const InputImagePixelType & a, const InputImagePixelType & b )
    {
    TCompare compare;
    return ! compare( a, b );
    }

  inline bool Compare2( const InputImagePixelType & a, const InputImagePixelType & b )
    {
    TCompare compare;
    return compare( a, b ) || a == b;
    }

}; // end of class
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkAnchorOpenCloseLine.txx"
#endif

#endif
