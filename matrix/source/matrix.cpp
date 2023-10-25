#define _MATRIX_ON_
#include <malloc.h>
#include "matrix.h"
#include <stdio.h>

MATRIX::MATRIX()
{
    row = col = 0;
    mat = NULL;
}
MATRIX::MATRIX(int n)
{
    row = col = n;
    mat = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        mat[i] = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        mat[i][i] = 1;
}
MATRIX::MATRIX(int r, int c, int **m)
{
    row = r;
    col = c;
    mat = (int **)malloc(sizeof(int *) * r);
    for (int i = 0; i < r; i++)
        mat[i] = (int *)malloc(sizeof(int) * c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            mat[i][j] = m[i][j];
}
MATRIX::MATRIX(const MATRIX &m)
{
    row = m.row;
    col = m.col;
    mat = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
        mat[i] = (int *)malloc(sizeof(int) * col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            mat[i][j] = m.mat[i][j];
}
MATRIX::~MATRIX()
{
    for (int i = 0; i < row; i++)
        free(mat[i]);
    free(mat);
    row = col = 0;
}
MATRIX operator*(const MATRIX &x, const MATRIX &y)
{
    int r, c, **m;
    r = x.row;
    c = y.col;
    m = (int **)malloc(sizeof(int *) * r);
    for (int i = 0; i < r; i++)
        m[i] = (int *)malloc(sizeof(int) * c);
    for (int i = 0; i < x.row; i++)
        for (int j = 0; j < y.col; j++)
            for (int k = 0; k < x.col; k++)
                m[i][j] = (m[i][j] + (x.mat[i][k] * y.mat[k][j])) % mod;
    MATRIX res(r, c, m);
    return res;
}
MATRIX operator*(const int &x,const MATRIX &y){
    int r, c, **m;
    r = y.row;
    c = y.col;
    m = (int **)malloc(sizeof(int *) * r);
    for (int i = 0; i < r; i++)
        m[i] = (int *)malloc(sizeof(int) * c);
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            m[i][j]=(x*y.mat[i][j])%mod;
    MATRIX res(r,c,m);
    return res;
}
MATRIX operator+(const MATRIX &x, const MATRIX &y)
{
    int r, c, **m;
    r = x.row;
    c = y.col;
    m = (int **)malloc(sizeof(int *) * r);
    for (int i = 0; i < r; i++)
        m[i] = (int *)malloc(sizeof(int) * c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            m[i][j] = (x.mat[i][j] + y.mat[i][j]) % mod;
    MATRIX res(r, c, m);
    return res;
}
