#include <iostream>

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
template <typename T>
struct Length 
{
    static const int value = 1 + Length<typename T::Tail>::value;
} ;

template <>
struct Length  < IntList<> >
{
    static const int value = 0;
} ;

////*****************************//////
template <int H, typename Types>
struct IntCons ;

template <int H, int ... Types>
struct IntCons<H, IntList<Types...> > {
    using type = IntList<H, Types...>;
};

////*****************************//////

template <typename TL1, typename TL2>
struct Concat ;

template <int... TL1, int... TL2>
struct Concat< IntList<TL1...>, IntList<TL2...> > {
    using type = IntList<TL1..., TL2...>;
};

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


/*template <int H, int Val = 0>
struct Generate {
    using type = IntList<Val, typename Generate<H-1, Val+1 >::type>;    
};

template <int Val>
struct Generate<1, Val> {
    using type = IntList<Val>;
};*/
 
int main() {
    using primes = IntList<2,3,5,7,11,13>;
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;
    
    constexpr size_t len = Length<primes>::value; // 6
    
    using L1 = IntList<2,3,4>; 
    using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>
    //using L3 = IntCons<1, IntList<> >::type;
    using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>
    using L4 = Generate<4>::type;      // IntList<0,1,2,3,4>
    L3 x;
 
    L4 y ; 
    std::cout << x.Head ;
    std::cout << y.Head ;
    x = y
        
}