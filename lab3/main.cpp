#include <iostream>
#include "TMatr.h"
#include "TMatr.cpp"
#include "TMatr_int.h"
#include "TMatr_int.cpp"
#include "TMatr_part.h"
#include "TMatr_part.cpp"
#include "mul_float_sp.cpp"

using namespace std;

int main()
{
    //Шаблон
    TMatr<long> matrix1(2,2);
    TMatr<float> matrix2(2,2);
    TMatr<int> matrix3(2,2);
    TMatr<int*> matrix4(2,2);
    TMatr<float*> matrix5(2,2);
    TMatr<long> matrix6(2,2);

    /*TMatr<double> matrix3;
    matrix3 = matrix1;*/

    //TMatr<double> matrix3 = matrix1;

    //TMatr<double> matrix3 = matrix1 + matrix2;
    //TMatr<double> matrix3 = matrix2 - matrix1;
    //TMatr<double> matrix3 = matrix1 * matrix2;

    //matrix1 += matrix2;
    //matrix2 -= matrix1;
    //matrix1 *= matrix2;

    cout << matrix1.getCounter() << endl;
    cout << matrix2.getCounter() << endl;
    cout << matrix3.getCounter() << endl;
    cout << matrix4.getCounter() << endl;
    cout << matrix5.getCounter() << endl;

    //cout << matrix1;
    //cout << matrix2;
    //cout << matrix3;

    //Полная специализация
    //TMatr<int> matrix1(2,2);
    //TMatr<double> matrix2(2,2);

    //cin >> matrix1;
    //cin >> matrix2;

    /*TMatr<double> matrix3;
    matrix3 = matrix1;*/

    //TMatr<double> matrix3 = matrix1;

    //TMatr<int> matrix3 = matrix1 + matrix2;
    //TMatr<double> matrix3 = matrix2 - matrix1;
    //TMatr<double> matrix3 = matrix1 * matrix2;

    //matrix1 += matrix2;
    //matrix2 -= matrix1;
    //matrix1 *= matrix2;

    //TMatr<float> matrix3 = matrix1 * 2.1;

    //cout << matrix1;
    //cout << matrix2;
    //cout << matrix3;

    //Частичная специализация
    //TMatr<int*> matrix1(2,2);
    //TMatr<double*> matrix2(2,2);

    //cin >> matrix1;
    //cin >> matrix2;

    /*TMatr<double*> matrix3;
    matrix3 = matrix1;*/

    //TMatr<double*> matrix3 = matrix1;

    //TMatr<double*> matrix3 = matrix1 + matrix2;
    //TMatr<double> matrix3 = matrix2 - matrix1;
    //TMatr<double> matrix3 = matrix1 * matrix2;

    //matrix1 += matrix2;
    //matrix2 -= matrix1;
    //matrix1 *= matrix2;

    //TMatr<float> matrix3 = matrix1 * 2.1;

    //cout << matrix1;
    //cout << matrix2;
    //cout << matrix3;

    return 0;
}
