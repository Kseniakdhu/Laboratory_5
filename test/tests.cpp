#include "gtest/gtest.h"
#include "Double_Linked_List.h"
#include "Fixed_Block_Memory_Resource.h"
#include <string>

struct Person {
    std::string name;
    int age;
    std::string city;
    
    Person(const std::string& n, int a, const std::string& c) : name(n), age(a), city(c) {}
    
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age && city == other.city;
    }
};

// Тесты для списка с числами
class DoubleLinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        memory_pool = new Fixed_Block_Memory_Resource(1024);
        numbers = new double_linked_list<int>(memory_pool);
    }
    
    void TearDown() override {
        delete numbers;
        delete memory_pool;
    }
    
    Fixed_Block_Memory_Resource* memory_pool;
    double_linked_list<int>* numbers;
};

// Тесты для списка с людьми
class DoubleLinkedListPersonTest : public ::testing::Test {
protected:
    void SetUp() override {
        memory_pool = new Fixed_Block_Memory_Resource(1024);
        people = new double_linked_list<Person>(memory_pool);
    }
    
    void TearDown() override {
        delete people;
        delete memory_pool;
    }
    
    Fixed_Block_Memory_Resource* memory_pool;
    double_linked_list<Person>* people;
};


TEST_F(DoubleLinkedListTest, EmptyOnCreation) {
    EXPECT_TRUE(numbers->empty());
    EXPECT_EQ(numbers->size_(), 0);
}

TEST_F(DoubleLinkedListTest, PushBack) {
    numbers->push_back(10);
    numbers->push_back(20);
    numbers->push_back(30);
    
    EXPECT_FALSE(numbers->empty());
    EXPECT_EQ(numbers->size_(), 3);
}

TEST_F(DoubleLinkedListTest, PushFront) {
    numbers->push_front(30);
    numbers->push_front(20);
    numbers->push_front(10);
    
    EXPECT_EQ(numbers->size_(), 3);
}

TEST_F(DoubleLinkedListTest, PopFront) {
    numbers->push_back(10);
    numbers->push_back(20);
    numbers->push_back(30);
    
    numbers->pop_front();
    EXPECT_EQ(numbers->size_(), 2);
}

TEST_F(DoubleLinkedListTest, PopBack) {
    numbers->push_back(10);
    numbers->push_back(20);
    numbers->push_back(30);
    
    numbers->pop_back();
    EXPECT_EQ(numbers->size_(), 2);
}

TEST_F(DoubleLinkedListTest, Clear) {
    numbers->push_back(10);
    numbers->push_back(20);
    numbers->push_back(30);
    
    numbers->clear();
    EXPECT_TRUE(numbers->empty());
    EXPECT_EQ(numbers->size_(), 0);
}

TEST_F(DoubleLinkedListTest, RangeBasedFor) {
    numbers->push_back(1);
    numbers->push_back(2);
    numbers->push_back(3);
    
    int sum = 0;
    for (const auto& num : *numbers) {
        sum += num;
    }
    
    EXPECT_EQ(sum, 6);
}

TEST_F(DoubleLinkedListTest, MixedOperations) {
    numbers->push_back(20);
    numbers->push_front(10);
    numbers->push_back(30);
    
    EXPECT_EQ(numbers->size_(), 3);
    
    numbers->pop_front();
    EXPECT_EQ(numbers->size_(), 2);
    
    numbers->push_front(5);
    EXPECT_EQ(numbers->size_(), 3);
    
    numbers->pop_back();
    EXPECT_EQ(numbers->size_(), 2);
}

TEST_F(DoubleLinkedListPersonTest, PersonPushBack) {
    people->push_back(Person("Alice", 25, "NY"));
    people->push_back(Person("Bob", 30, "LA"));
    
    EXPECT_EQ(people->size_(), 2);
    EXPECT_FALSE(people->empty());
}

TEST_F(DoubleLinkedListPersonTest, PersonPushFront) {
    people->push_front(Person("Charlie", 35, "Chicago"));
    people->push_front(Person("Diana", 28, "Boston"));
    
    EXPECT_EQ(people->size_(), 2);
}

TEST_F(DoubleLinkedListPersonTest, PersonIteration) {
    people->push_back(Person("Alice", 25, "NY"));
    people->push_back(Person("Bob", 30, "LA"));
    
    int count = 0;
    for (const auto& person : *people) {
        count++;
        EXPECT_TRUE(person.name == "Alice" || person.name == "Bob");
    }
    
    EXPECT_EQ(count, 2);
}

TEST_F(DoubleLinkedListPersonTest, PersonClear) {
    people->push_back(Person("Alice", 25, "NY"));
    people->push_back(Person("Bob", 30, "LA"));
    
    people->clear();
    EXPECT_TRUE(people->empty());
    EXPECT_EQ(people->size_(), 0);
}
