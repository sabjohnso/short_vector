#ifndef M512_HPP_INCLUDED_97185451340719794
#define M512_HPP_INCLUDED_97185451340719794 1

//
// ... Intrinsics header files
//
#include <immintrin.h>


//
// ... Short Vector header files
//
#include <short_vector/utility.hpp>



namespace AVX512
{

  using ShortVector::Private::unaligned;
  using ShortVector::Private::stream;



  class m512
  {
  public:

    enum{
      NEAREST_EVEN_INTEGER = 0,
      EQUAL_OR_SMALLER_INTEGER = 1,
      EQUAL_OR_LARGER_INTEGER =2,
      NEAREST_SMALLEST_MAGNITUDE_INTEGER=3
    };

    static m512 const zero;
    static m512 const one;
    
    //
    // constructors
    //
    m512(){}

    m512( m512 const& input ){
      data = input.data;
    }

    m512( float input ){
      data = _mm512_set1_ps( input );
    }

    m512( float const* input ){
      data = _mm512_load_ps( input );
    }

    m512( unaligned<float> const& u ){
      data = _mm512_loadu_ps(u.ptr);
    }

    m512( stream<float> const& u ){
      data = _mm512_casti512_ps( _mm512_stream_load_si512((void const*)(u.ptr)));
    }

    //
    // store
    //
    void
    store( float* ptr ){
      _mm512_store_ps( ptr, data );
    }

    void
    store(unaligned<float>& u){
      _mm512_storeu_ps( u.ptr, data );
    }

    void
    store(stream<float>& s){
      _mm512_stream_ps( s.ptr, data );
    }


    //
    // assignment
    //

    m512&
    operator =(m512 const& input){
      data = input.data;
      return *this;
    }

    m512&
    operator =(float input){
      data = _mm512_set1_ps(input);
      return *this;
    }

    m512&
    operator =(float const* ptr){
      data = _mm512_load_ps(input);
      return *this;
    }

    m512&
    operator =(unaligned<float> const& u){
      data = _mm512_loadu_ps(u.ptr);
      return *this;
    }

    m512&
    operator =(stream<float> const& s){
      data = _mm512_casti512_ps( _mm512_stream_load_si512((void const*)(u.ptr)));
      return *this;
    }

    //
    // compound assignment
    //
    m512&
    operator +=(m512 const& b){
      data = _mm512_add_ps(data, b.data);
      return *this;
    }

    m512&
    operator -=(m512 const& b){
      data = _mm512_sub_ps(data, b.data);
      return *this;
    }

    m512&
    operator *=(m512 const& b){
      data = _mm512_mul_ps(data, b.data);
      return *this;
    }

    m512&
    operator /=(m512 const& b){
      data = _mm512_div_ps(data, b.data);
      return *this;
    }

    //
    // unary operators
    //

    friend m512
    neg(m512 const& a){
      return -1.0*a;
    }

    friend m512
    abs(m512 const& a){
      m512 result;
      result.data = _mm512_abs_ps( a.data());
    }

    friend m512
    ceil( m512 const& a ){
      m512 result;
      result.data = _mm512_roundscale_ps( a.data(), EQUAL_OR_LARGER_INTEGER);
      return result;
    }

    friend m512
    floor( m512 const& a ){
      m512 result;
      result.data = _mm512_roundscale_ps( a.data(), EQUAL_OR_SMALLER_INTEGER);
      return result;
    }


    friend m512
    trunc( m512 const& a ){
      m512 result;
      result.data = _mm512_roundscale_ps( a.data(), NEAREST_SMALLEST_MAGNITUDE_INTEGER);
      return result;
    }
    
    //
    // binary arithmetic
    //
   
    friend m512
    operator +(m512 const& a, m512 const& b){
      m512 result;
      result.data = _mm512_add_ps(a.data, b.data);
      return result;
    }

    friend m512
    operator -(m512 const& a, m512 const& b){
      m512 result;
      result.data = _mm512_sub_ps(a.data, b.data);
      return result;
    }

    friend m512
    operator *(m512 const& a, m512 const& b){
      m512 result;
      result.data = _mm512_mul_ps(a.data, b.data);
      return result;
    }

    friend m512
    operator /(m512 const& a, m512 const& b){
      m512 result;
      result.data = _mm512_div_ps(a.data, b.data);
      return result;
    }

    //
    // trinary arithmetic
    //
    friend m512
    operator fmadd(m512 const& a, m512 const& b, m512 const& c){
      m512 result;
      result.data = _mm512_fmadd_ps(a.data, b.data, c.data);
      return result;
    }

    friend m512
    operator fmsub(m512 const& a, m512 const& b, m512 const& c){
      m512 result;
      result.data = _mm512_fmsub_ps(a.data, b.data, c.data);
      return result;
    }

    friend m512
    operator fnmadd(m512 const& a, m512 const& b, m512 const& c){
      m512 result;
      result.data = _mm512_fnmadd_ps(a.data, b.data, c.data);
      return result;
    }

    friend m512
    operator fnmsub(m512 const& a, m512 const& b, m512 const& c){
      m512 result;
      result.data = _mm512_fnmsub_ps(a.data, b.data, c.data);
      return result;
    }

    //
    // binary comparison
    //
    
    friend m512
    operator ==(m512 const& a, m512 const& b){
      m512 result;
      __mmask16 mask;
      mask = _mm512_cmp_ps_mash( a.data(), b.data(), _CMP_EQ_OS);
      result.data = _mm512_mask_blend_ps(mask, one.data, zero.data);
      return result;
    }

    friend m512
    operator !=(m512 const& a, m512 const& b){
      m512 result;
      __mmask16 mask;
      mask = _mm512_cmp_ps_mash( a.data(), b.data(), _CMP_NEQ_OS);
      result.data = _mm512_mask_blend_ps(mask, one.data, zero.data);
      return result;
    }

    friend m512
    operator <(m512 const& a, m512 const& b){
      m512 result;
      __mmask16 mask;
      mask = _mm512_cmp_ps_mash( a.data(), b.data(), _CMP_LT_OS);
      result.data = _mm512_mask_blend_ps(mask, one.data, zero.data);
      return result;
    }

    friend m512
    operator <=(m512 const& a, m512 const& b){
      m512 result;
      __mmask16 mask;
      mask = _mm512_cmp_ps_mash( a.data(), b.data(), _CMP_LE_OS);
      result.data = _mm512_mask_blend_ps(mask, one.data, zero.data);
      return result;
    }

    friend m512
    operator >(m512 const& a, m512 const& b){
      m512 result;
      __mmask16 mask;
      mask = _mm512_cmp_ps_mash( a.data(), b.data(), _CMP_GT_OS);
      result.data = _mm512_mask_blend_ps(mask, one.data, zero.data);
      return result;
    }

    friend m512
    operator >=(m512 const& a, m512 const& b){
      m512 result;
      __mmask16 mask;
      mask = _mm512_cmp_ps_mash( a.data(), b.data(), _CMP_GE_OS);
      result.data = _mm512_mask_blend_ps(mask, one.data, zero.data);
      return result;
    }

    //
    // conditional
    //

    friend m512
    cond( m512 const& test, m512 const& pass, m512 const& fail ){
      return test*pass + (one-test)*fail;
    }
    
  private:
    __m512 data;
  }; // end of class m512
  
  m512 const m512::zero(0.0f);
  m512 const m512::one(1.0f);

  
} // end of namespace AVX512

#endif // ! defined M512_HPP_INCLUDED_97185451340719794
