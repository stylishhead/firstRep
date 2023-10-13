#include <iostream>
#include <cmath>
using namespace std;

int random_num(int start, int end) {
    int r = rand() % (end - start + 1) + start;
    return r;
}

int main() {
    system("chcp 65001"); //проблема с кириллицей

    int sectors[5] = {5, 4, 3, 2, 1};
    int sumOfPoints = 0;
    int x, y;

    for (int i = 0; i < 5; i++) {
        cout << "Введите X" << i+1 << ": ";
        cin >> x;
        cout << "Введите Y" << i+1 << ": ";
        cin >> y;

        x = x + random_num(-5, 5);
        y = y + random_num(-5, 5);

        y=y*y;
        x=x*x;

        int sum, carry;
        do { //сложение двух чисел при помощи побитовых операций
            sum = x ^ y;
            carry = (x & y) << 1;
            x = sum;
            y = carry;
        } while (y != 0);

        int distance = sqrt(x); //для задачи достаточно целого значения

        int score = (distance < 5) ? sectors[distance] : 0;
        sumOfPoints += score;
    }
    string result = (sumOfPoints < 10) ? "лузер": "ультрамегасупердуперхарош";
    cout << "Результат: " << sumOfPoints << ", вы " << result;
}
