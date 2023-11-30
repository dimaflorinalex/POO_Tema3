#pragma once

#include <iostream>
#include <list>
#include "../SparseMatrix/SparseMatrix.cpp"

using namespace std;

class Calculator {
    private:
        const static string FOLDER_PATH;
        const static string FILE_EXTENSION;
        const static string FILE_DELIMITER;
        
        static Calculator * instance;
        string _stateDataType;

        Calculator(const string stateDataType = "int");

        void ShowOpeningView();
        void ShowMainMenuView();
        void ShowClosingView();
        void ShowChangeStateDataTypeView();
        template<typename T> void ShowComputationView(const int operationCode);
        template<typename T> SparseMatrix<T> ReadFile(const string & filename) const;

    public:
        Calculator(Calculator & other) = delete;
        void operator=(const Calculator & other) = delete;
        static Calculator * GetInstance();
        void Init();
};