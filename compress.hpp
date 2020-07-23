#pragma once

namespace itertools{
    template <typename CONTAINER1, typename CONTAINER2> class compress{
        private:
        CONTAINER1& con1; // First contaimner 
        CONTAINER2& con2; // Boolean container
        
        public:
            compress(CONTAINER1& cn1, CONTAINER2& cn2): con1(cn1), con2(cn2){}
            compress(CONTAINER1&& cn1, CONTAINER2&& cn2): con1(cn1), con2(cn2){}
            compress(CONTAINER1&& cn1, CONTAINER2& cn2): con1(cn1), con2(cn2){}
            compress(CONTAINER1& cn1, CONTAINER2&& cn2): con1(cn1), con2(cn2){}

        class iterator{
            typename CONTAINER1::iterator itrStart; // Container iterator
            typename CONTAINER1::iterator itrEnd; // Container end
            typename CONTAINER2::iterator itr2; // Boolean container iterator
            public:
                explicit iterator(typename CONTAINER1::iterator strt1,typename CONTAINER1::iterator fnsh1,typename CONTAINER2::iterator strt2): 
                itrStart(strt1), itrEnd(fnsh1), itr2(strt2){
                    while(itrStart != itrEnd && !(*itr2)){ // Skip bad values
                        ++itrStart;
                        ++itr2;
                    }
                }
                iterator& operator=(const iterator& other){
                    if(this != &other){
                        this->itrStart = other.itrStart;
                        this->itrEnd = other.itrEnd;
                        this->itr2 = other.itr2;
                    }
                    return *this;
                }
                
                //++i
                iterator& operator++(){
                   do{
                    itrStart++;
                    itr2++;
                   } while(itrStart != itrEnd && !(*itr2)); // Skip bad values
                   return *this; // Finally return good value
                }
                //i++
                iterator& operator++(int){
                    iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                bool operator==(const iterator& other){
                    return itrStart == other.itrStart;
                }

                bool operator!=(const iterator& other){
                    return itrStart != other.itrStart;
                }

                auto operator *(){
                    return *itrStart;
                }
        };
        iterator begin(){
            return iterator(con1.begin(),con1.end(),con2.begin());
        }
        iterator end(){
            return iterator(con1.end(),con1.end(),con2.end());
        }
    };
}