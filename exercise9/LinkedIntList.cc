/*
 * Name: Ray Oh
 * Email: rayoh101@uw.edu
 * Copyright @2023 Ray Oh
 */

#include "LinkedIntList.h"
#include <memory>

using std::shared_ptr;
using std::weak_ptr;

namespace intlist333 {

  LinkedIntList::LinkedIntList() {
    this->tail_ = NULL;
    this->head_ = NULL;
    this->num_elements_ = 0;
  }

  void LinkedIntList::Push(const int payload) {
    shared_ptr<Node> node(new Node());
    node->payload = payload;

    if (num_elements() == 0) {
      this->head_ = node;
      this->tail_ = node;
      node->next = NULL;
    } else {
      node->next = this->head_;
      this->head_->prev = node;
      this->head_ = node;
    }
    this->num_elements_++;
  }

  void LinkedIntList::Append(const int payload) {
    shared_ptr<Node> node(new Node());
    node->payload = payload;

    if (num_elements() == 0) {
      this->head_ = node;
      this->tail_ = node;
      node->next = NULL;
    } else {
      node->next = NULL;
      this->tail_->next = node;
      node->prev = this->tail_;
      this->tail_ = node;
      this->num_elements_++;
    }
  }

  bool LinkedIntList::Pop(int* const payload_ptr) {
    if (num_elements() == 0) {
      return false;
    } else {
      shared_ptr<Node> node(new Node());
      node = this->head_;
      *payload_ptr = node->payload;

      if (num_elements() == 1) {
        this->head_ = NULL;
        this->tail_ = NULL;
      } else {
        this->head_ = this->head_->next;
        this->head_->prev.lock() = NULL;
      }
      this->num_elements_--;
      return true;
    }
  }

  bool LinkedIntList::Slice(int* const payload_ptr) {
    if (num_elements() == 0) {
      return false;
    } else {
      shared_ptr<Node> node(new Node());
      node = this->tail_;
      *payload_ptr = node->payload;

      if (num_elements() == 1) {
        this->head_ = NULL;
        this->tail_ = NULL;
      } else {
        this->tail_ = this->tail_->prev.lock();
        this->tail_->next = NULL;
      }
      this->num_elements_--;
      return true;
    }
  }

  int LinkedIntList::num_elements() const {
    return this->num_elements_;
  }

}   // namespace intlist333
