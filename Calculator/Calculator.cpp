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

Calculator::Calculator() { }

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
    ShowMainMenuView();
}

void Calculator::ShowMainMenuView() {
    cout << endl;
    cout << "Meniul principal" << endl;
    cout << "- - - - - - - - -" << endl;
    cout << "0. Stinge calculatorul" << endl;
    cout << "1. Suma a 2 matrice" << endl;
    cout << "2. Produsul a 2 matrice" << endl;

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
                    ShowComputationView(0);
                    break;
                case 2:
                    ShowComputationView(1);
                    break;
                default:
                    choice = -1;
                    break;
            }
        }
        catch (invalid_argument & ex) {
            cout << "Eroare: " << ex.what() << endl;
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

    SparseMatrix<T> matrix(0, 0);

    if (!input) {
        return matrix;
    }
    
    int l, c;
    T v;

    input >> l >> c;
    matrix.SetRowsNo(l);
    matrix.SetColumnsNo(c);

    while (!input.eof()) {
        input >> l >> c >> v;
        matrix.SetValue(l, c, v);
    }

    input.close();

    return matrix;
}

void Calculator::ShowComputationView(const int operationCode) {
    string datatype;
    cout << "Tipul datelor = ";
    cin >> datatype;

    if (datatype == "int") {
        ShowComputationView2<int>(operationCode);
    }
    else if (datatype == "double") {
        ShowComputationView2<double>(operationCode);
    }
    else if (datatype == "char") {
        ShowComputationView2<char>(operationCode);
    }
    else {
        throw invalid_argument("Tipul de date cerut nu este implementat");
    }
}

template<typename T>
void Calculator::ShowComputationView2(const int operationCode) {
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
        case 0:
            result = op1 + op2;
            break;
        case 1:
            result = op1 * op2;
            break;
        default:
            throw invalid_argument("Operatia ceruta nu este implementata");
    }

    cout << endl << "op1 = " << op1 << endl << "op2 = " << op2 << endl << "result = " << result << endl;
    ShowMainMenuView();
}