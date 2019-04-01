#ifndef UTILITY_HPP_INCLUDED_622411775145667441
#define UTILITY_HPP_INCLUDED_622411775145667441 1

namespace AVX
{

  template< typename T >
  struct unaligned{ T* ptr; };

  template< typename T >
  struct stream { T* ptr; };
    
  
} // end of namespace AVX

#endif // ! defined UTILITY_HPP_INCLUDED_622411775145667441
