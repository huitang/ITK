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
#ifndef __itkImageShapeModelEstimatorBase_h
#define __itkImageShapeModelEstimatorBase_h

#include "itkImageToImageFilter.h"

namespace itk
{
/** \class ImageShapeModelEstimatorBase
 * \brief Base class for statistical shape model estimation.
 *
 * itkImageShapeModelEstimatorBase is the base class for the
 * ImageShapeModelEstimator objects. It provides the basic function
 * definitions that are inherent to a ImageShapeModelEstimator objects.
 *
 * This is the SuperClass for the ImageShapeModelEstimator
 * framework. This is an abstract class defining an interface for all
 * such objects available through the ImageShapeModelEstimator
 * framework in the ITK toolkit.
 *
 * The basic functionality of the ImageShapeModelEstimator framework
 * base class is to generate the ShapeModels. It requires input image
 * to be provided by the user. EstimateShapeModels() is a pure virtual
 * function making this an abstract class. Classes deriving from this
 * class are required to implement the EstimateShapeModels function.
 *
 *  \ingroup ImageFeatureExtraction
 * \ingroup ITKImageStatistics
 */

template< class TInputImage,
          class TOutputImage = Image< double, ::itk::GetImageDimension< TInputImage >::ImageDimension > >
class ITK_EXPORT ImageShapeModelEstimatorBase:
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef ImageShapeModelEstimatorBase                    Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self >                      ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageShapeModelEstimatorBase, ImageToImageFilter);

  /** Type definitions for the training image. */
  typedef          TInputImage          InputImageType;
  typedef typename TInputImage::Pointer InputImagePointer;
protected:
  ImageShapeModelEstimatorBase();
  ~ImageShapeModelEstimatorBase();
  void PrintSelf(std::ostream & os, Indent indent) const;

  virtual void GenerateData();

private:

  ImageShapeModelEstimatorBase(const Self &); //purposely not implemented
  void operator=(const Self &);               //purposely not implemented

  /**Container for holding the training image */
  InputImagePointer m_InputImage;

  /** The core virtual function to perform ShapeModelling of the input data */
  virtual void EstimateShapeModels() = 0;
}; // class ImageShapeModelEstimator
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImageShapeModelEstimatorBase.hxx"
#endif

#endif
