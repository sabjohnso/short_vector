#ifndef UTILITY_HPP_INCLUDED_622411775145667441
#define UTILITY_HPP_INCLUDED_622411775145667441 1

namespace ShortVector::Private
{

  template< typename T >
  struct unaligned{ T* ptr; };

  template< typename T >
  struct stream { T* ptr; };
  
} // end of namespace ShortVector::Private

#endif // ! defined UTILITY_HPP_INCLUDED_622411775145667441
