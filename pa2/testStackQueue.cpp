#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;

    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);

    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}

TEST_CASE("dequeue::equal functions","[weight=1][part=dequeue]") {
    Deque<int> d;
    vector<int> result;
    vector<int> expected;//1 2 3
    for (int i = 1; i <=3; i++) {
        expected.push_back(i);

    }
    //1 2 3 4 5 6 7 8 9 10
    for (int i = 1; i <= 10; i++) {
        d.pushR(i);
    }
    //1 2 3
    for (int i = 1; i <= 7; i++) {
        d.popR();
    }
    while (!d.isEmpty()) {
        result.push_back(d.popL());
    }
    REQUIRE( result == expected);
    REQUIRE(result.size()==expected.size());
}


TEST_CASE("queue::equal functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;//1 2 3 4 5
    for (int i = 1; i <= 5; i++) {
        expected.push_back(i);
    }
    //5 4 3 2 1
    for (int i =5; i <= 1; i++) {
        intQueue.enqueue(i);

    }
    //1
    for(int i=1;i<5;i++){
        intQueue.dequeue();
    }

    REQUIRE(intQueue.peek()==1);

    //1 2 3 4 5
    for(int i=2;i<=5;i++){
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }

    REQUIRE( result == expected);
}