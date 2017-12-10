#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>



// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    
    typedef std::function< Result(Base* a, Base* b) > Func;
    typedef std::map<std::type_index, Func > SubMap;    
    std::map<std::type_index, SubMap > methods;
    
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid 
    // f - это функция или функциональный объект
    // принимающий два указателя на Base 
    // и возвращающий значение типа Result

    void addImpl( std::type_index t1, 
                  std::type_index t2, 
                  Func f )
    {
         methods[t1][t2] = f;
    }

    bool getImpl(Base * a, Base * b, Func& f) const
    {
        const auto it_a = methods.find( typeid(*a) );
        if (it_a != methods.end() ){
            const auto it_ab = it_a->second.find( typeid(*b) );
            if (it_ab != it_a->second.end() ){
                f = it_ab->second;
                return true;
            }
        }        
        return false;
    }
    bool getImplReverse(Base * a, Base * b, Func& f) const
    {
        if(!Commutative) return false;
        return getImpl(b, a, f);
    }
    
    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно 
        // проверить есть ли реализация для b и а 
        
        Func foo;        
        return getImpl(a, b, foo) || getImplReverse(a, b, foo);
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        Func f;        
        if (getImpl(a, b, f)) return f(a, b);
        if (getImplReverse(a, b, f)) return f(b, a);
            
        throw "not Impl";
        return f(a, b);
    }
};


// базовый класс фигуры (полиморфный)
struct Shape { virtual ~Shape(){} };

// прямоугольник
struct Rectangle : Shape { virtual ~Rectangle(){}  };

// треугольник
struct Triangle : Shape { virtual ~Triangle(){}  };

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b){return true;};

// функция для проверки пересечения прямоугольника и треугольника


bool is_intersect_r_t(Shape * a, Shape * b){return true;};


//std::cout << len1 <<std::endl;




int main() 
{
    // мультиметод для наследников Shape
    // возращающий bool и являющийся коммутативным 
    Multimethod2<Shape, bool, true> is_intersect;

    // добавляем реализацию мультиметода для двух прямоугольников
    std::function< bool(Shape*, Shape*) > f = is_intersect_r_r;
    
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), f);

    // добавляем реализацию мультиметода для прямоугольника и треугольника
    //ошибка в примере ...  is_intersect_r_r -> is_intersect_r_t
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // создаём две фигуры    
    Shape * s1 = new Triangle();
    Shape * s2 = new Rectangle();

    // проверяем, что реализация для s1 и s2 есть
    if (is_intersect.hasImpl(s1, s2))
    {
         // вызывается функция is_intersect_r_t(s2, s1)
         bool res = is_intersect.call(s1, s2);
         std::cout <<  res <<std::endl;
         // Замечание: is_intersect_r_t ожидает,
         // что первым аргументом будет прямоугольник
         // а вторым треугольник, а здесь аргументы
         // передаются в обратном порядке. 
         // ваша реализация должна самостоятельно 
         // об этом позаботиться 
    }
    
    
    
    /*std::function<std::basic_string<char>(Shape*, Shape*)>’ 
    to std::basic_string<char> (*)(Shape*, Shape*)’*/
}

