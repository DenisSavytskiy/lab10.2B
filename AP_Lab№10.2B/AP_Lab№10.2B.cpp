// Main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialty { COMP_SCIENCE, INFORMATICS, MATH_ECON, PHYS_INFO, LABOR_EDU };
string specialtyStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка",
                         "Фізика та інформатика", "Трудове навчання" };

struct Student {
    string surname;
    unsigned course;
    Specialty specialty;
    int physics;
    int math;
    union {
        int programming;
        int numerical_methods;
        int pedagogy;
    };
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int BinSearch(Student* s, const int N, const string surname, const Specialty specialty, const int thirdMark);
void BuildIndexArray(Student* s, int* indexArray, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N: "; cin >> N;

    Student* s = new Student[N];
    int* indexArray = new int[N];

    int menuItem;
    do {
        cout << "\nВиберіть дію:\n";
        cout << " [1] - введення даних з клавіатури\n";
        cout << " [2] - вивід даних на екран\n";
        cout << " [3] - фізичне впорядкування даних\n";
        cout << " [4] - створення індексного масивуу\n";
        cout << " [5] - бінарний пошук студента\n";
        cout << " [0] - вихід\n";
        cout << "Введіть значення: "; cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            Sort(s, N);
            break;
        case 4:
            BuildIndexArray(s, indexArray, N);
            cout << "Індексний масив створено\n";
            break;
        case 5: {
            string surname;
            int ispecialty;
            int thirdMark;

            cout << "Введіть ключі пошуку:\n";
            cout << " спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
            cin >> ispecialty;

            cin.get();
            cin.sync();
            cout << " прізвище: "; getline(cin, surname);
            cout << " оцінка з профільного предмету: "; cin >> thirdMark;

            int found = BinSearch(s, N, surname, (Specialty)ispecialty, thirdMark);
            if (found != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        }
        }
    } while (menuItem != 0);

    delete[] s;
    delete[] indexArray;
    return 0;
}

void Create(Student* s, const int N)
{
    int specialty;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":\n";
        cin.get();
        cin.sync();

        cout << " прізвище: "; getline(cin, s[i].surname);
        cout << " курс: "; cin >> s[i].course;
        cout << " спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> specialty;
        s[i].specialty = (Specialty)specialty;

        cout << " оцінка з фізики: "; cin >> s[i].physics;
        cout << " оцінка з математики: "; cin >> s[i].math;

        switch (s[i].specialty)
        {
        case COMP_SCIENCE:
            cout << " оцінка з програмування: ";
            cin >> s[i].programming;
            break;
        case INFORMATICS:
            cout << " оцінка з чисельних методів: ";
            cin >> s[i].numerical_methods;
            break;
        default:
            cout << " оцінка з педагогіки: ";
            cin >> s[i].pedagogy;
            break;
        }
        cout << endl;
    }
}

void Print(Student* s, const int N)
{
    cout << "================================================================================================================="
        << endl;
    cout << "| № |  Прізвище  | Курс |      Спеціальність      | Фізика | Математика | Програмув. | Чис. методи | Педагогіка |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------"
        << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(11) << left << s[i].surname
            << "| " << setw(5) << right << s[i].course
            << "| " << setw(24) << left << specialtyStr[s[i].specialty]
            << "| " << setw(7) << right << s[i].physics
            << "| " << setw(11) << right << s[i].math;

        switch (s[i].specialty)
        {
        case COMP_SCIENCE:
            cout << "| " << setw(10) << right << s[i].programming
                << " | " << setw(14) << " | " << setw(12) << " |" << endl;
            break;
        case INFORMATICS:
            cout << "| " << setw(13) << " | " << setw(11) << right << s[i].numerical_methods
                << " | " << setw(12) << " |" << endl;
            break;
        default:
            cout << "| " << setw(13) << " | " << setw(14) << " | "
                << setw(10) << right << s[i].pedagogy << " |" << endl;
        }
    }
    cout << "================================================================================================================="
        << endl;
}

void Sort(Student* s, const int N)
{
    Student tmp;
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++)
        {
            bool needSwap = false;

            if (s[j].specialty > s[j + 1].specialty)
                needSwap = true;
            else if (s[j].specialty == s[j + 1].specialty)
            {
                int mark1 = (s[j].specialty == COMP_SCIENCE) ? s[j].programming :
                    (s[j].specialty == INFORMATICS) ? s[j].numerical_methods : s[j].pedagogy;

                int mark2 = (s[j + 1].specialty == COMP_SCIENCE) ? s[j + 1].programming :
                    (s[j + 1].specialty == INFORMATICS) ? s[j + 1].numerical_methods : s[j + 1].pedagogy;

                if (mark1 > mark2)
                    needSwap = true;
                else if (mark1 == mark2 && s[j].surname > s[j + 1].surname)
                    needSwap = true;
            }

            if (needSwap)
            {
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
        }
}

void BuildIndexArray(Student* s, int* indexArray, const int N)
{
    for (int i = 0; i < N; i++)
        indexArray[i] = i;

    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++)
        {
            bool needSwap = false;

            if (s[indexArray[j]].specialty > s[indexArray[j + 1]].specialty)
                needSwap = true;
            else if (s[indexArray[j]].specialty == s[indexArray[j + 1]].specialty)
            {
                int mark1 = (s[indexArray[j]].specialty == COMP_SCIENCE) ? s[indexArray[j]].programming :
                    (s[indexArray[j]].specialty == INFORMATICS) ? s[indexArray[j]].numerical_methods :
                    s[indexArray[j]].pedagogy;

                int mark2 = (s[indexArray[j + 1]].specialty == COMP_SCIENCE) ? s[indexArray[j + 1]].programming :
                    (s[indexArray[j + 1]].specialty == INFORMATICS) ? s[indexArray[j + 1]].numerical_methods :
                    s[indexArray[j + 1]].pedagogy;

                if (mark1 > mark2)
                    needSwap = true;
                else if (mark1 == mark2 && s[indexArray[j]].surname > s[indexArray[j + 1]].surname)
                    needSwap = true;
            }

            if (needSwap)
            {
                int tmp = indexArray[j];
                indexArray[j] = indexArray[j + 1];
                indexArray[j + 1] = tmp;
            }
        }
}

int BinSearch(Student* s, const int N, const string surname, const Specialty specialty, const int thirdMark)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        int currentMark = (s[m].specialty == COMP_SCIENCE) ? s[m].programming :
            (s[m].specialty == INFORMATICS) ? s[m].numerical_methods : s[m].pedagogy;

        if (s[m].specialty == specialty && s[m].surname == surname && currentMark == thirdMark)
            return m;

        if (s[m].specialty < specialty ||
            (s[m].specialty == specialty && currentMark < thirdMark) ||
            (s[m].specialty == specialty && currentMark == thirdMark && s[m].surname < surname))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);

    return -1;
}