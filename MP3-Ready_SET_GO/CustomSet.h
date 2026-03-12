#ifndef CUSTOM_SET_H
#define CUSTOM_SET_H

#include <vector>
#include <algorithm>

template<typename T>
class CustomSet{

private:
    std::vector<T> elements;

public:
    // Getters
    const std::vector<T>& get_elements() const {
        return elements;
    }

    bool is_empty() const{
        return elements.empty();
    }

    // Basic Operations (1 - insert & 2 - remove)
    void insert(const T& item){
        if(std::find(elements.begin(), elements.end(), item) == elements.end()){
            elements.push_back(item);
        }
    }

    void remove(const T& item){
        auto it = std::find(elements.begin(), elements.end(), item);
        if (it != elements.end()) {
            elements.erase(it);
        }
    }

    // Subsets (3)
    bool is_subset(const CustomSet<T>& other) const {
        for(const T& item : elements){
            if(std::find(other.elements.begin(), other.elements.end(), item) == other.elements.end()){
                return false;
            }
        }
        return true;
    }

    // Union (4)
    CustomSet<T> get_union(const CustomSet<T>& other) const {
        CustomSet<T> result;
        for(const T& item : elements) {result.insert(item);}
        for(const T& item: other.get_elements()) {result.insert(item);}
        return result;
    }

    // Intersection (5)
    CustomSet<T> get_intersection(const CustomSet<T>& other) const {
        CustomSet<T> result;
        for(const T& item: elements){
            if(std::find(other.elements.begin(), other.elements.end(), item) != other.elements.end()) {
                result.insert(item);
            }
        }
        return result;
    }
    
    // Difference (6)
    CustomSet<T> get_difference(const CustomSet<T>& other) const{
        CustomSet<T> result;
        for(const T& item: elements){
            if(std::find(other.elements.begin(), other.elements.end(), item) == other.elements.end()) {
                result.insert(item);
            }
        }
        return result;
    }

    // Power Set (7): Rewritten to group subsets by size (0 to N) to match the required format
    CustomSet<CustomSet<T>> get_powerset() const {
        CustomSet<CustomSet<T>> pset;
        int n = elements.size();

        for (int size = 0; size <= n; ++size) {
            if (size == 0) {
                CustomSet<T> empty_set;
                pset.insert(empty_set);
                continue;
            }
            
            std::vector<int> indices(size);
            for (int i = 0; i < size; ++i) indices[i] = i;
            
            while (true) {
                CustomSet<T> subset;
                for (int i = 0; i < size; ++i) {
                    subset.insert(elements[indices[i]]);
                }
                pset.insert(subset);
                
                int pos = size - 1;
                while (pos >= 0 && indices[pos] == n - size + pos) {
                    pos--;
                }
                if (pos < 0) break; 
                
                indices[pos]++;
                for (int i = pos + 1; i < size; ++i) {
                    indices[i] = indices[i - 1] + 1;
                }
            }
        }
        return pset;
    }

    // Overloader shizz
    bool operator==(const CustomSet<T>& other) const {
        return elements == other.elements; 
    }

    bool operator<(const CustomSet<T>& other) const{
        return elements < other.elements;
    }
};

#endif