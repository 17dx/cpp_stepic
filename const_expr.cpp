#include <cstdlib>

struct Point
{
    constexpr Point(double x, double y) 
        : x(x), y(y) 
    {}

    double x = 0;
    double y = 0;
};


// сложение
constexpr Point operator+ (Point a, Point b)
{
   return Point(a.x + b.x, a.y + b.y);
}

// вычитание
constexpr Point  operator-(Point a, Point b)
{
   return Point(a.x - b.x, a.y - b.y);
}

// скалярное произведение
constexpr double  operator*(Point a, Point b)
{
   return a.x * b.x + a.y * b.y;
}

int main(){
    constexpr size_t size = static_cast<size_t>(Point(2,4) * Point(4,3));
    int m[size]; // массив из 20 элементов    
}
