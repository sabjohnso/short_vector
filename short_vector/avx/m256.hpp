#ifndef AVX_HPP_INCLUDED_1088355495191842989
#define AVX_HPP_INCLUDED_1088355495191842989 1

//
// ... Intrinsics
//
#include <immintrin.h>

//
// ... Short Vector header files
//
#include <short_vector/avx/utility.hpp>

namespace AVX
{
  struct unaligned_tag{};
  struct stream_tag{};
  
  class m256
  {
  public:

    //
    // constructors
    // 
    m256(){}

    m256( float input ){
      data = _mm256_set1_ps(input);
    }
   
    m256( float const* ptr ){
      data = _mm256_load_ps(ptr);
    }

    m256( unaligned<float> const& u){
      data = _mm256_loadu_ps( u.ptr );
    }

    m256( stream<float> const& s ){      
      data =_mm256_castsi256_ps(_mm256_stream_load_si256((__m256i const*)s.ptr));
    }

    
    //
    // store
    //
    void
    store( float* ptr ){
      _mm256_store_ps( ptr, data );
    }

    void
    store( float* ptr, stream_tag){
      _mm256_stream_ps( ptr, data );
    }

    //
    // assignment
    //

    m256&
    operator =(float const* ptr){
      data = _mm256_load_ps(ptr);
      return *this;
    }

    m256&
    operator =(unaligned<float> const& u){
      data = _mm256_loadu_ps(u.ptr);
      return *this;
    }

    m256&
    operator =(stream<float> const& s){
      data =_mm256_castsi256_ps(_mm256_stream_load_si256((__m256i const*)s.ptr));
      return *this;
    }

    m256&
    operator =( m256 const& input ){      
      data = input.data;
      return *this;
    }

    //
    // compound assignment
    //
    m256&
    operator +=(m256 const& b){
      data = _mm256_add_ps( data, b.data );
      return *this;
    }

    m256&
    operator -=(m256 const& b){
      data = _mm256_sub_ps( data, b.data );
      return *this;
    }

    m256&
    operator *=(m256 const& b ){
      data = _mm256_mul_ps( data, b.data );
      return *this;
    }

    m256&
    operator /=(m256 const& b ){
      data = _mm256_div_ps( data, b.data );
      return *this;
    }

    //
    // unary operators
    //
    friend m256
    neg(m256 const& a){
      return -1.0f*a;
    }
    
    friend m256
    abs(m256 const& a){
      return cond( a < 0.0f, -1.0f*a, a);
    }

    friend m256
    ceil(m256 const& a){
      m256 result;
      result.data = _mm256_ceil_ps(a.data);
      return result;
    }

    friend m256
    floor(m256 const& a){
      m256 result;
      result.data = _mm256_floor_ps(a.data);
      return result;
    }

    friend m256
    round(m256 const& a){
      m256 result;
      result.data = _mm256_round_ps(a.data, _MM_FROUND_TO_NEAREST_INT);
      return result;
    }

    friend m256
    sqrt(m256 const& a){
      m256 result;
      result.data = _mm256_sqrt_ps(a.data);
      return result;
    }

    friend m256
    rsqrt(m256 const& a){
      m256 result;
      result.data = _mm256_rsqrt_ps(a.data);
      return result;
    }

    friend m256
    rcp(m256 const& a){
      m256 result;
      result.data = _mm256_rcp_ps(a.data);
      return result;
    }

    //
    // binary operators
    //
    friend m256
    operator +( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_add_ps(a.data, b.data);
      return result;
    }
    
    friend m256
    operator -( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_sub_ps(a.data, b.data);
      return result;
    }

    friend m256
    operator *( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_mul_ps(a.data, b.data);
      return result;
    }

    friend m256
    operator /( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_div_ps(a.data, b.data);
      return result;
    }

    //
    // trinary arithmetic
    //

    friend m256
    fma( m256 const& a, m256 const& b, m256 const& c ){
      m256 result;
      result.data = _mm256_fmadd_ps(a.data, b.data, c.data);
      return result;
    }

    friend m256
    fms( m256 const& a, m256 const& b, m256 const& c ){
      m256 result;
      result.data = _mm256_fmsub_ps(a.data, b.data, c.data);
      return result;
    }

    friend m256
    fnma( m256 const& a, m256 const& b, m256 const& c ){
      m256 result;
      result.data = _mm256_fnmadd_ps(a.data, b.data, c.data);
      return result;
    }

    friend m256
    fnms( m256 const& a, m256 const& b, m256 const& c ){
      m256 result;
      result.data = _mm256_fnmsub_ps(a.data, b.data, c.data);
      return result;
    }

    //
    // binary comparison
    //
    friend m256
    operator ==( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_cmp_ps(a.data, b.data, _CMP_EQ_OS);
      result.data = _mm256_and_ps(result.data, _mm256_set1_ps(1.0f));
      return result;
    }

    friend m256
    operator !=( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_cmp_ps(a.data, b.data, _CMP_NEQ_OS);
      result.data = _mm256_and_ps(result.data, _mm256_set1_ps(1.0f));
      return result;
    }

    friend m256
    operator <( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_cmp_ps(a.data, b.data, _CMP_LT_OS);
      result.data = _mm256_and_ps(result.data, _mm256_set1_ps(1.0f));
      return result;
    }

    friend m256
    operator <=( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_cmp_ps(a.data, b.data, _CMP_LE_OS);
      result.data = _mm256_and_ps(result.data, _mm256_set1_ps(1.0f));
      return result;
    }

    
    friend m256
    operator >( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_cmp_ps(a.data, b.data, _CMP_GT_OS);
      result.data = _mm256_and_ps(result.data, _mm256_set1_ps(1.0f));
      return result;
    }

    
    friend m256
    operator >=( m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_cmp_ps(a.data, b.data, _CMP_GE_OS);
      result.data = _mm256_and_ps(result.data, _mm256_set1_ps(1.0f));
      return result;
    }

    //
    // conditional
    //
    friend m256
    cond( m256 const& test, m256 const& pass, m256 const& fail ){
      return test*pass + (1.0f-test)*fail;
    }
    
  private:
    __m256 data;
  }; // end of class 
  
} // end of namespace AVX2

#endif // ! defined AVX_HPP_INCLUDED_1088355495191842989
