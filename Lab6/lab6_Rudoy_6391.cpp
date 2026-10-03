#include <iostream>
#include <cstdio>

using namespace std;

//Вычислить и вывести на экран в виде таблицы значения функции F на интервале
//от Хнач.до Хкон.с шагом dX.
//где а, Ь, с — действительные числа.
//Функция F должна принимать действительное значение, если выражение
//(Ац ИЛИ Вц) И(Ац ИЛИ Сц)
//не равно нулю, и целое значение в противном случае.Через Ац, Вц и Сц обозначены
//целые части значений а, Ь, с, операции И и ИЛИ — поразрядные.Значения
//а, Ь, с, Хнач., Хкон., dX ввести с клавиатуры.

void F(double x, double a, double b, double c, int Ac, int Bc, int Cc)
{
    double f;
    bool defined = true;

    if (x < 0 && b != 0) {
        f = a * x * x + b;
    }
    else if (x > 0 && b == 0) {
        if (x - c == 0) {          // защита от деления на ноль
            defined = false;
        }
        else {
            f = (x - a) / (x - c);
        }
    }
    else {
        if (c == 0) {              // защита от деления на ноль
            defined = false;
        }
        else {
            f = x / c;
        }
    }

    if (!defined) {
        printf("%10.4f %15s\n", x, "undefined");
    }
    else if (((Ac | Bc) & (Ac | Cc)) != 0) {
        printf("%10.4f %15.4f\n", x, f);      // действительное значение
    }
    else {
        printf("%10.4f %15d\n", x, (int)f);   // целое значение
    }
}

int main()
{
    double a, b, c, Xn, Xk, dX;

    cout << "Введите коэффициенты a, b и c" << endl;
    cin >> a >> b >> c;

    cout << "Введите значения Хнач. до Хкон. и шаг dX" << endl;
    cin >> Xn >> Xk >> dX;

    // Проверка корректности ввода
    if (dX == 0) {
        cout << "Ошибка: шаг dX не может быть равен нулю" << endl;
        return 1;
    }
    if (Xn > Xk && dX > 0) {
        cout << "Ошибка: Xнач больше Xкон при положительном шаге" << endl;
        return 1;
    }
    if (Xn < Xk && dX < 0) {
        cout << "Ошибка: Xнач меньше Xкон при отрицательном шаге" << endl;
        return 1;
    }

    // Целые части коэффициентов для поразрядных операций
    int Ac = int(a);
    int Bc = int(b);
    int Cc = int(c);

    // Заголовок таблицы
    printf("%10s %15s\n", "x", "F(x)");
    printf("-----------------------------\n");

    // Выбор направления обхода в зависимости от знака шага
    if (dX > 0) {
        // Положительный шаг: x растёт от Xn до Xk
        for (double x = Xn; x <= Xk; x += dX) {
            F(x, a, b, c, Ac, Bc, Cc);
        }
    }
    else {
        // Отрицательный шаг: x убывает от Xn до Xk
        for (double x = Xn; x >= Xk; x += dX) {
            F(x, a, b, c, Ac, Bc, Cc);
        }
    }

    return 0;
}
