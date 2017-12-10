#include <typeinfo>
#include <iostream>

//без таблицы виртуальных нельзя
struct  Expression{ virtual ~Expression(){}};

struct Expression2: Expression {};

struct Expression3: Expression {};

bool check_equals(Expression const *left, Expression const *right)
{
    std::cout<< typeid(*left).name() << std::endl;
    std::cout<< typeid(*right).name() << std::endl;
    //для получения настоящего типа нужно разименовать
    return typeid(*left)  == typeid(*right) ;
}


int main(){

    Expression2 e2;
    Expression3 e3;
    
    std::cout<< check_equals(&e3, &e2) << std::endl;
    std::cout<< check_equals(&e2, &e2) << std::endl;
}
