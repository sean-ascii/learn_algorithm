#pragma once

namespace sakabatou_algorithm {
namespace stl {

template <typename T>
class MySharedPtr {
 public:
  MySharedPtr(T* p) : cnt_(new int(1)), ptr_(p) {}
  MySharedPtr(MySharedPtr<T>& other) : cnt_(&(++*other.cnt_)), ptr_(other.ptr_) {}

  T* operator->() { return ptr_; }
  T& operator*() { return *ptr_; }

  MySharedPtr<T>& operator=(MySharedPtr<T>& other) {
    if (ptr_ && --*cnt_ == 0) {
      delete cnt_;
      delete ptr_;
    }
    ++*other.cnt_;
    this->cnt_ = other.cnt_;
    this->ptr_ = other.ptr_;
    return *this;
  }

  void reset(T* p) {
    if (ptr_ && --*cnt_ == 0) {
      delete cnt_;
      delete ptr_;
    }
    cnt_ = new int(1);
    ptr_ = p;
  }

  ~MySharedPtr() {
    if (ptr_ && --*cnt_ == 0) {
      delete cnt_;
      delete ptr_;
    }
  }

  int useCnt() { return *cnt_; }

 private:
  T* ptr_;
  int *cnt_;
};

} // stl
} // sakabatou_algorithm