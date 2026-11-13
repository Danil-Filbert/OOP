#include "TMatr_int.h"

using namespace std;

int TMatr<int>::counter = 1;

TMatr<int>::TMatr(int rows, int cols) : numRows(rows), numCols(cols)
{
    matrix = new int*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        matrix[i] = new int[numCols];
    }

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            matrix[i][j] = 0;
        }
    }
    counter++;
    id = counter;
}

TMatr<int>::TMatr(const TMatr<int> &other) : numRows(other.numRows), numCols(other.numCols)
{
    this->matrix = new int*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        this->matrix[i] = new int[numCols];
    }

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
    counter++;
    id = counter;
}

TMatr<int>::TMatr(TMatr<int> &&other) : matrix(other.matrix), numRows(other.numRows), numCols(other.numCols)
{
    other.matrix = nullptr;
    other.numRows = 0;
    other.numCols = 0;
    id = counter;
}

void TMatr<int>::resize(int newRows, int newCols)
{
    int** newMatrix = new int*[newRows];
    for(int i = 0; i < newRows; i++)
    {
        newMatrix[i] = new int[newCols];
    }

    for(int i = 0; i < newRows; i++)
    {
        for(int j = 0; j < newCols; j++)
        {
            newMatrix[i][j] = 0;
        }
    }

    for(int i = 0; i < min(newRows, numRows); i++)
    {
        for(int j = 0; j < min(newCols, numCols); j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    for(int i = 0; i < numRows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    matrix = newMatrix;
    numRows = newRows;
    numCols = newCols;
}

void TMatr<int>::input()
{
    cout << "Enter elements of the matrix:" << endl;
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            cin >> matrix[i][j];
        }
    }
}

void TMatr<int>::setValue(int row, int col, int value)
{
    if(row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        matrix[row][col] = value;
    }
    else
    {
        throw out_of_range("Error: Index out of bounds.");
    }
}

int TMatr<int>::getValue(int row, int col) const
{
    if(row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return matrix[row][col];
    }
    else
    {
        throw out_of_range("Error: Index out of bounds.");
    }
}

int TMatr<int>::getNumRows() const
{
    return numRows;
}

int TMatr<int>::getNumCols() const
{
    return numCols;
}

int TMatr<int>::getCounter()
{
    return counter;
}

int TMatr<int>::getId() const
{
    return id;
}

void TMatr<int>::outputMatrix() const
{
    cout << endl << "Matrix" << id << ":" << endl;
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void TMatr<int>::outputSubmatrix(int startRow, int startCol, int subRows, int subCols) const
{
    cout << endl << "Submatrix" << id << ":" << endl;
    for(int i = startRow; i < startRow + subRows && i < numRows; i++)
    {
        for(int j = startCol; j < startCol + subCols && j < numCols; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

TMatr<int>::~TMatr()
{
    for(int i = 0; i < numRows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    counter--;
}

void TMatr<int>::mulByScalar(int scalar)
{
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            matrix[i][j] *= scalar;
        }
    }
}

TMatr<int> TMatr<int>::addMatrix(const TMatr &other)
{
    if(this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    TMatr result(this->numRows, this->numCols);
    for(int i = 0; i < this->numRows; i++)
    {
        for(int j = 0; j < this->numCols; j++)
        {
            result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

template<int>
TMatr<int> sub(const TMatr<int> &matrix1, const TMatr<int> &matrix2)
{
    if(matrix1.numRows != matrix2.numRows || matrix1.numCols != matrix2.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for subtraction.");
    }

    TMatr<int> result(matrix1.numRows, matrix1.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix1.numCols; j++)
        {
            result.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
        }
    }
    return result;
}

TMatr<int> &TMatr<int>::operator = (const TMatr &other)
{
    this->numRows = other.numRows;
    this->numCols = other.numCols;
    delete[] this->matrix;

    this->matrix = new int*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        this->matrix[i] = new int[numCols];
    }

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
    return *this;
}

istream &operator >> (istream &in, TMatr<int> &matrix)
{
    cout << "Enter elements of the matrix:" << endl;
    for (int i = 0; i < matrix.numRows; i++)
    {
        for (int j = 0; j < matrix.numCols; j++)
        {
            in >> matrix.matrix[i][j];
        }
    }
    return in;
}

ostream &operator << (ostream &out, const TMatr<int> &matrix)
{
    out << endl << "Matrix" << matrix.id << ":" << endl;
    for(int i = 0; i < matrix.numRows; i++)
    {
        for(int j = 0; j < matrix.numCols; j++)
        {
            out << matrix.matrix[i][j] << "\t";
        }
        out << endl;
    }
    return out;
}

/*template<typename T1, typename T2>
TMatr<decltype (T1()+T2())> operator + (const TMatr<T1>& matrix1, const TMatr<T2>& matrix2)
{
    if(matrix1.numRows != matrix2.numRows || matrix1.numCols != matrix2.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    TMatr<decltype (T1()+T2())> result(matrix1.numRows, matrix1.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix1.numCols; j++)
        {
            result[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
        }
    }
    return result;
}*/

/*template<typename T1, typename T2>
TMatr<decltype (T1()-T2())> operator - (const TMatr<T1> &matrix1, const TMatr<T2> &matrix2)
{
    if(matrix1.numRows != matrix2.numRows || matrix1.numCols != matrix2.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for subtraction.");
    }

    TMatr<decltype (T1()-T2())> result(matrix1.numRows, matrix1.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix1.numCols; j++)
        {
            result[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
        }
    }
    return result;
}*/

/*template<typename T1, typename T2>
TMatr<decltype (T1()*T2())> operator * (const TMatr<T1> &matrix1, const TMatr<T2> &matrix2)
{
    if(matrix1.numCols != matrix2.numRows)
    {
        throw runtime_error("Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication.");
    }

    TMatr<decltype (T1()*T2())> result(matrix1.numRows, matrix2.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix2.numCols; j++)
        {
            for(int k = 0; k < matrix1.numCols; k++)
            {
                result[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
            }
        }
    }
    return result;
}*/

bool TMatr<int>::operator == (const TMatr &other)
{
    if(this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for comparing.");
    }

    for(int i = 0; i < this->numRows; i++)
    {
        for(int j = 0; j < this->numCols; j++)
        {
            if(this->matrix[i][j] != other.matrix[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool TMatr<int>::operator != (const TMatr &other)
{
    if(this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for comparing.");
    }

    for(int i = 0; i < this->numRows; i++)
    {
        for(int j = 0; j < this->numCols; j++)
        {
            if(this->matrix[i][j] != other.matrix[i][j])
            {
                return true;
            }
        }
    }
    return false;
}

int* TMatr<int>::operator [] (int index)
{
    if (index >= 0 && index < numRows)
    {
        return matrix[index];
    }
    else
    {
        throw out_of_range("Error: Index out of bounds.");
    }
}

TMatr<int> &TMatr<int>::operator += (const TMatr<int> &other)
{
    if (this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < this->numCols; j++)
        {
            this->matrix[i][j] += static_cast<int>(other.matrix[i][j]);
        }
    }
    return *this;
}

TMatr<int> &TMatr<int>::operator -= (const TMatr<int> &other)
{
    if (this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < this->numCols; j++)
        {
            this->matrix[i][j] -= static_cast<int>(other.matrix[i][j]);
        }
    }
    return *this;
}

TMatr<int> &TMatr<int>::operator *= (const TMatr<int> &other)
{
    if(this->numCols != other.numRows)
    {
        throw runtime_error("Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication.");
    }

    TMatr<int> result(this->numRows, other.numCols);
    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < other.numCols; j++)
        {
            for (int k = 0; k < this->numCols; k++)
            {
                result.matrix[i][j] += this->matrix[i][k] * static_cast<int>(other.matrix[k][j]);;
            }
        }
    }
    *this = result;
    return *this;
}

TMatr<int> TMatr<int>::operator * (int scalar) const
{
    cout << "full" << endl;
    TMatr<int> result(numRows, numCols);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            result.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

TMatr<int> operator * (int scalar, const TMatr<int> &other)
{
    TMatr<int> result(other.numRows, other.numCols);
    for (int i = 0; i < other.numRows; i++)
    {
        for (int j = 0; j < other.numCols; j++)
        {
            result.matrix[i][j] = other.matrix[i][j] * scalar;
        }
    }
    return result;
}

TMatr<int> &TMatr<int>::operator ++ ()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            ++matrix[i][j];
        }
    }
    return *this;
}

TMatr<int> TMatr<int>::operator ++ (int)
{
    TMatr<int> temp(*this);
    ++(*this);
    return temp;
}

TMatr<int> &TMatr<int>::operator -- ()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            --matrix[i][j];
        }
    }
    return *this;
}

TMatr<int> TMatr<int>::operator -- (int)
{
    TMatr<int> temp(*this);
    --(*this);
    return temp;
}

template<typename T>
TMatr<int>::TMatr(const TMatr<T> &other) : numRows(other.numRows), numCols(other.numCols)
{
    matrix = new int*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        matrix[i] = new int[numCols];
    }

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            matrix[i][j] = static_cast<T>(other.matrix[i][j]);
        }
    }
    counter++;
    id = counter;
}

template<typename T>
TMatr<int> &TMatr<int>::operator = (const TMatr<T>& other)
{
    for (int i = 0; i < numRows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    numRows = other.numRows;
    numCols = other.numCols;
    matrix = new int*[numRows];
    for (int i = 0; i < numRows; i++)
    {
        matrix[i] = new int[numCols];
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            matrix[i][j] = static_cast<T>(other.matrix[i][j]);
        }
    }
    counter++;
    id = counter;
    return *this;
}
