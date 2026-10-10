#include <iostream>
#include <cstdio>

using namespace std;

//Пересчёт индексов: элемент (i, j) лежит в линейном массиве по адресу i * ширина + j, где ширина — число столбцов матрицы.

//Умножение двух матриц: C = A * B
void multiply(double* A, double* B, double* C, int M, int N, int K)
{
    //Обнуляем C перед накоплением
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            C[i * K + j] = 0.0;
        }
    }

    //Умножение матриц
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < N; k++) {
                C[i * K + j] += A[i * N + k] * B[k * K + j];
            }
        }
    }
}


//Возведение матрицы A в степень n: result = A в n степени
//Работает для n >= 1 (n — положительное целое)
void power(double* A, int n, double* result, int S)
{
    //n >= 1: начинаем с A в 1
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            result[i * S + j] =  A[i * S + j];
        }
    }

    //При n = 1 дальше умножать нечего, возвращаем просто матрицу A
    if (n == 1) {
        return;
    }

    //Для n >= 2: на каждом шаге умножаем текущий результат на A
    double* temp = new double [S*S];
    for (int p = 2; p <= n; p++) {
        multiply(result, A, temp, S, S, S);   // temp = result × A = A^p

        //Копируем temp в result, чтобы использовать на следующем шаге
        for (int i = 0; i < S * S; i++) {
            result[i] = temp[i];
        }
    }
    delete[] temp;
}


int main()
{
    int M, N;
    cout << "Введите размеры матрицы A рамзерами M на N:" << endl;
    cin >> M >> N;

    cout << "Введите элементы матрицы по строкам:" << endl;
    //Выделяем память под M×N элементов
    double* A = new double[M * N];

    //Ввод построчно: A[i][j] = A[i * N + j], ширина = N
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i * N + j];
        }
    }

    int choice;
    cout << "Что делать дальше? (1 - умножение, 2 - возведение в степень)" << endl;
    cin >> choice;
    
    switch (choice) {
        case 1: {
            int K;
            cout << "Введите количество столбцев матрицы B для умножения:" << endl;
            cin >> K;
            //B имеет размер N×K (строки B = столбцы A)
            double* B = new double[N * K];

            //Ввод B: B[i][j] = B[i * K + j], ширина = K
            cout << "Введите элементы матрицы по строкам:" << endl;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < K; j++) {
                    cin >> B[i * K + j];
                }
            }

            double* C = new double[M * K];
            multiply(A, B, C, M, N, K);

            //Вывод C построчно, C[i][j] = C[i * K + j]
            cout << "Вывод итоговой матрицы C:" << endl;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < K; j++) {
                    printf("%10.2f", C[i * K + j]);
                }
                printf("\n");
            }

            //Освобождаем память, выделенную в этой ветке
            delete[] B;
            delete[] C; 
            break;
        }
        case 2: {
            int n;

            //Для степени матрица должна быть квадратной
            if (M != N) {
                cout << "Матрица не квадратная, возведение в степень невозможно" << endl;
                break;
            }
            else {
                cout << "Введите степень:" << endl;
                cin >> n;

                //Степень должна быть положительной
                if (n < 1) {
                    cout << "Степень должна быть целым положительным числом!" << endl;
                    break;
                }
                else {
                    //C — размер M×N (то же, что M×M, так как M == N)
                    double* C = new double[M * N];
                    power(A, n, C, M);
                    cout << "Вывод итоговой матрицы C:" << endl;
                    for (int i = 0; i < M; i++) {
                        for (int j = 0; j < N; j++) {
                            printf("%10.2f", C[i * N + j]);
                        }
                        printf("\n");
                    }
                    //Освобождаем память, выделенную в этой ветке
                    delete[] C;
                    break;
                }
            }  
        }
        default:
            cout << "Неверный выбор." << endl;
            break;
    }
    //A нужна была до конца — освобождаем здесь
    delete[] A;
    return 0;
}