#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <exception>
#include "Calculator.hpp"
#include "../SparseMatrix/SparseMatrix.cpp"

const string Calculator::FOLDER_PATH = "Inputs/";
const string Calculator::FILE_EXTENSION = ".smc";
const string Calculator::FILE_DELIMITER = " ";

Calculator::Calculator(const string stateDataType) : _stateDataType(stateDataType) { }

Calculator * Calculator::instance = nullptr;

Calculator * Calculator::GetInstance() {
    if (instance == nullptr){
        instance = new Calculator();
    }

    return instance;
}

void Calculator::Init() {
    ShowOpeningView();
}

void Calculator::ShowOpeningView() {
    cout << "Calculatorul se aprinde..." << endl;
    cout << "Tipul de date setat = " << this->_stateDataType << endl;
    ShowMainMenuView();
}

void Calculator::ShowMainMenuView() {
    cout << endl;
    cout << "Meniul principal" << endl;
    cout << "- - - - - - - - -" << endl;
    cout << "0. Stinge calculatorul" << endl;
    cout << "1. Seteaza tipul de date folosit" << endl;
    cout << "2. Suma a 2 matrice" << endl;
    cout << "3. Produsul a 2 matrice" << endl;

    int choice;

    do {
        cout << "Alegeti o optiune valida: " << endl;
        cin >> choice;

        try {
            switch(choice) {
                case 0:
                    ShowClosingView();
                    break;
                case 1:
                    ShowChangeStateDataTypeView();
                    break;
                case 2:
                case 3: {
                    int operationCode = 0;
                    if (choice == 2) operationCode = 1;
                    else if (choice == 3) operationCode = 2;

                    if (_stateDataType == "int") ShowComputationView<int>(operationCode);
                    else if (_stateDataType == "double") ShowComputationView<double>(operationCode);
                    else if (_stateDataType == "uchar") ShowComputationView<unsigned char>(operationCode);
                    else throw invalid_argument("Tipul de date selectat nu este implementat");
                    break;
                }
                default:
                    choice = -1;
                    break;
            }
        }
        catch (invalid_argument & ex) {
            cout << "Eroare: " << ex.what() << endl << endl;
            choice = -1;
        }
        
    } while (choice == -1);
}

void Calculator::ShowClosingView() {
    cout << endl;
    cout << "Calculatorul se stinge..." << endl;
}

template<typename T>
SparseMatrix<T> Calculator::ReadFile(const string & filename) const {
    string filepath = "";
    string path = __FILE__;
    path = path.substr(0, 1 + path.find_last_of('\\'));
    filepath.append(path);
    filepath.append(Calculator::FOLDER_PATH);
    filepath.append(filename);
    filepath.append(Calculator::FILE_EXTENSION);

    ifstream input;
    input.open(filepath);

    SparseMatrix<T> matrix;

    if (!input) {
        return matrix;
    }
    
    int l, c;
    double v;

    input >> l >> c;
    matrix.SetRowsNo(l);
    matrix.SetColumnsNo(c);

    while (!input.eof()) {
        input >> l >> c >> v;
        matrix.SetValue(l, c, (T)v);
    }

    input.close();

    return matrix;
}

void Calculator::ShowChangeStateDataTypeView() {
    cout << endl << "Tipul de date curent = " << this->_stateDataType << endl;
    cout << "Seteaza alt tip de date (int, double, uchar) = ";
    string datatype;
    cin >> datatype;

    if (datatype == "int" || datatype == "double" || datatype == "uchar") {
        _stateDataType = datatype;
    }
    else {
        throw invalid_argument("Tipul de date cerut nu este implementat");
    }

    cout << "Noul tip de date a fost actualizat = " << _stateDataType << endl;

    ShowMainMenuView();
}

template<typename T>
void Calculator::ShowComputationView(const int operationCode) {
    string fisier1;
    cout << "Nume fisier 1 = ";
    cin >> fisier1;

    string fisier2;
    cout << "Nume fisier 2 = ";
    cin >> fisier2;

    SparseMatrix<T> op1 = ReadFile<T>(fisier1);
    SparseMatrix<T> op2 = ReadFile<T>(fisier2);

    SparseMatrix<T> result;

    switch (operationCode) {
        case 1:
            result = op1 + op2;
            break;
        case 2:
            result = op1 * op2;
            break;
        default:
            throw invalid_argument("Operatia ceruta nu este implementata");
            break;
    }

    cout << endl << "op1 = " << op1 << endl << "op2 = " << op2 << endl << "result = " << result << endl;
    ShowMainMenuView();
}