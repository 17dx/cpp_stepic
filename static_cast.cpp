 struct Number {};

struct BigInt : Number
{
     BigInt(int x);
};

struct String
{
    explicit String(char const * s);
};

int main(){
     int a =  (3.5);
    double b =  (7);
    BigInt c = (100500);
    String d = static_cast<String>("Stepik");
    Number * e = new Number();// static_cast<Number *>(&d); //не работает
    BigInt * f = static_cast<BigInt *>(e); 
    void * g = (f);   
    BigInt * h = static_cast<BigInt *>(g); 
    
}
