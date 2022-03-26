#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* elem = new Node(value);
    if (front_ == nullptr) {
      front_ = elem;
      back_ = elem;
    } else {
      back_->next = elem;
      back_ = elem;
    }
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 || index > size_) {
      return false;
    }else {
      Node* node = new Node(value);
      if (IsEmpty()) {
        front_ = node;
        back_ = node;
      }else if (index == 0){
        node->next = front_;
        front_ = node;
      }else if (index == size_){
        back_->next = node;
        back_ = node;
      }else {
        node->next = FindNode(index-1)->next;
        FindNode(index-1)->next = node;
      }
      size_++;
      return true;
    }
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index < 0 || index >= size_) {
      return false;
    }else {
      FindNode(index)->value = new_value;
      return true;
    }
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }else{
      int val;
      if (index == 0){
        val = front_->value;
        front_= front_->next;
      }else {
        val = FindNode(index)->value;
        FindNode(index-1)->next = FindNode(index)->next;
      }
      size_--;
      return val;
    }
  }

  void LinkedList::Clear() {
    Node* del = front_;
    for (int i =0; i < size_;i++) {
      Node* del2 = del->next;
      delete del;
      del = del2;
    }
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }else {
      Node* node = FindNode(index);
      return node->value;
    }
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; i++){
      if (node->value == value) {
        return i;
      }
      node = node->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; i++){
      if (node->value == value) {
        return true;
      }
      node = node->next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_== 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ == nullptr) {
      return std::nullopt;
    }else {
      return front_->value;
    }
  }

  std::optional<int> LinkedList::back() const {
    if (back_ == nullptr) {
      return std::nullopt;
    }else {
      return back_->value;
    }
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 || index >= size_) {
      return nullptr;
    }else {
      Node* node = front_;
      for (int i = 0; i < index; i++) {
        node = node->next;
      }
      return node;
    }
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment