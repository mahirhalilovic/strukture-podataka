#include <iostream>

template<typename T>
class Queue{
  public:
    Queue();
    Queue(Queue&);
    Queue& operator=(Queue&);
    Queue(Queue&&);
    Queue& operator=(Queue&&);
    Queue(size_t);
    ~Queue();

    template<typename F>
    Queue& push(F&&);
    T pop();

    T& front();
    T& front() const;
    T& back();
    T& back() const;

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

  private:
    void realoc();
    void clear();
    size_t capacity_ = 10;
    size_t size_ = 0;
    T* arr_;
    int first_ = 0;
    int last_ = 0;
};
