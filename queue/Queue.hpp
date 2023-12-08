#include <iostream>

template<typename T>
class Queue{
  public:
    Queue();
    Queue(const Queue&);
    Queue(Queue&&);
    Queue& operator=(const Queue&);
    Queue& operator=(Queue&&);
    ~Queue();

    Queue& enqueue(T&);
    Queue& enqueue(T&&);
    Queue& dequeue();

    T& top() const;
    size_t size() const;
    void clear();

  private:
    struct Node{
      Node* prev_;
      Node* next_;
      T data_;

      Node(T& element) : data_{std::move(element)}, prev_{nullptr}, next_{nullptr} {}
      Node(T&& element) : data_{std::move(element)}, prev_{nullptr}, next_{nullptr} {}
    };
    size_t size_{0};
    Node* head_{nullptr};
    Node* tail_{nullptr};
};

template<typename T>
Queue<T>::Queue() {}

template<typename T>
Queue<T>::Queue(const Queue& other) {
  auto temp = other.head_;
  size_ = other.size_;
  while(temp != nullptr) {
    enqueue(temp->data_);
    temp = temp->next_;
  }
}

template<typename T>
Queue<T>::Queue(Queue&& other) {
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
  if(this != &other) {
    clear();
    auto temp = other.head_;
    size_ = other.size_;
    while(temp != nullptr) {
      enqueue(temp->data_);
      temp = temp->next_;
    }
  }

  return *this;
}
  
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) {
  if(this != &other) {
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
Queue<T>::~Queue() { clear(); }

template<typename T>
Queue<T>& Queue<T>::enqueue(T& element) {
  auto temp = new Node(element);
  if(!size_) head_ = tail_ = temp;
  else {
    temp->next_ = head_;
    head_ = temp;
  }
  ++size_;
  return *this;
}

template<typename T>
Queue<T>& Queue<T>::enqueue(T&& element) {
  auto temp = new Node(std::move(element));
  if(!size_) head_ = tail_ = temp;
  else {
    tail_->next_ = temp;
    tail_ = temp;
  }
  ++size_;
  return *this;
}

template<typename T>
Queue<T>& Queue<T>::dequeue() {
  if(!size_) throw std::out_of_range{"Container is empty."};
  auto temp = head_;
  head_ = head_->next_;
  delete temp;
  --size_;
  return *this;
}

template<typename T>
T& Queue<T>::top() const {
  if(!size_) throw std::out_of_range{"Container is empty."};
  return head_->data_;
}

template<typename T>
size_t Queue<T>::size() const { return size_; }

template<typename T>
void Queue<T>::clear() { while(size_) dequeue(); }
