#include <iostream>
#include <list>
 
#include <future> 


template <class It, class UnarFunc, class BinarFun>
auto map(It p, It q, UnarFunc f1, BinarFun f2) -> decltype(f1(*p))
{
    auto res = f1(*p);
    while(++p != q)
        res = f2(res, f1(*p));
    return res;
} 

// реализация функции mapreduce
template <class It, class UnarFunc, class BinarFun>
auto  map_reduce(It p, It q, UnarFunc f1, BinarFun f2,  size_t threads) -> decltype(f1(*p))
{
    using Res =  decltype(f1(*p));
    
    size_t count = std::distance(p,q);
    size_t range_size = count / threads;
    size_t remain_size = count % threads;
    
    std::future<Res> fut[threads];
    for(size_t i=0; i <threads; ++i ) {
        It end = p;
        std::advance(end, range_size);
        if (remain_size > 0) {
            ++end;
            --remain_size;
        }
        fut[i] = std::async(std::launch::async,
                            map<It, UnarFunc, BinarFun>, p, end, f1, f2);

        p = end;
    }
    
    Res res = fut[0].get();
    for(size_t i=1; i <threads; ++i ) {
       res = f2(res, fut[i].get());
    }
    return res; 

}

        /*fut[i] = std::async(std::launch::async,[p, end, f1, f2](){
                auto res = f1(*p);
                while(++p != end)
                    res = f2(res, f1(*p));
                return res;
        });*/
 
int main() {

 
   std::list<int> l = {1,2,3,4,5,6,7,8,9,10};
   // параллельное суммирование в 3 потока
   auto sum = map_reduce(l.begin(), l.end(), 
           [](int i){return i;}, 
           std::plus<int>(), 3);

   // проверка наличия чётных чисел в четыре потока
   auto has_even = map_reduce(l.begin(), l.end(), 
                 [](int i){return i % 2 == 0;}, 
                  std::logical_or<bool>(), 4);
   std::cout << sum << std::endl; 
   std::cout << has_even << std::endl;               
                  
}