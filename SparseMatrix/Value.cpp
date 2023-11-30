#pragma once

#include <iostream>

template<typename T>
class Value {
    private:
        int _index;
        T _value;
        Value<T> * _next;

    public:
        Value(int const index = 0, T const value = 0, Value<T> * const next = nullptr) :
            _index(index),
            _value(value),
            _next(next) { }
        
        int GetIndex() {
            return this->_index;
        }

        void SetIndex(int const index) {
            this->_index = index;
        }

        T GetValue() {
            return this->_value;
        }

        void SetValue(T const value) {
            this->_value = value;
        }

        Value<T> * GetNext() {
            return this->_next;
        }
        
        void SetNext(Value<T> * const next) {
            this->_next = next;
        }
};

template<>
class Value<char> {
    private:
        int _index;
        char _value;
        Value<char> * _next;

    public:
        Value(int const index = 0, char const value = '\0', Value<char> * const next = nullptr) :
            _index(index),
            _value(value),
            _next(next) { }
        
        int GetIndex() {
            return this->_index;
        }

        void SetIndex(int const index) {
            this->_index = index;
        }

        char GetValue() {
            return this->_value;
        }

        void SetValue(char const value) {
            char normalizedValue = 'a' + value % ('z' - 'a');
            this->_value = normalizedValue;
        }

        Value<char> * GetNext() {
            return this->_next;
        }
        
        void SetNext(Value<char> * const next) {
            this->_next = next;
        }
};