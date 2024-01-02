#include <iostream>
#include <string>
#include <stdlib.h>
#include "client.h"
#include <time.h>
using namespace std;

class zakaz {
protected:
    client cl;
    int heightB, heightA,type;
    string date, grob;
public:
    client getClient() {
        return cl;
    }
    int getType() {
        return type;
    }
    string getDate() {
        return date;
    }
    string getGrob() {
        return grob;
    }
    int getHB() {
        return heightB;
    }
    int getHA() {
        return heightA;
    }
    virtual string getUrna() = 0;
    virtual void get_info() = 0;
    virtual void change_info() = 0;
    virtual void create_info() = 0;
    virtual int getNBus() = 0;
    virtual bool getV() = 0;
    virtual bool getS() = 0;
    virtual bool getA() = 0;
    virtual int getSize() = 0;
};

class Pogrebenie :public zakaz{
private:
    int bus_n, sizeclothes;

    string vid_groba[4] = {
        "Элитный.",
        "Деревянный.",
        "Обитый тканью.",
        "Мусульманский."
    };
    string desc[4] = {
        "Изготовленный из древесного массива, двукрышечные, с богатой отделкой.",
        "Вскрытый лаком и фигурной отделкой, со съёмной крышкой на винтовых зажимах.",
        "Гробы из струганной доски, трапециевидной формы. Крышка съёмная.",
        "Прямоугольные ящики с минимумом отделки."
    };

    bool venok = false, stone = false, relig_attr = false;
public:
    Pogrebenie() {
        this->type = 0;
    }
    Pogrebenie(string name,string surname,string number, string date,int n,int heightB,int heightA,string grob,bool venok,bool stone,bool relig_attr,int sizeclothes) {
        this->cl = *(new client(name, surname, number));
        this->date = date;
        this->bus_n = n;
        this->heightB = heightB;
        this->heightA = heightA;
        this->grob = grob;
        this->venok = venok;
        this->stone = stone;
        this->relig_attr = relig_attr;
        this->sizeclothes = sizeclothes;
    }
    void create_info() {
        string name, surname, number;

        cout << "Укажите ваши имя и фамилию: ";
        cin >> name >> surname;

        cout << "Укажите номер телефона для связи: "; cin >> number;
        cl = client(name, surname, number);
        cout << "Введите дату проведения прощальной церемонии: ";
        cin >> date;

        cout << "Введите кол-во мест в автобусе, который доставит гостей до места погребения: ";
        cin >> bus_n;

        cout << "Введите рост усопшего, до и после смерти: ";
        cin >> heightB >> heightA;

        cout << "Укажите вид гроба, который вы предпочитаете увидеть на похоронах:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "[" << i + 1 << "] " << vid_groba[i]<<" "<<desc[i] << endl;
        }
        int k = 0;
        while (k < 1 || k>4) {
            cin >> k;
        }
        grob = vid_groba[k - 1];
        string select = "";
        while (select != "Y" && select != "N" && select != "y" && select != "n") {
            cout << "Нужен ли венок? [Y/N]" << endl;
            cin >> select;
        }
        if (select == "Y" or select == "y") venok = true;

        select = "";
        while (select != "Y" && select != "N" && select != "y" && select != "n") {
            cout << "Нужен ли мемориальный камень? Если нет, вместо камня будет стоять крест. [Y/N]" << endl;
            cin >> select;
        }
        if (select == "Y" or select == "y") stone = true;

        select = "";
        while (select != "Y" && select != "N" && select != "y" && select != "n") {
            cout << "Нужны ли религиозные атрибуты? [Y/N]" << endl;
            cin >> select;
        }
        if (select == "Y") relig_attr = true;

        cout << "Введите размер одежды покойного: ";
        cin >> sizeclothes;
    }
    
    client getClient() {
        return cl;
    }
    
    string getClientInfo() {
        cl.print();
    }
    int getNBus() {
        return bus_n;
    }
    bool getV() {
        return venok;
    }
    bool getS() {
        return stone;
    }
    bool getA() {
        return relig_attr;
    }
    int getSize() {
        return sizeclothes;
    }
    void get_info() {
        cl.print();
        string v, s, a;

        if (venok)v = "Да";
        else v = "Нет";

        if (stone)s  = "Да";
        else s = "Нет";

        if (relig_attr)a = "Да";
        else a = "Нет";

        cout << "Тип заказа: Погребение;" << " Дата: " <<date <<"; Количество мест в автобусе: " <<bus_n<<"; Венок: "<<v<<"; Могильный камень: " <<s<<"; Аттрибуты: "<<a<<"\nРост усопшего (b / a): " 
            << heightB<<" - " <<heightA<<"; Размер одежды: " <<sizeclothes<< "; Тип гроба: "<<grob<<endl;
    }
    string getUrna() {
        return "";
    }
    void change_info() {
        cout << "Выберите пункт заказа, который вы хотели бы отредактировать:\n";
        cout << "(1). Дата" << endl;
        cout << "(2). Количество людей в автобусе" << endl;
        cout << "(3). Вид гроба" << endl;
        cout << "(4). Информацию о клиенте" << endl;
        cout << "(5). Рост до смерти" << endl;
        cout << "(6). Рост после смерти" << endl;
        cout << "(7). Наличие венка" << endl;
        cout << "(8). Наличие могильного камня" << endl;
        cout << "(9). Наличие религ. атр." << endl;
        cout << "(10). Размер одежды" << endl;
        int select = 0;
        while (select < 1 || select>10){
            cin >> select;
        }
        switch (select){
        case 1:
            {
            cout << "Введите дату проведения прощальной церемонии: ";
            cin >> date;
            break;
        }
        case 2:
        {
            cout << "Введите кол-во мест в автобусе, который доставит гостей до места погребения: ";
            cin >> bus_n;
            break;
        }
        case 3:
        {
            cout << "Укажите вид гроба, который вы предпочитаете увидеть на похоронах:" << endl;
            for (int i = 0; i < 4; i++) {
                cout << "[" << i + 1 << "] " << vid_groba[i] << " " << desc[i] << endl;
            }
            int k = 0;
            while (k < 1 || k>4) {
                cin >> k;
            }
            grob = vid_groba[k - 1];
            break;
        }
        case 4:
        {
            string name, surname, number;
            cout << "Укажите имя нового клиента: ";
            cin >> name;
            cout << "Укажите фамилию нового клиента: ";
            cin >> name;
            cout << "Укажите номер телефона нового клиента для дальнейшей связи: ";
            cin >> number;
            cl = client(name, surname, number);
            break;
        }
        case 5: {
            cout << "Введите рост усопшего до смерти: ";
            cin >> heightB;
            break;
        }
        case 6: {
            cout << "Введите рост усопшего после смерти: ";
            cin >> heightA;
            break;
        }
        case 7: {
            string select = "";
            while (select != "Y" && select != "N" && select != "y" && select != "n") {
                cout << "Нужен ли венок? [Y/N]" << endl;
                cin >> select;
            }
            if (select == "Y" or select == "y") venok = true;
            else venok = false;
            break;
        }
        case 8: {
            string select = "";
            while (select != "Y" && select != "N" && select != "y" && select != "n") {
                cout << "Нужен ли мемориальный камень? Если нет, вместо камня будет стоять крест. [Y/N]" << endl;
                cin >> select;
            }
            if (select == "Y" or select == "y") stone = true;
            else stone = false;
            break;
        }
        case 9: {
            string select = "";
            while (select != "Y" && select != "N" && select != "y" && select != "n") {
                cout << "Нужны ли религиозные атрибуты? [Y/N]" << endl;
                cin >> select;
            }
            if (select == "Y") relig_attr = true;
            else relig_attr = false;
            break;
        }
        case 10: {
            cout << "Введите размер одежды покойного: ";
            cin >> sizeclothes;
            break;
        }
        default:
            break;
        }
    }
};
class Cremacia :public zakaz{
private:
    string urna;
    int urna_n;
    string vid_groba[3] = {
        "Картонный",
        "Ротанговый",
        "Фанерный",
    };

    string vid_urni[4] = {
        "Деревянная",
        "Керамическая",
        "Фарфоровая",
        "Гипсовая",
    };

public:
    Cremacia() { this->type = 1; }
    Cremacia(string name, string surname, string number, string date, int heightB, int heightA, string grob, string urna) {
        cl = client(name, surname, number);
        this->date = date;
        this->heightB = heightB;
        this->heightA = heightA;
        this->grob = grob;
        this->urna = urna;
        this->type = 1;
    }
    void create_info() {
        string name, surname, number;
        int grob_n, urna_n;
        cout << "Укажите ваше имя и фамилию: ";
        cin >> name >> surname;

        cout << "Укажите номер телефона для связи: ";
        cin >> number;
        cl = client(name, surname, number);
        cout << "Введите дату проведения прощальной церемонии: ";
        cin >> date;

        cout << "Введите рост усопшего, до и после смерти: ";
        cin >> heightB >> heightA;

        cout << "Укажите вид гроба, который вы предпочитаете увидеть во время кремации:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "[" << i + 1 << "] " << vid_groba[i] << endl;
        }
        int choose = 0;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        grob = vid_groba[choose - 1];

        cout << "Из какого материала изготовить урну?" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "[" << i + 1 << "] " << vid_urni[i] << endl;
        }
        choose = 0;
        while (choose < 1 || choose>4) {
            cin >> choose;
        }
        urna = vid_urni[choose - 1];
    }
    void get_info() {
        cl.print();
        cout << "Тип заказа: Кремация;" << " Дата: " << date << ";\nРост усопшего (b/a): "
            << heightB << " - " << heightA << "; Вид гроба: " << grob<<"; Материал урны: "<<urna<<endl;
    }
    string getUrna() {
        return urna;
    }
    void change_info() {
        cout << "Выберите пункт заказа, который вы хотели бы отредактировать" << endl;
        cout << "(1). Дата" << endl;
        cout << "(2). Рост до смерти" << endl;
        cout << "(3). Рост после смерти" << endl;
        cout << "(4). Информацию о клиенте" << endl;
        cout << "(5). Вид гроба" << endl;
        cout << "(6). Материал урны" << endl;;
        int select = 0;
        while (select < 1 || select>6) {
            cin >> select;
        }
        switch (select) {
        case 1: {
            cout << "Введите дату проведения прощальной церемонии: ";
            cin >> date;
            break;
        }
        case 2: {
            cout << "Введите рост усопшего до смерти: ";
            cin >> heightB;
            break;
        }
        case 3: {
            cout << "Введите рост усопшего после смерти: ";
            cin >> heightA;
            break;
        }
        case 4:
        {
            string name, surname, number;
            cout << "Укажите имя нового клиента: ";
            cin >> name;
            cout << "Укажите фамилию нового клиента: ";
            cin >> name;
            cout << "Укажите номер телефона нового клиента для дальнейшей связи: ";
            cin >> number;
            cl = client(name, surname, number);
            break;
        }
        case 5:
        {
            cout << "Укажите вид гроба, который вы предпочитаете увидеть во время кремации:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "[" << i + 1 << "] " << vid_groba[i] << endl;
            }
            int k = 0;
            while (k < 1 || k>3) {
                cin >> k;
            }
            grob = vid_groba[k - 1];
            break;
        }
        case 6: {
            cout << "Укажите вид гроба, который вы предпочитаете увидеть во время кремации:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "[" << i + 1 << "] " << vid_groba[i] << endl;
            }
            int k = 0;
            while (k < 1 || k>3) {
                cin >> k;
            }
            grob = vid_groba[k - 1];
        }
        default: {
            break;
        }
        }
    }
    int getNBus() {
        return 0;
    }
    bool getV() {
        return 0;
    }
    bool getS() {
        return 0;
    }
    bool getA() {
        return 0;
    }
    int getSize() {
        return 0;
    }
};
