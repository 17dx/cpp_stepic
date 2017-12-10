#include <string>
#include <iostream>


struct Unit  
{
    explicit Unit(size_t id) 
        : id_(id) 
    {}

    size_t id() const { return id_; }

private:
    size_t id_;
};


// базовый класс для животных
struct Animal: virtual Unit
{
    // name хранит название животного
    // "bear" для медведя
    // "pig" для свиньи  
    Animal(std::string const & name, size_t id):
         Unit(id), name_(name){}
    

    std::string const& name() const { return name_; }
private:
    std::string name_;
};

// класс для человека
struct Man: virtual Unit 
{
    explicit Man(size_t id): Unit(id){}
    // ...
};

// класс для медведя
struct Bear:  Animal
{
    explicit Bear(size_t id): Unit(id), Animal("bear", id){}
    // ...
};

// класс для свиньи
struct Pig:  Animal
{
    explicit Pig(size_t id): Unit(id), Animal("pig", id){}
    // ...
};

// класс для челмедведосвина
struct ManBearPig: Man, Bear, Pig 
{
    ManBearPig(size_t id): Unit(id),  Man(id), Bear(id), Pig(id) {} 
};

int main(void) {
   Bear bear(0);
   Pig pig(0);
   ManBearPig manBearPig(0);
   std::cout << bear.name() <<  std::endl;
   std::cout << pig.name() <<  std::endl;
   std::cout << manBearPig.name() <<  std::endl;
}