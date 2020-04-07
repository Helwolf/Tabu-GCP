#ifndef TWOAXISARRAY_H
#define TWOAXISARRAY_H

template <class Type>
void newArray(Type **&a, int m, int n)
{
    a = new Type *[m];
    for (int i = 0; i < m; i++)
        a[i] = new Type[n];
}
template <class Type>
void initArray(Type **a, Type v, int m, int n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = v;
}
template <class Type>
void deleteArray(Type **a, int m, int n)
{
    for (int i = 0; i < m; i++)
        delete[] a[i];
    delete[] a;
}

#endif // TWOAXISARRAY_H
