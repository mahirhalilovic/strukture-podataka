#include <iostream>

template<typename T>
class myQueue{
  public:
    myQueue();
    myQueue(const myQueue&);
    myQueue(myQueue&&);
    myQueue& operator=(const myQueue&);
    myQueue& operator=(myQueue&&);

    myQueue& enqueue(T&);
    myQueue& enqueue(T&&);
    myQueue& dequeue();

    T& top() const;
    size_t size() const;

  private:
    size_t capacity_;
    size_t size_;
    T* arr_;
    void realoc();
};

template<typename T>
myQueue<T>::myQueue() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}

template<typename T>
myQueue<T>::myQueue(const myQueue& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = new T[capacity_];
  std::copy(other.arr_, other.arr_ + other.size_, arr_);
}

template<typename T>
myQueue<T>::myQueue(myQueue&& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = other.arr_;
  other.arr_ = nullptr;
  other.capacity_ = other.size_ = 0;
}

template<typename T>
myQueue<T>& myQueue<T>::operator=(const myQueue& other) {
  if(this != &other) {
    delete[] arr_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = new T[capacity_];
  }
  return *this;
}

template<typename T>
myQueue<T>& myQueue<T>::operator=(myQueue&& other) {
  if(this != &other) {
    delete[] arr_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = other.arr_;
    other.arr_ = nullptr;
    other.capacity_ = other.size_ = 0;
  }
  return *this;
}

template<typename T>
myQueue<T>& myQueue<T>::enqueue(T& element) {
  if(size_ == capacity_) realoc();
  std::copy(arr_, arr_ + size_, arr_ + 1);
  arr_[0] = element;
  ++size_;
  return *this;
}

template<typename T>
myQueue<T>& myQueue<T>::enqueue(T&& element) {
  if(size_ == capacity_) realoc();
  std::copy(arr_, arr_ + size_, arr_ + 1);
  arr_[0] = std::move(element);
  ++size_;
  return *this;
}

template<typename T>
myQueue<T>& myQueue<T>::dequeue() {
  if(size_) --size_;

  return *this;
}

template<typename T>
T& myQueue<T>::top() const { 
  if(!size_) throw std::out_of_range{"Container is empty."};
  return arr_[size_ - 1];
}

template<typename T>
size_t myQueue<T>::size() const { return size_; }

template<typename T>
void myQueue<T>::realoc() {
  auto temp = new T[capacity_ *= 2];
  std::copy(arr_, arr_ + size_, temp);
  delete[] arr_;
  arr_ = temp;
}
