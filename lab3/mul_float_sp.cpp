#include "TMatr.h"

using namespace std;

template<> TMatr<float> TMatr<float>::operator * (float scalar) const
{
    cout << "method" << endl;
    TMatr<float> result(numRows, numCols);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            result.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}
