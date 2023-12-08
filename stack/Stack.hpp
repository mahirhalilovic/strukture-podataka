#include <iostream>
#include <vector>

template<typename T>
class myStack{
  public:
    myStack();
    myStack(const myStack&);
    myStack(myStack&&);
    myStack& operator=(const myStack&);
    myStack& operator=(myStack&&);

    myStack& push(T&);
    myStack& push(T&&);
    myStack& pop();
    
    T& top() const;
    size_t size() const;
  
  private:
    T* arr_{nullptr};
    size_t size_{0};
    size_t capacity_{10};
    void realoc();
};

template<typename T>
myStack<T>::myStack() : arr_{new T[10]}{}

template<typename T>
myStack<T>::myStack(const myStack& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  std::copy(other.arr_, other.arr_ + other.size_, arr_);

  return *this;
}

template<typename T>
myStack<T>::myStack(myStack&& other) {
  arr_ = other.arr_;
  other.arr_ = nullptr;
  size_ = other.size_;
  other.size_ = 0;
  return *this;
}

template<typename T>
myStack<T>& myStack<T>::operator=(const myStack& other) {
    if(this != &other) {
      capacity_ = other.capacity_;
      size_ = other.size_;
      delete[] arr_;
      arr_ = new T[capacity_];
      std::copy(other.arr_, other.arr_ + other.size_, arr_);
    }

    return *this;
}

template<typename T>
myStack<T>& myStack<T>::operator=(myStack&& other) {
  if(this != &other) {
    capacity_ = other.capacity_;
    delete[] arr_;
    arr_ = other.arr_;
    size_ = other.size_;
    other.arr_ = nullptr;
    other.capacity_ = other.size_ = 0;
  }

  return *this;
}

template<typename T>
myStack<T>& myStack<T>::push(T& element) {
  if(size_ == capacity_) realoc();
  
  arr_[size_] = element;
  ++size_;
  return *this;
}

template<typename T>
myStack<T>& myStack<T>::push(T&& element) {
  if(size_ == capacity_) realoc();

  arr_[size_] = std::move(element);
  ++size_;
  return *this;
}

template<typename T>
myStack<T>& myStack<T>::pop() {
  if(size_) --size_;

  return *this;
}

template<typename T>
T& myStack<T>::top() const {
  if(!size_) throw std::out_of_range{"Container is empty."};
  return arr_[size_ - 1];
}

template<typename T>
size_t myStack<T>::size() const { return size_; }

template<typename T>
void myStack<T>::realoc() {
  auto temp = new T[capacity_ *= 2];
  std::copy(arr_, arr_ + size_, temp);
  delete[] arr_;
  arr_ = temp;
}
