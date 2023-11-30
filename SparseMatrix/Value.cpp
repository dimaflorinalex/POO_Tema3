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
            _next(next) {
                this->SetValue(value);
            }
        
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

        ~Value() { };
};

template<>
void Value<unsigned char>::SetValue(unsigned char const value) {
    unsigned char normalizedValue = value;
    if (value < 'a' || value > 'z') {
        normalizedValue = 'a' + normalizedValue % ('z' - 'a');
    }

    this->_value = normalizedValue;
}