#pragma once

namespace itertools{

        template <typename FUNCTOR, typename CONTAINER> // Use of std library function plus by default (If there is no lambada expression supplied).
    class filterfalse{
        CONTAINER& _CONTAINER;
        FUNCTOR _function;
    public:
        filterfalse(FUNCTOR func, CONTAINER& container)
                : _CONTAINER(container), _function(func){}
        filterfalse(FUNCTOR func, CONTAINER&& container)
                : _CONTAINER(container), _function(func){}

        //Inner CONTAINER class
        class iterator{
            typename CONTAINER::iterator current; // Iterator begin
            typename CONTAINER::iterator finish; // Iterator end
            FUNCTOR func;
        public:
            explicit iterator(typename CONTAINER::iterator strt, typename CONTAINER::iterator end, FUNCTOR func)
                    : current(strt), finish(end), func(func){
                while(current != finish && func(*current)) //Jump over bad values
                    ++current;
            };
            iterator& operator=(const iterator& other){
                if(this != &other) {
                    this->current = other.current;
                    this->finish = other.finish;
                    this->func = other.func;
                }
                return *this;
            };
            //++i
            iterator& operator ++(){
                do{
                    ++current; //Jump over bad values
                } while (current != finish && func(*current));
                return *this;
            }
            //i++
            iterator operator ++(int){
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            bool operator ==(const iterator& other) {
                return (current == other.current);
            }
            bool operator !=(const iterator& other) {
                return (current != other.current);
            }

            auto operator *(){
                return *current;
            }
        };


        iterator begin(){
            return iterator(_CONTAINER.begin(), _CONTAINER.end(), _function);
        }
        iterator end(){
            return iterator(_CONTAINER.end(), _CONTAINER.end(), _function);
        }

    };
}