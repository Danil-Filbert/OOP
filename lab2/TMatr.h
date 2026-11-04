#ifndef TMATR_H_INCLUDED
#define TMATR_H_INCLUDED

using namespace std;

class TMatr
{
private:
    int** matrix;
    int numRows;
    int numCols;
    static int counter;
    int id;

public:
    explicit TMatr(int rows = 5, int cols = 5);
    TMatr(const TMatr &);
    TMatr(TMatr &&);

    void resize(int newRows, int newCols);
    void input();

    void setValue(int row, int col, int value);
    int getValue(int row, int col) const;
    int getNumRows() const;
    int getNumCols() const;
    static int getCounter();
    int getId() const;

    void outputMatrix() const;
    void outputSubmatrix(int startRow, int startCol, int subRows, int subCols) const;

    ~TMatr();

    void mulByScalar(int scalar);
    TMatr addMatrix(const TMatr &);
    friend TMatr sub(const TMatr &, const TMatr &);


    TMatr &operator = (const TMatr &);

    friend istream &operator >> (istream &, TMatr &);
    friend ostream &operator << (ostream &, const TMatr &);

    friend TMatr operator + (const TMatr &, const TMatr &);
    friend TMatr operator - (const TMatr &, const TMatr &);
    friend TMatr operator * (const TMatr &, const TMatr &);

    bool operator == (const TMatr &);
    bool operator != (const TMatr &);

    int* operator [] (int index);

    TMatr &operator += (const TMatr &);
    TMatr &operator -= (const TMatr &);
    TMatr &operator *= (const TMatr &);

    TMatr operator * (int scalar) const;
    friend TMatr operator * (int scalar, const TMatr &);

    TMatr &operator ++ ();
    TMatr operator ++ (int);
    TMatr &operator -- ();
    TMatr operator -- (int);
};

TMatr mul(TMatr &, TMatr &);

#endif // TMATR_H_INCLUDED
