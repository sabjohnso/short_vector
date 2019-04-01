#ifndef CORE_HPP_INCLUDED_117669730265165748
#define CORE_HPP_INCLUDED_117669730265165748 1

//
// ... Short Vector header files
//
#include <short_vector/import.hpp>

namespace ShortVector::Private
{
  template< typename T>
  struct Type
  {
    using type = T;
  }; // end of struct Type

  template< size_type N, size_type ... Indices >
  struct Generate_indices : Generate_indices<N-1,N-1,Indices ...>
  {
    static_assert(N > 0);
  };// end of struct Generate_indices

  template<size_type ... Indices>
  struct Generate_indices<0,Indices ...> : Type<integer_sequence<size_type,Indices ...>>
  {}; // end of struct Generate_indices

  
  
  /** A tag indicating automatic vectorization */
  struct auto_tag{};

  /** a tag indicating a function */
  struct function_tag{};

  template< typename T, size_type N, size_type Align, typename Inst = auto_tag >
  class alignas(Align) Short_vector
  {
  public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    
    static constexpr size_type extent = N;
    static constexpr size_type alignment = Align;

    static constexpr value_type zero = 0;
    static constexpr value_type one = 1;


    constexpr
    Short_vector(value_type input) : values{}{
      for(auto& x : values){
	x = input;
      } 
    }

    template< typename T1, typename T2, typename ... Ts >
    constexpr
    Short_vector(T1&& x1, T2&& x2, Ts&& ... xs) : values{{forward<T1>(x1), forward<T2>(x2), forward<Ts>(xs) ... }}
    {}

    template<typename F>
    constexpr
      Short_vector(F&& f, function_tag ) : values{} {
      for(size_t i = 0; i < extent; ++i){
	values[ i ] = f(i);
      }	
    }

    Short_vector&
    operator =( value_type input ){
      for( auto& x : values ){
	x = input;
      }
      return *this;
    }

    Short_vector&
    operator +=( value_type input ){
      for( auto& x : values ){
	x += input;
      }
      return *this;
    }

    Short_vector&
    operator +=( Short_vector const&  input ){
      for(size_type i = 0; i < extent; ++ i){
	values[i] += input.values[i];
      }
      return *this;
    }

    Short_vector&
    operator -=( value_type input ){
      for( auto& x : values ){
	x -= input;
      }
      return *this;
    }

    Short_vector&
    operator -=( Short_vector const&  input ){
      for(size_type i = 0; i < extent; ++ i){
	values[i] -= input.values[i];
      }
      return *this;
    }

    Short_vector&
    operator *=( value_type input ){
      for( auto& x : values ){
	x *= input;
      }
      return *this;
    }

    Short_vector&
    operator *=( Short_vector const&  input ){
      for(size_type i = 0; i < extent; ++ i){
	values[i] *= input.values[i];
      }
      return *this;
    }

    Short_vector&
    operator /=( value_type input ){
      for( auto& x : values ){
	x /= input;
      }
      return *this;
    }

    Short_vector&
    operator /=( Short_vector const&  input ){
      for(size_type i = 0; i < extent; ++ i){
	values[i] /= input.values[i];
      }
      return *this;
    }
    
    constexpr const_reference
    operator []( size_type i ) const& {
      return values[i];
    }

    reference
    operator []( size_type i ) & {
      return values[i];
    }
    
    static constexpr size_type
    size() { return extent; }

  private:

    
    template< typename Indices >
    struct Core;


    template<size_type ... Indices>
    struct Core<integer_sequence<size_type,Indices...>>
    {
      static constexpr Short_vector
      add( Short_vector const& xs, Short_vector const& ys ){
	return Short_vector{xs[Indices]+ys[Indices] ... };
      }

      static constexpr Short_vector
      add( Short_vector const& xs, value_type y ){
	return Short_vector{xs[Indices]+y ... };
      }

      static constexpr Short_vector
      add( value_type x, Short_vector const& ys ){
	return Short_vector{x+ys[Indices] ... };
      }


      static constexpr Short_vector
      subtract( Short_vector const& xs, Short_vector const& ys ){
	return Short_vector{xs[Indices]-ys[Indices] ... };
      }

      static constexpr Short_vector
      subtract( Short_vector const& xs, value_type y ){
	return Short_vector{xs[Indices]-y ... };
      }

      static constexpr Short_vector
      subtract( value_type x, Short_vector const& ys ){
	return Short_vector{x-ys[Indices] ... };
      }


      static constexpr Short_vector
      multiply( Short_vector const& xs, Short_vector const& ys ){
	return Short_vector{xs[Indices]*ys[Indices] ... };
      }

      static constexpr Short_vector
      multiply( Short_vector const& xs, value_type y ){
	return Short_vector{xs[Indices]*y ... };
      }

      static constexpr Short_vector
      multiply( value_type x, Short_vector const& ys ){
	return Short_vector{x*ys[Indices] ... };
      }


      static constexpr Short_vector
      divide( Short_vector const& xs, Short_vector const& ys ){
	return Short_vector{xs[Indices]/ys[Indices] ... };
      }

      static constexpr Short_vector
      divide( Short_vector const& xs, value_type y ){
	return Short_vector{xs[Indices]/y ... };
      }

      static constexpr Short_vector
      divide( value_type x, Short_vector const& ys ){
	return Short_vector{x/ys[Indices] ... };
      }


      static constexpr Short_vector
      eq( Short_vector const& x, Short_vector const& y ){
	return Short_vector{ x[Indices] == y[Indices] ? one : zero ...};
      }

      static constexpr Short_vector
      eq( Short_vector const& x, value_type y )
      {
	return Short_vector{ x[Indices] == y ? one : zero ...};
      }

      static constexpr Short_vector
      eq( value_type x, Short_vector const& y ){
	return Short_vector{ x == y[Indices] ? one : zero ...};
      }

      

      static constexpr Short_vector
      neq( Short_vector const& x, Short_vector const& y ){
	return Short_vector{ x[Indices] != y[Indices] ? one : zero ...};
      }

      static constexpr Short_vector
      neq( Short_vector const& x, value_type y )
      {
	return Short_vector{ x[Indices] != y ? one : zero ...};
      }

      static constexpr Short_vector
      neq( value_type x, Short_vector const& y ){
	return Short_vector{ x != y[Indices] ? one : zero ...};
      }


      static constexpr Short_vector
      lt( Short_vector const& x, Short_vector const& y ){
	return Short_vector{ x[Indices] < y[Indices] ? one : zero ...};
      }

      static constexpr Short_vector
      lt( Short_vector const& x, value_type y )
      {
	return Short_vector{ x[Indices] < y ? one : zero ...};
      }

      static constexpr Short_vector
      lt( value_type x, Short_vector const& y ){
	return Short_vector{ x < y[Indices] ? one : zero ...};
      }

      static constexpr Short_vector
      le( Short_vector const& x, Short_vector const& y ){
	return Short_vector{ x[Indices] <= y[Indices] ? one : zero ...};
      }

      static constexpr Short_vector
      le( Short_vector const& x, value_type y )
      {
	return Short_vector{ x[Indices] <= y ? one : zero ...};
      }

      static constexpr Short_vector
      le( value_type x, Short_vector const& y ){
	return Short_vector{ x <= y[Indices] ? one : zero ...};
      }


      static constexpr Short_vector
      gt( Short_vector const& x, Short_vector const& y ){
	return Short_vector{ x[Indices] > y[Indices] ? one : zero ...};
      }

      static constexpr Short_vector
      gt( Short_vector const& x, value_type y )
      {
	return Short_vector{ x[Indices] > y ? one : zero ...};
      }

      static constexpr Short_vector
      gt( value_type x, Short_vector const& y ){
	return Short_vector{ x > y[Indices] ? one : zero ...};
      }


      static constexpr Short_vector
      ge( Short_vector const& x, Short_vector const& y ){
	return Short_vector{ x[Indices] >= y[Indices] ? one : zero ...};
      }

      static constexpr Short_vector
      ge( Short_vector const& x, value_type y )
      {
	return Short_vector{ x[Indices] >= y ? one : zero ...};
      }

      static constexpr Short_vector
      ge( value_type x, Short_vector const& y ){
	return Short_vector{ x >= y[Indices] ? one : zero ...};
      }


      static constexpr Short_vector
      fma( Short_vector const& a, Short_vector const& b, Short_vector const& c){
	using std::fma;
	return Short_vector{ fma( a[Indices], b[Indices], c[Indices]) ... };
      }

      static constexpr Short_vector
      fms( Short_vector const& a, Short_vector const& b, Short_vector const& c){
	using std::fma;
	return Short_vector{ fma(a[Indices],b[Indices],-c[Indices]) ... };
      }

      static constexpr Short_vector
      fnma( Short_vector const& a, Short_vector const& b, Short_vector const& c){
	using std::fma;
	return Short_vector{ fma(-a[Indices],b[Indices],c[Indices]) ... };
      }

      static constexpr Short_vector
      fnms( Short_vector const& a, Short_vector const& b, Short_vector const& c){
	using std::fma;
	return Short_vector{ fma(-a[Indices],b[Indices],-c[Indices]) ... };
      }
 
    }; // end of class Core

    using core_type = Core<typename Generate_indices<extent>::type>;


    friend constexpr Short_vector
    operator +( Short_vector const& xs, Short_vector const& ys ){
      return core_type::add( xs, ys );
    }

    friend constexpr Short_vector
    operator +( Short_vector const& xs, value_type y ){
      return core_type::add( xs, y );
    }

    friend constexpr Short_vector
    operator +( value_type x, Short_vector const& ys ){
      return core_type::add(x, ys);
    }


    friend constexpr Short_vector
    operator -( Short_vector const& xs, Short_vector const& ys ){
      return core_type::subtract( xs, ys );
    }

    friend constexpr Short_vector
    operator -( Short_vector const& xs, value_type y ){
      return core_type::subtract( xs, y );
    }

    friend constexpr Short_vector
    operator -( value_type x, Short_vector const& ys ){
      return core_type::subtract(x, ys);
    }


    friend constexpr Short_vector
    operator *( Short_vector const& xs, Short_vector const& ys ){
      return core_type::multiply( xs, ys );
    }

    friend constexpr Short_vector
    operator *( Short_vector const& xs, value_type y ){
      return core_type::multiply( xs, y );
    }

    friend constexpr Short_vector
    operator *( value_type x, Short_vector const& ys ){
      return core_type::multiply(x, ys);
    }


    friend constexpr Short_vector
    operator /( Short_vector const& xs, Short_vector const& ys ){
      return core_type::divide( xs, ys );
    }

    friend constexpr Short_vector
    operator /( Short_vector const& xs, value_type y ){
      return core_type::divide( xs, y );
    }

    friend constexpr Short_vector
    operator /( value_type x, Short_vector const& ys ){
      return core_type::divide(x, ys);
    }


    friend constexpr Short_vector
    operator <( Short_vector const& xs, Short_vector const& ys ){
      return core_type::lt( xs, ys );
    }

    friend constexpr Short_vector
    operator <( Short_vector const& xs, value_type y ){
      return core_type::lt( xs, y );
    }

    friend constexpr Short_vector
    operator <( value_type x, Short_vector const& ys ){
      return core_type::lt(x, ys);
    }

    friend constexpr Short_vector
    operator <=( Short_vector const& xs, Short_vector const& ys ){
      return core_type::le( xs, ys );
    }

    friend constexpr Short_vector
    operator <=( Short_vector const& xs, value_type y ){
      return core_type::le( xs, y );
    }

    friend constexpr Short_vector
    operator <=( value_type x, Short_vector const& ys ){
      return core_type::le(x, ys);
    }


    friend constexpr Short_vector
    operator >( Short_vector const& xs, Short_vector const& ys ){
      return core_type::gt( xs, ys );
    }

    friend constexpr Short_vector
    operator >( Short_vector const& xs, value_type y ){
      return core_type::gt( xs, y );
    }

    friend constexpr Short_vector
    operator >( value_type x, Short_vector const& ys ){
      return core_type::gt(x, ys);
    }

    friend constexpr Short_vector
    operator >=( Short_vector const& xs, Short_vector const& ys ){
      return core_type::ge( xs, ys );
    }

    friend constexpr Short_vector
    operator >=( Short_vector const& xs, value_type y ){
      return core_type::ge( xs, y );
    }

    friend constexpr Short_vector
    operator >=( value_type x, Short_vector const& ys ){
      return core_type::ge(x, ys);
    }

    friend constexpr Short_vector
    operator ==( Short_vector const& xs, Short_vector const& ys ){
      return core_type::eq( xs, ys );
    }

    friend constexpr Short_vector
    operator ==( Short_vector const& xs, value_type y ){
      return core_type::eq( xs, y );
    }

    friend constexpr Short_vector
    operator ==( value_type x, Short_vector const& ys ){
      return core_type::eq(x, ys);
    }
    
    friend constexpr Short_vector
    operator !=( Short_vector const& xs, Short_vector const& ys ){
      return core_type::neq( xs, ys );
    }

    friend constexpr Short_vector
    operator !=( Short_vector const& xs, value_type y ){
      return core_type::neq( xs, y );
    }

    friend constexpr Short_vector
    operator !=( value_type x, Short_vector const& ys ){
      return core_type::neq(x, ys);
    }


    friend constexpr Short_vector
    fma( Short_vector const& as, Short_vector const& bs, Short_vector const& cs){
      return core_type::fma(as, bs, cs);
    }

    friend constexpr Short_vector
    fms( Short_vector const& as, Short_vector const& bs, Short_vector const& cs){
      return core_type::fms(as, bs, cs);
    }

    friend constexpr Short_vector
    fnma( Short_vector const& as, Short_vector const& bs, Short_vector const& cs){
      return core_type::fnma(as, bs, cs);
    }

    friend constexpr Short_vector
    fnms( Short_vector const& as, Short_vector const& bs, Short_vector const& cs){
      return core_type::fnms(as, bs, cs);
    }
    
  private:

    array<value_type,extent> values;

  }; // end of class Short_vector


  
  
 

  /** A short vector as a view 
   *
   * This class describes an object that can refer to a contiguous
   * sequence of values and allow their treatment as a short vector
   */
  template< typename T, size_type N, size_type Align, typename Inst = auto_tag >
  class Short_view
  {
  public:
    using value_type = T;
    using pointer = value_type*;

    using short_vector = Short_vector<T,N,Align,Inst>;

    static constexpr size_type extent = N;
    static constexpr size_type alignment = Align;

    Short_view() = delete;

    Short_view( Short_view const& input )
      : ptr( input.ptr )
    {}

    Short_view( pointer input ) : ptr(input){
      assert(input);
    }



    Short_view&
    operator =( Short_view const& input ){
      for( size_type i = 0; i < extent; ++i ){
	ptr[i] = input.ptr[i];	    
      }
      return *this;
    }

    Short_view&
    operator =( short_vector const& input ){
      for( size_type i = 0; i < extent; ++i ){
	ptr[i] = input[i];
      }
    }


    Short_view&
    operator =( value_type input ){
      for( size_type i = 0; i < extent; ++i ){
	ptr[i] = input;
      }
    }

    Short_view&
    operator +=( short_vector const& input ){
      for( size_type i = 0; i < extent; ++i ){
	ptr[i] += input[i];
      }
    }


    Short_view&
    operator -=( short_vector const& input ){
      for( size_type i = 0; i < extent; ++i ){
	ptr[i] -= input[i];
      }
    }


    Short_view&
    operator *=( short_vector const& input ){
      for( size_type i = 0; i < extent; ++i ){
	ptr[i] *= input[i];
      }
    }

    Short_view&
    operator /=( short_vector const& input ){
      for( size_type i = 0; i < extent; ++i ){
	ptr[i] /= input[i];
      }
    }


    operator short_vector() const& {
      short_vector result;
      for(size_type i = 0; i < extent; ++i){
	result[i] = ptr[i];
      }
      return result;
    }

    friend short_vector
    operator +( Short_view const& a, Short_view const& b ){
      return short_vector(a)+short_vector(b);
    }

    friend short_vector
    operator +( Short_view const& a, short_vector const& b ){
      return short_vector(a)+b;
    }

    friend short_vector
    operator +( short_vector const& a, short_vector const& b ){
      return a+short_vector(b);
    }

    friend short_vector
    operator +( Short_view const& a, value_type b ){
      return short_vector(a)+b;
    }

    friend short_vector
    operator +( value_type a, Short_view const& b ){
      return a+short_vector(b);
    }


    

    friend short_vector
    operator -( Short_view const& a, Short_view const& b ){
      return short_vector(a)-short_vector(b);
    }

    friend short_vector
    operator -( Short_view const& a, short_vector const& b ){
      return short_vector(a)-b;
    }

    friend short_vector
    operator -( short_vector const& a, short_vector const& b ){
      return a-short_vector(b);
    }

    friend short_vector
    operator -( Short_view const& a, value_type b ){
      return short_vector(a)-b;
    }

    friend short_vector
    operator -( value_type a, Short_view const& b ){
      return a-short_vector(b);
    }



    friend short_vector
    operator *( Short_view const& a, Short_view const& b ){
      return short_vector(a)*short_vector(b);
    }

    friend short_vector
    operator *( Short_view const& a, short_vector const& b ){
      return short_vector(a)*b;
    }

    friend short_vector
    operator *( short_vector const& a, short_vector const& b ){
      return a*short_vector(b);
    }

    friend short_vector
    operator *( Short_view const& a, value_type b ){
      return short_vector(a)*b;
    }

    friend short_vector
    operator *( value_type a, Short_view const& b ){
      return a*short_vector(b);
    }

    


    friend short_vector
    operator /( Short_view const& a, Short_view const& b ){
      return short_vector(a)/short_vector(b);
    }

    friend short_vector
    operator /( Short_view const& a, short_vector const& b ){
      return short_vector(a)/b;
    }

    friend short_vector
    operator /( short_vector const& a, short_vector const& b ){
      return a/short_vector(b);
    }

    friend short_vector
    operator /( Short_view const& a, value_type b ){
      return short_vector(a)/b;
    }

    friend short_vector
    operator /( value_type a, Short_view const& b ){
      return a/short_vector(b);
    }

  private:
    pointer ptr;
  };

  
  
} // end of namespace ShortVector::Private

#endif // ! defined CORE_HPP_INCLUDED_117669730265165748
