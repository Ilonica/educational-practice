#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void PrintMatr(int** mas, int m) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++)
            cout << mas[i][j] << " ";
        cout << endl;
    }
}

void Minor(int** mas, int** p, int i, int j, int m) {
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < m - 1; ki++) {
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj < m - 1; kj++) {
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}

int Opred(int** mas, int m, int k, int n1, int j) {
    int i, d, t, n;
    int** p;
    p = new int* [m];
    for (i = 0; i < m; i++)
        p[i] = new int[m];
    d = 0;
    t = 1;
    n = m - 1;
    if (m < 1) cout << "Определитель вычислить невозможно!";
    if (k < 0 || k > n1) cout << "Введен недопустимый номер столбца!";
    if (k >= 0 && k <= n1) {
        if (m == 1) {
            d = mas[0][0];
            return(d);
        }

        else if (m == 2) {
            d = mas[1][1] * mas[0][0] - (mas[0][1] * mas[1][0]);
            return(d);
        }

        else if (m > 2) {
            for (i = 0; i < m; i++) {
                if (k == n1) {
                    Minor(mas, p, i, k, m);
                    cout << "Минор " << n << "-го порядка для элелемента " << mas[i][j] << " имеет вид:\n";
                    PrintMatr(p, n);
                    if (k % 2 == 0) {
                        if (n % 2 == 0)
                            d = d + t * mas[i][j] * Opred(p, n, k, n1, j - 1);
                        else
                            d = d - t * mas[i][j] * Opred(p, n, k, n1, j - 1);
                    }
                    else {
                        if (n % 2 == 0)
                            d = d - t * mas[i][j] * Opred(p, n, k, n1, j - 1);
                        else
                            d = d + t * mas[i][j] * Opred(p, n, k, n1, j - 1);
                    }
                    t = -t;
                }
                else if (k == n1 - 1 && n1 > 4) {
                    Minor(mas, p, i, k, m);
                    cout << "Минор " << n << "-го порядка для элелемента " << mas[i][j] << " имеет вид:\n";
                    PrintMatr(p, n);

                    if (k % 2 == 0) {
                        if (n > k)
                            d = d - t * mas[i][j] * Opred(p, n, k, n1, j);
                        else d = d + t * mas[i][j] * Opred(p, n, k, n1, j - 1);
                    }
                    else {
                        if (n > k)
                            d = d + t * mas[i][j] * Opred(p, n, k, n1, j);
                        else
                            d = d - t * mas[i][j] * Opred(p, n, k, n1, j - 1);
                    }
                    t = -t;
                }
                else {
                    Minor(mas, p, i, k, m);
                    cout << "Минор " << n << "-го порядка для элелемента " << mas[i][j] << " имеет вид:\n";
                    PrintMatr(p, n);
                    if (k % 2 == 0)
                        d = d + t * mas[i][j] * Opred(p, n, k, n1, j);
                    else d = d - t * mas[i][j] * Opred(p, n, k, n1, j);
                    t = -t;
                }
            }
            return(d);
        }
    }
}


int main()
{
    setlocale(0, "");
    ifstream f;
    int n, d, k;
    int** a;
    f.open("matr.txt");


    cout << "Программа вычисления определителя методом разложения по k столбцу.\nСоздайте файл с именем matr.txt и укажите в нем размер матрицы, \n номер строки и значение самой матрицы через пробел.\n";
        if (!f.is_open()) cout << "Файл не найден!\n";
    if (f.is_open() && f.peek() == EOF) cout << "Файл пустой!\n";

    if (f.is_open() && f.peek() != EOF) {
        f >> n >> k;

        if (f.fail()) cout << "Данные введены неверно!\n";

        else {
            a = new int* [n];
            for (int i = 0; i < n; i++)
                a[i] = new int[n];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    f >> a[i][j];
                }
            }
            if (f.fail()) cout << "Данные введены неверно!\n";
            else {
                cout << "Вы ввели матрицу:\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        cout << a[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << "Вы ввели столбец под номером " << k << endl << " \n";
                k--;
                int n1 = n - 1;
                int j = k;
                d = Opred(a, n, k, n1, j);

                cout << "Определитель матрицы равен: " << d << endl;
                f.close();
                for (int i = 0; i < n; i++)
                    delete a[i];
                delete[]a;

                ofstream t("opred.txt");
                t << "Определитель матрицы равен: " << d << endl;
                t.close();
            }
        }
    }

    system("pause");
}
