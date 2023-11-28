#pragma once

#include <iostream>
#include "Direction.cpp"

using namespace std;

template<typename T>
class SparseMatrix {
    private:
        int _rowsNo, _columnsNo;
        Direction<T> * _rows, * _columns;

    public:
        SparseMatrix(int const rowsNo = 0, int const columnsNo = 0) :
            _rowsNo(rowsNo),
            _columnsNo(columnsNo),
            _rows(nullptr),
            _columns(nullptr) { }

        SparseMatrix(const SparseMatrix<T> & other) :
            _rowsNo(other._rowsNo),
            _columnsNo(other._columnsNo),
            _rows(nullptr),
            _columns(nullptr) {
            Direction<T> * rowDir = other.GetRows();
            while (rowDir != nullptr) {
                Value<T> * values = rowDir->GetValues();
                while (values != nullptr) {
                    this->SetValue(rowDir->GetIndex(), values->GetIndex(), values->GetValue());
                    values = values->GetNext();
                }

                rowDir = rowDir->GetNext();
            }
        }

        ~SparseMatrix() {
            Direction<T> * oldRows = nullptr;
            Direction<T> * rows = this->_rows;

            while (rows != nullptr) {
                oldRows = rows;
                rows = rows->GetNext();
                delete oldRows;
            }

            Direction<T> * oldColumns = nullptr;
            Direction<T> * columns = this->_columns;

            while (columns != nullptr) {
                oldColumns = columns;
                columns = columns->GetNext();
                delete oldColumns;
            }
        }

        int GetRowsNo() const {
            return this->_rowsNo;
        }

        void SetRowsNo(int const value) {
            if (value < this->_rowsNo) {
                Direction<T> * rowDir = this->_rows;
                while (rowDir != nullptr && rowDir->GetIndex() <= value) {
                    rowDir = rowDir->GetNext();
                }

                if (rowDir != nullptr) {
                    return;
                }
            }

            this->_rowsNo = value;
        }

        int GetColumnsNo() const {
            return this->_columnsNo;
        }

        void SetColumnsNo(int const value) {
            if (value < this->_columnsNo) {
                Direction<T> * colDir = this->_columns;
                while (colDir != nullptr && colDir->GetIndex() <= value) {
                    colDir = colDir->GetNext();
                }

                if (colDir != nullptr) {
                    return;
                }
            }

            this->_columnsNo = value;
        }

        Direction<T> * GetRows() const {
            return this->_rows;
        }

        Direction<T> * GetColumns() const {
            return this->_columns;
        }

        T GetValue(int const row, int const column) const {
            Direction<T> * rowsDir = this->_rows;

            while (rowsDir != nullptr && rowsDir->GetIndex() != row) {
                rowsDir = rowsDir->GetNext();
            }

            if (rowsDir != nullptr) {
                return rowsDir->GetValue(column);
            }

            return 0;
        }

        void SetValue(int const row, int const column, T const value = 0) {
            if (row > this->_rowsNo || column > this->_columnsNo) {
                return;
            }

            if (this->_rows == nullptr && this->_columns == nullptr && value != 0) {
                this->_rows = new Direction<T>(row, new Value<T>(column, value));
                this->_columns = new Direction<T>(column, new Value<T>(row, value));
            }
            else {
                Direction<T> * oldRowDir = nullptr;
                Direction<T> * rowDir = this->_rows;
                while (rowDir != nullptr && rowDir->GetIndex() != row) {
                    oldRowDir = rowDir;
                    rowDir = rowDir->GetNext();
                }

                if (rowDir != nullptr) {
                    rowDir->SetValue(column, value);
                    if (rowDir->GetValues() == nullptr) {
                        if (oldRowDir == nullptr) {
                            this->_rows = rowDir->GetNext();
                        }
                        else {
                            oldRowDir->SetNext(rowDir->GetNext());
                        }
                        delete rowDir;
                    }
                }
                else {
                    rowDir = new Direction<T>(row, new Value<T>(column, value)); 
                    if (oldRowDir != nullptr) {
                        oldRowDir->SetNext(rowDir);
                    }
                }

                Direction<T> * oldColDir = nullptr;
                Direction<T> * colDir = this->_columns;
                while (colDir != nullptr && colDir->GetIndex() != column) {
                    oldColDir = colDir;
                    colDir = colDir->GetNext();
                }

                if (colDir != nullptr) {
                    colDir->SetValue(row, value);
                    if (colDir->GetValues() == nullptr) {
                        if (oldColDir == nullptr) {
                            this->_columns = colDir->GetNext();
                        }
                        else {
                            oldColDir->SetNext(colDir->GetNext());
                        }
                        delete colDir;
                    }
                }
                else {
                    colDir = new Direction<T>(column, new Value<T>(row, value)); 
                    if (oldColDir != nullptr) {
                        oldColDir->SetNext(colDir);
                    }
                }
            }
        }

        SparseMatrix<T> & operator=(const SparseMatrix<T> & other) {
            if (this != &other) {
                this->_columnsNo = other.GetColumnsNo();
                this->_rowsNo = other.GetRowsNo();
                
                delete this->_rows;
                delete this->_columns;

                this->_rows = nullptr;
                this->_columns = nullptr;

                Direction<T> * rowDir = other.GetRows();
                while (rowDir != nullptr) {
                    Value<T> * values = rowDir->GetValues();
                    while (values != nullptr) {
                        this->SetValue(rowDir->GetIndex(), values->GetIndex(), values->GetValue());
                        values = values->GetNext();
                    }
                    rowDir = rowDir->GetNext();
                }
            }

            return *this;
        }

        SparseMatrix<T> operator+(const SparseMatrix<T> & rhs) {
            if (this->_rowsNo != rhs.GetRowsNo() || this->_columnsNo != rhs.GetColumnsNo()) {
                SparseMatrix<T> blankResult(0, 0);
                return blankResult;
            }

            SparseMatrix<T> result(this->_rowsNo, this->_columnsNo);
            
            Direction<T> * rowDir = nullptr;

            rowDir = this->_rows;
            while (rowDir != nullptr) {
                Value<T> * values = rowDir->GetValues();
                while (values != nullptr) {
                    result.SetValue(rowDir->GetIndex(), values->GetIndex(), values->GetValue());
                    values = values->GetNext();
                }
                rowDir = rowDir->GetNext();
            }

            rowDir = rhs.GetRows();
            while (rowDir != nullptr) {
                Value<T> * values = rowDir->GetValues();
                while (values != nullptr) {
                    result.SetValue(rowDir->GetIndex(), values->GetIndex(), result.GetValue(rowDir->GetIndex(), values->GetIndex()) + values->GetValue());
                    values = values->GetNext();
                }
                rowDir = rowDir->GetNext();
            }

            return result;
        }

        friend SparseMatrix<T> operator-(const SparseMatrix<T> & matrix) {
            SparseMatrix<T> result(matrix.GetRowsNo(), matrix.GetColumnsNo());
            
            Direction<T> * rowDir = nullptr;
            rowDir = matrix.GetRows();
            while (rowDir != nullptr) {
                Value<T> * values = rowDir->GetValues();
                while (values != nullptr) {
                    result.SetValue(rowDir->GetIndex(), values->GetIndex(), -values->GetValue());
                    values = values->GetNext();
                }
                rowDir = rowDir->GetNext();
            }

            return result;
        }

        SparseMatrix<T> operator-(const SparseMatrix<T> rhs) {
            SparseMatrix<T> result = *this + -rhs;

            return result;
        }

        friend SparseMatrix<T> operator*(const SparseMatrix<T> & lhs, const SparseMatrix<T> & rhs) {
            if (lhs.GetColumnsNo() != rhs.GetRowsNo()) {
                SparseMatrix<T> blankResult(0, 0);
                return blankResult;
            }

            SparseMatrix<T> result(lhs.GetRowsNo(), rhs.GetColumnsNo());

            Direction<T> * rowDir = lhs.GetRows();
            while (rowDir != nullptr) {
                Value<T> * valRow = rowDir->GetValues();
                while (valRow != nullptr) {
                    Direction<T> * colDir = rhs.GetColumns();
                    while (colDir != nullptr) {
                        Value<T> * valCol = colDir->GetValues();
                        while (valCol != nullptr) {
                            if (valRow->GetIndex() == valCol->GetIndex()) {
                                result.SetValue(rowDir->GetIndex(), colDir->GetIndex(), result.GetValue(rowDir->GetIndex(), colDir->GetIndex()) + valRow->GetValue() * valCol->GetValue());
                            }
                            valCol = valCol->GetNext();
                        }
                        colDir = colDir->GetNext();
                    }
                    valRow = valRow->GetNext();
                }
                rowDir = rowDir->GetNext();
            }

            return result;
        }

        friend SparseMatrix<T> operator*(const SparseMatrix<T> & lhs, const T rhs) {
            if (rhs == 0) {
                SparseMatrix<T> blankResult(lhs.GetRowsNo(), lhs.GetColumnsNo());
                return blankResult;
            }

            SparseMatrix<T> result(lhs.GetRowsNo(), lhs.GetColumnsNo());

            Direction<T> * rowDir = nullptr;
            rowDir = lhs.GetRows();
            while (rowDir != nullptr) {
                Value<T> * values = rowDir->GetValues();
                while (values != nullptr) {
                    result.SetValue(rowDir->GetIndex(), values->GetIndex(), rhs * values->GetValue());
                    values = values->GetNext();
                }
                rowDir = rowDir->GetNext();
            }

            return result;
        }

        friend SparseMatrix<T> operator*(const T lhs, const SparseMatrix<T> & rhs) {
            return rhs * lhs;
        }

        friend ostream & operator<<(ostream & os, const SparseMatrix<T> & matrix) {
            os << "Matrice rara (" << matrix.GetRowsNo() << " linii x " << matrix.GetColumnsNo() << " coloane) - Elemente (LCV):" << endl;
            Direction<T> * rowDir = matrix.GetRows();
            while (rowDir != nullptr) {
                Value<T> * values = rowDir->GetValues();
                while (values != nullptr) {
                    os << rowDir->GetIndex() << " " << values->GetIndex() << " " << values->GetValue() << endl;
                    values = values->GetNext();
                }
                rowDir = rowDir->GetNext();
            }

            return os;
        }
};