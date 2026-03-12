#ifndef CUSTOM_SET_H
#define CUSTOM_SET_H


#include <set>

template<typename T>
class CustomSet{

private:
    std::set<T> elements;

public:
    // Getters
    const std::set<T>& get_elements() const {
        return elements;
    }

    bool is_empty() const{
        return elements.empty();
    }

    // Basic Operationrs (1 - insert & 2 - remove)
    void insert(const T& item){
        elements.insert(item);
    }
    void remove(const T& item){
        elements.erase(item);
    }

    // Subsets (3): checking if every item in this set exists isn the other one :)
    bool is_subset(const CustomSet<T>& other) const {

        for(const T& item : elements){
            if(other.get_elements().find(item) == other.get_elements().end() ){return false;}
        }
        return true;
    }

    // Union (4) : add everything from both sets into new set
    CustomSet<T> get_union(const CustomSet<T>& other) const {
        CustomSet<T> result;

        for(const T& item : elements) {result.insert(item);}

        for(const T& item: other.get_elements()) {result.insert(item);}

        return result;
    }

    // Intersection (5): Keep items present only in both
    CustomSet<T> get_intersection(const CustomSet<T>& other) const {
        CustomSet<T> result;
        
        for(const T& item: elements){
            if(other.get_elements().find(item) != other.get_elements().end()) {result.insert(item);}
        }
        return result;
    }
    
    // Difference (6): Items in this set - items in other set
    CustomSet<T> get_difference(const CustomSet<T>& other) const{
        CustomSet<T> result;
        
        for(const T& item: elements){
            if(other.get_elements().find(item) == other.get_elements().end()) {result.insert(item);}
        }
        return result;
    }

    // Power Set (7): 
    CustomSet<CustomSet<T>> get_powerset() const {

        CustomSet<CustomSet<T>> pset;
        CustomSet<T> empty_set;
        pset.insert(empty_set);

        for(const T& item: elements){
            CustomSet<CustomSet<T>> current_subsets = pset;
            for(CustomSet<T> subset : current_subsets.get_elements()){
                subset.insert(item);
                pset.insert(subset);
            }
        }
        return pset;
    }

    // Overloader shizz : overload the < operator so that CustomSets can 
    // be stored in side other CustomSets

    bool operator<(const CustomSet<T>& other) const{
        return elements < other.elements;
    }
};

#endif