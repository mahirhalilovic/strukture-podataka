#include <iostream>

template<typename K, typename V>
struct Node{
    K key_;
    V value_;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
  };

template <typename K, typename V>
class Map {
  public:
  Map() = default;
  Map(const Map& other) {
    insert_subtree(other.root_);
    size_ = other.size_;
  }
  Map(Map&& other) : root_{other.root_}, size_{other.size_} {
    other.root_ = nullptr;
    other.size_ = 0;
  }
  Map& operator=(const Map& other) {
    if(this != &other) {
      clear();
      insert_subtree(other.root_);
      size_ = other.size_;
    }

    return *this;
  }
  Map& operator=(Map&& other) {
    if(this != &other) {
      clear();
      root_ = other.root_;
      size_ = other.size_;

      other.root_ = nullptr;
      other.size_ = 0;
    }

    return *this;
  }
  ~Map() { clear(); }

  bool empty() const { return size_ == 0; }
  size_t size() const { return size_; }

  // Metod baca iznimku ako element pod kljucem k ne postoji
  V& at(const K& k) {
    auto f = find(k);
    if(f == nullptr) throw std::out_of_range{"Element not found!"};

    return *f;
  }
  const V& at(const K& k) const {
    auto f = find(k);
    if(f == nullptr) throw std::out_of_range{"Element not found!"};

    return *f;
  }

  // Metod vraca nullptr ako element nije pronaden
  V* find(const K& k) {
    auto current = root_;
    while(current != nullptr) {
      if(current->key_ < k) {
        current = current->right_;
      } else if(current->key_ == k) {
        return &current->value_;
      } else {
        current = current->left_;
      }
    }

    return nullptr;
  }
  const V* find(const K& k) const {
    auto current = root_;
    while(current != nullptr) {
      if(current->key_ < k) {
        current = current->right_;
      } else if(current->key_ == k) {
        return &current->value_;
      } else {
        current = current->left_;
      }
    }

    return nullptr;
  }

  // Metod vraca referencu na element u stablu. Ako element ne
  // postoji potrebno je ubaciti novi cvor pod kljucem k, sa default
  // konstruisanom vrijednosti v (stoga ovaj metod ne moze biti const)
  V& operator[](const K& k) {
    auto f = find(k);

    if(f == nullptr) {
      insert(k, 0);
      f = find(k);
      return *f;
    }

    return *f;
  }

  // Ubacuje novi cvor u stablo pod kljucem k. Vrijednost se konstruise
  // koristeci forward referencu. Potrebno je baciti iznimku ako vrijednost
  // pod tim kljucem vec postoji
  template<typename F>
  void insert(const K& k, F&& v) {
    if(size_ == 0) {
      root_ = new Node<K, V>{k, std::forward<F>(v)};
    } else {
      auto current = root_;
      while(current != nullptr) {
        if(k > current->key_) {
          if(current->right_ == nullptr) {
            current->right_ = new Node<K, V>{k, std::forward<F>(v)};
            break;
          } else {
            current = current->right_;
          }
        } else {
          if(current->left_ == nullptr) {
            current->left_ = new Node<K, V>{k, std::forward<F>(v)};
            break;
          } else {
            current = current->left_;
          }
        }
      }
    }

    ++size_;
  }

  // Vraca true ako je vrijednost izbrisana iz stabla, false ako ta vrijednost
  // ne postoji
  bool erase(const K& k) {
    auto f = findNode(k);
    if(f == nullptr) return false;

    Node<K, V> *previous = nullptr;
    auto current = f->right_;

    while(current->left_ != nullptr) {
      previous = current;
      current = current->left_;
    }

    f->value_ = current->value_;

    if(previous != nullptr) {
      previous->left_ = current->right_;
    } else {
      f->right_ = current->left_;
    }

    delete current;
    --size_;
    return true;
  }
  void clear() { clear_subtree(root_); }

  void print() {
    print_inorder(root_);
    std::cout << std::endl;
  }

  private:
  Node<K, V> *root_;
  size_t size_ = 0;

  void insert_subtree(Node<K, V> *root) {
    if(root == nullptr) return;

    insert(root->key_, root->value_);
    insert_subtree(root->left_);
    insert_subtree(root->right_);
  }

  void clear_subtree(Node<K, V> *root) {
    if(root == nullptr) return;
    clear_subtree(root->left_);
    clear_subtree(root->right_);
    delete root;
  }

  void print_inorder(Node<K, V> *root) {
    if(root->left_) print_inorder(root->left_);
    std::cout << '[' << root->key_ << ", " << root->value_ << "] ";
    if(root->right_) print_inorder(root->right_);
  }

  Node<K, V>* findNode(const K &k) {
    auto current = root_;
    while(current != nullptr) {
      if(current->key_ > k) {
        current = current->left_;
      } else if(current->key_ == k) {
        return current;
      } else {
        current = current->right_;
      }
    }

    return nullptr;
  }
};
