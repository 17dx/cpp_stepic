/*
Напишите шаблонную функцию count_permutations, которая принимает некоторую последовательность и вычисляет количество перестановок этой последовательности, в которых нет подряд идущих одинаковых элементов. 
*/

#include <array>
#include <iostream>
#include <string>

#include <algorithm>
template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    if (p == q) return 0;
    
     struct {
        bool operator()(Iterator a, Iterator b) const
        {   
            return *a < *b;
        }   
    } customLess; 
    size_t count  = std::distance(p, q) ;
    std::vector < Iterator  > v( count);
    
    for (size_t i=0 ;i < count;  ++i, ++p){
        v[i] = p;
    }
    
    std::sort(v.begin(), v.end(), customLess);  
    
    
    size_t count_repeated = 1;
    size_t count_all = 1;
    size_t permutations_swap_eq = 1;
    size_t permutations_all = 1;
    
    
    auto pv = v.begin();
    auto qv = v.end();
    //auto back = p++;
    auto back = pv++;
    
    for (;pv != qv;  back = pv++){
        ++count_all;
        permutations_all *= count_all;
        if (*(*back) == *(*pv)) {            
             ++count_repeated; 
             permutations_swap_eq *= count_repeated;
             permutations_all *= (1 + count - count_repeated) ;             
        } 
        else{            
            count_repeated = 1;
        }
    }
        
     //std::cout << " pall" <<permutations_all << std::endl;
     //std::cout << " prp" <<permutations_repeted << std::endl;
    
    return  permutations_all / permutations_swap_eq;
}

 void gen(std::string s, 
         int back, 
         std::array <int, 7>& a, 
         std::array <bool, 7>& free){
     for (int i = 0 ; i < 7; i++){
         if (free[i] == true && a[i] != back){             
             free[i] = false;
             gen(s+std::to_string(a[i]), a[i], a, free);
             free[i] = true;
         }         
     }
     for (int i = 0 ; i < 7; i++){
        if (free[i] ==  true) return; 
     }
     std::cout << s << std::endl;
         
} 


int gen2(std::string s,
         std::vector <int>& a, 
         std::vector <bool>& free){
     int result = 0;       
     for (int i = 0 ; i < a.size(); i++){
         bool skipt =false;
         for (int j = i+1 ; j < a.size(); j++){
             if (a[j] == a[i] && free[j] == false ) skipt =true;
         }
         if (skipt) continue; 
         if (free[i] == true ){             
             free[i] = false;
             result += gen2(s+std::to_string(a[i]), a, free);
             free[i] = true;
         }         
     }
     for (int i = 0 ; i < free.size(); i++){
        if (free[i] ==  true) return result; 
     }
     std::cout << s << std::endl;  
     return result+1; 
}

std::string combin(std::vector <int>& a){
    int count_all = 1;
    int count_repeated = 1;
    int permutations_all = 1;    
    int permutations_eq = 1;
    
    
    std::string s_permutations_eq ;
    
    auto it = a.begin();
    auto back = it++;
        
    for (;it != a.end();  back = it++){
        ++count_all;
        permutations_all *= count_all;
        if ( (*back) ==  (*it)) {            
             ++count_repeated; 
             permutations_eq *= count_repeated;                        
        } 
        else{                        
            if (count_repeated >1){
                s_permutations_eq += std::to_string(count_repeated) + "!";
            }
            count_repeated = 1;
        }
    }  
    
    if (count_repeated >1){
         s_permutations_eq += std::to_string(count_repeated) + "!";
    }
    
    std::string s_permutations_all = std::to_string(count_all) + "!";
    return  s_permutations_all + std::string("/(")
                   + s_permutations_eq +  std::string(") = ") 
                   + std::to_string( permutations_all/permutations_eq);
}
         
int gen3(std::string s,
         int back,
         std::vector <int>& a, 
         std::vector <bool>& free){
     int result = 0;       
     for (int i = 0 ; i < a.size(); i++){
         bool skipt =false;
         for (int j = i+1 ; j < a.size(); j++){
             if (a[j] == a[i] && free[j] == false ) skipt =true;
         }
         if (skipt) continue; 
         if (free[i] == true && a[i] != back){             
             free[i] = false;
             result += gen3(s+std::to_string(a[i]), a[i], a, free);
             free[i] = true;
         }         
     }
     for (int i = 0 ; i < free.size(); i++){
        if (free[i] ==  true) return result; 
     }
     //std::cout << s << std::endl;  
     return result+1; 
}

int main(){
    {
        std::vector <int> a = {1,1,2,2};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,2 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;
        
    }
    
    {
        std::vector <int> a = {1,1,2,3};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,3 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;
        
    }    
    
    {
        std::vector <int> a = {1,1,2,2,3};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,2,3 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;
        
    } 

    {
        std::vector <int> a = {1,1,2,2,3,3};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,2,3,3 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;        
    } 
    
    {
        std::vector <int> a = {1,1,2,2,3,4};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,2,3,4 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    }    

    {
        std::vector <int> a = {1,1,2,2,3,4,5};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,2,3,4,5 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    }    
    
    {
        std::vector <int> a = {1,1,1,2,2,3};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,1,2,2,3 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    } 
    
    {
        std::vector <int> a = {1,1,1,2,2,3,3};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,1,2,2,3,3 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    } 
    
    {
        std::vector <int> a = {1,1,1,2,2,3,4};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,1,2,2,3,4 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    }     
    
    {
        std::vector <int> a = {1,1,1,2,2,3,3,3};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,1,2,2,3,3,3 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    } 
    
    {
        std::vector <int> a = {1,1,2,3,4};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,3,4 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    } 
    
    {
        std::vector <int> a = {1,1,2,3,4,5};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,3,4,5 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    } 
    
    {
        std::vector <int> a = {1,1,2,3,4,5,6};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,3,4,5,6 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    }   
    
    {
        std::vector <int> a = {1,1,2,2,3,3,4,4};
        std::vector <bool> free (a.size(),true);
        
        std::cout << "1,1,2,2,3,3,4,4 = " << combin(a) << "*? = " 
                                  << gen3("",-1, a, free)  <<  std::endl;  
    } 

     
    
  
    
     
    
    /*std::array <int, 3> a1 = {1,2,3};
    size_t c1 = count_permutations(a1.begin(), a1.end()); // 6
        
    std::array <int, 5> a2 = {1,2,3,4,4};
    size_t c2 = count_permutations(a2.begin(), a2.end()); // 36
    
    std::array <int, 7> a3 = {1,1,1, 2,2,2, 3};
    size_t c3 = count_permutations(a3.begin(), a3.end()); // 36
    
     std::array <bool, 7> free = {true, true, true, true,  true, true, true};
   //  gen("", -1, a3, free);
    std::cout << c1 << " ";
    std::cout << c2 << " ";
    std::cout << c3 << " ";*/
   
}
