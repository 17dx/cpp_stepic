#include <iostream>
#include <vector>
#include <list>
#include <iterator>

template<class T>
class VectorList
{
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q)  // определена снаружи
    {
        if (p != q)
            data_.push_back(VectT(p,q));
    } 


    bool empty() const { return size() == 0; } 

    // определите метод size
    size_t size() const 
    {
        size_t sum = 0;
        for(const VectT& x: data_ ){
            sum += x.size();
        }
        return sum;
    }

    // определите const_iterator
    //typedef typename VectT::const_iterator const_iterator;

    struct const_iterator: 
      std::iterator<std::bidirectional_iterator_tag,
                  typename VectT::value_type const>{               
      typename VectT::const_iterator curr_elem;
      typename ListT::const_iterator elems;  
      const ListT* data; 
      const_iterator (ListT const* data) :data(data){};
      const_iterator (const_iterator const &) = default;
      const_iterator (const_iterator &&) = default;        
      const_iterator & operator=(const_iterator const & rhs) {
            data = rhs.data; 
            curr_elem = rhs.curr_elem;
            elems = rhs.elems;
            return *this;
      };
      const_iterator & operator=(const_iterator &&)     = default;
      
      const_iterator base(){
          /*const_iterator it(*this);
          --(it);*/
          return *this;           
      };
    
      const_iterator& begin(){
          elems = data->cbegin();
          curr_elem = elems->cbegin();
          return *this; 
      } ;
      const_iterator& end() {
          if ( data->size() == 0) return begin();
          elems = --data->cend();
          curr_elem = elems->cend();
          return *this; 
      }; 
      
      //префиксный инкремент
      const_iterator& operator++ (){
         // if (elems == data->cend()) throw "out of range"; 
          ++curr_elem;
          if (curr_elem == elems->cend()){
              ++elems;
              if (elems == data->cend()) return *this; 
              curr_elem = elems->cbegin(); 
          }
          return *this;
      }
      
      const_iterator& operator-- (){          
          if (curr_elem != elems->cbegin()) {
              --curr_elem;
              return *this;
          }
          
          if (elems != data->cbegin()) {
              --elems;    
              curr_elem = --elems->cend(); 
              return *this;
          } else if (elems == data->cbegin()){
              //для reverse, чтобы указывать на rend
              --curr_elem;
              return *this;              
          }
          
          throw "out of range";          
          return *this;
      }
      
      //постфиксный инкремент
      const_iterator operator++ (int){
          const_iterator old(*this);
          ++(*this);
          return old;
      }
      
      const_iterator operator-- (int){
          const_iterator old(*this);
          --(*this);
          return old;
      }
      
      typename VectT::value_type const&  operator* () const{
          return *curr_elem;
      }  
      
      
      typename VectT::value_type const * operator->() const {
          return &(*curr_elem);
      }
 
      bool operator != (const const_iterator& that) const{
          return curr_elem != that.curr_elem;
      }   

      bool operator == (const const_iterator& that) const{
          return curr_elem == that.curr_elem;
      } 
    };

    // определите методы begin / end
    const_iterator begin() const {
        const_iterator ci(&data_);
        return ci.begin() ; 
    }
    const_iterator end()   const { 
        const_iterator ci(&data_);
        return ci.end() ;
    }

    // определите const_reverse_iterator
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    

    // определите методы begin / end
    const_reverse_iterator rbegin() const {
        const_iterator ci(&data_);
        return const_reverse_iterator(ci.end()) ; 
    }
    const_reverse_iterator rend()   const { 
        const_iterator ci(&data_);
        return const_reverse_iterator(ci.begin()) ;
    }

private:
    ListT data_;
};


    
int main() 
{
    typedef VectorList<std::string> VL;
    //std::vector<int> v{1,2,3};
    //VectorList<int> vectorList;

    std::vector<std::string > v_empty;
    std::vector<std::string > v{"a","b","c"};
    VectorList<std::string > vectorList;
    
    std::cout <<   vectorList.size() <<std::endl;
    std::cout <<   vectorList.empty() <<std::endl;
     
    
    static_assert(std::is_same<
    typename std::iterator_traits<VL::const_iterator>::value_type,
    std::string const>::value, "fffff iterator value_type");
    
    vectorList.append(v_empty.begin(), v_empty.end());
    
    std::cout <<   vectorList.size() <<std::endl;
    std::cout <<  std::distance (vectorList.begin(), vectorList.end() ) <<std::endl;
    
    //vectorList.append(v.begin(), v.end());
    //vectorList.append(v.begin(), v.end());
    std::cout <<   vectorList.size() <<std::endl;
    
    vectorList.begin()->c_str();
    
    auto a = vectorList.begin();
    auto ra = vectorList.rbegin();
    
        
    ra = VL::const_reverse_iterator(a); 
    ++ra;
    
    
    std::string  const * ps = &*vectorList.begin();
  
    
    for (auto it = vectorList.begin();
          it != vectorList.end(); ++it){
        std::cout <<  *it <<std::endl;
    }
    
    std::cout <<std::endl;
    std::cout <<std::endl;
    
    for (auto it = vectorList.rbegin();
          it != vectorList.rend(); ++it){
        std::cout <<  *it <<std::endl;
    }
    
   
}

