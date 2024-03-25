#ifndef HEADER_GUARD_STACK_HPP_INCLUDED
#define HEADER_GUARD_STACK_HPP_INCLUDED

#pragma once
#include <cstdint>
#include <algorithm>

#include "utils.hpp"


namespace stack
{
	template <typename data_t>
	class Stack
	{
		private:
			data_t *data_;
			size_t size_;

			bool ok() const 
			{
				if (data_ == nullptr)
		        {
		            return false;
		        }
        		return true;
			}

			friend void swap(Stack& lvalue, Stack& rvalue)
			{
				VERIFY_CONTRACT(!lvalue.empty() && !rvalue.empty() &&
				                lvalue.ok() && rvalue.ok(),
				                "Unable to perform swap command");
				std::swap(lvalue.data_, rvalue.data_);
				std::swap(lvalue.size_, rvalue.size_);
			}
		public:
			// Member functions
			Stack();
	        Stack(size_t size);

			Stack(const Stack& other);
			Stack(Stack&& temporary);

			~Stack();

			Stack& operator=(const Stack& other);
			Stack& operator=(Stack&& temporary);

			// Element access
			data_t& top() const;

			// Capacity
			size_t size() const;
			bool empty() const;

			// Modifiers
			void push(const data_t& value);
			void push(data_t&& temporary_value);

			void emplace(const data_t& value);
			void emplace(data_t&& temporary_value);

            void pop();
	};

	template <typename data_t>
    Stack<data_t>::Stack() : 
        data_ (new data_t[1]), 
        size_ (1) 
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to construct Stack instance");
    }

    template <typename data_t>
    Stack<data_t>::Stack(size_t size) : 
        data_ (new data_t[size]), 
        size_ (size)
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to construct Stack instance");
    }

    // Copy constructor
    template <typename data_t>
    Stack<data_t>::Stack(const Stack<data_t>& other)
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to construct Stack instance from invalid source");

        data_ = new data_t[other.size_];
        size_ = other.size_;

        std::copy_n(other.data_, size_, data_);

        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to construct Stack instance");
    }

    // Move constructor
    template <typename data_t>
    Stack<data_t>::Stack(Stack<data_t>&& temporary)
    {
        VERIFY_CONTRACT(!temporary.empty() && temporary.ok(), 
                "Unable to construct Stack instance from invalid source");

        data_ = temporary.data_;
        size_ = temporary.size_;

        temporary.data_ = nullptr;
        temporary.size_ = (size_t) 0;

        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to construct Stack instance");
        VERIFY_CONTRACT(temporary.empty() && !temporary.ok(), 
                "Move operation is non-destructive for move origin");
    }

    template <typename data_t>
    Stack<data_t>::~Stack()
    {
        if (data_ != nullptr) 
        {
            delete[] data_;
        }

        data_ = nullptr;
    }

    // Copy assignment
    template <typename data_t>
    Stack<data_t>& Stack<data_t>::operator=(const Stack<data_t>& other)
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Invalid lvalue for the copy assignment");
        VERIFY_CONTRACT(!other.empty() && other.ok(), 
                "Invalid rvalue for the copy assignment");

        if (this == &other) {
            return *this;
        }

        delete[] data_;

        data_ = new data_t[other.size_];
        size_ = other.size_;

        std::copy_n(other.data_, size_, data_);

        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to perform copy assignment");

        return *this;
    }

    // Move assignment
    template <typename data_t>
    Stack<data_t>& Stack<data_t>::operator=(Stack<data_t>&& temporary)
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Invalid lvalue for the copy assignment");
        VERIFY_CONTRACT(!temporary.empty() && temporary.ok(), 
                "Invalid rvalue for the copy assignment");

        delete[] data_;

        data_ = temporary.data_;
        size_ = temporary.size_;

        temporary.data_ = nullptr;
        temporary.size_ = (size_t) 0;

        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to perform move assignment");
        VERIFY_CONTRACT(temporary.empty() && !temporary.ok(), 
                "Move operation is non-destructive for move origin");

        return *this;
    }

    template <typename data_t>
    data_t& Stack<data_t>::top() const
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to perform top command");
        return data_[size_ - 1];
    }

    template <typename data_t>
    size_t Stack<data_t>::size() const
    {
        VERIFY_CONTRACT(this->ok() && !this->empty(), 
                "Invalid vector data");
        return size_;
    }

    template <typename data_t>
    bool Stack<data_t>::empty() const
    {
        return size_ == (size_t) 0;
    }

    template <typename data_t>
    void Stack<data_t>::push(const data_t& value)
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to perform push command");
        data_[size_ - 1] = value;
    }

    template <typename data_t>
    void Stack<data_t>::push(data_t&& temporary_value)
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(), 
                "Unable to perform push command");
        data_[size_ - 1] = std::move(temporary_value);
    }

    template <typename data_t>
    void Stack<data_t>::emplace(const data_t& value) {
        data_t *data_new = new data_t[size_ + 1];
        VERIFY_CONTRACT(data_new != nullptr, 
                "Unable to perform emplace command");
        
        for (uint64_t i = 0; i < size_; ++i) {
            data_new[i] = std::move(data_[i]);
        }

        delete[] data_;

        data_ = data_new;
        ++size_;

        push(value);
    }

    template <typename data_t>
    void Stack<data_t>::emplace(data_t&& temporary_value) {
        data_t *data_new = new data_t[size_ + 1];
        VERIFY_CONTRACT(data_new != nullptr, 
                "Unable to perform emplace command");
        
        for (uint64_t i = 0; i < size_; ++i) {
            data_new[i] = std::move(data_[i]);
        }

        delete[] data_;

        data_ = data_new;
        ++size_;

        push(temporary_value);
    }

    template <typename data_t>
    void Stack<data_t>::pop()
    {
        VERIFY_CONTRACT(!Stack::empty() && this->ok(),
                "Unable to perform pop command");
        --size_;
    }
} // namespace stack

#endif // HEADER_GUARD_STACK_HPP_INCLUDED