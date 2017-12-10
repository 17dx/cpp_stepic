/*
Напишите шаблонную функцию count_permutations, которая принимает некоторую последовательность и вычисляет количество перестановок этой последовательности, в которых нет подряд идущих одинаковых элементов. 
*/

#include <array>
#include <iostream>
#include <string>

#include <algorithm>
#include <vector>

size_t fact(size_t n)
{
    size_t result = 1;
    while (n > 0) result *=  n--; 
    return result; 
}

/*template<class Iterator>
size_t count_uniq_permutations(Iterator p, Iterator q)
{
    size_t count_repeated = 1;
    size_t count_all = 1;
    size_t permutations_repeated = 1;
    size_t permutations_all = 1;
    auto back = p++;
    
    for (;p != q;  back = p++){
        ++count_all;
        permutations_all *= count_all;
        //нужно чтобы был отсортирован
        if (*(*back) == *(*p)) {            
             ++count_repeated; 
             permutations_repeated *= count_repeated;            
        } 
        else{            
            count_repeated = 1;
        }
    }
    return permutations_all / permutations_repeated;
}*/

/*template<class Iterator, class Compare>
size_t custom_next_permutation(Iterator a, Iterator q, Compare comp){
    size_t count_see = 0;
    for (;a != q;  ++a){
        ++count_see;
        Iterator b = a;
        ++b;
        if ( q ==  b) return count_see;
        
        Iterator last = q;
        --last;
        if ( last ==  b) return count_see;
        for (; b != last;  ++b){
            if(comp(a, b)){
                 std::swap(*a, *b);                 
                 return count_see;
            }
        }
        std::swap(*a, *b);
        std::reverse(++a, q);        
    }
    return count_see;
}*/
template<class Iterator, class Compare>
size_t  custom_next_permutation(Iterator first,
		       Iterator last, Compare comp)
{
      size_t count_see = 0;
      //пустой массив
      if (first == last) return count_see;
      Iterator i = first;
      ++i;
      //массив из одного элемента
      if (i == last) return count_see;
      i = last;
      --i;

      for(;;){
          Iterator ii = i; //последний элемент
          --i; //предпоследний элемент
          if (comp(i, ii) ){
              Iterator j = last;
              while (!comp(i, --j)) {}
              std::iter_swap(i, j);
              std::reverse(ii, last);
              return count_see+1;//return true;
          } 
          //++count_see;
          
          //подходящий элемент не найден
          if (i == first){
              std::reverse(first, last);
              return count_see+1;
          }
      }
    return count_see;    
}

template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    
    typedef typename  std::vector < Iterator  >::iterator  It;
    size_t count_elems  = std::distance(p, q) ;
    std::vector < Iterator  > v(count_elems);
    for (auto& x:v) x = p++; 
    
    struct {
        bool operator()(const It& a, const It& b) const
        {   
            return *(*a) < *(*b);
        }   
    } customLess; 
    
    auto customEq = [](const Iterator& a, const Iterator& b){ 
                         return (*a) == (*b); 
                      };
    
    It vp = v.begin();
    It vq = v.end();
        
    size_t sum = 0;
    size_t count = 0;
    size_t count_combine = fact(count_elems);
    //size_t balance 
    do 
    {
         if (std::adjacent_find(vp, vq, customEq) == vq)
             ++sum;
        count += custom_next_permutation(vp, vq, customLess);
        for (auto& x:v) std::cout << *x << "";
        std::cout << std::endl;
    } while( count < count_combine );
    return sum;
}

/*template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    using VectorType = std::vector<typename std::iterator_traits<Iterator>::value_type>;
    VectorType v(p, q);
    typename VectorType::iterator vp = v.begin(), vq = v.end();
    std::sort(vp, vq);
    
    size_t sum = 0;
    do 
    {
        if (std::adjacent_find(vp, vq) == vq)
            ++sum;
    } while(std::next_permutation(vp, vq));
    return sum;
}*/

int main(){
    
     std::array <int, 3> a1 = {1,2,3};
    size_t c1 = count_permutations(a1.begin(), a1.end()); // 6
      
      
    std::array <int, 5> a2 = {1,2,3,4,4};
    size_t c2 = count_permutations(a2.begin(), a2.end()); // 36
    

    std::cout << c1 << " ";
    std::cout << c2 << " "; 
    
    /*std::vector <int> a = {2,1,2,2};
    
    std::cout << std::next_permutation(a.begin(), a.end()) << " : ";    
    for (int x:a) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << std::next_permutation(a.begin(), a.end()) << " : ";    
    for (int x:a) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << std::next_permutation(a.begin(), a.end()) << " : ";    
    for (int x:a) std::cout << x << " ";
    std::cout << std::endl;

    std::cout << std::next_permutation(a.begin(), a.end()) << " : ";    
    for (int x:a) std::cout << x << " ";
    std::cout << std::endl;

    std::cout << std::next_permutation(a.begin(), a.end()) << " : ";    
    for (int x:a) std::cout << x << " ";
    std::cout << std::endl;   */ 
   
}
