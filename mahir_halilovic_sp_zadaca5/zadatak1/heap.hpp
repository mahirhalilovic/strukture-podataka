#pragma once

#include <iostream>
#include <stack>
#include <queue>

template<typename T>
class Heap{
  public:
    Heap(size_t cap = 15) : capacity_{cap}, size_{0}, heap_{new T[capacity_]} {}
    Heap(Heap& other) : capacity_{other.capacity_}, size_{other.size_}, heap_{new T[capacity_]} {
      for(int i = 0; i < size_; ++i)
        heap_[i] = other.heap_[i];
    }
    Heap(Heap&& other) : capacity_{other.capacity_}, size_{other.size_}, heap_{other.heap_} {
      other.heap_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 15;
    }
    Heap& operator=(Heap& other) {
      if(this != &other) {
        delete[] heap_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        heap_ = new T[capacity_];

        for(int i = 0; i < size_; ++i)
          heap_[i] = other.heap_[i];
      }

      return *this;
    }
    Heap& operator=(Heap&& other) {
      if(this != &other) {
        delete[] heap_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        heap_ = other.heap_;
        other.heap_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 15;
      }

      return *this;

    }
    ~Heap() { clear(); }

    void insert(T v) {
      if(size_ == capacity_) realoc();

      heap_[size_++] = std::move(v);
      for(int i = size_ - 1; i > 0 && heap_[i] > heap_[parent(i)]; i = parent(i))
        std::swap(heap_[i], heap_[parent(i)]);
    }

    T& max() {
      if(empty()) throw std::out_of_range{"Heap is empty!"};

      return heap_[0];
    }
    T& max() const {
      if(empty()) throw std::out_of_range{"Heap is empty!"};

      return heap_[0];
    }
    T removeMax() {
      if(empty()) throw std::out_of_range{"Heap is empty!"};
      auto temp = heap_[0];
      heap_[0] = heap_[--size_];
      maxHeapify(0);
      return temp;
    }

    void clear() {
      delete[] heap_;
      heap_ = nullptr;
      size_ = 0;
    }

    friend std::ostream& operator<<(std::ostream& out, const Heap<T>& heap) {
      std::stack<int> ps;
      std::queue<int> pq;
      ps.push(0);

      while(ps.size()) {
        int k = ps.top();
        pq.push(k);
        ps.pop();

        if(2 * k + 2 < heap.size())
          ps.push(2 * k + 2);
        if(2 * k + 1 < heap.size())
          ps.push(2 * k + 1);
      }

      while(pq.size()) {
        out << heap.at(pq.front()) << ' ';
        pq.pop();
      }

      out << std::endl;
      return out;
    }

    size_t size() const { return size_; }
    T& at(int index) const { return heap_[index]; }

  private:
    size_t capacity_;
    size_t size_;
    T *heap_;

    void realoc() {
      auto temp = new T[capacity_ *= 2];
      std::move(heap_, heap_ + capacity_, temp);
      delete[] heap_;
      heap_ = temp;
    }
    void maxHeapify(int index) {
      int left = leftChild(index);
      int right = rightChild(index);
      int largest = index;

      if(left <= size_ && heap_[left] > heap_[largest])
        largest = left;

      if(right <= size_ && heap_[right] > heap_[largest])
        largest = right;

      if(largest != index) {
        std::swap(heap_[index], heap_[largest]);
        maxHeapify(largest);
      }
    }
    int parent(int k) { return (k - 1) / 2; }
    int leftChild(int k) { return k * 2 + 1; }
    int rightChild(int k) { return k * 2 + 2; }
    bool empty() const { return size_ == 0; }
};






// Implementirati strukturu podataka Heap pomoću niza kao sto je to objašnjeno
// na predavanju. Ta struktura treba da implementira sljedeće:
// • Pravilno ponašanje konstruktora i destruktora,
// • ubacivanje novog elementa i njegovo uređenje kao max heap,
// • metod max koji vraća referencu na maksimalni element,
// • metod removeMax koji uklanja i vraća maksimalni element iz heapa,
// • operator<< koji ispisuje heap koristeći preorder obilazak.
//
// Napisati kratki main program u kojem se testiraju sve gore navedene funkcional-
// nosti.
