#ifndef __LU_H__
#define __LU_H__

#include <vector>
using std::vector;

// ��nά����A����LU�ֽ�
// ��L�����U����洢��ͬһ����ά����LU���Խ�Լ�洢�ռ�
// A,LU���±궼��1��ʼ
void LU_decomposition(vector<vector<double> > &A, vector<vector<double> > &LU)
{
    const int n = A.size()-1;

    LU[1][1] = A[1][1];
    for(int j=2; j<=n; ++j)
    {
        LU[j][1] = A[j][1];
        LU[1][j] = A[1][j]/LU[1][1];
    }
    for(int j=2; j<=n-1; ++j)
    {
        for(int i=j; i<=n; ++i)
        {
            LU[i][j] = A[i][j];
            for(int k=1; k<=j-1; ++k) { LU[i][j] -= LU[i][k]*LU[k][j]; }
        }
        for(int k=j+1; k<=n; ++k)
        {
            LU[j][k] = A[j][k];
            for(int i=1; i<=j-1; ++i) { LU[j][k] -= LU[j][i]*LU[i][k]; }
            LU[j][k] /= LU[j][j];
        }
    }
    LU[n][n] = A[n][n];
    for(int k=1; k<=n-1; ++k) { LU[n][n] -= LU[n][k]*LU[k][n]; }
}

// ����LU�ֽ�,���Ax = b
// A,b,x���±궼��1��ʼ
void solve_linear_eqs(vector<vector<double> > &A, vector<double> &b, vector<double> &x)
{
    const int n = A.size()-1;
    vector<vector<double> > LU(n+1, vector<double>(n+1, 0));

    LU_decomposition(A, LU);

    vector<double> d(n+1, 0);
    d[1] = b[1]/LU[1][1];
    for(int i=2; i<=n; ++i)
    {
        d[i] = b[i];
        for(int j=1; j<=i-1; ++j) { d[i] -= LU[i][j]*d[j]; }
        d[i] /= LU[i][i];
    }

    x[n] = d[n];
    for(int i=n-1; i>=1; --i)
    {
        x[i] = d[i];
        for(int j=i+1; j<=n; ++j) { x[i] -= LU[i][j]*x[j]; }
    }
}

// ����LU�ֽ⣬����A�������
// �����±��1��ʼ
void matrix_inversion(vector<vector<double> > &A, vector<vector<double> > &A_inversion)
{
    const int n = A.size()-1;
    vector<vector<double> > LU(n+1, vector<double>(n+1, 0));

    LU_decomposition(A, LU);

    vector<double> b(n+1, 0);

    for(int k=1; k<=n; ++k)
    {
        b[k-1] = 0;
        b[k] = 1;

        vector<double> d(n+1, 0);
        d[1] = b[1]/LU[1][1];
        for(int i=2; i<=n; ++i)
        {
            d[i] = b[i];
            for(int j=1; j<=i-1; ++j) { d[i] -= LU[i][j]*d[j]; }
            d[i] /= LU[i][i];
        }

        A_inversion[n][k] = d[n];
        for(int i=n-1; i>=1; --i)
        {
            A_inversion[i][k] = d[i];
            for(int j=i+1; j<=n; ++j) { A_inversion[i][k] -= LU[i][j]*A_inversion[j][k]; }
        }
    }
}

#endif
