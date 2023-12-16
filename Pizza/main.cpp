#include <iostream>
#include <vector>
using namespace std;

vector<string> namelist = {"Pepperoni", "FourCheese", "Margarita"}; //общий список названий пицц
vector<int> sizelist = {25, 30, 35, 40}; //список размеров пицц

class Pizza{
protected:
    string name;
    string description;
    int size=0;
    float price=0;
    int cheese=0;
    int salt=0;
public:
    Pizza (int size) : size(size) {}
    void addCheese(){cheese ++;};
    void addSalt(){salt ++;}
    void virtual setPrice()=0;
    float getPrice() const{return price;}
    int getCheese() const{return cheese;}
    int getSalt() const {return salt;}
    string getName() const {return name;}
    string getDiscr() const {return description;}
    int getSize() const {return size;}
};

class Pepperoni : public Pizza{
public:
    Pepperoni(int size) :  Pizza(size){
        name = namelist[0];
        price = 10.5 * size; //стартовая цена, зависящая от размера пиццы
        description = "Mozzarella, specialty sauce, pepperoni";
    }
    void setPrice() override {
        this->price = 10.5 * this->size + cheese * 5 + salt * 2;
    }
};

class FourCheese : public Pizza{
public:
    FourCheese(int size) :  Pizza(size){
        name = namelist[1];
        price = 11.5 * size; //стартовая цена, зависящая от размера пиццы
        description = "Mozzarella, cream cheese, cream sauce, grano podano";
    }
    void setPrice() override {
        this->price = 11.5 * this->size + cheese * 3 + salt * 1;
    }
};

class Margarita : public Pizza{
public:
    Margarita(int size) :  Pizza(size){
        name = namelist[2];
        price = 9.5 * size; //стартовая цена, зависящая от размера пиццы
        description = "Tomato sauce, tomatoes, mozzarella";
    }
    void setPrice() override {
        this->price = 9.5 * this->size + cheese * 4 + salt * 5;
    }
};

class Order{
private:
    int quantity;
    struct Node{
        int numberOfPizza;
        Pizza* data;
        Node* next;
        Node* prev;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* current = nullptr;
    void process(){
        int selectedT; //выбранный пользователем тип пиццы
        int selectedS; //выбранный пользователем размер пиццы
        for(int i=0; i<quantity; i++) {//заполняем все пиццы
            cout << "----------Pizza number " << i + 1 << "----------" << endl;
            cout << "Select a pizza type number:" << endl; //выбор типа пиццы из предложенный вариантов
            do {
                for (int j = 1; j < 4; j++) {
                    cout << j << ". " << namelist[j - 1] << "; ";
                }
                cout << endl;
                cin >> selectedT;
                if (selectedT < 1 || selectedT > 3) {
                    cout << "Incorrect input. Try again." << endl; //вывод ошибки
                }
            } while (!(selectedT > 0 && selectedT < 4)); //корректный выбор типа пиццы
            cout << "Select a pizza size number:" << endl; //выбор размера пиццы из предложенный вариантов
            do {
                for (int j = 1; j < 5; j++) {
                    cout << j << ". " << sizelist[j - 1] << "; ";
                }
                cout << endl;
                cin >> selectedS;
                if (!(selectedS == 1 || selectedS == 2 || selectedS == 3 || selectedS == 4)){
                    cout << "Incorrect input. Try again." << endl; //вывод ошибки
                }
            } while (!(selectedS == 1 || selectedS == 2 || selectedS == 3 || selectedS == 4)); //корректный выбор размера пиццы
            current = current = new Node();;
            switch (selectedT){ //создаем новый экземпляр пиццы по указанию пользователя
                case 1: current->data = new Pepperoni(sizelist[selectedS-1]);break;
                case 2:current->data = new FourCheese(sizelist[selectedS-1]);break;
                case 3:current->data = new Margarita(sizelist[selectedS-1]);break;
            }
            cout << "Selected pizza: ";
            printCurrent();
            string wantCheck; //необходима для понимания, хочет ли пользователь добавить сыр или соль в пиццу (string, чтобы уменьшить шанс ошибки)
            do { //добавить еще сыра?
                wantCheck = "";
                cout << "Would you like to add a little more cheese? (1 to YES, 0 to NO)" << endl;
                cin >> wantCheck;
                if (wantCheck == "0" || wantCheck == "1"){
                    if (wantCheck == "1"){
                        current->data->addCheese();
                        cout << "+1 cheese" << endl;
                    }
                } else{
                    cout << "Incorrect input. Try again." << endl;
                }
            } while (wantCheck != "0");
            do { //посолить еще?
                wantCheck = "";
                cout << "Would you like to add a little more salt? (1 to YES, 0 to NO)" << endl;
                cin >> wantCheck;
                if (wantCheck == "0" || wantCheck == "1"){
                    if (wantCheck == "1"){
                        current->data->addSalt();
                        cout << "+1 salt" << endl;
                    }
                } else {
                    cout << "Incorrect input. Try again." << endl;
                }
            } while (wantCheck != "0");
            cout << "End result for the " << i+1 << " pizza: " << endl;
            printCurrent();
            if(i==0){
                head = current;
                head->numberOfPizza = 1;
                tail = head;
            } else {
                tail->next = current;
                current->prev = tail;
                tail = tail->next;
                tail->numberOfPizza = tail->prev->numberOfPizza + 1;
            }
        }
        printFull();
    }


public:
    Order() : quantity(0){}
    void startNew(){
        cout<<"How many pizzas will an order consist of?" << endl;
        cin >> this->quantity;
        process();
    }

    void printCurrent(){
        cout << current->data->getName() << "-"<< current->data->getSize() << " (" << current->data->getDiscr() << ") (" << current->data->getCheese() << " extra cheeses, " << current->data->getSalt() << " extra salts)" << endl;
    }

    void printFull(){
        current = head;
        float sumPrice = 0;
        cout << "\nReceipt" << endl;
        for(int i=1; i<=quantity; i++){
            sumPrice+=current->data->getPrice();
            cout << i << "..." << current->data->getName() << "-" << current->data->getSize() << "..+" << current->data->getCheese() << ".Cheese..+" << current->data->getSalt() << ".Salt..." << current->data->getPrice() << ".rubles" << endl;
            current = current->next;
        }
        cout << "Total..............................." << sumPrice << ".rubles" << endl;
    }
};

int main() {
    Order order1;
    order1.startNew();
    return 0;
}