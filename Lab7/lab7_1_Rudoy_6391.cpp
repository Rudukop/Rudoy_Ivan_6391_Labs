#include <iostream>
#include <clocale>
#include <cstdio>

using namespace std;

//Реализовать программу перемножения матриц(размерности двух исходных матриц
//задаются именованными константами), вводимых с клавиатуры
//Требования :
//1) элементы матриц вводятся построчно
//2) при выводе на экран результирующая матрица должна форматироваться в
//соответствии с ее размерностью

const int M = 2;
const int K = 3;
const int N = 2;

int main()
{
    double A[M][K];
    double B[K][N];
    double C[M][N] = { 0.0 };

    cout << "Введите построчно матрицу A:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Введите построчно матрицу B:" << endl;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            cin >> B[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "Матрица C = A * B:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%10.2f", C[i][j]);  
        }
        printf("\n");                
    }

    return 0;
}

