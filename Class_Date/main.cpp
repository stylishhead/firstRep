#include <iostream>
using namespace std;

class Date{
private:
    int year, month, day, hour, minute, second;
    bool isOurEra;

public:
    Date () {
        this->year = 1960;
        this->month = 1, this->day = 1;
        this->hour = 0, this->minute = 0, this->second = 0;
        this->isOurEra = true;
    }

    Date (int year, int month, int day, int hour, int minute, int second, bool isOurEra) {
        //проверять начинаем секунды, минуты, часы. потом переходим к году, месяцам. затем (из-за условия вискосного года) проверяем дни и заново месяца, года
        if ((second > 59) or (second < 0)){
            minute += (second/60);
            if (second > 0){
                this->second = second - 60*(second/60);
            }
            if (second < 0){
                second = !second;
                second = second - 60*(second/60);
                this->second = 60 - second;
            }
            if (second == 0){
                this->second = 0;
            }
        } else {
            this->second = second;
        }

        if ((minute > 59) or (minute < 0)){ //проверка минут аналогична проверке секунд
            hour += (minute/60);
            if (minute > 0){
                this->minute = minute - 60*(minute/60);
            }
            if (minute < 0){
                minute = !minute;
                minute = minute - 60*(minute/60);
                this->minute = 60 - minute;
            }
            if (minute == 0){
                this->minute = 0;
            }
        } else {
            this->minute = minute;
        }

        if ((hour > 23) or (hour < 0)){ //проверка часов аналогична проверке секунд и минут
            day += (hour/24);
            if (hour > 0){
                this->hour = hour - 24*(hour/24);
            }
            if (hour < 0){
                hour = !hour;
                hour = hour - 24*(hour/24);
                this->hour = 24 - hour;
            }
            if (hour == 0){
                this->hour = 0;
            }
        } else {
            this->hour = hour;
        }

        if (year == 0) { //нулевой год считаем на Нашу Эру
            this->isOurEra = true;
            this->year = 0;
        } else {
            this->isOurEra = isOurEra;
        }

        if (year < 0) { //отрицательный год означает смену эры
            this->isOurEra = !this->isOurEra;
            this->year = (-year);
        } else {
            this->year = year;
            this->isOurEra = isOurEra;
        }

        if ((month > 12) or (month < 1)) { //неверный месяц задан пользователем
            this->year += ((month-1) / 12);
            if (month > 0){
                this->month = month - 12*(month/12);
                month = this->month;
            }
            if (month < 0) {
                month = !month;
                month = month - 12*(month/12);
                this->month = 12 - month;
            }
            if (month == 0) {
                this->month = 12;
            }
            if (year < 0) { //если ввели очень большое отрицательно число (месяц), что перешли в отрицательный год, то меняем эру и убираем минус у года
                this->isOurEra = !this->isOurEra;
                this->year = !this->year;
            }
        } else {
            this->month = month;
        }


        if ((day > 31) or (day < 1)){ //задана неверная дата (пользователь + секунды, часы, минуты) - корректировка года, месяца и эры
            bool stipulation = false;
            while (!stipulation){
                switch (this->month){
                    case 1:{ //январь
                        if (day > 31) {
                            this->month = 2;
                            day = day - 31;
                        } else if(day < 1){
                            this->month = 12;
                            this->year--;
                            day= 31 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    case 2: { //февраль
                        if ((this->year%4 == 0) or ((this->year%4 == 0) and (this->year%100 == 0) and (this->year%400 == 0))) { // високосный год
                            if(day > 29){
                                this->month = 3;
                                day = day - 29;
                            } else if (day < 1){
                                this->month=1;
                                day = 31 + day;
                            } else {
                                this->day = day;
                                stipulation = true;
                            }
                        } else { // невисокосный год
                            if(day > 28){
                                this->month = 3;
                                day = day - 28;
                            } else if (day < 1){
                                this->month=1;
                                day = 31 + day;
                            } else {
                                this->day = day;
                                stipulation = true;
                            }
                        }
                        break;
                    }
                    case 3:{ //март
                        if (day > 31){
                            this->month = 4;
                            day = day - 31;
                        } else if (day < 1){
                            this->month = 2;
                            if ((this->year%4 == 0) or ((this->year%4 == 0) and (this->year%100 == 0) and (this->year%400 == 0))) {// високосный год
                                day = 29 + day;
                            } else { //невисокосный год
                                day = 28 + day;
                            }
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    case 4: case 6: case 9: case 11:{ //апрель, июнь, сентябрь, ноябрь
                        if (day > 30){
                            this->month++;
                            day = day - 30;
                        } else if (day < 1){
                            this->month--;
                            day = 31 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    case 5: case 7: case 10: { //май, июль, октябрь
                        if (day > 31){
                            this->month++;
                            day = day - 31;
                        } else if (day < 1){
                            this->month--;
                            day = 30 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    case 8:{ //август
                        if (day > 31) {
                            this->month=9;
                            day = day - 31;
                        } else if (day < 1){
                            this->month = 7;
                            day = 31 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                    case 12:{//декабрь
                        if (day > 31){
                            this->year++;
                            this->month=1;
                            day = day - 31;
                        } else if (day < 1) {
                            this->month--;
                            day = 30 + day;
                        } else {
                            this->day = day;
                            stipulation = true;
                        }
                        break;
                    }
                }
            }

            if (year == 0) {
                this->isOurEra = true;
            }
            if (year < 0) {
                this->isOurEra = !this->isOurEra;
                this->year = -(this->year);
            }
        } else {
            this->day = day;
        }

    }

    Date add(int year, int month, int day, int hour, int minute, int second){
        return Date(this->year + year, this->month + month, this->day + day, this->hour + hour, this->minute + minute, this->second + second, this->isOurEra);
    }

    Date subtract(int year, int month, int day, int hour, int minute, int second){
        return Date(this->year - year, this->month - month, this->day - day, this->hour - hour, this->minute - minute, this->second - second, this->isOurEra);
    }

    friend ostream& operator<<(ostream& os, const Date& ec) { // перегрузка <<
        os << ec.isOurEra <<" " << ec.year << " " << ec.month << " " << ec.day << " " << ec.hour << " " << ec.minute << " " << ec.second << endl;
        return os;
    }

    Date operator=(const Date &other) {
        this->year = other.year;
        this->month = other.month;
        this->day = other.day;
        this->hour = other.hour;
        this->minute = other.minute;
        this->second = other.second;
        this->isOurEra = other.isOurEra;
    }

    Date operator+(const Date &other){
        if (other.isOurEra == this->isOurEra) {
            return Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            return Date(other.year-this->year, other.month-this->month, other.day-this->day, other.hour-this->hour, other.minute-this->minute, other.second-this->second, other.isOurEra);
        }
    }

    Date operator+=(const Date &other){
        if (other.isOurEra == this->isOurEra) {
            *this = Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            *this = Date(other.year-this->year, other.month-this->month, other.day-this->day, other.hour-this->hour, other.minute-this->minute, other.second-this->second, other.isOurEra);
        }
    }

    Date operator-(const Date &other) {
        if (this->isOurEra != other.isOurEra) {
            return Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            return Date(this->year - other.year, this->month - other.month, this->day - other.day,this->hour - other.hour, this->minute - other.minute, this->second - other.second, this->isOurEra);
        }
    }

    Date operator-=(const Date &other) {
        if (this->isOurEra != other.isOurEra) {
            *this = Date(this->year + other.year, this->month + other.month, this->day + other.day, this->hour + other.hour, this->minute + other.minute, this->second + other.second, this->isOurEra);
        } else {
            *this = Date(this->year - other.year, this->month - other.month, this->day - other.day,this->hour - other.hour, this->minute - other.minute, this->second - other.second, this->isOurEra);
        }
    }

    bool operator>(const Date &two) const {
        bool answer = false;
        if (this->isOurEra > two.isOurEra) {
            answer = true;
        } else if (this->isOurEra == two.isOurEra) {
            if (this->year > two.year) {
                answer = true;
            } else if (this->year == two.year) {
                if (this->month > two.month) {
                    answer = true;
                } else if (this->month == two.month) {
                    if (this->day > two.day) {
                        answer = true;
                    } else if (this->day == two.day) {
                        if (this->hour > two.hour) {
                            answer = true;
                        } else if (this->hour == two.hour) {
                            if (this->minute > two.minute) {
                                answer = true;
                            } else if (this->minute == two.minute) {
                                if (this->second > two.second) {
                                    answer = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((this->isOurEra == two.isOurEra) and (this->isOurEra == false)) and (answer == true)) {
            answer = false;
        }
        return answer;
    }

    bool operator<(const Date &two) const {
        bool answer = false;
        if (this->isOurEra < two.isOurEra) {
            answer = true;
        } else if (this->isOurEra == two.isOurEra) {
            if (this->year < two.year) {
                answer = true;
            } else if (this->year == two.year) {
                if (this->month < two.month) {
                    answer = true;
                } else if (this->month == two.month) {
                    if (this->day < two.day) {
                        answer = true;
                    } else if (this->day == two.day) {
                        if (this->hour < two.hour) {
                            answer = true;
                        } else if (this->hour == two.hour) {
                            if (this->minute < two.minute) {
                                answer = true;
                            } else if (this->minute == two.minute) {
                                if (this->second < two.second) {
                                    answer = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((this->isOurEra == two.isOurEra) and (this->isOurEra == false)) and (answer == true)) {
            answer = false;
        }
        return answer;
    }

    bool operator==(const Date &two) const {
        bool answer = false;
        if (this->isOurEra == two.isOurEra){
            if (this->year == two.year){
                if (this->month == two.month){
                    if (this->day == two.day){
                        if (this->hour == two.hour){
                            if(this->minute == two.minute){
                                if (this->second == two.second){
                                    answer = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return answer;
    }

}; //это не смешно, Боря...

int main() {
    system("chcp 65001"); //проблема с кириллицей
    return 0;
}
