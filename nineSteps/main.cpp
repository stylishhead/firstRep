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
            return false;
        }
        for (int i=0; i<this->marks.size(); i++){
            if(this->marks[i]!=5){
                return false;
            }
        }
        return true;
    }
};

int main() {
    Student Nick = Student("Nick");
    Nick.addMark(6);
    cout << Nick.isHonors() << endl;
    Nick.addMark(5);
    cout << Nick.isHonors() << endl;

    Student Tony = Student("Tony");
    cout << Tony.isHonors() << endl;

    return 0;
}