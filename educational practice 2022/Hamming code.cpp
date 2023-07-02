#include <iostream>
#include <fstream>
using namespace std;

int main() {
    setlocale(0, "");
    fstream f("posled.txt");
    int r;

    cout << "Программа кодирования и декодирования заданных двоичных последовательностей.\nСоздайте файл с именем posled.txt и укажите в нем номер команды\nи значение двоичной последовательности через пробел.\n\n";
        if (!f.is_open()) cout << "Файл не найден!\n";
    if (f.is_open() && f.peek() == EOF) cout << "Файл пустой!\n";

    if (f.is_open() && f.peek() != EOF) {
        f >> r;
        if (f.fail()) cout << "Данные введены неверно!\n";

        else {
            cout << "Вы ввели номер команды " << r;
            if (r == 1) {
                cout << " - закодировать.\n";
                int step = 0, t = 0, sum = 0, j = 0, p = 0;
                const int n = 26;
                int a[n], b[n + 5];
                for (int i = 0; i < n; i++)
                    f >> a[i];
                if (f.fail()) cout << "Данные введены неверно!\n";

                else {
                    f.close();
                    cout << "Вы ввели двоичную последовательность:\n";
                    for (int i = 0; i < n; i++)
                        cout << a[i];
                    cout << endl << endl;

                    for (int i = 0; i < n + 5; i++) {
                        if (i == (pow(2, step) - 1)) {
                            b[i] = 0;
                            step++;
                        }
                        else {
                            b[i] = a[t];
                            t++;
                        }
                    }

                    cout << "Двоичная последовательность с контрольными битами, равными нулю:\n";
                    for (int i = 0; i < n + 5; i++)
                        cout << b[i];
                    cout << endl << endl;

                    step = 0;
                    for (int i = 0; i < n + 5; i++) {
                        if (i == (pow(2, step) - 1)) {
                            j = i;
                            while (j < n + 5) {
                                if (p < pow(2, step)) {
                                    sum += b[j];
                                    j++; p++;
                                }
                                else {
                                    j += (pow(2, step));
                                    p = 0;
                                }
                            }
                            if (sum % 2 == 0) b[i] = 0;
                            else b[i] = 1;
                            p = 0;
                            sum = 0;
                            step++;
                        }
                    }

                    cout << "Закодированная двоичная последовательность:\n";
                    for (int i = 0; i < n + 5; i++)
                        cout << b[i];
                    cout << endl;

                    ofstream v("kod.txt");
                    for (int i = 0; i < n + 5; i++)
                        v << b[i] << " ";
                    v.close();
                }
            }


            if (r == 2) {
                cout <<" - декодировать.\n";
                int step = 0, t = 0, sum = 0, j = 0, p = 0, kontrol = 0, iter = 0;
                const int n = 31;
                int a[n], b[n], c[n - 5];
                for (int i = 0; i < n; i++) {
                    f >> a[i];
                    b[i] = a[i];
                }
                if (f.fail()) cout << "Данные введены неверно!\n";

                else {
                    f.close();

                    cout << "Вы ввели двоичную последовательность:\n";
                    for (int i = 0; i < n; i++)
                        cout << a[i];
                    cout << endl << endl;

                    for (int i = 0; i < n; i++) {
                        if (i == (pow(2, step) - 1)) {
                            j = i;
                            while (j < n) {
                                if (j == pow(2, step) - 1) {
                                    j++; p++;
                                }
                                else if (p < pow(2, step)) {
                                    sum += b[j];
                                    j++; p++;
                                }
                                else {
                                    j += (pow(2, step));
                                    p = 0;
                                }
                            }
                            if (sum % 2 == 0) b[i] = 0;
                            else b[i] = 1;
                            p = 0;
                            sum = 0;
                            step++;
                        }
                    }
                    cout << "Двоичная последовательность с пересчитанными контрольными битами:\n";
                    for (int i = 0; i < n; i++)
                        cout << b[i];
                    cout << endl;

                    step = 0;
                    for (int i = 0; i < n; i++) {
                        if (i == (pow(2, step) - 1)) {
                            if (b[i] != a[i]) {
                                if (i == 0) kontrol++;
                                else {
                                    kontrol += i;
                                    iter++;
                                }
                            }
                            step++;
                        }
                    }

                    if ((kontrol + iter) > 0)
                        cout << "Ошибка в " << (kontrol + iter) << "-ом бите!\n" << endl;
                    else cout << "Ошибок нет.\n" << endl;

                    for (int i = 0; i < n; i++) {
                        if (kontrol != 0 && ((kontrol + iter) - 1) == i && b[i] == 0) b[i] = 1;
                        else if (kontrol != 0 && ((kontrol + iter) - 1) == i && b[i] == 1) b[i] = 0;
                    }
                    step = 0;
                    for (int i = 0; i < n; i++) {
                        if (i == (pow(2, step) - 1)) {
                            step++;
                        }
                        else {
                            c[t] = b[i];
                            t++;
                        }
                    }
                    cout << "Декодированная двоичная последовательность:\n";
                    for (int i = 0; i < n - 5; i++)
                        cout << c[i];
                    cout << endl;

                    ofstream v("kod.txt");
                    for (int i = 0; i < n - 5; i++)
                        v << c[i] << " ";
                    v.close();
                }
            }

            if (r < 1 || r > 2) cout << "." << "\nВведен неверный номер команды!\n";
        }
    }
    system("pause");
}
