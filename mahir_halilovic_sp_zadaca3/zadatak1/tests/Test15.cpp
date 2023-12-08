#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("move assignment operator moves elements from source list") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;
  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);

  list2 = std::move(list1);

  CHECK(list1.empty());
  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
}

TEST_CASE("move assignment operator creates new list with independent memory") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;
  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);

  list2 = std::move(list1);

  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
  CHECK_THROWS_AS(list1.back(), std::out_of_range);
  CHECK_THROWS_AS(list1.front(), std::out_of_range);
  CHECK(list1.size() == 0);
}

TEST_CASE("move assignment operator handles self-assignment") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto list2 = std::move(list);

  CHECK(list.size() == 0);
  CHECK_THROWS_AS(list.front(), std::out_of_range);
  CHECK(list2.back() == 3);
  CHECK(list2.size() == 3);
}

TEST_CASE("move assignment operator returns a reference to the list") {
  DoubleLinkedList<int> list1;
  DoubleLinkedList<int> list2;

  DoubleLinkedList<int>& list1Ref = (list1 = std::move(list2));

  CHECK(&list1Ref == &list1);
  CHECK(&list1Ref != &list2);
}

TEST_CASE("move assignment operator handles empty source list") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;

  list2 = std::move(list1);

  CHECK(list1.empty());
  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
}

