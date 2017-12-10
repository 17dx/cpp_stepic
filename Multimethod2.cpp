#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>



// Base - ������� ����� ��������
// Result - ��� ������������� �������� ������������
// Commutative - ����, ������� ����������, ���
// ����������� ������������� (�.�. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    
    typedef std::function< Result(Base* a, Base* b) > Func;
    typedef std::map<std::type_index, Func > SubMap;    
    std::map<std::type_index, SubMap > methods;
    
    // ������������� ���������� ������������
    // ��� ����� t1 � t2 �������� ����� typeid 
    // f - ��� ������� ��� �������������� ������
    // ����������� ��� ��������� �� Base 
    // � ������������ �������� ���� Result

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
    
    // ���������, ���� �� ���������� ������������
    // ��� ����� �������� a � b
    bool hasImpl(Base * a, Base * b) const
    {
        // ���������� true, ���� ���������� ����
        // ���� �������� �������������, �� ����� 
        // ��������� ���� �� ���������� ��� b � � 
        
        Func foo;        
        return getImpl(a, b, foo) || getImplReverse(a, b, foo);
    }

    // ��������� ����������� � ��������
    // �� ���������� a � b
    Result call(Base * a, Base * b) const
    {
        // ���������� ��������� ���������� ����������
        // ������������ � a � b
        Func f;        
        if (getImpl(a, b, f)) return f(a, b);
        if (getImplReverse(a, b, f)) return f(b, a);
            
        throw "not Impl";
        return f(a, b);
    }
};


// ������� ����� ������ (�����������)
struct Shape { virtual ~Shape(){} };

// �������������
struct Rectangle : Shape { virtual ~Rectangle(){}  };

// �����������
struct Triangle : Shape { virtual ~Triangle(){}  };

// ������� ��� �������� ����������� ���� ���������������
bool is_intersect_r_r(Shape * a, Shape * b){return true;};

// ������� ��� �������� ����������� �������������� � ������������


bool is_intersect_r_t(Shape * a, Shape * b){return true;};


//std::cout << len1 <<std::endl;




int main() 
{
    // ����������� ��� ����������� Shape
    // ����������� bool � ���������� ������������� 
    Multimethod2<Shape, bool, true> is_intersect;

    // ��������� ���������� ������������ ��� ���� ���������������
    std::function< bool(Shape*, Shape*) > f = is_intersect_r_r;
    
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), f);

    // ��������� ���������� ������������ ��� �������������� � ������������
    //������ � ������� ...  is_intersect_r_r -> is_intersect_r_t
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // ������ ��� ������    
    Shape * s1 = new Triangle();
    Shape * s2 = new Rectangle();

    // ���������, ��� ���������� ��� s1 � s2 ����
    if (is_intersect.hasImpl(s1, s2))
    {
         // ���������� ������� is_intersect_r_t(s2, s1)
         bool res = is_intersect.call(s1, s2);
         std::cout <<  res <<std::endl;
         // ���������: is_intersect_r_t �������,
         // ��� ������ ���������� ����� �������������
         // � ������ �����������, � ����� ���������
         // ���������� � �������� �������. 
         // ���� ���������� ������ �������������� 
         // �� ���� ������������ 
    }
    
    
    
    /*std::function<std::basic_string<char>(Shape*, Shape*)>� 
    to std::basic_string<char> (*)(Shape*, Shape*)�*/
}

