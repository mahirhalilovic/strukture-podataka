#pragma once

#include "Queue.hpp"

template<typename T>
Queue<T>::Queue() : arr_{new T[capacity_]} {}

template<typename T>
Queue<T>::Queue(Queue& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]}, first_{other.first_}, last_{other.last_} {
  for(int i = 0; i < capacity_; ++i)
    arr_[i] = other.arr_[i];
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue& other) {
  if(this != &other) {
    clear();
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = new T[capacity_];
    first_ = other.first_;
    last_ = other.last_;

    for(int i = 0; i < capacity_; ++i)
      arr_[i] = other.arr_[i];
  }

  return *this;
}

template<typename T>
Queue<T>::Queue(Queue&& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]}, first_{other.first_}, last_{other.last_} {
  for(int i = 0; i < capacity_; ++i)
    arr_[i] = std::move(other.arr_[i]);

  other.size_ = 0;
  other.capacity_ = 10;
  delete[] other.arr_;
  other.arr_ = new T[other.capacity_];
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) {
  if(this != &other) {
    clear();
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = new T[capacity_];
    first_ = other.first_;
    last_ = other.last_;

    for(int i = 0; i < capacity_; ++i)
      arr_[i] = std::move(other.arr_[i]);

    other.size_ = 0;
    other.capacity_ = 10;
    delete[] other.arr_;
    other.arr_ = new T[other.capacity_];
  }

  return *this;
}

template<typename T>
Queue<T>::Queue(size_t n) : capacity_{n}, arr_{new T[capacity_]} {}

template<typename T>
Queue<T>::~Queue() { clear(); }

template<typename T>
template<typename F>
Queue<T>& Queue<T>::push(F&& value) {
  if(!size_) {
    first_ = last_ = 0;
  } else if(size_ == capacity_) {
    realoc();
    ++last_;
  } else if(last_ == capacity_ - 1) {
    last_ = 0;
  } else {
    ++last_;
  }

  arr_[last_] = std::forward<F>(std::move(value));
  ++size_;
  return *this;
}

template<typename T>
T Queue<T>::pop() {
  if(!size_) throw std::out_of_range{"Container is empty!"};

  auto temp = arr_[first_];
  if(first_ == capacity_ - 1) first_ = 0;
  else ++first_;
  --size_;

  return temp;
}

template<typename T>
T& Queue<T>::front() {
  if(!size_) throw std::out_of_range{"Container empty!"};
  return arr_[first_];
}

template<typename T>
T& Queue<T>::front() const {
  if(!size_) throw std::out_of_range{"Container empty!"};
  return arr_[first_];
}

template<typename T>
T& Queue<T>::back() {
  if(!size_) throw std::out_of_range{"Container empty!"};
  return arr_[last_];
}

template<typename T>
T& Queue<T>::back() const {
  if(!size_) throw std::out_of_range{"Container empty!"};
  return arr_[last_];
}

template<typename T>
size_t Queue<T>::size() const { return size_; }

template<typename T>
size_t Queue<T>::capacity() const { return capacity_; }

template<typename T>
bool Queue<T>::empty() const { return size_ == capacity_; }

template<typename T>
void Queue<T>::realoc() {
  T* temp = new T[capacity_];

  if(first_ < last_) std::move(arr_ + first_, arr_ + last_ + 1, temp);
  if(first_ > last_) {
    std::move(arr_ + first_, arr_ + capacity_, temp);
    std::move(arr_, arr_ + last_ + 1, temp + capacity_ - first_);
  }

  delete[] arr_;
  arr_ = temp;
  first_ = 0;
  last_ = size_ - 1;
}

template<typename T>
void Queue<T>::clear() { delete[] arr_; }
