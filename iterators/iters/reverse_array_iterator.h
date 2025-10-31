#pragma once
#include <cstddef>
#include <functional>
template <typename T>
class reverse_array_iterator
{
private:
    T* data;
    int current ;
    std::size_t size;
public:

    reverse_array_iterator(T* value1,std::size_t size1): data(value1) ,size(size1),current((size1 - 1)){}
    T& operator*( )const{
        return data[current];
    }
    bool operator!=(const reverse_array_iterator& other) const {
        return current != other.current;
    }
    reverse_array_iterator& operator++()
    {
        if(current > 0){
            current--;
        }
        return  *this;
    }
};
template <typename T>
class reverse_array_iterator_builder {
private:
    T* data;
    std::size_t size;
public:

    reverse_array_iterator_builder(T* data, std::size_t size)
            : data(data), size(size){}

    reverse_array_iterator<T> begin(){
        return reverse_array_iterator<T>(data,size);
    }
    reverse_array_iterator<T> end(){
        return reverse_array_iterator<T>(data,0);
    }


};