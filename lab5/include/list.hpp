#pragma once

#include <memory_resource>
#include <iterator>
#include <initializer_list>
#include <concepts>
#include <memory>

template<typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
    requires std::is_default_constructible_v<T> && std::is_same_v<Allocator, std::pmr::polymorphic_allocator<T>>
class List {
private:
    class Node {
    public:
        T value_;
        Node* prev_;
        Node* next_;

        explicit Node(const T& value) : value_(value), prev_(nullptr), next_(nullptr) {}
    };

    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    using NodeAllocatorTraits = std::allocator_traits<NodeAllocator>;

public:
    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        ListIterator& operator++() {
            node_ = node_->next_;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reference operator*() const {
            return node_->value_;
        }

        pointer operator->() const {
            return &node_->value_;
        }

        bool operator==(const ListIterator& other) const {
            return node_ == other.node_;
        }

        bool operator!=(const ListIterator& other) const {
            return node_ != other.node_;
        }

    private:
        Node* node_;
        explicit ListIterator(Node* node) : node_(node) {}

        friend class List;
    };

    List(std::pmr::memory_resource* mr = std::pmr::get_default_resource()) : alloc_(mr), head_(nullptr), tail_(nullptr), sz_(0) {}

    List(size_t sz, std::pmr::memory_resource* mr = std::pmr::get_default_resource()) : List(mr) {
        for (size_t i = 0; i < sz; ++i) {
            this->PushBack(T());
        }
    }

    List(const std::initializer_list<T>& items, std::pmr::memory_resource* mr = std::pmr::get_default_resource()) : List(mr) {
        for (auto& item : items) {
            this->PushBack(item);
        }
    }

    List(const List& other) : List(other.alloc_.resource()) {
        for (auto item = other.begin(); item != other.end(); ++item) {
            this->PushBack(*item);
        }
    }

    List(List&& other) noexcept : alloc_(std::move(other.alloc_)), head_(other.head_), tail_(other.tail_), sz_(other.sz_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.sz_ = 0;
    }

    ~List() {
        while (head_) {
            Node* next = head_->next_;
            NodeAllocatorTraits::destroy(alloc_, head_);
            NodeAllocatorTraits::deallocate(alloc_, head_, 1);
            head_ = next;
        }
    }

    ListIterator begin() const noexcept {
        return ListIterator(head_);
    }

    ListIterator end() const noexcept {
        return ListIterator(nullptr);
    }

    T& Front() const {
        return head_->value_;
    }

    T& Back() const {
        return tail_->value_;
    }

    bool IsEmpty() const noexcept {
        return head_ == nullptr;
    }

    size_t Size() const noexcept {
        return sz_;
    }

    ListIterator Find(const T& value) const {
        if (this->IsEmpty()) {
            return this->end();
        }
        for (auto item = this->begin(); item != this->end(); ++item) {
            if (*item == value) {
                return item;
            }
        }
        return this->end();
    }

    void Erase(ListIterator pos) {
        Node* cur_node = pos.node_;
        if (this->IsEmpty()) {
            return;
        } else if (cur_node == head_) {
            this->PopFront();
        } else if (cur_node == tail_) {
            this->PopBack();
        } else {
            Node* next = cur_node->next_;
            Node* prev = cur_node->prev_;
            NodeAllocatorTraits::destroy(alloc_, cur_node);
            NodeAllocatorTraits::deallocate(alloc_, cur_node, 1);

            next->prev_ = prev;
            prev->next_ = next;
            sz_--;
        }
    }

    void Insert(ListIterator pos, const T& value) {
        Node* cur_node = pos.node_;
        if (cur_node == head_) {
            this->PushFront(value);
        } else {
            Node* new_node = NodeAllocatorTraits::allocate(alloc_, 1);
            NodeAllocatorTraits::construct(alloc_, new_node, value);
            new_node->prev_ = cur_node->prev_;
            new_node->next_ = cur_node;
            cur_node->prev_->next_ = new_node;
            cur_node->prev_ = new_node;
            sz_++;
        }
    }

    void PushBack(const T& value) {
        Node* new_node = NodeAllocatorTraits::allocate(alloc_, 1);
        NodeAllocatorTraits::construct(alloc_, new_node, value);
        if (tail_) {
            tail_->next_ = new_node;
            new_node->prev_ = tail_;
            tail_ = new_node;
        } else {
            head_ = tail_ = new_node;
        }
        ++sz_;
    }

    void PushFront(const T& value) {
        Node* new_node = NodeAllocatorTraits::allocate(alloc_, 1);
        NodeAllocatorTraits::construct(alloc_, new_node, value);
        if (head_) {
            head_->prev_ = new_node;
            new_node->next_ = head_;
            head_ = new_node;
        } else {
            head_ = tail_ = new_node;
        }
        ++sz_;
    }

    void PopBack() {
        if (this->IsEmpty()) {
            return;
        } else if (head_ == tail_) {
            NodeAllocatorTraits::destroy(alloc_, tail_);
            NodeAllocatorTraits::deallocate(alloc_, tail_, 1);
            head_ = tail_ = nullptr;
        } else {
            Node* tmp = tail_->prev_;
            tmp->next_ = nullptr;
            NodeAllocatorTraits::destroy(alloc_, tail_);
            NodeAllocatorTraits::deallocate(alloc_, tail_, 1);
            tail_ = tmp;
        }
        --sz_;
    }

    void PopFront() {
        if (this->IsEmpty()) {
            return;
        } else if (head_ == tail_) {
            NodeAllocatorTraits::destroy(alloc_, tail_);
            NodeAllocatorTraits::deallocate(alloc_, tail_, 1);
            head_ = tail_ = nullptr;
        } else {
            Node* tmp = head_->next_;
            tmp->prev_ = nullptr;
            NodeAllocatorTraits::destroy(alloc_, head_);
            NodeAllocatorTraits::deallocate(alloc_, head_, 1);
            head_ = tmp;
        }
        --sz_;
    }

private:
    NodeAllocator alloc_;
    Node* tail_;
    Node* head_;
    size_t sz_;
};