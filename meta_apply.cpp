#include <iostream>
#include <tuple>


////*****************************//////
template <int ... Types>
struct IntList ;

template <int H, int ... T>
struct IntList<H, T...> {
    static const int Head = H;
    using Tail = IntList<T...>;
};

template <>
struct IntList<> {};


////*****************************//////

template <typename TL1, typename TL2>
struct Concat ;

template <int... TL1, int... TL2>
struct Concat< IntList<TL1...>, IntList<TL2...> > {
    using type = IntList<TL1..., TL2...>;
};

////*****************************//////

template <int H>
struct Generate {
    using type = typename 
                 Concat< typename Generate<H-1>::type ,
                         IntList<H-1>
                        >::type;    
};

template <>
struct Generate<1> {
    using type =  IntList<0> ;
};

template <>
struct Generate<0> {
    using type = IntList<>;
};

////*****************************//////

template<class F, class Tuple, int... Arg>
auto apply_( F& f, const Tuple& tuple, IntList<Arg...> )  ->
            decltype(f( std::get<Arg>( tuple )... ))
{
    return f( std::get<Arg>( tuple )... );
}

template<class F, typename ...Arg>
auto apply ( F f,  std::tuple<Arg...> t)  ->
         decltype(apply_( f, t, typename Generate< sizeof...(Arg) >::type() ))
{    
    return apply_( f, t, typename Generate< sizeof...(Arg) >::type() );
}


 
int main() {
    auto f = [](int x, double y, double z) { return x + y + z; };
    auto t = std::make_tuple(30, 5, 1.6);  // std::tuple<int, double, double>
    //std::get<0,1>(t)
    auto res = apply(f, t);                // res = 36.6
        
}