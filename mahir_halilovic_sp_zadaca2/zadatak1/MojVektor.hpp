#pragma once
#include <initializer_list>
#include <iterator>

template <typename T>
class MojVektor {
  public:
  class Iterator;
  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;
  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;
  bool empty() const;
  size_t capacity() const;
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;
  MojVektor subvector(Iterator begin, Iterator end);
  Iterator begin() const;
  Iterator end() const;
  Iterator find(const T&) const;
  Iterator erase(Iterator pos);
  Iterator insert(Iterator, const T&);
  Iterator insert(Iterator, T&&);
  Iterator rbegin() const;
  Iterator rend() const;
  Iterator erase(Iterator beginIt, Iterator endIt);
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);

  T* data();

  template<typename U>
  friend std::ostream& operator<<(std::ostream&, const MojVektor<U>&);

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

template<typename T>
MojVektor<T>::MojVektor() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}

template<typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T> &l) : capacity_{l.size()}, size_{l.size()}, arr_{new T[capacity_]} {
  std::copy(l.begin(), l.end(), arr_);
}

template<typename T>
MojVektor<T>::MojVektor(const MojVektor& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]} {
  std::copy(other.begin(), other.end(), arr_);
}

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  std::copy(other.begin(), other.end(), arr_);

  return *this;
}

template<typename T>
MojVektor<T>::MojVektor(MojVektor&& other) : capacity_{other.capacity_}, size_{other.size_}, arr_{std::move(other.arr_)} {
  other.capacity_ = 0;
  other.size_ = 0;
}

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& other) {
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = std::move(other.arr_);
  other.capacity_ = other.size_ = 0;

  return *this;
}

template<typename T>
MojVektor<T>::~MojVektor() {
  delete[] arr_;
  capacity_ = size_ = 0;
  arr_ = nullptr;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const MojVektor<T>& vec) {
  if(vec.size() == 0)
    out << "{}";
  else {
    out << '{' << vec[0];
    for(int i = 1; i < vec.size(); ++i) {
      out << ", " << vec[i];
    }
    out << '}';
  }

  return out;
}

template<typename T>
void MojVektor<T>::realoc() {
  auto temp = new T[capacity_*=2];
  for(int i = 0; i < size_; ++i)
    temp[i] = arr_[i];

  delete[] arr_;
  arr_ = temp;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& elem) {
  if(size_ == capacity_) realoc();
  if(!arr_) arr_ = new T[capacity_];
  arr_[size_++] = elem;

  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& elem) {
  if(size_ == capacity_) realoc();
  if(!arr_) arr_ = new T[capacity_];

  if(size_) {
    int i = size_;
    while(i > 0) {
      arr_[i] = arr_[i-1];
      --i;
    }
  }
  arr_[0] = elem;
  ++size_;

  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& elem) {
  if(size_ == capacity_) realoc();
  if(!arr_) arr_ = new T[capacity_];

  arr_[size_++] = std::move(elem);

  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& elem) {
  if(size_ == capacity_) realoc();
  if(!arr_) arr_ = new T[capacity_];

  if(size_) {
    int i = size_;
    while(i > 0) {
      arr_[i] = arr_[i-1];
      --i;
    }
  }

  arr_[0] = std::move(elem);
  ++size_;

  return *this;
}

template<typename T>
size_t MojVektor<T>::size() const { return size_; }

template<typename T>
T& MojVektor<T>::at(size_t index) const {
  if(index < 0 || index > (size_ - 1)) throw std::out_of_range{"Index out of range!"};

  return arr_[index];
}

template<typename T>
T& MojVektor<T>::operator[](size_t index) const { return arr_[index]; }
  

template<typename T>
void MojVektor<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
}

template<typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value) {
  if(size_ > newSize) size_ = newSize;
  else {
    if(newSize > capacity_) capacity_ = newSize;

    for(int i = size_; i < newSize; ++i)
      push_back(difference_value);
  }
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
  if(!size_) throw std::out_of_range{"Can't pop out of empty vector!"};

  --size_;

  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_front() {
  if(!size_) throw std::out_of_range{"Can't pop out of empty vector!"};

  for(int i = 0; i < size_ - 1; ++i)
    arr_[i] = arr_[i+1];

  --size_;

  return *this;
}

template<typename T>
T& MojVektor<T>::back() const {
  if(!size_) throw std::out_of_range{"Vector is empty!"};

  return arr_[size_ - 1];
}

template<typename T>
T& MojVektor<T>::front() const {
  if(!size_) throw std::out_of_range{"Vector is empty!"};

  return arr_[0];
}

template<typename T>
bool MojVektor<T>::empty() const { return !size_; }

template<typename T>
size_t MojVektor<T>::capacity() const { return capacity_; }

template<typename T>
bool MojVektor<T>::operator==(const MojVektor& other) const {
  if(size_ != other.size_) return false;

  for(int i = 0; i < size_; i++)
    if(arr_[i] != other.arr_[i]) return false;

  return true;
}
  
template<typename T>
bool MojVektor<T>::operator!=(const MojVektor& other) const { return !(*this == other); }

template<typename T>
bool MojVektor<T>::full() const { return size_ == capacity_; }

template<typename T>
class MojVektor<T>::Iterator{
  public:

    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;

    Iterator() : ptr_{nullptr} {}

    Iterator(T* ptr) : ptr_{ptr} {}

    Iterator(Iterator &it) : ptr_{it.ptr_} {}
    Iterator& operator=(Iterator &it) { ptr_ = it.ptr_; }

    Iterator(Iterator &&it) { ptr_ = std::move(it.ptr_); it.ptr_ = nullptr; }
    Iterator& operator=(Iterator &&it) { ptr_ = std::move(it.ptr_); it.ptr_ = nullptr; }

    Iterator& operator++() {
      ++ptr_;
      return *this;
    }

    Iterator operator++(int) {
      auto temp = ptr_;
      ++ptr_;
      return Iterator(temp);
    }

    Iterator& operator--() {
      --ptr_;
      return *this;
    }

    Iterator operator--(int) {
      auto temp = ptr_;
      --ptr_;
      return Iterator(temp);
    }

    Iterator operator+(int n) { return Iterator(ptr_ + n); }
    Iterator operator-(int n) { return Iterator(ptr_ - n); }

    T* operator[](int n) { return ptr_ + n; }

    int operator-(const Iterator &rhs) { return ptr_ - rhs.ptr_; }

    bool operator<(const Iterator &rhs) { return ptr_ < rhs.ptr_; }
    bool operator<=(const Iterator &rhs) { return ptr_ <= rhs.ptr_; }
    bool operator>(const Iterator &rhs) { return ptr_ > rhs.ptr_; }
    bool operator>=(const Iterator &rhs) { return ptr_ >= rhs.ptr_; }
    bool operator==(const Iterator &rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const Iterator &rhs) { return ptr_ != rhs.ptr_; }

    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_; }

  private:
    T* ptr_;
};

template<typename T>
MojVektor<T> MojVektor<T>::subvector(Iterator begin, Iterator end) {
  MojVektor<T> temp;
  while(begin != end) {
    temp.push_back(*begin);
    ++begin;
  }

  return temp;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::begin() const { return Iterator(arr_); }

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::end() const { return Iterator(arr_+size_); }

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& elem) const {
  for(int i = 0; i < size_; i++)
    if(arr_[i] == elem) return Iterator(arr_+i);

  return end();
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos) {
  if(pos < begin() || pos >= end()) return end();
  Iterator it = pos;
  while((it + 1) != end()){
    *it = *(it + 1);
    ++it;
  }
  
  --size_;
  return pos;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, const T& elem) {
  if(pos < begin() || pos >= end()) { throw std::out_of_range{"Cannot insert outside of range!"}; }

  int offset = pos - begin();

  if(size_ == capacity_) realoc();
  ++size_;
  auto it = Iterator(arr_ + size_ - 1);
  pos = Iterator(arr_ + offset);

  while(it != pos) {
    *it = *(it-1);
    --it;
  }

  *pos = elem;
  return pos;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, T&& elem) {
  if(pos < begin() || pos >= end()) throw std::out_of_range{"Cannot insert outside of range!"};
  
  int offset = pos - begin();
  if(size_ == capacity_) realoc();
  ++size_;
  auto it = end() - 1;
  pos = begin() + offset;
  while(it != pos) {
    *it = std::move(*(it - 1));
    --it;
  }

  *pos = std::move(elem);
  return pos;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rbegin() const { return Iterator(arr_ + size_ - 1); }
  
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rend() const { return Iterator(arr_ - 1); }

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt) {
  /* for(; beginIt != endIt; ++beginIt)
    erase(beginIt);

  return endIt; */

  if(beginIt >= endIt || beginIt < begin() || endIt > end())
    return end();

  while(beginIt < endIt){
    beginIt = erase(beginIt);
    --endIt;
  }

  return beginIt;
}

template<typename T>
void MojVektor<T>::rotate() {
  MojVektor<T> temp = *this;
  for(int i = 0; i < size_; ++i)
    arr_[i]  = temp.arr_[size_ - 1 - i];
}

template<typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt) {
  MojVektor<T> temp = *this;
  auto begin = beginIt - arr_;
  auto end = endIt - arr_ - 1;
  for(; beginIt != endIt; ++beginIt)
    *beginIt = temp.arr_[end + begin - (beginIt - arr_)];
}

template<typename T>
T* MojVektor<T>::data() { return arr_; }
