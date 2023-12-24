#include <iostream>
#include <string>
#include <stdlib.h>
#include "people.h"
#include <time.h>
#include <map>
using namespace std;

class record {
protected:
    people client;
    int heightB, heightA,type;
    string date, grob;
public:
    people getClient() {
        return client;
    }
    string getClientInfo() {
        client.print();
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
    virtual void print() = 0;//виртуальные функции для дальнейшего их переопредления в классах наследниках
    virtual void change() = 0;
    virtual void create() = 0;
    virtual int getNBus() = 0;
    virtual bool getV() = 0;
    virtual bool getS() = 0;
    virtual bool getA() = 0;
    virtual int getSize() = 0;

    bool check_year(int y) {
        if (y % 400 == 0)return true;
        else {
            if (y % 100 == 0)return false;
            else {
                if (y % 4 == 0)return true;
                else return false;
            }
        }
    }

    bool check_date(string date) {
        int p1 = date.find('.');
        int p2 = date.find('.', p1 + 1);
        if (p1 == -1 || p2 == -1) {
            cout << "Некорректная дата." << endl;
            return false;
        }
        int d = stoi(date.substr(0, p1));
        int m = stoi(date.substr(p1 + 1, p2 - p1));
        int y = stoi(date.substr(p2 + 1, date.length() - p2));
        if (y < 0 || m>12 || m < 1 || d < 1) {
            cout << "Некорректная дата." << endl;
            return false;
        }
        map<string, int> days;
        days["1"] = 31;
        if (check_year(y))days["2"] = 29;
        else days["2"] = 28;
        days["3"] = 31;
        days["4"] = 30;
        days["5"] = 31;
        days["6"] = 30;
        days["7"] = 31;
        days["8"] = 31;
        days["9"] = 30;
        days["10"] = 31;
        days["11"] = 30;
        days["12"] = 31;
        if (d > days[to_string(m)])
        {
            cout << "Некорректная дата." << endl;
            return false;
        }
        return true;
    }


};

class Pogrebenie :public record{
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
    Pogrebenie(string name,string surname,string number, string date,int bus_n,int heightB,int heightA,string grob,bool venok,bool stone,bool relig_attr,int sizeclothes) {
        this->client = people(name, surname, number);
        this->date = date;
        this->bus_n = bus_n;
        this->heightB = heightB;
        this->heightA = heightA;
        this->grob = grob;
        this->venok = venok;
        this->stone = stone;
        this->relig_attr = relig_attr;
        this->sizeclothes = sizeclothes;
    }

    void create() {
        string name, surname, number;

        cout << "Укажите ваше имя и фамилию: ";
        cin >> name >> surname;

        cout << "Укажите номер телефона для связи: ";
        cin >> number;
        client = people(name, surname, number);
        cout << "Введите дату проведения прощальной церемонии: ";
        string newdate;
        do 
        {
            cin >> newdate;
        } while (!(check_date(newdate)));
        date = newdate;

        cout << "Введите кол-во мест в автобусе, который доставит гостей до места погребения: ";
        cin >> bus_n;

        cout << "Введите рост усопшего, до и после смерти: ";
        cin >> heightB >> heightA;

        cout << "Укажите вид гроба, который вы предпочитаете увидеть на похоронах:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "[" << i + 1 << "] " << vid_groba[i]<<" "<<desc[i] << endl;
        }
        int choose = 0;
        while (choose < 1 || choose>4) {
            cin >> choose;
        }
        grob = vid_groba[choose - 1];
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
     void print() {
        client.print();
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
    void change() {
        cout << "Выберите пункт заказа, который вы хотели бы отредактировать:\n";
        cout << "1 - Дата\n";
        cout << "2 - Количество людей в автобусе\n";
        cout << "3 - Вид гроба\n";
        cout << "4 - Информацию о клиенте\n";
        cout << "5 - Рост до смерти\n";
        cout << "6 - Рост после смерти\n";
        cout << "7 - Наличие венка\n";
        cout << "8 - Наличие могильного камня\n";
        cout << "9 - Наличие религ. атр.\n";
        cout << "10 - Размер одежды\n";
        int choose = 0;
        while (choose < 1 || choose>10){
            cin >> choose;
        }
        switch (choose){
        case 1:
            {
            cout << "Введите дату проведения прощальной церемонии: ";
            string newdate;
            do
            {
                cin >> newdate;
            } while (!(check_date(newdate)));
            date = newdate;
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
            int choose = 0;
            while (choose < 1 || choose>4) {
                cin >> choose;
            }
            grob = vid_groba[choose - 1];
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
            client = people(name, surname, number);
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
class Cremacia :public record{
private:
    string urna;
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
        client = people(name, surname, number);
        this->date = date;
        this->heightB = heightB;
        this->heightA = heightA;
        this->grob = grob;
        this->urna = urna;
        this->type = 1;
    }
    void create() {
        string name, surname, number;
        int grob_n, urna_n;
        cout << "Укажите ваше имя и фамилию: ";
        cin >> name >> surname;

        cout << "Укажите номер телефона для связи: ";
        cin >> number;
        client = people(name, surname, number);
        cout << "Введите дату проведения прощальной церемонии: ";
        string newdate;
        do
        {
            cin >> newdate;
        } while (!(check_date(newdate)));
        date = newdate;

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
    void print() {
        client.print();
        cout << "Тип заказа: Кремация;" << " Дата: " << date << ";\nРост усопшего (b/a): "
            << heightB << " - " << heightA << "; Вид гроба: " << grob<<"; Материал урны: "<<urna<<endl;
    }
    string getUrna() {
        return urna;
    }
    void change() {
        cout << "Выберите пункт заказа, который вы хотели бы отредактировать:\n";
        cout << "1 - Дата\n";
        cout << "2 - Рост до смерти\n";
        cout << "3 - Рост после смерти\n";
        cout << "4 - Информацию о клиенте\n";
        cout << "5 - Вид гроба\n";
        cout << "6 - Материал урны\n";
        int choose = 0;
        while (choose < 1 || choose>6) {
            cin >> choose;
        }
        switch (choose) {
        case 1: {
            cout << "Введите дату проведения прощальной церемонии: ";
            string newdate;
            do
            {
                cin >> newdate;
            } while (!(check_date(newdate)));
            date = newdate;
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
            client = people(name, surname, number);
            break;
        }
        case 5:
        {
            cout << "Укажите вид гроба, который вы предпочитаете увидеть во время кремации:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "[" << i + 1 << "] " << vid_groba[i] << endl;
            }
            int choose = 0;
            while (choose < 1 || choose>3) {
                cin >> choose;
            }
            grob = vid_groba[choose - 1];
            break;
        }
        case 6: {
            cout << "Укажите вид гроба, который вы предпочитаете увидеть во время кремации:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "[" << i + 1 << "] " << vid_groba[i] << endl;
            }
            int choose = 0;
            while (choose < 1 || choose>3) {
                cin >> choose;
            }
            grob = vid_groba[choose - 1];
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