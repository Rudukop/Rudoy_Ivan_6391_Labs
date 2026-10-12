#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

//1. Описать структуру с именем STUDENT, содержащую следующие поля :
//• ФИО;
//• номер группы;
//• успеваемость(массив из пяти оценок по 5 - бальной шкале).
//2. Реализовать программу, выполняющую следующие действия :
//а) ввод с клавиатуры данных в массив, состоящий из заданного с клавиатуры
//количества структур типа STUDENT;
//б) упорядочивание массива по возрастанию номера группы;
//в) вывод на дисплей фамилий и номеров групп для всех студентов, включенных в
//массив, если средний балл студента больше 4, 0 (если таких студентов нет, вывести
//соответствующее сообщение);
//г) вывод на экран таблицы, содержащей столбцы : «Номер группы», «Количество
//студентов», «Количество двоечников».Строки таблицы должны быть упорядочены по
//убыванию значений в столбце «Количество двоечников».

struct STUDENT {
    string fio;          // ФИО одной строкой
    int group = 0;
    int grades[5] = { 0,0,0,0,0 };
};

struct GroupStats {
    int groupNum;
    int total;
    int fails;
};

double average(STUDENT s) {
    double sum = 0.0;
    for (int i = 0; i < 5; i++) {
        sum += s.grades[i];
    }
    return sum / 5.0;
}

int main()
{
    int n;
    cout << "Введите количество студентов:" << endl;
    cin >> n;
    //Проверка, что количество студентов больше 0
    if (n <= 0) {
        cout << "Количество студентов должно быть положительным." << endl;
        return 1;
    }
    cin.ignore(10000, '\n');

    //Ввод массива структур
    cout << "а) Ввод с клавиатуры данных в массив:" << endl;
    STUDENT* students = new STUDENT[n];
    for (int i = 0; i < n; i++) {
        cout << "Введите ФИО студента:" << endl;
        getline(cin, students[i].fio);

        cout << "Введите номер группы:" << endl;
        cin >> students[i].group;

        cout << "Введите 5 оценок:" << endl;
        for (int j = 0; j < 5; j++) {
            cin >> students[i].grades[j];
        }
        cin.ignore(10000, '\n');
    }

    cout << "б) Упорядочивание массива по возрастанию номера группы." << endl;
    //Сортировка пузыркем
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (students[j].group > students[j + 1].group) {
                STUDENT temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    cout << "в) Вывод на дисплей фамилий и номеров групп, если средний балл студента больше 4:" << endl;
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (average(students[i]) > 4.0) {
            cout << students[i].fio << endl;
            cout << students[i].group << endl;
            found++;
        }
    }
    if (found == 0) {
        cout << "Нет студентов со средним баллом > 4,0" << endl;
    }

    cout << "г) Вывод на экран таблицы:" << endl;
    GroupStats* stats = new GroupStats[n];
    int groupCount = 0;

    for (int i = 0; i < n; i++) {
        //Группа сменилась — создаём новую карточку
        if (groupCount == 0 || stats[groupCount - 1].groupNum != students[i].group) {
            stats[groupCount].groupNum = students[i].group;
            stats[groupCount].total = 0;
            stats[groupCount].fails = 0;
            groupCount++;
        }

        //Обновляем счётчики последней карточки
        //Двоечники - это те, у кого средний балл ниже 3
        stats[groupCount - 1].total++;
        if (average(students[i]) < 3.0) {
            stats[groupCount - 1].fails++;
        }
    }

    //Сортировка массива stats по убыванию 
    for (int i = 0; i < groupCount - 1; i++) {
        for (int j = 0; j < groupCount - 1 - i; j++) {
            if (stats[j].fails < stats[j + 1].fails) {
                GroupStats temp = stats[j];
                stats[j] = stats[j + 1];
                stats[j + 1] = temp;
            }
        }
    }

    printf("%15s %20s %20s\n", "Номер группы", "Количество студентов", "Количество двоечников");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < groupCount; i++) {
        printf("%12d %20d %20d\n",
            stats[i].groupNum,
            stats[i].total,
            stats[i].fails);
    }

    //Освобождение памяти
    delete[] students;
    delete[] stats;

    return 0;
}