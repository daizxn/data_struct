#ifdef _MATRIX_ON_
#define _MATRIX_ON_
#include <malloc.h>
#include <stdio.h>

#define mod 1111

class MATRIX
{
private:
    int **mat;
    int row, col;


public:
    MATRIX();                      // 默认构造函数
    MATRIX(int n);                 // 构造函数 构造nE
    MATRIX(int r, int c, int **m); // 构造函数 建立r行c列数据为m的矩阵
    MATRIX(const MATRIX &m);       // 构造函数 赋值
    ~MATRIX();                     // 析构函数
    friend MATRIX operator*(const MATRIX &x, const MATRIX &y);
    friend MATRIX operator*(const int &x, const MATRIX &y);
    friend MATRIX operator+(const MATRIX &x, const MATRIX &y);
};

#endif