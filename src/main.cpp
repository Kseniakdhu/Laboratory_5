#include "Double_Linked_List.h"
#include "Fixed_Block_Memory_Resource.h"
#include <iostream>
#include <string>

using namespace std;

struct Person {
    string name;
    int age;
    string city;
    
    Person(const string& n, int a, const string& c) : name(n), age(a), city(c) {}
    
    friend ostream& operator<<(ostream& os, const Person& p) {
        return os << p.name << " (" << p.age << "), " << p.city;
    }
};

int main() {
    Fixed_Block_Memory_Resource memory_pool(1024);
    
    double_linked_list<int> numbers(&memory_pool);
    
    numbers.push_back(10);
    numbers.push_back(4);
    numbers.push_back(-1);
    numbers.push_front(0);
    numbers.push_front(100);
    
    cout << "Numbers: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    numbers.pop_front();
    numbers.pop_back();
    
    cout << "After pop_front and pop_back: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "Size: " << numbers.size_() << endl;
    
    double_linked_list<Person> people(&memory_pool);
    
    people.push_back(Person("Alice", 25, "New York"));
    people.push_back(Person("Ivan", 20, "Moscow"));
    people.push_front(Person("Francya", 40, "Paris"));
    
    cout << "People: " << endl;
    for (const auto& person : people) {
        cout << "  " << person << endl;
    }
    
    people.pop_front();
    people.pop_back();
    
    cout << "After pop_front and pop_back: " << endl;
    for (const auto& person : people) {
        cout << "  " << person << endl;
    }
    
    cout << "Size: " << people.size_() << endl;
    
    return 0;
}