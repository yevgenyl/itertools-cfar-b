#pragma once

namespace itertools{
    class range{
        private:
        int start,finish;
        public:
            range(int a, int b): start(a), finish(b){}
        class iterator{
            private:
                int currentNumber; // The current number in range.
            public:
                explicit iterator(int currentNum) : currentNumber(currentNum){ // iterator constructor

                }

                iterator& operator =(const iterator& other){ // operator =.
                    if(this != &other){
                        this->currentNumber = other.currentNumber;
                    }
                    return *this;
                }

                bool operator==(const iterator& other){ // Check if two iterators are equal by value
                    return currentNumber == other.currentNumber;
                }

                bool operator !=(const iterator& other){ // Check if two operators are not equal by value
                    return currentNumber != other.currentNumber;
                }

                iterator& operator++(){ // Increment range by 1 ++i
                    ++currentNumber;
                    return *this;
                }

                iterator& operator++(int){ // Increment range by 1 i++
                    iterator tmp = *this; // First save value of current iterator before incrementing it.
                    ++currentNumber;
                    return *this; // Return the value of last iterator before increment.
                }

                int operator*(){ // Return value of int.
                    return currentNumber;
                }
        };

        iterator begin(){
            return iterator(start);
        }
        iterator end(){
            return iterator(finish);
        }

        typedef int	value_type;
    };
}
