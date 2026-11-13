#ifndef TMATR_H_INCLUDED
#define TMATR_H_INCLUDED
#include <iostream>

using namespace std;

template<typename T>
class TMatr
{
private:
    T** matrix;
    int numRows;
    int numCols;
    static int counter;
    int id;

public:
    template<class> friend class TMatr;
    explicit TMatr(int rows = 5, int cols = 5);
    TMatr(const TMatr &);
    TMatr(TMatr &&);
    template<typename T1> TMatr(TMatr<T1> &&);

    void resize(int newRows, int newCols);
    void input();

    void setValue(int row, int col, T value);
    T getValue(int row, int col) const;
    int getNumRows() const;
    int getNumCols() const;
    static int getCounter();
    int getId() const;

    void outputMatrix() const;
    void outputSubmatrix(int startRow, int startCol, int subRows, int subCols) const;

    ~TMatr();

    void mulByScalar(T scalar);
    TMatr addMatrix(const TMatr &);
    template<typename T1> friend TMatr<T1> sub(const TMatr<T1> &, const TMatr<T1> &);


    TMatr &operator = (const TMatr &);

    template<typename T1> friend istream &operator >> (istream &, TMatr<T1> &);
    template<typename T1> friend ostream &operator << (ostream &, const TMatr<T1> &);

    template<typename T1, typename T2> friend TMatr<decltype (T1()+T2())> operator + (const TMatr<T1> &, const TMatr<T2> &);
    template<typename T1, typename T2> friend TMatr<decltype (T1()-T2())> operator - (const TMatr<T1> &, const TMatr<T2> &);
    template<typename T1, typename T2> friend TMatr<decltype (T1()*T2())> operator * (const TMatr<T1> &, const TMatr<T2> &);

    bool operator == (const TMatr &);
    bool operator != (const TMatr &);

    T* operator [] (int index);

    template<typename T1> TMatr<T> &operator += (const TMatr<T1> &);
    template<typename T1> TMatr<T> &operator -= (const TMatr<T1> &);
    template<typename T1> TMatr<T> &operator *= (const TMatr<T1> &);

    TMatr operator * (T scalar) const;
    template<typename T1> friend TMatr<T1> operator * (T1 scalar, const TMatr<T1> &);

    TMatr &operator ++ ();
    TMatr operator ++ (int);
    TMatr &operator -- ();
    TMatr operator -- (int);


    template<typename T1> TMatr(const TMatr<T1> &);
    template<typename T1> TMatr<T> &operator = (const TMatr<T1> &);
};

#endif // TMATR_H_INCLUDED
