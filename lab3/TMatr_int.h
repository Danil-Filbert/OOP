#ifndef TMATR_INT_H_INCLUDED
#define TMATR_INT_H_INCLUDED
#include "TMatr.h"

using namespace std;

template<> class TMatr<int>
{
private:
    int** matrix;
    int numRows;
    int numCols;
    static int counter;
    int id;

public:
    template<typename> friend class TMatr;
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
    friend TMatr<int> sub(const TMatr<int> &, const TMatr<int> &);


    TMatr &operator = (const TMatr &);

    friend istream &operator >> (istream &, TMatr<int> &);
    friend ostream &operator << (ostream &, const TMatr<int> &);

    template<typename T1, typename T2> friend TMatr<decltype (T1()+T2())> operator + (const TMatr<T1> &, const TMatr<T2> &);
    template<typename T1, typename T2> friend TMatr<decltype (T1()-T2())> operator - (const TMatr<T1> &, const TMatr<T2> &);
    template<typename T1, typename T2> friend TMatr<decltype (T1()*T2())> operator * (const TMatr<T1> &, const TMatr<T2> &);

    bool operator == (const TMatr &);
    bool operator != (const TMatr &);

    int* operator [] (int index);

    TMatr<int> &operator += (const TMatr &);
    TMatr<int> &operator -= (const TMatr &);
    TMatr<int> &operator *= (const TMatr &);

    TMatr operator * (int scalar) const;
    friend TMatr<int> operator * (int scalar, const TMatr<int> &);

    TMatr &operator ++ ();
    TMatr operator ++ (int);
    TMatr &operator -- ();
    TMatr operator -- (int);


    template<typename T> TMatr(const TMatr<T> &);
    template<typename T> TMatr<int> &operator = (const TMatr<T> &);
};

#endif // TMATR_INT_H_INCLUDED
