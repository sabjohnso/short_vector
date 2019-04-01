//
// ... Standard header files
//
#include <cstddef>
#include <utility>
#include <array>
#include <vector>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... Short Vector header files
//
#include <short_vector/avx/m256.hpp>

namespace 
{
  using size_type = std::ptrdiff_t;
  using std::forward;
  using std::array;
  using std::vector;

  template< typename ...Ts >
  void
  pass( Ts&& ... ){
  }


  using AVX::m256;
  using AVX::stream_tag;
  
  template< typename T, size_t N, size_t A >
  class alignas(A) aligned_array : public array<T,N>
  {
  public:
    using value_type = T;
    using pointer = value_type*;
    using const_pointer = value_type const*;

    static constexpr size_t extent = N;
    static constexpr size_t alignment = A;

    template< typename ... Ts >
    constexpr
      aligned_array( value_type x1, value_type x2, Ts&& ... xs )
      : base({x1, x2, xs ...})
    {}
   
    using base = array<value_type , extent>;
    using base::base;

    pointer
    data(){ return &base::operator[](0); }

    const_pointer
    data() const { return &base::operator[](0); }
  }; // end of class alignas
  

  TEST(m256, construction_pointer)
  {
    aligned_array<float,8,32> xs(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f);
    aligned_array<float,8,32> out;

    []( auto a ){ return a; }( m256( xs.data())).store(out.data());

    for(size_type i = 0; i < 8; ++i){
      EXPECT_EQ(xs[i], out[i]);
    }

  } // end of test m256.construction_pointer


  TEST(m256, construction_value)
  {
    float x = 3.2;
    aligned_array<float,8,32> out;

    []( auto a ){ return a; }( m256( x )).store(out.data());

    for(size_type i = 0; i < 8; ++i){
      EXPECT_EQ(out[i],  x);
    }

  }

  TEST(m256, addition){
    aligned_array<float,8,32> xs(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f);
    aligned_array<float,8,32> out;

    for( size_t i = 0; i < 100; ++i){
    
      [](auto const& a, auto const& b ){
	return a+b;
      }( m256( xs.data()), m256(3.4f)).store( out.data());
    }

    for(size_type i = 0; i< 8; ++i){
      EXPECT_EQ( out[i], xs[i]+3.4f);
    }        
  }


  TEST(m256, addition_scalar){
    aligned_array<float,8,32> xs(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f);
    aligned_array<float,8,32> out1;
    [](auto const& a, auto b ){
      return a+b;
    }( m256( xs.data()), 3.4f ).store(out1.data());

    for(size_type i = 0; i< 8; ++i){
      EXPECT_EQ( out1[i], xs[i]+3.4f);
    }

    aligned_array<float,8,32> out2;

    [](auto a, auto const& b ){
      return a+b;
    }( 3.4f, m256( xs.data())).store(out2.data());

    for(size_type i = 0; i< 8; ++i){
      EXPECT_EQ( out2[i], xs[i]+3.4f);
    }
  }


  TEST(m256, fma){
    aligned_array<float,8,32> as(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f);
    aligned_array<float,8,32> bs(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f);
    aligned_array<float,8,32> cs(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f);
    
    aligned_array<float,8,32> out;
    [](auto const& a, auto const& b, auto const& c){
      return fma(a, b, c);
    }( m256(as.data()), m256(bs.data()), m256(cs.data())).store(out.data());
  }

  TEST(m256, abs){
    aligned_array<float,8,32> as{-3.0f,-2.0f,-1.0f,0.0f,1.0f,2.0f,3.0f,4.0f};
    aligned_array<float,8,32> out;
    abs(m256(as.data())).store(out.data());

    EXPECT_EQ(out[0], 3.0f);
    EXPECT_EQ(out[1], 2.0f);
    EXPECT_EQ(out[2], 1.0f);
    EXPECT_EQ(out[3], 0.0f);
    EXPECT_EQ(out[4], 1.0f);
    EXPECT_EQ(out[5], 2.0f);
    EXPECT_EQ(out[6], 3.0f);
    EXPECT_EQ(out[7], 4.0f);
    
  }



  TEST(m256,laplace){
    constexpr size_type n = 64;
    constexpr size_type nm1 = n-1;
    using simd_type = aligned_array<float,8,32>;
    vector<simd_type> u(64*64);
    vector<simd_type> un(64*64);
    for(size_type i = 0; i < n; ++i){
      for(size_type j = 0; j < n; ++j){
	m256 ui(0.0f);
	ui.store( u[i*n+j].data());
	ui.store( un[i*n+j].data());
      }
    }

    auto lap =  [](auto & vn, auto const& v, size_type i, size_type j ){
      m256 vij = 0.01f*(-4.0f*m256(v[i*n+j].data())
			+ m256(v[i*n+j-1].data())
			+ m256(v[i*n+j+1].data())
			+ m256(v[(i-1)*n+j].data())
			+ m256(v[(i+1)*n+j].data()));
      vij.store(vn[i*n+j].data(), stream_tag{});
      return 0;
    };
      
      

    for( size_type i = 1; i < nm1; i+= 4 ){
      for(size_type j = 1; j < nm1; j+= 4){
	pass(lap(un, u, i, j),
	     lap(un, u, i, j+1),	     
	     lap(un, u, i+1, j),
	     lap(un, u, i+1, j+1),	     
	     lap(un, u, i+2, j),
	     lap(un, u, i+2, j+1),	     
	     lap(un, u, i+3, j),
	     lap(un, u, i+3, j+1),	     
	     lap(un, u, i, j+2),
	     lap(un, u, i, j+3),	     
	     lap(un, u, i+1, j+2),
	     lap(un, u, i+1, j+3),	     
	     lap(un, u, i+2, j+2),
	     lap(un, u, i+2, j+3),	     
	     lap(un, u, i+3, j+2),
	     lap(un, u, i+3, j+3));
      }
    }
  }

} // end of namespace 
