//
// ... Testing header files
//
#include <gtest/gtest.h>


//
// ... Short Vector header files
//
#include <short_vector/core.hpp>

namespace 
{
  using ShortVector::Private::function_tag;
  using ShortVector::Private::Short_vector;


  TEST( short_vector_auto, value_construction )
  {
    constexpr Short_vector<double,4,64> xs( 2.0 );

    static_assert(xs[0] == 2.0);
    static_assert(xs[1] == 2.0);
    static_assert(xs[2] == 2.0);
    static_assert(xs[3] == 2.0);
    
    EXPECT_EQ( xs[0], 2.0 );
    EXPECT_EQ( xs[1], 2.0 );
    EXPECT_EQ( xs[2], 2.0 );
    EXPECT_EQ( xs[3], 2.0 );

    EXPECT_EQ( xs.size(), 4 );

  } // end of test auto_short_vector.arithmetic

  TEST( short_vector_auto, multivalue_construction )
  {
    constexpr Short_vector<double,4,64> xs( 1.0, 2.0, 3.0, 4.0);

    static_assert(xs[0] == 1.0);
    static_assert(xs[1] == 2.0);
    static_assert(xs[2] == 3.0);
    static_assert(xs[3] == 4.0);
    
    EXPECT_EQ( xs[0], 1.0);
    EXPECT_EQ( xs[1], 2.0);
    EXPECT_EQ( xs[2], 3.0);
    EXPECT_EQ( xs[3], 4.0);
    
    EXPECT_EQ(xs.size(), 4);
    
  } // end of test short_vector_auto.multivalue_construction

  TEST( short_vector_auto, function_construction )
  {
    constexpr Short_vector<double,4,64> xs([](auto x){ return double(x); },
					   function_tag{});

    static_assert(xs[0] == 0.0);
    static_assert(xs[1] == 1.0);
    static_assert(xs[2] == 2.0);
    static_assert(xs[3] == 3.0);
    
    EXPECT_EQ( xs[0], 0.0);
    EXPECT_EQ( xs[1], 1.0);
    EXPECT_EQ( xs[2], 2.0);
    EXPECT_EQ( xs[3], 3.0);
    
    EXPECT_EQ(xs.size(), 4);
    
  } // end of test short_vector_auto.function_construction


  TEST( short_vector_auto, copy_construction )
  {
    constexpr Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    
    Short_vector<double,4,64> ys{ xs };
    
    
    EXPECT_EQ(ys[0], 0.0);
    EXPECT_EQ(ys[1], 1.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 3.0);
    
    EXPECT_EQ(ys.size(), 4);
    
  } // end of test short_vector_auto.function_construction

  TEST( short_vector_auto, copy_assignment )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});

    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 2.0);
    EXPECT_EQ(xs[3], 3.0);
    
    Short_vector<double,4,64> ys([](auto x){ return double(x*x); }, function_tag{});

    EXPECT_EQ(ys[0], 0.0);
    EXPECT_EQ(ys[1], 1.0);
    EXPECT_EQ(ys[2], 4.0);
    EXPECT_EQ(ys[3], 9.0);

    ys = xs;
    
    EXPECT_EQ(ys[0], 0.0);
    EXPECT_EQ(ys[1], 1.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 3.0);

    
  } // end of test short_vector_auto.copy_assignment

  TEST( short_vector_auto, addition_inplace )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y*y); }, function_tag{});

    xs += ys;
    
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 2.0);
    EXPECT_EQ(xs[2], 6.0);
    EXPECT_EQ(xs[3], 12.0);
    
  } // end of test short_vector_auto.addition_inplace

  TEST( short_vector_auto, addition )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y*y); }, function_tag{});

    auto zs = xs+ys;
    
    EXPECT_EQ(zs[0], 0.0);
    EXPECT_EQ(zs[1], 2.0);
    EXPECT_EQ(zs[2], 6.0);
    EXPECT_EQ(zs[3], 12.0);
    
  } // end of test short_vector_auto.addition


  TEST( short_vector_auto, subtraction_inplace )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y*y); }, function_tag{});
    xs -= ys;
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 0.0);
    EXPECT_EQ(xs[2],-2.0);
    EXPECT_EQ(xs[3],-6.0);
    
  } // end of test short_vector_auto.subtraction_inplace


  TEST( short_vector_auto, subtraction )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y*y); }, function_tag{});
    Short_vector<double,4,64> zs = xs - ys;
    
    EXPECT_EQ(zs[0], 0.0);
    EXPECT_EQ(zs[1], 0.0);
    EXPECT_EQ(zs[2],-2.0);
    EXPECT_EQ(zs[3],-6.0);

  } // end of test short_vector_auto.subtraction


  TEST( short_vector_auto, multiplication_inplace )
  {
    
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y*y); }, function_tag{});

    xs *= ys;

    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 8.0);
    EXPECT_EQ(xs[3], 27.0);
    
  } //  short_vector_auto, multiplication_inplace


  TEST( short_vector_auto, multiplication )
  {
    
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y*y); }, function_tag{});

    auto zs = xs * ys;

    EXPECT_EQ(zs[0], 0.0);
    EXPECT_EQ(zs[1], 1.0);
    EXPECT_EQ(zs[2], 8.0);
    EXPECT_EQ(zs[3], 27.0);
    
  } //  short_vector_auto, multiplication



  TEST( short_vector_auto, division_inplace )
  {
    
    Short_vector<double,4,64> xs([](auto x){ return double((x+1)*(x+1)); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y+1); }, function_tag{});

    xs /= ys;

    EXPECT_EQ(xs[0], 1.0);
    EXPECT_EQ(xs[1], 2.0);
    EXPECT_EQ(xs[2], 3.0);
    EXPECT_EQ(xs[3], 4.0);
    
  } //  short_vector_auto.division_inplace

  
  TEST( short_vector_auto, division )
  {    
    Short_vector<double,4,64> xs([](auto x){ return double((x+1)*(x+1)); }, function_tag{});
    Short_vector<double,4,64> ys([](auto y){ return double(y+1); }, function_tag{});

    auto zs = xs / ys;

    EXPECT_EQ(zs[0], 1.0);
    EXPECT_EQ(zs[1], 2.0);
    EXPECT_EQ(zs[2], 3.0);
    EXPECT_EQ(zs[3], 4.0);
    
  } // end of test short_vector_auto.division

  TEST( short_vector_auto, equal )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 2.0);
    EXPECT_EQ(xs[3], 3.0);

    Short_vector<double,4,64> ys([](auto y){ return double(4-y); }, function_tag{});

    EXPECT_EQ(ys[0], 4.0);
    EXPECT_EQ(ys[1], 3.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 1.0);

    auto zs = xs == ys;

    EXPECT_EQ(zs[0], 0.0);
    EXPECT_EQ(zs[1], 0.0);
    EXPECT_EQ(zs[2], 1.0);
    EXPECT_EQ(zs[3], 0.0);
    
  } // end of test short_vector.equal


  TEST( short_vector_auto, not_equal )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 2.0);
    EXPECT_EQ(xs[3], 3.0);

    Short_vector<double,4,64> ys([](auto y){ return double(4-y); }, function_tag{});

    EXPECT_EQ(ys[0], 4.0);
    EXPECT_EQ(ys[1], 3.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 1.0);

    auto zs = xs != ys;

    EXPECT_EQ(zs[0], 1.0);
    EXPECT_EQ(zs[1], 1.0);
    EXPECT_EQ(zs[2], 0.0);
    EXPECT_EQ(zs[3], 1.0);
    
  } // end of test short_vector.not_equal

  TEST( short_vector_auto, less_than )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 2.0);
    EXPECT_EQ(xs[3], 3.0);

    Short_vector<double,4,64> ys([](auto y){ return double(4-y); }, function_tag{});

    EXPECT_EQ(ys[0], 4.0);
    EXPECT_EQ(ys[1], 3.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 1.0);

    auto zs = xs < ys;

    EXPECT_EQ(zs[0], 1.0);
    EXPECT_EQ(zs[1], 1.0);
    EXPECT_EQ(zs[2], 0.0);
    EXPECT_EQ(zs[3], 0.0);
  } // end of test short_vector_auto.less_than


  TEST( short_vector_auto, less_than_or_equal )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 2.0);
    EXPECT_EQ(xs[3], 3.0);

    Short_vector<double,4,64> ys([](auto y){ return double(4-y); }, function_tag{});

    EXPECT_EQ(ys[0], 4.0);
    EXPECT_EQ(ys[1], 3.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 1.0);

    auto zs = xs <= ys;

    EXPECT_EQ(zs[0], 1.0);
    EXPECT_EQ(zs[1], 1.0);
    EXPECT_EQ(zs[2], 1.0);
    EXPECT_EQ(zs[3], 0.0);
  } // end of test short_vector_auto.less_than_or_equal



  TEST( short_vector_auto, greater_than )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 2.0);
    EXPECT_EQ(xs[3], 3.0);

    Short_vector<double,4,64> ys([](auto y){ return double(4-y); }, function_tag{});

    EXPECT_EQ(ys[0], 4.0);
    EXPECT_EQ(ys[1], 3.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 1.0);

    auto zs = xs > ys;

    EXPECT_EQ(zs[0], 0.0);
    EXPECT_EQ(zs[1], 0.0);
    EXPECT_EQ(zs[2], 0.0);
    EXPECT_EQ(zs[3], 1.0);
  } // end of test short_vector_auto.greater_than


  TEST( short_vector_auto, greater_than_or_equal )
  {
    Short_vector<double,4,64> xs([](auto x){ return double(x); }, function_tag{});
    
    EXPECT_EQ(xs[0], 0.0);
    EXPECT_EQ(xs[1], 1.0);
    EXPECT_EQ(xs[2], 2.0);
    EXPECT_EQ(xs[3], 3.0);

    Short_vector<double,4,64> ys([](auto y){ return double(4-y); }, function_tag{});

    EXPECT_EQ(ys[0], 4.0);
    EXPECT_EQ(ys[1], 3.0);
    EXPECT_EQ(ys[2], 2.0);
    EXPECT_EQ(ys[3], 1.0);

    auto zs = xs >= ys;

    EXPECT_EQ(zs[0], 0.0);
    EXPECT_EQ(zs[1], 0.0);
    EXPECT_EQ(zs[2], 1.0);
    EXPECT_EQ(zs[3], 1.0);
    
  } // end of test short_vector_auto.greater_than_or_equal

  TEST( short_vector_auto, fma )
  {
    Short_vector<double,4,64> as([](auto x){ return double(x+1); }, function_tag{});
    Short_vector<double,4,64> bs([](auto x){ return double(x+2); }, function_tag{});
    Short_vector<double,4,64> cs([](auto x){ return double(x+3); }, function_tag{});

    auto ds = fma(as,bs,cs);

    EXPECT_EQ(ds[0], 5.0);
    EXPECT_EQ(ds[1], 10.0);
    EXPECT_EQ(ds[2], 17.0);
    EXPECT_EQ(ds[3], 26.0);
    
            
    
  } // end of test short_vector_auto.fma

  
  
} // end of namespace


