#include <typeinfo>
#include <iostream>

//без таблицы виртуальных нельзя
struct  A{ virtual ~A(){}};
struct  B: A{ };

struct  C: A{ };

struct  D: B, C {};


template<class T>
bool isSameObject(T const * p, T const * q)
{
    /*std::cout<< typeid(*p).name() << std::endl;
    std::cout<< typeid(*q).name() << std::endl;
    //для получения настоящего типа нужно разименовать
    return typeid(*p)  == typeid(*q) ;*/
    
    /*Оператор приведение dynamic_cast<void *> для некоторого объекта
    возвращает самый маленький адрес из всех возможных адресов для
    этого объекта, т.е. адрес его первого байта.*/
    return dynamic_cast<void const *> (p) == dynamic_cast<void const *> (q);
     
}


int main(){

    D d;
    B* b = &d;
    C* c = &d;
    A a ;
   
    std::cout<< isSameObject<A>(&a, c) << std::endl;
    std::cout<< isSameObject<A>(b, c) << std::endl;

}
