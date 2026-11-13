#include <iostream>
#include "TMatr.h"

using namespace std;

template<typename T>
int TMatr<T>::counter = 0;

template<typename T>
TMatr<T>::TMatr(int rows, int cols) : numRows(rows), numCols(cols)
{
    matrix = new T*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        matrix[i] = new T[numCols];
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

template<typename T>
TMatr<T>::TMatr(const TMatr &other) : numRows(other.numRows), numCols(other.numCols)
{
    this->matrix = new T*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        this->matrix[i] = new T[numCols];
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

template<typename T>
TMatr<T>::TMatr(TMatr &&other) : matrix(other.matrix), numRows(other.numRows), numCols(other.numCols)
{
    other.matrix = nullptr;
    other.numRows = 0;
    other.numCols = 0;
    id = counter;
}

template<typename T>
template<typename T1>
TMatr<T>::TMatr(TMatr<T1>&& other) : numRows(other.numRows), numCols(other.numCols), matrix(nullptr)
{
    matrix = new T*[numRows];
    for (int i = 0; i < numRows; ++i)
    {
        matrix[i] = new T[numCols];
    }

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            matrix[i][j] = static_cast<T>(other.matrix[i][j]);
        }
    }

    for (int i = 0; i < other.numRows; ++i)
    {
        delete[] other.matrix[i];
    }
    delete[] other.matrix;

    id = counter;
}

template<typename T>
void TMatr<T>::resize(int newRows, int newCols)
{
    T** newMatrix = new T*[newRows];
    for(int i = 0; i < newRows; i++)
    {
        newMatrix[i] = new T[newCols];
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

template<typename T>
void TMatr<T>::input()
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

template<typename T>
void TMatr<T>::setValue(int row, int col, T value)
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

template<typename T>
T TMatr<T>::getValue(int row, int col) const
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

template<typename T>
int TMatr<T>::getNumRows() const
{
    return numRows;
}

template<typename T>
int TMatr<T>::getNumCols() const
{
    return numCols;
}

template<typename T>
int TMatr<T>::getCounter()
{
    return counter;
}

template<typename T>
int TMatr<T>::getId() const
{
    return id;
}

template<typename T>
void TMatr<T>::outputMatrix() const
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

template<typename T>
void TMatr<T>::outputSubmatrix(int startRow, int startCol, int subRows, int subCols) const
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

template<typename T>
TMatr<T>::~TMatr()
{
    for(int i = 0; i < numRows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    counter--;
}

template<typename T>
void TMatr<T>::mulByScalar(T scalar)
{
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            matrix[i][j] *= scalar;
        }
    }
}

template<typename T>
TMatr<T> TMatr<T>::addMatrix(const TMatr &other)
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

template<typename T>
TMatr<T> sub(const TMatr<T> &matrix1, const TMatr<T> &matrix2)
{
    if(matrix1.numRows != matrix2.numRows || matrix1.numCols != matrix2.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for subtraction.");
    }

    TMatr<T> result(matrix1.numRows, matrix1.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix1.numCols; j++)
        {
            result.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
        }
    }
    return result;
}

template<typename T>
TMatr<T> &TMatr<T>::operator = (const TMatr &other)
{
    this->numRows = other.numRows;
    this->numCols = other.numCols;
    delete[] this->matrix;

    this->matrix = new T*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        this->matrix[i] = new T[numCols];
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

template<typename T>
istream &operator >> (istream &in, TMatr<T> &matrix)
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

template<typename T>
ostream &operator << (ostream &out, const TMatr<T> &matrix)
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

template<typename T1, typename T2>
TMatr<decltype (T1()+T2())> operator + (const TMatr<T1> &matrix1, const TMatr<T2> &matrix2)
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
}

template<typename T1, typename T2>
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
}

template<typename T1, typename T2>
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
}

template<typename T>
bool TMatr<T>::operator == (const TMatr &other)
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

template<typename T>
bool TMatr<T>::operator != (const TMatr &other)
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

template<typename T>
T* TMatr<T>::operator [] (int index)
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

template<typename T>
template<typename T1>
TMatr<T> &TMatr<T>::operator += (const TMatr<T1> &other)
{
    if (this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < this->numCols; j++)
        {
            this->matrix[i][j] += static_cast<T>(other.matrix[i][j]);
        }
    }
    return *this;
}

template<typename T>
template<typename T1>
TMatr<T> &TMatr<T>::operator -= (const TMatr<T1> &other)
{
    if (this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < this->numCols; j++)
        {
            this->matrix[i][j] -= static_cast<T>(other.matrix[i][j]);
        }
    }
    return *this;
}

template<typename T>
template<typename T1>
TMatr<T> &TMatr<T>::operator *= (const TMatr<T1> &other)
{
    if(this->numCols != other.numRows)
    {
        throw runtime_error("Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication.");
    }

    TMatr<T> result(this->numRows, other.numCols);
    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < other.numCols; j++)
        {
            for (int k = 0; k < this->numCols; k++)
            {
                result.matrix[i][j] += this->matrix[i][k] * static_cast<T>(other.matrix[k][j]);;
            }
        }
    }
    *this = result;
    return *this;
}

template<typename T>
TMatr<T> TMatr<T>::operator * (T scalar) const
{
    cout << "base" << endl;
    TMatr<T> result(numRows, numCols);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            result.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

template<typename T>
TMatr<T> operator * (T scalar, const TMatr<T> &other)
{
    TMatr<T> result(other.numRows, other.numCols);
    for (int i = 0; i < other.numRows; i++)
    {
        for (int j = 0; j < other.numCols; j++)
        {
            result.matrix[i][j] = other.matrix[i][j] * scalar;
        }
    }
    return result;
}

template<typename T>
TMatr<T> &TMatr<T>::operator ++ ()
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

template<typename T>
TMatr<T> TMatr<T>::operator ++ (int)
{
    TMatr<T> temp(*this);
    ++(*this);
    return temp;
}

template<typename T>
TMatr<T> &TMatr<T>::operator -- ()
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

template<typename T>
TMatr<T> TMatr<T>::operator -- (int)
{
    TMatr<T> temp(*this);
    --(*this);
    return temp;
}

template<typename T>
template<typename T1>
TMatr<T>::TMatr(const TMatr<T1> &other) : numRows(other.numRows), numCols(other.numCols)
{
    matrix = new T*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        matrix[i] = new T[numCols];
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
template<typename T1>
TMatr<T> &TMatr<T>::operator = (const TMatr<T1> &other)
{
    for (int i = 0; i < numRows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    numRows = other.numRows;
    numCols = other.numCols;
    matrix = new T*[numRows];
    for (int i = 0; i < numRows; i++)
    {
        matrix[i] = new T[numCols];
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
