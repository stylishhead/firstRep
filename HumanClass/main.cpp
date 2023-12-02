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
    Human() : name("Josh"), age(18), height(180) {}
    Human(string n, int a, float h) : name(std::move(n)), age(a), height(h) {}

    string getName() const {return name;}
    int getAge() const {return age;}
    float getHeight() const {return height;}

    void setName (string n) {name = n;}
    void setAge (int a) {age = a;}
    void setHeight (float h) {height = h;}
};



int main() {
    system("chcp 65001"); //проблема с кириллицей
    Human Adam("Adam", 20, 175);
    Human Eva("Eva", 20, 165);

    return 0;
}
