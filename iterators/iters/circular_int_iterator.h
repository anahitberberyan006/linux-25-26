#pragma once
#include <cstddef>
#include <functional>



class circular_int_iterator_builder
{
private:
    int* data;
    int current ;
    std::size_t size;
public:
    circular_int_iterator_builder(int* value1,std::size_t size1): data(value1) ,size(size1),current(0){}
    int& operator*( )const{
        return data[current];
    }
    circular_int_iterator_builder& operator++()
    {

        current = (++current) % size ;
        return  *this;
    }
};