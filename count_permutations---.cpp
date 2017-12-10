/*
Напишите шаблонную функцию count_permutations, которая принимает некоторую последовательность и вычисляет количество перестановок этой последовательности, в которых нет подряд идущих одинаковых элементов. 
*/

#include <array>
#include <iostream>


#include <algorithm>
template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    if (p == q) return 0;
    
    std::sort(p, q);  
    
    Iterator back = p++;
    size_t count_unique = 1;
    size_t permutation_unique = 1;
    
    for (;p != q;  back = p++){
        if (*back != *q) {            
           ++count_unique;
           permutation_unique *=count_unique;           
        } 
    }
    
    Iterator back = p++;
    for (;p != q;  back = p++){
        if (*back != *q) {            
           ++count_unique;
           permutation_unique *=count_unique;           
        } 
    }
    
    
    
    return  permutation_uniq;
}



int main(){
    std::array <int, 3> a1 = {1,2,3};
    size_t c1 = count_permutations(a1.begin(), a1.end()); // 6
        
    std::array <int, 5> a2 = {1,2,3,4,4};
    size_t c2 = count_permutations(a2.begin(), a2.end()); // 36
    
    std::cout << c1 << " ";
    std::cout << c2 << " ";
   
}
