#pragma once

#include <functional>
#include <iterator>
#include <ostream>

template <typename T>
struct Node {
  Node* prev{nullptr};
  Node* next{nullptr};
  T data;
  Node(const T& element) : data{element}, next{nullptr}, prev{nullptr} {}
};

template <typename T>
class DoubleLinkedList {
  public:
  class Iterator;
  DoubleLinkedList();
  DoubleLinkedList(const DoubleLinkedList&);
  DoubleLinkedList(DoubleLinkedList&&);
  DoubleLinkedList& operator=(const DoubleLinkedList&);
  DoubleLinkedList& operator=(DoubleLinkedList&&);
  ~DoubleLinkedList();

  DoubleLinkedList& push_back(const T&);
  DoubleLinkedList& push_front(const T&);
  DoubleLinkedList& push_back(T&&);
  DoubleLinkedList& push_front(T&&);
  DoubleLinkedList& pop_front();
  DoubleLinkedList& pop_back();
  bool empty() const;
  size_t size() const;
  T& front();
  T& back();
  Iterator begin() const;
  Iterator end() const;
  const Iterator cbegin() const;
  const Iterator cend() const;
  Iterator rbegin() const;
  Iterator rend() const;
  const Iterator rcbegin() const;
  const Iterator rcend() const;
  void clear();
  Iterator insert(Iterator pos, const T& element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);
  void remove_if(std::function<bool(const T&)>&& p);
  void reverse();
  Iterator find(const T& element) const;

  DoubleLinkedList& sort() {
    for(auto outerIt = end(); outerIt != begin(); --outerIt) {
      for(auto innerIt = begin(); innerIt != outerIt; ++innerIt) {
        auto it = innerIt;
        --it;
        if(*innerIt < *it) std::swap(*innerIt, it);
      }
    }
  }

  private:
  void dealoc();
  Node<T>* head_{nullptr};
  Node<T>* tail_{nullptr};
  size_t size_{0};
};

template <typename T>
class DoubleLinkedList<T>::Iterator
    : public std::iterator<std::bidirectional_iterator_tag, T> {
  public:
  Iterator() {}
  Iterator(Node<T>* p) : ptr_{p} {}
  Iterator(const Iterator& other) : ptr_{other.ptr_} {}
  Iterator& operator=(const Iterator& other) {
    if (this != &other) ptr_ = other.ptr_;
    return *this;
  }
  Iterator(Iterator&& other) : ptr_{other.ptr_} { other.ptr_ = nullptr; }
  Iterator& operator=(Iterator&& other) {
    if (this != &other) {
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  Iterator& operator++() {
    ptr_ = ptr_->next;
    return *this;
  }

  Iterator operator++(int) {
    auto temp = Iterator(ptr_);
    ptr_ = ptr_->next;
    return temp;
  }

  Iterator& operator--() {
    ptr_ = ptr_->prev;
    return *this;
  }

  Iterator operator--(int) {
    auto temp = Iterator(ptr_);
    ptr_ = ptr_->prev;
    return temp;
  }

  T& operator*() { return ptr_->data; }
  T* operator->() { return &(ptr_->data); }

  bool operator==(const Iterator& other) { return ptr_ == other.ptr_; }
  bool operator!=(const Iterator& other) { return ptr_ != other.ptr_; }

  Node<T>* node() { return ptr_; }

  private:
  Node<T>* ptr_{nullptr};
};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() {}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other) {
  auto it = other.begin();
  while (it != other.end()) {
    push_back(*it);
    ++it;
  }
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& other)
    : size_{other.size_}, head_{other.head_}, tail_{other.tail_} {
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& other) {
  if (this != &other) {
    clear();
    auto it = other.begin();
    while (it != other.end()) {
      push_back(*it);
      ++it;
    }
  }
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& other) {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() { dealoc(); }

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(const T& element) {
  auto temp = new Node<T>(element);
  if (size_ == 0)
    head_ = tail_ = temp;
  else {
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
  }

  ++size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(const T& element) {
  auto temp = new Node<T>(element);
  if (size_ == 0)
    head_ = tail_ = temp;
  else {
    head_->prev = temp;
    temp->next = head_;
    head_ = temp;
  }

  ++size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(T&& element) {
  auto temp = new Node<T>(std::move(element));
  if (size_ == 0)
    head_ = tail_ = temp;
  else {
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
  }

  ++size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(T&& element) {
  auto temp = new Node<T>(std::move(element));
  if (size_ == 0)
    head_ = tail_ = temp;
  else {
    head_->prev = temp;
    temp->next = head_;
    head_ = temp;
  }

  ++size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front() {
  if (size_ == 0) throw std::out_of_range{"Container is empty."};
  if (size_ == 1)
    head_ = tail_ = nullptr;
  else {
    head_->next->prev = nullptr;
    head_ = head_->next;
  }

  --size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back() {
  if (size_ == 0) throw std::out_of_range{"Container is empty."};
  if (size_ == 1)
    head_ = tail_ = nullptr;
  else {
    tail_->prev->next = nullptr;
    tail_ = tail_->prev;
  }

  --size_;
  return *this;
}

template<typename T>
bool DoubleLinkedList<T>::empty() const { return size_ == 0; }

template<typename T>
size_t DoubleLinkedList<T>::size() const { return size_; }

template<typename T>
T& DoubleLinkedList<T>::front() {
  if (size_ == 0) throw std::out_of_range{"Container is empty!"};
  return *(begin());
}

template<typename T>
T& DoubleLinkedList<T>::back() {
  if (size_ == 0) throw std::out_of_range{"Container is empty."};
  return *(rbegin());
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const { return Iterator(head_); }

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const { return Iterator(); }

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cbegin() const { return Iterator(head_); }

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cend() const { return Iterator(); }

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rbegin() const { return Iterator(tail_); }

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rend() const { return Iterator(); }

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcbegin() const { return Iterator(tail_); }

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcend() const { return Iterator(); }

template<typename T>
void DoubleLinkedList<T>::clear() {
  while (size_) pop_back();
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(Iterator pos, const T& element) {
  if (pos == begin()) {
    push_front(element);
    return begin();
  } else if (pos == end()) {
    push_back(element);
    return rbegin();
  } else {
    auto temp = new Node<T>(element);
    pos.node()->prev->next = temp;
    temp->prev = pos.node()->prev;
    pos.node()->prev = temp;
    temp->next = pos.node();

    ++size_;
    return --pos;
  }
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator pos) {
  if (pos == begin()) {
    pop_front();
    return begin();
  } else if (pos == rbegin()) {
    pop_back();
    return rbegin();
  } else {
    auto temp = pos.node();
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;

    --size_;
    return ++pos;
  }
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator beginIt, Iterator endIt) {
  while (beginIt != endIt) {
    erase(beginIt);
    ++beginIt;
  }

  return endIt;
}

template<typename T>
void DoubleLinkedList<T>::remove_if(std::function<bool(const T&)>&& p) {
  auto it = begin();
  while (it != end()) {
    if (p(*it)) erase(it);
    ++it;
  }
}

template<typename T>
void DoubleLinkedList<T>::reverse() {
  auto b = begin();
  auto rb = rbegin();
  for (int i = 0; i < size_ / 2; ++i, ++b, --rb) {
    std::swap(*b, *rb);
  }
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(const T& element) const {
  auto it = begin();
  while (it != end()) {
    if (*it == element) break;

    ++it;
  }

  return it;
}

template<typename T>
void DoubleLinkedList<T>::dealoc() {
  clear();
  head_ = tail_ = nullptr;
}
