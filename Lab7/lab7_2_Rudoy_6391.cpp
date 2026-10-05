#include <iostream>
#include <cstdio>

using namespace std;

//Размерности матрицы 
const int M = 3;  
const int N = 2;  


//Умножение двух матриц: temp = result * A
//Все матрицы имеют размер M×N
void multiply(double result[M][N], double A[M][N], double temp[M][N])
{
    //Обнуляем temp перед накоплением
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            temp[i][j] = 0.0;
        }
    }

    //Умножение матриц
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                temp[i][j] += result[i][k] * A[k][j];
            }
        }
    }
}


//Возведение матрицы A в степень n: result = A в n степени
//Работает для n >= 1 (n — положительное целое)
void power(double A[M][N], int n, double result[M][N])
{
    //n >= 1: начинаем с A в 1
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = A[i][j];
        }
    }

    //При n = 1 дальше умножать нечего, возвращаем просто матрицу A
    if (n == 1) {
        return;
    }

    //Для n >= 2: на каждом шаге умножаем текущий результат на A
    double temp[M][N];
    for (int p = 2; p <= n; p++) {
        multiply(result, A, temp);   // temp = result × A = A^p

        //Копируем temp в result, чтобы использовать на следующем шаге
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                result[i][j] = temp[i][j];
            }
        }
    }
}


int main()
{
    //Проверка квадратности матрицы (во время выполнения)
    if (M != N) {
        cout << "Ошибка: матрица не квадратная (M = " << M << ", N = " << N << ")." << endl;
        cout << "Возведение в степень невозможно." << endl;
        return 1;
    }

    double A[M][N];
    double result[M][N];
    int n;

    //Ввод матрицы построчно
    cout << "Введите построчно матрицу " << M << "x" << N << ":" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    //Ввод степени
    cout << "Введите положительную целую степень n: ";
    cin >> n;

    //Проверка: степень должна быть положительной
    if (n < 1) {
        cout << "Степень должна быть положительным целым числом." << endl;
        return 1;
    }

    //Возведение в степень
    power(A, n, result);

    //Вывод результата в виде таблицы
    cout << "Итоговая матрица A^" << n << ":" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%10.2f", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}