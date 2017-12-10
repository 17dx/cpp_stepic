#include <iostream>
#include <tuple>


////*****************************//////
// бинарная метафункция
template<int a, int b>
struct Plus
{
    static int const value = a + b;    
};

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
template <int H, typename Types>
struct IntCons ;

template <int H, int ... Types>
struct IntCons<H, IntList<Types...> > {
    using type = IntList<H, Types...>;
};



////*****************************//////

template <typename TL1, typename TL2, template <int , int > class F>
struct Zip {
    using type = typename IntCons< F<TL1::Head, TL2::Head>::value, 
                            typename Zip<typename TL1::Tail, typename TL2::Tail, F>::type >::type;
};

template <template <int , int > class F>
struct Zip<IntList<>, IntList<>, F> {
    using type = IntList<>;
};
 
int main() {
    // два списка одной длины
    using L1 = IntList<1,2,3,4,5>;
    using L2 = IntList<1,3,7,7,2>;

    // результат применения — список с поэлементными суммами
    using L3 = Zip<L1, L2, Plus>::type;  // IntList<2, 5, 10, 11, 7>
    L1 z;
    L3 y;
    y = z;
}