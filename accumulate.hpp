#pragma once

#include <iostream>
namespace itertools{

    template <typename CONTAINER, typename  FUNCTOR = std::plus<>> // Use of std library function plus by default (If there is no lambada expression supplied).
    class accumulate{
        CONTAINER& _container;
        FUNCTOR _function;
    public:
        explicit accumulate(CONTAINER& container, FUNCTOR func = std::plus<>())
                : _container(container), _function(func){}
        explicit accumulate(CONTAINER&& container, FUNCTOR func = std::plus<>())
                : _container(container), _function(func){}

        //Inner container class
        class iterator{
            typename CONTAINER::value_type container; // Must have value_type otherwise will not compile
            typename CONTAINER::iterator start; // Iterator begin
            typename CONTAINER::iterator finish; // Iterator end
            FUNCTOR func;
        public:
            explicit iterator(typename CONTAINER::iterator strt, typename CONTAINER::iterator end, FUNCTOR func)
                    : start(strt), finish(end), func(func){
                if(start != end)
                    container = *strt;
            };
            iterator& operator=(const iterator& other){
                if(this != &other) {
                    this->container = other.container;
                    this->start = other.start;
                    this->finish = other.finish;
                    this->func = other.func;
                }
                return *this;
            };
            //++i
            iterator& operator ++(){
                ++start;
                    container = func(container, *start);
                return *this;
            }
            //i++
            iterator operator ++(int){
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            bool operator ==(const iterator& other) {
                return (start == other.start);
            }
            bool operator !=(const iterator& other) {
                return (start != other.start);
            }

            auto operator *(){
                return container;
            }
        };


        iterator begin(){
            return iterator(_container.begin(), _container.end(), _function);
        }
        iterator end(){
            return iterator(_container.end(), _container.end(), _function);
        }

    };
}
