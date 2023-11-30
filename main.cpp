#include <iostream>
#include "Calculator/Calculator.cpp"

using namespace std;

int main() {
    Calculator::GetInstance()->Init();
    
    return 0;
}