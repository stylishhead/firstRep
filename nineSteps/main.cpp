#include <ctime>
#include <iostream>
#include <vector>
using namespace std;
class Student;
class Teacher;
vector<Student> studentList;
vector<Teacher> teacherList;

class Student{
private:
    string name;
    vector<int> marks;
public:
    Student() : name("Josh") {studentList.push_back(*this);};
    Student(string name) : name(name) {studentList.push_back(*this);};

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
    int freak = 0; // переменная, отвечающая за то, ставит ли препод только 5 или 2 (==1 -> ставит 5, ==2 -> ставит 2, иначе...)
    int every = 5; //каждая 5 (по стандарту) оценка менеят настроение
    int statTrak = 0; //кол-во оценок, которые препод поставил студентам
    int random_mark(int x, int y){
        int random = rand() % 2;
        random==1? random=x: random=y;
        return random;
    }
public:
    Teacher(): name("Josh"), mood(true){teacherList.push_back(*this);};
    Teacher(string name): name(name), mood(true){teacherList.push_back(*this);};

    void addMarkTo(Student &student){
        statTrak++;
        switch (this->freak){
            case 1: {
                student.addMark(5);
                break;
            }
            case 2: {
                student.addMark(2);
                break;
            }
            default: {
                switch (mood) {
                    case true: {
                        student.isHonors() ? student.addMark(5) : student.addMark(4);
                        break;
                    }
                    case false: {
                        student.isHonors() ? student.addMark(random_mark(4, 5)) : student.addMark(random_mark(2, 3));
                        break;
                    }
                }
                break;
            }
        }
        if (this->statTrak % every == 0){
            this->mood = !this->mood;
        }
    }

    bool getMood() const {
        return this->mood;
    }

    void setMood(bool mood){
        this->mood = mood;
    }

    void setFreak(int fr){
        this->freak = fr;
    }

    void setEvery(int num){//устанавливает какое количество оценок меняет настроение
        this->every = num;
    }
};

class Lesson{
private:
    Teacher* tchr;
    vector<Student*> comers;
public:
    void addTeacher(Teacher &teacher){
        this->tchr = &teacher;
    }

    void addStudent(Student &student){
        this->comers.push_back(&student);
    }
    void grading(){
        if(!(&tchr == nullptr || comers.empty())) {
            int numberStudents = rand() % (comers.size() + 1) ; //количество студентов, которые получат оценки
            for (int i = 0; i < numberStudents; i++) {
                int stud = rand() % (comers.size()); //номер студента в списке
                switch (this->tchr->getMood()) {
                    case true: { //если хорошее настроение, то 1-5 оценок
                        int y = rand() % 5 + 1;
                        for (int j = 0; j < y; j++) {
                            tchr->addMarkTo(*comers[stud]);
                        }
                    }
                    case false: { //если плохое настроение, то 1-2
                        int y = rand() % 2 + 1;
                        for (int j = 0; j < y; j++) {
                            tchr->addMarkTo(*comers[stud]);
                        }
                    }
                }
            }
        }
    }
};

int main() {
    srand(time(0));
    Student Nick = Student("Nick");
    Student Tony = Student("Tony");

    Teacher James = Teacher("James");
    James.setMood(true);
    James.setEvery(2); //каждую 2 оценку меняется настроение
    James.addMarkTo(Nick);
    James.addMarkTo(Nick);
    cout << James.getMood() << endl;

    return 0;
}
