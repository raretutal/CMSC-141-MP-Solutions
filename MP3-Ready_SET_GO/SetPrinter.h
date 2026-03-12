#ifndef SET_PRINTER_H
#define SET_PRINTER_H

#include <iostream>
#include <iomanip>
#include <type_traits>
#include "CustomSet.h"

// Forward Declaration for nrested sets
template <typename T>
void print_set(const CustomSet<T>& s);

// Helpers to print individual items
template <typename T>
void print_element(const T& item){
    if constexpr(std::is_same_v<T, double>){
        // force double to 2 decimal places
        std::cout << std::fixed << std::setprecision(2) << item;
    }else{
        std::cout << item;
    }
}

// Specialization for printing a CustomSet
template <typename T>
void print_element(const CustomSet<T>& item){
    print_set(item);
}

// Main print function

template <typename T>
void print_set(const CustomSet<T>& s){
    if (s.is_empty()){
        std::cout << "empty";
        return;
    }

    std::cout << "{";
    auto it = s.get_elements().begin(); // puts iterator at the start
    while(it != s.get_elements().end()){
        print_element(*it);
        it++;

        if(it != s.get_elements().end()){
            std::cout << ",";
        }
    }
    std::cout << "}";

}

#endif