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
#ifndef __itkDemonsImageToImageMetricv4GetValueAndDerivativeThreader_hxx
#define __itkDemonsImageToImageMetricv4GetValueAndDerivativeThreader_hxx

#include "itkDemonsImageToImageMetricv4GetValueAndDerivativeThreader.h"

namespace itk
{

template< class TDomainPartitioner, class TImageToImageMetric, class TDemonsMetric >
bool
DemonsImageToImageMetricv4GetValueAndDerivativeThreader< TDomainPartitioner, TImageToImageMetric, TDemonsMetric >
::ProcessPoint( const VirtualIndexType &,
                const VirtualPointType &,
                const FixedImagePointType &,
                const FixedImagePixelType &        fixedImageValue,
                const FixedImageGradientType &     fixedImageGradient,
                const MovingImagePointType &,
                const MovingImagePixelType &       movingImageValue,
                const MovingImageGradientType &    movingImageGradient,
                MeasureType &                      metricValueReturn,
                DerivativeType &                   localDerivativeReturn,
                const ThreadIdType ) const
{
   TDemonsMetric * associate = dynamic_cast< TDemonsMetric * >( this->m_Associate );

  /* Metric value */
  const InternalComputationValueType speedValue = fixedImageValue - movingImageValue;
  const InternalComputationValueType sqr_speedValue = vnl_math_sqr( speedValue );
  metricValueReturn = sqr_speedValue;

  /* Derivative */
  InternalComputationValueType  gradientSquaredMagnitude = 0;
  const FixedImageGradientType* gradient;
  SizeValueType                 numberOfDimensions;

  if( associate->GetGradientSourceIncludesFixed() )
    {
    gradient = &fixedImageGradient;
    numberOfDimensions = ImageToImageMetricv4Type::FixedImageDimension;
    }
  else
    {
    gradient = &movingImageGradient;
    numberOfDimensions = ImageToImageMetricv4Type::MovingImageDimension;
    }

  for ( ImageDimensionType j = 0; j < numberOfDimensions; j++ )
    {
    gradientSquaredMagnitude += vnl_math_sqr( (*gradient)[j] );
    }

  /*
   * In the original equation the denominator is defined as (g-f)^2 + grad_mag^2.
   * However there is a mismatch in units between the two terms.
   * The units for the second term is intensity^2/mm^2 while the
   * units for the first term is intensity^2. This mismatch is particularly
   * problematic when the fixed image does not have unit spacing.
   * In this implemenation, we normalize the first term by a factor K,
   * such that denominator = (g-f)^2/K + grad_mag^2
   * where K = mean square spacing to compensate for the mismatch in units.
   */
  const InternalComputationValueType denominator = sqr_speedValue / associate->m_Normalizer + gradientSquaredMagnitude;

  if ( vnl_math_abs(speedValue) < associate->GetIntensityDifferenceThreshold() ||
       denominator < associate->GetDenominatorThreshold() )
    {
    localDerivativeReturn.Fill( NumericTraits<DerivativeValueType>::Zero );
    return true;
    }

  for ( SizeValueType p = 0; p < associate->GetNumberOfLocalParameters(); p++ )
    {
    localDerivativeReturn[p] = speedValue * (*gradient)[p] / denominator;
    }

  return true;
}

} // end namespace itk

#endif
