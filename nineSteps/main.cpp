#include <ctime>
#include <iostream>
#include <vector>
#include <string>

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
        } else { //проверка на корректность ввода оценки (5ти бальная система)
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

    string getName(){
        return this->name;
    }

    int getLastMark() const {
        return marks[marks.size()-1];
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

    string getName() const {
        return this->name;
    }
};

class Lesson{
private:
    Teacher* tchr;
    vector<Student*> comers;
    vector<pair<Student&, int>> marks;
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
                            this->marks.emplace_back(*comers[stud],comers[stud]->getLastMark() );
                        }
                    }
                    case false: { //если плохое настроение, то 1-2
                        int y = rand() % 2 + 1;
                        for (int j = 0; j < y; j++) {
                            tchr->addMarkTo(*comers[stud]);
                            this->marks.emplace_back(*comers[stud],comers[stud]->getLastMark() );
                        }
                    }
                }
            }
        }
    }

    bool isOnLesson(Student &student){
        for (int i = 0; i < marks.size(); i++){
            if (student.getName() == marks[i].first.getName()) {
                return true;
            }
        }
        return false;
    }

    Teacher *getTeacher() const {
        return tchr;
    }
};

class Parent{
protected:
    string name;
    bool mood = true;
    vector<Student*> childList;
    void saying(int i){
        cout << childList[i]->getName();
        switch (childList[i]->isHonors()) {
            case true: {
                cout << " is an honors student.";
                break;
            }
            case false: {
                cout << " is learning like everyone else.";
                break;
            }
        }
        if (this->mood) {
            cout << " But no matter how my child learns, I will still always love him.";
        }
        cout << endl;
    }
    bool isHonorsAverage(){
        int x;
        if (childList.size() % 2 == 0){
            x = childList.size()/2;
        } else {
            x = childList.size()/2 + 1;
        }
        int y;
        for (int i = 0; i < childList.size(); i++){
            if (childList[i]->isHonors()) {
                y++;
            }
        }
        if (y>=x){
            return true;
        } else {
            return false;
        }
    }
public:
    Parent() : name("Josh"){};
    Parent(string name) :name(name){};

    void setMood (bool mood) {
        this->mood = mood;
    }

    void addChild(Student &student){
        childList.push_back(&student);
    }

    virtual void somethingAboutEveryone(){
        if (childList.size() > 0) {
            for (int i = 0; i < childList.size(); i++) {
                cout << this->name << ": ";
                saying(i);
            }
        }
    }

    virtual void somethingAboutRandom(){
        if (childList.size() > 0) {
            int i = rand() % (childList.size());
            cout << this->name << ": ";
            saying(i);
        }
    }

    virtual void somethingSummary(){
        cout << this->name << ": ";
        if (isHonorsAverage()){
            cout << "They're all good.";
        } else {
            cout << "I'm proud of them.";
        }
        if (this->mood) {
            cout << " And I love them all very much.";
        } else {
            cout << " But they can do better";
        }
        cout << endl;
    }
    virtual void somethingAboutSpecific(string name){
        bool have = false;
        for (int i = 0; i < childList.size(); i++){
            if(childList[i]->getName()==name){
                cout << this->name << ": ";
                have = true;
                if (isHonorsAverage()){
                    cout << childList[i]->getName() << " is good, too.";
                } else {
                    cout << childList[i]->getName() << " is my kid, and I'll always be proud of him.";
                }
                if (this->mood) {
                    cout << " And I love him very much.\n";
                } else {
                    cout << " But he can do better\n";
                }
            }
        }
        if (have==false){
            cout << "This parent does not have this child" << endl;
        }
    }

    bool isHis(Student &student){
        for (int i=0; i<childList.capacity(); i++){
            if (childList[i]->getName() == student.getName()){
                return true;
            }
        }
        return false;
    }
};

class Grandmother: public Parent {
public:
    Grandmother(){this->name = "Fiby";};
    Grandmother(string name) : Parent(name) {};

    void somethingAboutSpecific(string name) override {
        cout << this->name << ": ";
        bool have = false;
        for (int i=0; i < childList.size(); i++){
            if (childList[i]->getName() == name){
                have = true;
            }
        }
        if (have){
            cout << name << " is my grandchild. I'm so proud of him." << endl;
        } else {
            if (mood) {
                cout << name << " good student. I know him" << endl;
            } else {
                cout << name << " is a disgrace to the family for sure." << endl;
            }
        }
    }
};

class Meeting{
private:
    vector<Teacher*> teachers;
    vector<Student*> students;
    vector<Parent*> parents;
    vector<Lesson*> lessons;
    vector<Student*> withoutParent;
public:
    void addTeacher(Teacher &tchr){
        teachers.push_back(&tchr);
    }
    void addStudent(Student &stud){
        students.push_back(&stud);
    }
    void addParent(Parent &prt){
        parents.push_back(&prt);
    }
    void addLesson(Lesson &lsn){
        lessons.push_back(&lsn);
    }
    void discussion(){
        cout << "Discussion:" << endl;
        for (int i=0; i < lessons.size(); i++){ //идем по всем прошедшим урокам
            bool tchrHere = false;
            for (int l=0; l<teachers.size(); l++) {
                if (lessons[i]->getTeacher()->getName() == teachers[l]->getName()) {
                    tchrHere = true;
                    for (int j = 0; j < students.size(); j++) { //нужно для проверки был ли на уроке студент
                        if (lessons[i]->isOnLesson(*students[j])) {
                            for (int k = 0; k <parents.size(); k++) { //нужно для проверки, если студент присутствовал, то кто родитель
                                if (parents[k]->isHis(*students[j])) {
                                    parents[k]->somethingAboutSpecific(students[j]->getName());
                                }
                            }
                        }
                    }
                }
            }
            if (!tchrHere) {
                for (int j = 0; j < students.size(); j++) { //нужно для проверки был ли на уроке студент
                    if (lessons[i]->isOnLesson(*students[j])) {
                        for (int k = 0; k <parents.size(); k++) { //нужно для проверки, если студент присутствовал, то кто родитель
                            if (parents[k]->isHis(*students[j])) {
                                cout << students[j]->getName() << " is my pride." << endl;
                            }
                        }
                    }
                }
            }
        }
        for (int i=0; i<students.size(); i++){
            bool have = false;
            for (int j=0; j<parents.size(); j++) {
                if (parents[j]->isHis(*students[i])){
                    have = true;
                }
            }
            if (have == false) {
                withoutParent.push_back(students[i]);
            }
        }
        cout << "Discussion end." << endl;
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
    James.addMarkTo(Tony);

    Parent Frank = Parent("Frank");
    Frank.addChild(Nick);

    Grandmother Fiby;
    Fiby.addChild(Tony);

    Lesson lesson1;
    lesson1.addStudent(Tony);
    lesson1.addStudent(Nick);
    lesson1.addTeacher(James);
    lesson1.grading();

    Meeting meeting1;
    meeting1.addTeacher(James);
    meeting1.addStudent(Nick);
    meeting1.addStudent(Tony);
    meeting1.addParent(Frank);
    meeting1.addLesson(lesson1);
    meeting1.addParent(Fiby);

    meeting1.discussion();
    Fiby.setMood(false);
    Fiby.somethingAboutSpecific("Nick");
    return 0;
}
