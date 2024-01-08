#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

class Student{
private:
    string name;
    vector<int> marks;
public:
    Student() : name("Josh") {};
    Student(string name) : name(name) {};

    void addMark(int mark){ //добавление оценки
        if (mark<=5 && mark >=1){
            this->marks.push_back(mark);
        }else{ //проверка на корректность ввода оценки (5-ти бальная система)
            cout << this->name << " was given the wrong grade - " << mark << endl;
        }
    }

    bool isHonors(){ //является ли отличником студент
        if(this->marks.size()==0){
            return true; //изменил, чтобы при выставлении оценки за счет настроения преподавателя было разнообразие студентов (логика: отличник не тот у кого все оценки 5, а тот у кого нет плохих (ну типа))
        }
        for (int i=0; i<this->marks.size(); i++){
            if(this->marks[i]!=5){
                return false;
            }
        }
        return true;
    }
};

class Teacher{
private:
    string name;
    bool mood;
    int random_mark(int x, int y){
        int random = rand() % 2;
        random==1? random=x: random=y;
        return random;
    }
public:
    Teacher(): name("Josh"){};
    Teacher(string name): name(name), mood(true){};


    void addMarkTo(Student &student){
        switch(mood){
            case true: student.isHonors()? student.addMark(5) : student.addMark(4);
            case false: student.isHonors()? student.addMark(random_mark(4,5)) : student.addMark(random_mark(2,3));
        }
    }

    void setMood(bool mood){
        this->mood = mood;
    }
};

int main() {
    srand(time(0));
    Student Nick = Student("Nick");
    Student Tony = Student("Tony");

    Teacher James = Teacher("James");
    James.addMarkTo(Nick);
    James.addMarkTo(Tony);
    cout << Nick.isHonors() << endl;
    cout << Tony.isHonors() << endl;
    return 0;
}
