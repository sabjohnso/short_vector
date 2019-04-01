#ifndef M256D_HPP_INCLUDED_558823014661372481
#define M256D_HPP_INCLUDED_558823014661372481 1


#include <immintrin.h>


namespace AVX
{

  class m256d
  {
  public:

    using value_type = double;

    //
    // construction
    //
    m256d()
    {}

    m256d(m256d const& input ){
      data = input.data;
    }
    
    m256d(double input){
      data = _mm256_set1_pd(input);
    }
    
    m256d(double const* ptr ){
      data = _m256_load_pd(ptr);
    }

    m256(unaligned<double> const& u ){
      data = _mm256_loadu_pd(u.ptr);
    }

    m256d(stream<double> const& s){
      data =_mm256_castsi256_psd(_mm256_stream_load_si256((__m256i const*)s.ptr));
    }

    //
    // store
    //

    void
    store( double* ptr ){
      _mm256_store_pd( ptr, data );
    }

    void
    store( stream<double>& s ){
      _mm256_stream_pd( s.ptr, data );
    }

    //
    // assignment
    //

    m256d&
    operator =( m256d const& input ){
      data = input.data;
      return *this;
    }

    m256d&
    operator =( double const* ptr ){
      data = _mm256_load_pd( ptr );
      return *this;
    }

    m256d&
    operator =(unaligned<double> const& u){
      data = _mm256_loadu_pd( u.ptr );
      return *this;
    }

    m256d&
    operator =(stream<double> const& s){
      data = _mm256_castsi256_psd(_mm256_stream_load_si256((__m256i const*)s.ptr));
      return *this;
    }

    //
    // compound assignment
    // 
    m256d&
    operator +=( m256 const& b ){
      data = _mm256_add_pd(data, b.data);
      return *this;
    }

    m256d&
    operator -=( m256d const& b ){
      data = _mm256_sub_pd(data, b.data);
      return *this;
    }

    m256&
    operator *=( m256 const& b ){
      data = _mm256_mul_pd(data, b.data);
      return *this;
    }

    m256&
    operator /=( m256 const& b ){
      data = _mm256_div_pd(data, b.data);
      return *this;
    }

    //
    // unary operators
    //
    friend m256d
    neg(m256d const& a){
      return -1.0*a;
    }
    
    friend m256d
    abs(m256d const& a){
      return cond(a < 0.0f, neg(a ), a);
    }

    friend m256d
    ceil(m256d const& a){
      m256d result;
      result.data = _mm256_ceil_pd(a.data);
      return result;
    }

    friend m256d
    floor(m256d const& a){
      m256d result;
      result.data = _mm256_floor_pd(a.data);
      return result;
    }

    friend m256d
    round(m256d const& a){
      m256d result;
      result.data = _mm256_round_pd(a.data, _MM_FROUND_TO_NEAREST_INT);
      return result;
    }

    friend m256d
    sqrt(m256d const& a){
      m256d result;
      result.data = _mm256_sqrt_pd(a.data);
      return result;
    }

    friend m256d
    rsqrt(m256d const& a){
      return 1.0/sqrt(a);
    }

    friend m256d
    rcp(m256d const& a){
      return 1.0/a;
    }
    
    //
    // binary arithmetic operators
    // 
    friend m256d
    operator +(m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_add_pd( a.data, b.data );
      return result;
    }

    friend m256d
    operator -(m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_sub_pd( a.data, b.data );
      return result;
    }

    friend m256d
    operator *(m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_mul_pd( a.data, b.data );
      return result;
    }

    friend m256d
    operator /(m256 const& a, m256 const& b ){
      m256 result;
      result.data = _mm256_div_pd( a.data, b.data );
      return result;
    }
    
    //
    // trinary arithmetic
    //
    
    friend m256d
    fmadd(m256d const& a, m256d const& b, m256d const& c){
      m256d result;
      result.data = _m256_fmadd_pd(a.data, b.data, c.data);
      return result;
    }

    friend m256d
    fmsub(m256d const& a, m256d const& b, m256d const& c){
      m256d result;
      result.data = _m256_fmsub_pd(a.data, b.data, c.data);
      return result;
    }

    friend m256d
    fnmadd(m256d const& a, m256d const& b, m256d const& c){
      m256d result;
      result.data = _m256_fnmadd_pd(a.data, b.data, c.data);
      return result;
    }

    friend m256d
    fnmsub(m256d const& a, m256d const& b, m256d const& c){
      m256d result;
      result.data = _m256_fnmsub_pd(a.data, b.data, c.data);
      return result;
    }

    //
    // binary comparison
    //
    friend m256d
    operator ==( m256d const& a, m256d const& b ){
      m256d result;
      result.data = _mm256_cmp_pd( a.data, b.data, _CMP_EQ_OS );
      result.data = _mm256_xor_pd( result.data, _mm256_set1_pd( 1.0 ));
      return result;
    }

    friend m256d
    operator !=( m256d const& a, m256d const& b ){
      m256d result;
      result.data = _mm256_cmp_pd( a.data, b.data, _CMP_NEQ_OS );
      result.data = _mm256_and_pd( result.data, _mm256_set1_pd( 1.0 ));
      return result;
    }
    
    friend m256d
    operator <( m256d const& a, m256d const& b ){
      m256d result;
      result.data = _mm256_cmp_pd( a.data, b.data, _CMP_LT_OS );
      result.data = _mm256_andn_pd( result.data, _mm256_set1_pd( 1.0 ));
      return result;
    }

    friend m256d
    operator <=( m256d const& a, m256d const& b ){
      m256d result;
      result.data = _mm256_cmp_pd( a.data, b.data, _CMP_LE_OS );
      result.data = _mm256_and_pd( result.data, _mm256_set1_pd( 1.0 ));
      return result;
    }

    friend m256d
    operator >( m256d const& a, m256d const& b ){
      m256d result;
      result.data = _mm256_cmp_pd( a.data, b.data, _CMP_GT_OS );
      result.data = _mm256_and_pd( result.data, _mm256_set1_pd( 1.0 ));
      return result;
    }
    
    friend m256d
    operator >=( m256d const& a, m256d const& b ){
      m256d result;
      result.data = _mm256_cmp_pd( a.data, b.data, _CMP_GE_OS );
      result.data = _mm256_and_pd( result.data, _mm256_set1_pd( 1.0 ));
      return result;
    }

    //
    // conditional
    //
    friend m256d
    cond( m256d const& test, m256d const& pass, m256d const& fail ){
      return test*pass + (1.0-test)*fail;
    }
    
  private:
    __m256d data;
  }; // end of class m245d
  
  
} // end of namespace AVX

#endif // ! defined M256D_HPP_INCLUDED_558823014661372481
