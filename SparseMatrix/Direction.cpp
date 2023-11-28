#pragma once

#include <iostream>
#include "Value.cpp"

template<typename T>
class Direction {
    private:
        int _index;
        Value<T> * _values;
        Direction<T> * _next;
    public:
        Direction(int const index = 0, Value<T> * const values = nullptr, Direction<T> * const next = nullptr) :
            _index(index),
            _values(values),
            _next(next) { }

        ~Direction() {
            Value<T> * oldValues = nullptr;
            Value<T> * values = this->_values;

            while (values != nullptr) {
                oldValues = values;
                values = values->GetNext();
                delete oldValues;
            }
        }

        int GetIndex() {
            return this->_index;
        }

        void SetIndex(int const index) {
            this->_index = index;
        }

        Direction<T> * GetNext() {
            return this->_next;
        }

        void SetNext(Direction<T> * const next) {
            this->_next = next;
        }

        Value<T> * GetValues() {
            return this->_values;
        }

        T GetValue(int const index) {
            Value<T> * valptr = this->_values;
    
            while (valptr != nullptr && valptr->GetIndex() != index) {
                valptr = valptr->GetNext();
            }

            if (valptr != nullptr) {
                return valptr->GetValue();
            }

            return 0;
        }

        void SetValue(int const index, T const value = 0) {
            if (value == 0) {
                Value<T> * oldValptr = nullptr;
                Value<T> * valptr = this->_values;

                while (valptr != nullptr && valptr->GetIndex() != index) {
                    oldValptr = valptr;
                    valptr = valptr->GetNext();
                }

                if (valptr != nullptr) {
                    if (oldValptr == nullptr) {
                        this->_values = valptr->GetNext();
                    }
                    else {
                        oldValptr->SetNext(valptr->GetNext());
                    }
                    delete valptr;
                }
            }
            else {
                Value<T> * oldValptr = nullptr;
                Value<T> * valptr = this->_values;

                while (valptr != nullptr && valptr->GetIndex() != index) {
                    oldValptr = valptr;
                    valptr = valptr->GetNext();
                }

                if (valptr == nullptr) {
                    valptr = new Value<T>(index, value);

                    if (oldValptr != nullptr) {
                        oldValptr->SetNext(valptr);
                    }
                }
                else {
                    valptr->SetIndex(index);
                    valptr->SetValue(value);
                }
            }
        }
};