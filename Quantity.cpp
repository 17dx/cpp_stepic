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


/////*********************************///////
// бинарная метафункция
template<int a, int b>
struct Plus
{
    static int const value = a + b;    
};

template<int a, int b>
struct Minus
{
    static int const value = a - b;    
};

template <typename TL1 >
struct Quantity{
    double _value;
    Quantity():_value(0){}
    explicit  Quantity(double _value):_value(_value){}
    double value() const{ return _value;} 
    
    template < typename TL2 >
    auto operator / (Quantity<TL2>  that) -> 
         Quantity< typename Zip<  TL1, TL2, Minus>::type>
    {
      return  Quantity< typename Zip<  TL1, TL2, Minus>::type> (_value / that.value() );
    }
    
    Quantity operator / (double a){
      return  Quantity (_value / a);
    }
    
    template < typename TL2 >
    auto operator * (Quantity<TL2>  that)  -> 
       Quantity< typename Zip<  TL1, TL2, Plus>::type>
    {
      return  Quantity< typename Zip<  TL1, TL2, Plus>::type> (_value * that.value() );
    }
    
    Quantity operator * (double a){
      return  Quantity (_value * a);
    }
    

    Quantity operator + (Quantity that){
      return  Quantity (_value + that.value());
    }
    Quantity operator - (Quantity that){
      return  Quantity (_value - that.value());
    }
};
 
template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;
    
int main() {


    using NumberQ   = Quantity<Dimension<>>;          // число без размерности
    using LengthQ   = Quantity<Dimension<1>>;          // метры
    using MassQ     = Quantity<Dimension<0, 1>>;       // килограммы
    using TimeQ     = Quantity<Dimension<0, 0, 1>>;    // секунды
    using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
    using AccelQ    = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
    using ForceQ    = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах

    LengthQ   l{30000};      // 10 км
    TimeQ     t{10 * 60};    // 10 минут
    TimeQ     t2{10 * 60};    // 10 минут
    TimeQ     t3 = t + t2;
    // вычисление скорости
    VelocityQ v = l / t;     // результат типа VelocityQ, 50 м/с

    AccelQ    a{9.8};        // ускорение свободного падения
    MassQ     m{80};         // 80 кг
    // сила притяжения, которая действует на тело массой 80 кг
    ForceQ    f = m * a;     // результат типа ForceQ
    f = f/5.0;     // результат типа ForceQ
}