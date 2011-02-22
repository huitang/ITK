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
#ifndef __itkWatershedSegmentTree_txx
#define __itkWatershedSegmentTree_txx

namespace itk
{
namespace watershed
{
//template <class TScalarType>
//void  SegmentTree<TScalarType>
//::PrintDeque()
//{
//  std::cout << "Deque has " << this->Size() << " entries. " << std::endl;
//  Iterator it = this->Begin();
//  while ( it != this->End() )
//    {
//      std::cout << (*it).from << " -> "
//                << (*it).to << " " << (*it).saliency
//                << std::endl;
//      ++it;
//    }
//}

template< class TScalarType >
void
SegmentTree< TScalarType >
::Initialize()
{
  //
  // We don't modify ourselves because the "ReleaseData" methods depend upon
  // no modification when initialized.
  //

  // Call the superclass method
  Superclass::Initialize();

  // Clear the segment tree
  this->Clear();
}

template< class TScalarType >
void
SegmentTree< TScalarType >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}
} // end namespace watershed
} // end namespace itk

#endif