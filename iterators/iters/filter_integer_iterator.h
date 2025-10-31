#pragma once
#include <cstddef>
#include <functional>
class filter_integer_iterator
{
private:
    int* data;
    int current ;
    std::size_t size;
    std::function<bool(int)> predicate;
public:
    filter_integer_iterator(int* value1,std::size_t size1,std::function<bool(int)> pred): data(value1) ,size(size1),predicate(pred),current(0)
    {
        while(current < size && !predicate(data[current])) {
            current++;
        }
    }
    filter_integer_iterator(T* value1,std::size_t size1,std::function<bool(int)> pred,std::size_t cur): data(value1) ,size(size1),predicate(pred) ,current(cur)
    {
        while(current < size && !predicate(data[current])) {
            current++;
        }
    }
    T& operator*( )const{
        return data[current];
    }
    bool operator!=(const filter_integer_iterator& other) const {
        return current != other.current;
    }
    filter_integer_iterator& operator++()
    {
        current++;
        while (current < size && !predicate(data[current])){
            current++;
        }
        return  *this;
    }
};
template <typename T>
class filter_integer_iterator_builder {
private:
    T* data;
    std::size_t size;
    std::function<bool(int)> predicate;
public:

    filter_integer_iterator_builder(T* data, std::size_t size, std::function<bool(int)> pred)
            : data(data), size(size), predicate(pred) {}




    filter_integer_iterator<T> begin(){
        return filter_integer_iterator<T>(data,size,predicate,0);
    }
    filter_integer_iterator<T> end(){
        return filter_integer_iterator<T>(data,size,predicate,size);
    }


};