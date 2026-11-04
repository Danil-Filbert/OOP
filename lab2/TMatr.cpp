#include <iostream>
#include "TMatr.h"

using namespace std;

int TMatr::counter = 0;

TMatr::TMatr(int rows, int cols) : numRows(rows), numCols(cols)
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

TMatr::TMatr(const TMatr &other) : numRows(other.numRows), numCols(other.numCols)
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

TMatr::TMatr(TMatr &&other) : matrix(other.matrix), numRows(other.numRows), numCols(other.numCols)
{
    other.matrix = nullptr;
    other.numRows = 0;
    other.numCols = 0;
    id = counter;
}

void TMatr::resize(int newRows, int newCols)
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

void TMatr::input()
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

void TMatr::setValue(int row, int col, int value)
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

int TMatr::getValue(int row, int col) const
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

int TMatr::getNumRows() const
{
    return numRows;
}

int TMatr::getNumCols() const
{
    return numCols;
}

int TMatr::getCounter()
{
    return counter;
}

int TMatr::getId() const
{
    return id;
}

void TMatr::outputMatrix() const
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

void TMatr::outputSubmatrix(int startRow, int startCol, int subRows, int subCols) const
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

TMatr::~TMatr()
{
    for(int i = 0; i < numRows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    counter--;
}

void TMatr::mulByScalar(int scalar)
{
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            matrix[i][j] *= scalar;
        }
    }
}

TMatr TMatr::addMatrix(const TMatr &other)
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

TMatr sub(const TMatr &matrix1, const TMatr &matrix2)
{
    if(matrix1.numRows != matrix2.numRows || matrix1.numCols != matrix2.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for subtraction.");
    }

    TMatr result(matrix1.numRows, matrix1.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix1.numCols; j++)
        {
            result.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
        }
    }
    return result;
}

TMatr mul(TMatr &matrix1, TMatr &matrix2)
{
    if(matrix1.getNumCols() != matrix2.getNumRows())
    {
        throw runtime_error("Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication.");
    }

    TMatr result(matrix1.getNumRows(), matrix2.getNumCols());
    for(int i = 0; i < matrix1.getNumRows(); i++)
    {
        for(int j = 0; j < matrix2.getNumCols(); j++)
        {
            for(int k = 0; k < matrix1.getNumCols(); k++)
            {
                result.setValue(i, j, result.getValue(i, j) + (matrix1.getValue(i, k) * matrix2.getValue(k, j)));
            }
        }
    }
    return result;
}

TMatr &TMatr::operator = (const TMatr &other)
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

istream &operator >> (istream &in, TMatr &matrix)
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

ostream &operator << (ostream &out, const TMatr &matrix)
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

TMatr operator + (const TMatr &matrix1, const TMatr &matrix2)
{
    if(matrix1.numRows != matrix2.numRows || matrix1.numCols != matrix2.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    TMatr result(matrix1.numRows, matrix1.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix1.numCols; j++)
        {
            result[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
        }
    }
    return result;
}

TMatr operator - (const TMatr &matrix1, const TMatr &matrix2)
{
    if(matrix1.numRows != matrix2.numRows || matrix1.numCols != matrix2.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for subtraction.");
    }

    TMatr result(matrix1.numRows, matrix1.numCols);
    for(int i = 0; i < matrix1.numRows; i++)
    {
        for(int j = 0; j < matrix1.numCols; j++)
        {
            result[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
        }
    }
    return result;
}

TMatr operator * (const TMatr &matrix1, const TMatr &matrix2)
{
    if(matrix1.numCols != matrix2.numRows)
    {
        throw runtime_error("Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication.");
    }

    TMatr result(matrix1.numRows, matrix2.numCols);
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

bool TMatr::operator == (const TMatr &other)
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

bool TMatr::operator != (const TMatr &other)
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

int* TMatr::operator [] (int index)
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

TMatr &TMatr::operator += (const TMatr &other)
{
    if (this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < this->numCols; j++)
        {
            this->matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

TMatr &TMatr::operator -= (const TMatr &other)
{
    if (this->numRows != other.numRows || this->numCols != other.numCols)
    {
        throw runtime_error("Error: Matrices must have the same dimensions for addition.");
    }

    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < this->numCols; j++)
        {
            this->matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}

TMatr &TMatr::operator *= (const TMatr &other)
{
    if(this->numCols != other.numRows)
    {
        throw runtime_error("Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication.");
    }

    TMatr result(this->numRows, other.numCols);
    for (int i = 0; i < this->numRows; i++)
    {
        for (int j = 0; j < other.numCols; j++)
        {
            for (int k = 0; k < this->numCols; k++)
            {
                result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    *this = result;
    return *this;
}

TMatr TMatr::operator * (int scalar) const
{
    TMatr result(numRows, numCols);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            result.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

TMatr operator * (int scalar, const TMatr &other)
{
    TMatr result(other.numRows, other.numCols);
    for (int i = 0; i < other.numRows; i++)
    {
        for (int j = 0; j < other.numCols; j++)
        {
            result.matrix[i][j] = other.matrix[i][j] * scalar;
        }
    }
    return result;
}

TMatr& TMatr::operator ++ ()
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

TMatr TMatr::operator ++ (int)
{
    TMatr temp(*this);
    ++(*this);
    return temp;
}

TMatr& TMatr::operator -- ()
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

TMatr TMatr::operator -- (int)
{
    TMatr temp(*this);
    --(*this);
    return temp;
}
