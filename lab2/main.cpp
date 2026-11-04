#include <iostream>
#include "TMatr.h"

using namespace std;

int main()
{
    TMatr matrix1(2,2);
    TMatr matrix2(2,2);
    //TMatr matrix3(2,2);

    cin >> matrix1;
    cin >> matrix2;
    //cin >> matrix3;

    try
    {
        //TMatr matrix3 = matrix1 + matrix2;
        //TMatr matrix3 = matrix2 - matrix1;
        //TMatr matrix3 = matrix1 * matrix2;

        //matrix3 = matrix2 = matrix1;

        //bool result = matrix1 == matrix2;
        //bool result = matrix1 != matrix2;
        //cout << endl << result << endl;

        //matrix1 += matrix2;
        //matrix2 -= matrix1;
        //matrix1 *= matrix2;

        //TMatr matrix3 = matrix1 * 2;
        //TMatr matrix3 = 2 * matrix1;

        //TMatr matrix3 = ++matrix1;
        //TMatr matrix3 = matrix1++;
        //TMatr matrix3 = --matrix1;
        //TMatr matrix3 = matrix1--;

        //cout << matrix1;
        //cout << matrix2;
        //cout << matrix3;
    }
    catch (const runtime_error &error)
    {
        cout << endl << error.what() << endl;
    }

    try
    {
        //matrix1[0][0] = 5;
        //cout << matrix1;

        //int value = matrix1[1][1];
        //cout << endl << value << endl;
    }
    catch (const out_of_range &error)
    {
        cout << endl << error.what() << endl;
    }
}
