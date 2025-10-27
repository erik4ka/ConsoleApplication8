#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

// ==============================
// МОДУЛЬ 1: Введення і перевірка даних
// ==============================
void inputData(double& x, double& eps) {
    // x – аргумент функції (передається за адресою)
    // eps – задана точність (передається за адресою)
    while (true) {
        cout << "Введіть значення x (у радіанах): ";
        cin >> x;

        // Перевірка на коректність введення
        if (cin.fail()) {
            cout << "Помилка введення! Введіть число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Введіть точність ε (наприклад, 1e-6): ";
        cin >> eps;

        if (cin.fail() || eps <= 0) {
            cout << "Помилка! Точність має бути більшою за 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        break;
    }
}

// ==============================
// МОДУЛЬ 2: Обчислення наближеного значення cos(x)
// ==============================
void cosSeries(double x, double eps, double& approx, int& steps, bool& limitReached) {
    // x – аргумент (передається за значенням)
    // eps – точність (передається за значенням)
    // approx – наближене значення cos(x) (передається за адресою)
    // steps – кількість членів ряду (передається за адресою)
    // limitReached – прапорець, якщо перевищено ліміт ітерацій (передається за адресою)

    const int LIMIT = 1000; // ліміт ітерацій для запобігання зацикленню
    approx = 0.0;
    limitReached = false;
    steps = 0;

    double term; // поточний член ряду
    int n = 0;

    do {
        // формула члена ряду: (-1)^n * x^(2n) / (2n)!
        term = pow(-1, n) * pow(x, 2 * n) / tgamma(2 * n + 1); // tgamma(k+1) = k!
        approx += term;
        n++;

        if (n > LIMIT) {
            limitReached = true;
            break;
        }
    } while (fabs(term) >= eps);

    steps = n;
}

// ==============================
// МОДУЛЬ 3: Точне значення функції
// ==============================
double cosExact(double x) {
    // Обчислення точного значення cos(x)
    return cos(x);
}

// ==============================
// МОДУЛЬ 4: Виведення результатів
// ==============================
void printResults(double x, double eps, double approx, double exact, int steps, bool limitReached) {
    cout << "\n=== РЕЗУЛЬТАТИ ОБЧИСЛЕНЬ ===\n";
    cout << "x = " << x << endl;
    cout << "ε = " << eps << endl;
    cout.precision(10);
    cout << "Наближене значення cos(x): " << approx << endl;
    cout << "Точне значення cos(x):     " << exact << endl;
    cout << "Абсолютна різниця:         " << fabs(approx - exact) << endl;
    cout << "Кількість членів ряду:     " << steps << endl;
    if (limitReached)
        cout << "Досягнуто ліміт кількості кроків! Можливе зациклення.\n";
    cout << "=============================\n\n";
}

// ==============================
// МОДУЛЬ 5: Керуючий
// ==============================
int main() {
    setlocale(LC_ALL, "ukr");

    double x, eps, approx, exact;
    int steps;
    bool limitReached;
    char again;

    do {
        inputData(x, eps);                         // Введення даних
        cosSeries(x, eps, approx, steps, limitReached); // Обчислення через ряд
        exact = cosExact(x);                       // Точне значення
        printResults(x, eps, approx, exact, steps, limitReached); // Вивід результатів

        cout << "Бажаєте виконати ще раз? (т/н): ";
        cin >> again;
        cout << endl;

    } while (again == 'т' || again == 'y' || again == 'Y');

    cout << "Програму завершено.\n";
    return 0;
}
