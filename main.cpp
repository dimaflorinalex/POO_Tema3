#include <iostream>
#include "SparseMatrix/SparseMatrix.cpp"

using namespace std;

int main() {
    SparseMatrix<int> m23(2, 3);
    m23.SetValue(1, 1, 1);
    m23.SetValue(1, 2, 2);
    m23.SetValue(1, 3, 3);
    m23.SetValue(2, 1, 4);
    m23.SetValue(2, 2, 5);
    m23.SetValue(2, 3, 6);

    cout << "m23 = " << endl << m23 << endl;

    SparseMatrix<int> m32(3, 2);
    m32.SetValue(1, 1, 1);
    m32.SetValue(1, 2, 2);
    m32.SetValue(2, 1, 3);
    m32.SetValue(2, 2, 4);
    m32.SetValue(3, 1, 5);
    m32.SetValue(3, 2, 6);

    cout << "m32 = " << endl << m32 << endl;

    SparseMatrix<int> m22(2, 2);
    m22.SetValue(1, 1, 1);
    m22.SetValue(1, 2, 2);
    m22.SetValue(2, 1, 3);
    m22.SetValue(2, 2, 4);

    cout << "m22 = " << endl << m22 << endl;

    SparseMatrix<int> m00;
    m00 = m00 + m00;
    cout << "m00 = " << endl << m00 << endl;

    SparseMatrix<int> m23m32_m22 = m23 * m32 + m22;
    cout << "m23 * m32 + m22 = " << m23m32_m22 << endl;

    m23m32_m22 = m23m32_m22 + m23m32_m22;
    cout << "m23m32_m22 = m23m32_m22 + m23m32_m22 => " << endl << m23m32_m22 << endl;

    m23m32_m22 = 2 * m23m32_m22;
    cout << "m23m32_m22 = 2 * m23m32_m22 => " << endl << m23m32_m22 << endl;

    m23m32_m22 = m23m32_m22 * 2;
    cout << "m23m32_m22 = m23m32_m22 * 2 => " << endl << m23m32_m22 << endl;

    SparseMatrix<int> m23m32m22 = m23 * m32 * m22;
    cout << "m23 * m32 * m22 = " << m23m32m22 << endl;
    
    m23m32m22 = m23m32m22 * m23m32m22;
    cout << "m23m32m22 = m23m32m22 * m23m32m22 => " << endl << m23m32m22 << endl;

    SparseMatrix<double> m74(7, 4);
    m74.SetValue(2, 3, 42.67);
    m74.SetValue(3, 1, 9);
    m74.SetValue(4, 4, -6);
    m74.SetValue(5, 2, 7);
    m74.SetValue(6, 3, -3);

    SparseMatrix<double> m47(4, 7);
    m47.SetValue(1, 7, 109);
    m47.SetValue(2, 2, 15);
    m47.SetValue(2, 5, 49);
    m47.SetValue(3, 4, 24);

    cout << "m74 = " << endl << m74 << endl;
    cout << "m47 = " << endl << m47 << endl;

    SparseMatrix<double> m74m47 = m74 * m47;
    cout << "m74 * m47 = " << endl << m74m47 << endl;

    SparseMatrix<double> m100000_1(100000, 100000);
    m100000_1.SetValue(9214, 10248, 2914);
    cout << "m100000_1 = " << endl << m100000_1 << endl;

    SparseMatrix<double> m100000_2(100000, 100000);
    m100000_2.SetValue(10248, 9214, 86);
    cout << "m100000_2 = " << endl << m100000_2 << endl;

    cout << "m100000_1 * m100000_2 = " << endl << m100000_1 * m100000_2 << endl;
    cout << "m100000_1 + m100000_2 = " << endl << m100000_1 + m100000_2 << endl;

    return 0;
}