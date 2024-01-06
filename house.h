#include <iostream>
#include <string>
#include "zakaz.h"
#include <vector>
#include <fstream>

using namespace std;

class funeral_home {
private:
    int n;
    zakaz** zakazi;
    string vid_groba_pogrebenie[4] = {
        "Элитные. Изготовленные из древесного массива, двукрышечные, с богатой отделкой.",
        "Деревянные. Вскрытые лаком и фигурной отделкой, со съёмной крышкой на винтовых зажимах.",
        "Обитые тканью. Гробы из струганной доски, трапециевидной формы. Крышка съёмная.",
        "Мусульманские. Прямоугольные ящики с минимумом отделки."
    };
    string vid_groba_cremacia[3] = {
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
    funeral_home() {
        n = 1;
        zakazi = new zakaz*[n];
        for (int j = 0; j < n; j++) {
            int select = 0;
            cout << "Выберите тип заказа" << endl;
            cout << "[1] Погребение."<<endl;
            cout << "[2] Кремация." << endl;
            while (select < 1 || select>2) {
                cin >> select;
            }
            if (select == 1) {
                
                zakaz* new_zakaz = new Pogrebenie;
                new_zakaz->create_info();
                zakazi[j] = new_zakaz;
            }
            else {
                zakaz* new_zakaz = new Cremacia;
                new_zakaz->create_info();
                zakazi[j] = new_zakaz;
            }
        }
    }
    int getN() {
        return n;
    }
    void get_info() {
        for (int i = 0; i < n; i++) {
            zakaz* zk = zakazi[i];
            cout << "[" << i + 1 << "] ";
            zk->get_info();
        }
    }
    void new_zakaz() {
        int select = 0;
        cout << "Выберите тип заказа:\n";
        cout << "[1] Погребение."<<endl;
        cout << "[2] Кремация." << endl;
        zakaz* new_zakaz;
        while (select < 1 || select>2) {
            cin >> select;
        }
        if (select == 1) {

            new_zakaz = new Pogrebenie;
            new_zakaz->create_info();
        }
        else {
            new_zakaz = new Cremacia;
            new_zakaz->create_info();
        }
        zakaz** new_zakazi = new zakaz*[n + 1];
        for (int i = 0; i < n; i++) {
            new_zakazi[i] = zakazi[i];
        }
        new_zakazi[n] = new_zakaz;
        n++;
        zakazi = new_zakazi;
    }

    void delete_zakaz(int k) {
        zakaz** newor = new zakaz*[n - 1];
        for (int i = 0,j=0; i < n; i++,j++) {
            if (i == (k - 1))i++;
            if (i<n)newor[j] = zakazi[i];
        }
        n--;
        zakazi = newor;
    }
    void push_zakaz(zakaz* new_zakaz) {
        zakaz** new_zakazi = new zakaz * [n + 1];
        for (int i = 0; i < n; i++) {
            new_zakazi[i] = zakazi[i];
        }
        new_zakazi[n] = new_zakaz;
        n++;
        zakazi = new_zakazi;
    }
      void save_file() {
    ofstream out;
    out.open("zakazi.txt", ios::app);
    if (out.is_open()) {
        string info;
        for (int i = 0; i < n; i++) {
            zakaz *zk = zakazi[i];
            if (zk->getType()) {
                info = to_string(zk->getType()) + ";" + zk->getClient().getname() +
                       ";" + zk->getClient().getsurname() + ";" +
                       zk->getClient().getnumber() + ";" + zk->getDate() + ";" +
                       to_string(zk->getHB()) + ";" + to_string(zk->getHA()) + ";" +
                       zk->getGrob() + ";" + zk->getUrna() + ";";
            } else {
                info = to_string(zk->getType()) + ";" + zk->getClient().getname() +
                       ";" + zk->getClient().getsurname() + ";" +
                       zk->getClient().getnumber() + ";" + zk->getDate() + ";" +
                       to_string(zk->getNBus()) + ";" + to_string(zk->getHB()) + ";" +
                       to_string(zk->getHA()) + ";" + zk->getGrob() + ";" +
                       to_string(zk->getV()) + ";" + to_string(zk->getS()) + ";" +
                       to_string(zk->getA()) + ";" + to_string(zk->getSize()) + ";";
            }
            out << info << endl;
        }
        out.close();
    }
}

void load_file() {
    ifstream in("zakazi.txt");
    if (in.is_open()) {
        string newrc;
        while (getline(in, newrc)) {
            int type = stoi(newrc.substr(0, newrc.find(";")));
            if (type) {
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string name = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string surname = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string number = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string date = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                int heightB = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                int heightA = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string grob = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string urna = newrc.substr(0, newrc.find(";"));
                zakaz *newZakaz = new Cremacia(name, surname, number, date, heightB,
                                              heightA, grob, urna);
                push_zakaz(newZakaz);
            } else {
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string name = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string surname = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string number = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string date = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                int bus = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                int heightB = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                int heightA = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                string grob = newrc.substr(0, newrc.find(";"));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                bool v = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                bool s = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                bool a = stoi(newrc.substr(0, newrc.find(";")));
                newrc = newrc.substr(newrc.find(";") + 1,
                                     newrc.length() - newrc.find(";") - 1);
                int size = stoi(newrc.substr(0, newrc.find(";")));
                zakaz *newZakaz = new Pogrebenie(name, surname, number, date, bus,
                                                heightB, heightA, grob, v, s, a, size);
                push_zakaz(newZakaz);
            }
        }
    }
    in.close();
}
    void change_zakaz_info(int n) {
        zakazi[n - 1]->change_info();
    }

};
