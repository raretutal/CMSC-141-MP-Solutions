#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include "CustomSet.h"
#include "SetPrinter.h"

using namespace std;

// Custom String parser
// This tells C++ how to read a string like "{1,2,3}" and turn it into a CustomSet object
template <typename T>
istream& operator>>(istream& is, CustomSet<T>& s) {
    string token;
    if (is >> token) {
        // Handle empty edge cases
        if (token == "empty" || token == "{}") return is;
        
        // Stripping the curly brackets from the ends B)

        if (!token.empty() && token.front() == '{') token.erase(0, 1);
        if (!token.empty() && token.back() == '}') token.pop_back();
        
        // Convert commas into spaces so it's for stringstream can easily read them
        for (char& c : token) {
            if (c == ',') c = ' ';
        }
        
        // Load the cleaned string into stringstream
        stringstream ss(token);
        while (true) {
            T item;
            if(ss >> item){
                s.insert(item);
            }else{
                break;
            }
        }
    }
    return is;
}

// Populate a set from a whole line of text 
template <typename T>
void populate_set(CustomSet<T>& mySet, const string& line) {
    stringstream ss(line);
    // Keep pulling items off the stringstream until it is empty
    while (true) {
        T item;
        if(ss >> item){
            mySet.insert(item);
        }else{
            break;
        }
       }
}

// Execute Operations
template <typename T>
void execute_operations(ifstream& infile, CustomSet<T>& set1, CustomSet<T>& set2, int num_ops) {
    for (int i = 0; i < num_ops; i++) {
        int op_code;
        infile >> op_code;

        if (op_code == 1 || op_code == 2) {
            int target;
            T item;
            infile >> target >> item; // If item is a nested set, it uses parser right away (I know its so kewl)
            
            if (op_code == 1) {
                if (target == 1) set1.insert(item); else set2.insert(item);
            } else {
                if (target == 1) set1.remove(item); else set2.remove(item);
            }
            
            print_set(target == 1 ? set1 : set2);
            cout << endl;

        } else if (op_code == 3) {
            cout << (set1.is_subset(set2) ? "true" : "false") << endl;

        } else if (op_code == 4) {
            print_set(set1.get_union(set2)); cout << endl;

        } else if (op_code == 5) {
            print_set(set1.get_intersection(set2)); cout << endl;

        } else if (op_code == 6) {
            print_set(set1.get_difference(set2)); cout << endl;

        } else if (op_code == 7) {
            int target;
            infile >> target;
            print_set(target == 1 ? set1.get_powerset() : set2.get_powerset()); 
            cout << endl;
        }
    }
}

// Helper to reduce repetitive code in main() because Iowanna do this enimore :(
template <typename T>
void setup_and_execute(ifstream& infile, const string& line1, const string& line2, int num_ops) {
    CustomSet<T> s1, s2;
    populate_set(s1, line1);
    populate_set(s2, line2);
    execute_operations(infile, s1, s2, num_ops);
}

int main() {
    ifstream infile("mpa1.in");
    if (!infile.is_open()) {
        cout << "Could not open mpa1.in" << endl;
        return 1;
    }

    int test_cases;
    infile >> test_cases;

    for (int t = 0; t < test_cases; t++) {
        int type;
        infile >> type;
        
        int nested_type = 0;
        if (type == 5) {
            infile >> nested_type; // Read the second number if it's a set
        }

        string line1, line2;
        // '>> ws' clears any leftover invisible newline characters 
        // from the stream before we attempt to grab an entire line
        getline(infile >> ws, line1); 
        getline(infile, line2);

        int num_ops;
        infile >> num_ops;

        // Route to the correct data type
        if (type == 1) {
            setup_and_execute<int>(infile, line1, line2, num_ops);
        } else if (type == 2) {
            setup_and_execute<double>(infile, line1, line2, num_ops);
        } else if (type == 3) {
            setup_and_execute<char>(infile, line1, line2, num_ops);
        } else if (type == 4) {
            setup_and_execute<string>(infile, line1, line2, num_ops);
        } else if (type == 5) {
            if (nested_type == 1) setup_and_execute< CustomSet<int> >(infile, line1, line2, num_ops);
            else if (nested_type == 2) setup_and_execute< CustomSet<double> >(infile, line1, line2, num_ops);
            else if (nested_type == 3) setup_and_execute< CustomSet<char> >(infile, line1, line2, num_ops);
            else if (nested_type == 4) setup_and_execute< CustomSet<string> >(infile, line1, line2, num_ops);
        }
    }

    infile.close();
    return 0;
}