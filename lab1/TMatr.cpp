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
    cout << "Enter the elements of the matrix:" << endl;
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
        cout << "Error: Index out of bounds." << endl;
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
        cout << "Error: Index out of bounds." << endl;
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
        cout << "Error: Matrices must have the same dimensions for additions." << endl;
        return TMatr(0, 0);
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
        cout << "Error: Matrices must have the same dimensions for substraction." << endl;
        return TMatr(0, 0);
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
        cout << "Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication." << endl;
        return TMatr(0, 0);
    }

    TMatr result(matrix1.getNumRows(), matrix2.getNumCols());

    for(int i = 0; i < matrix1.getNumRows(); i++)
    {
        for(int j = 0; j < matrix2.getNumCols(); j++)
        {
            result.setValue(i, j, 0);
            for(int k = 0; k < matrix1.getNumRows(); k++)
            {
                result.setValue(i, j, result.getValue(i, j) + (matrix1.getValue(i, k) * matrix2.getValue(k, j)));
            }
        }
    }
    return result;
}
