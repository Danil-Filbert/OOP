#ifndef TMATR_PART_H_INCLUDED
#define TMATR_PART_H_INCLUDED
#include "TMatr.h"

using namespace std;

template<typename T> class TMatr<T*>
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

    void setValue(int row, int col, T value);
    T getValue(int row, int col) const;
    int getNumRows() const;
    int getNumCols() const;
    static int getCounter();
    int getId() const;

    ~TMatr();


    TMatr<T*> &operator = (const TMatr<T*> &);
    template<typename T1> TMatr<T*> &operator = (const TMatr<T1*> &);

    template<typename T1> friend istream &operator >> (istream &, TMatr<T1*> &);
    template<typename T1> friend ostream &operator << (ostream &, const TMatr<T1*> &);

    template<typename T1, typename T2> friend TMatr<decltype (T1()+T2())*> operator + (const TMatr<T1*> &, const TMatr<T2*> &);
    template<typename T1, typename T2> friend TMatr<decltype (T1()-T2())*> operator - (const TMatr<T1*> &, const TMatr<T2*> &);
    template<typename T1, typename T2> friend TMatr<decltype (T1()*T2())*> operator * (const TMatr<T1*> &, const TMatr<T2*> &);

    bool operator == (const TMatr &);
    bool operator != (const TMatr &);

    T* operator [] (int index);

    template<typename T1> TMatr<T*> &operator += (const TMatr<T1*> &);
    template<typename T1> TMatr<T*> &operator -= (const TMatr<T1*> &);
    template<typename T1> TMatr<T*> &operator *= (const TMatr<T1*> &);

    TMatr operator * (T scalar) const;

    TMatr &operator ++ ();
    TMatr operator ++ (int);
    TMatr &operator -- ();
    TMatr operator -- (int);


    template<typename T1> TMatr(const TMatr<T1*> &);
};

#endif // TMATR_PART_H_INCLUDED
