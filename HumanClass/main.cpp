#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Human{
private:
    string name;
    int age;
    float height;
public:
    Human() : name("Josh"), age(30), height(180) {}
    Human(string n, int a, float h) : name(std::move(n)), age(a), height(h) {}

    string getName() const {return name;}
    int getAge() const {return age;}
    float getHeight() const {return height;}

    void setName (string n) {name = n;}
    void setAge (int a) {age = a;}
    void setHeight (float h) {height = h;}
};

class Student : public Human {
private:
    int course;
public:
    Student() : Human(), course(1) {}
    Student(string n, int a, float h, int c) : Human(n, a, h), course(c){}

    int getCourse() const {return course;}
    void setCourse(int c) {course = c;}
};

class UniversityEmployee : public Human{
private:
    int code;
public:
    UniversityEmployee() : Human(), code(0) {}
    UniversityEmployee(string n, int a, float h, int c) : Human(n, a, h), code(c) {}

    int getCode() const {return code;}
    void setCode(int c) {code = c;}
};

class Lecturer : public UniversityEmployee{
private:
    string subject;
public:
    Lecturer() : UniversityEmployee(), subject("разные") {}
    Lecturer(string n, int a, float h, int c, string s) : UniversityEmployee(n, a, h, c), subject(s) {}

    string getSubject() const {return subject;}
    void setSubject(string s) {subject = s;}
};

class DepartmentDirector : public Lecturer{
private:
    string department;
public:
    DepartmentDirector() : Lecturer(), department("Математика") {}
    DepartmentDirector(string n, int a, float h, int c, string s, string d) : Lecturer(n, a, h, c, s), department(d) {}

    string getDepartment() const {return department;}
    void setDepartment(string d) {department = d;}
};

int main() {
    system("chcp 65001"); //проблема с кириллицей
    Human Adam("Adam", 20, 175);
    Human Eva("Eva", 20, 165);

    Student Robert("Robert", 21, 185, 3);
    cout << Robert.getAge() << "-летний " << Robert.getName() << " учился на " << Robert.getCourse() << " курсе" << endl;
    Robert.setAge(22);
    Robert.setCourse(4);
    cout << "Но время идет. " << Robert.getName() << " стал старше на год. Теперь ему " << Robert.getAge() << " и он на " << Robert.getCourse() << " курсе"<< endl;

    cout << "Помимо него, в университете еще есть ";
    UniversityEmployee Guard;
    cout << Guard.getName() << ", он работает охранником здесь второй месяц. Ему " << Guard.getAge() << endl;
    cout << "Сначала ему дали код работника - " << Guard.getCode() << endl;
    Guard.setCode(42);
    cout << "Но затем сменили. Теперь " << Guard.getName() << " забит в систему под кодом " << Guard.getCode() << endl;

    Lecturer Anastasia("Anastasia", 36, 168, 12, "Физика");
    cout << "Любимый лектор " << Robert.getName() << "а - это " << Anastasia.getName() << ". Её предмет - " << Anastasia.getSubject() << endl;

    DepartmentDirector Paul("Paul", 40, 170, 2, "Проекты в информационных технологиях", "Программная инженерия и искусственный интеллект");
    cout << Robert.getName() << " лично знаком с " << Paul.getName() << ". Он ведет " << Paul.getSubject() << ", а также является главой департамента '" << Paul.getDepartment() << "'" << endl;

    return 0;
}
