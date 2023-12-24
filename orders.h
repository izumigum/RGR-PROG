#include <iostream>
#include <string>
#include "record.h"
#include <vector>
#include <fstream>

using namespace std;

class funeral_home {
private:
    int n;
    record** orders;
    
public:
    funeral_home() {
        n = 1;//колво заказов
        setlocale(LC_ALL, "ru");
        orders = new record*[n];
        for (int j = 0; j < n; j++) {
            int choose = 0;
            cout << "Выберите тип заказа:\n";
            cout << "[1] Погребение\n";
            cout << "[2] Кремация" << endl;
            while (choose < 1 || choose>2) {
                cin >> choose;
            }
            if (choose ==  1) {
                
                record* newrc = new Pogrebenie;
                newrc->create();//наполняем заказ данными
                orders[j] = newrc;//добавляем заказ в массив
            }
            else {
                record* newrc= new Cremacia;
                newrc->create();//наполняем заказ данными
                orders[j] = newrc;//добавляем заказ в массив
            }
        }
    }

    void print() { //вывод заказа
        setlocale(LC_ALL, "ru");
        for (int i = 0; i < n; i++) {
            record* current_record = orders[i];
            cout << "[" << i + 1 << "] ";
            current_record->print();//вызываем принт из функции первого файла
        }
    }
    void addRc() { //добавить новый элемент
        int choose = 0;
        cout << "Выберите тип заказа:\n";
        cout << "[1] Погребение\n";
        cout << "[2] Кремация" << endl;
        record* newrc; //заготовка под новый заказ
        while (choose < 1 || choose>2) {
            cin >> choose;
        }
        if (choose == 1) {

            newrc = new Pogrebenie;
            newrc->create(); //вызываем функцию создания из погребения
        }
        else {
            newrc = new Cremacia;
            newrc->create(); //вызываем функцию создания из кремации
        }
        record** newor = new record*[n + 1];
        for (int i = 0; i < n; i++) {
            newor[i] = orders[i];
        } //копируем данные из ордерса в ньюор
        newor[n] = newrc; //добавляем новый заказ, который ввели на 61 или 65
        n++; //увеличиваем общее колво заказов
        orders = newor; //измененную копию с новым заказом суем в изначальный массив заказов
    }
    void addRcFile(record * newrc) {//добавляем заказ из файла в массив заказов (126-180) 
        record** newor = new record * [n + 1];
        for (int i = 0; i < n; i++) {
            newor[i] = orders[i];
        }
        newor[n] = newrc;
        n++;
        orders = newor;
    }
    void deleteRc(int k) {
        record** newor = new record*[n - 1];
        for (int i = 0,j=0; i < n; i++,j++) {// i-изначальный массив, j-новый массив с меньшей длиной
            if (i == (k - 1))i++;//скипаем элемент который нужно удалить
            if (i<n)newor[j] = orders[i];//копируем нужные элементы массива в копию
        }
        n--;
        orders = newor;//перенос копии в основной массив
    }
    void saveToFile(bool app) {//сохранить в файл (все заказы)
        ofstream out;
        try {
            if (app)
                out.open("orders.txt", ios::app);//ios::app-дозапись файла
            else out.open("orders.txt");//перезапись файла
        }
        catch (const char* error_message) {//если вдруг ошибка, выводим.
            cout << error_message << endl;
            return;
        }
        if (out.is_open())
        {
            string rcInfo;
            for (int i = 0; i < n; i++) {
                record* cr_rc = orders[i];
               
                if (cr_rc->getType()) {//проверяем тип (Погребение или Кремация)
                    //Кремация
                    rcInfo = to_string(cr_rc->getType()) + "||" + cr_rc->getClient().getName() + "||" + cr_rc->getClient().getSurname()+"||" + cr_rc->getClient().getNumber() + "||" + cr_rc->getDate() + "||" + to_string(cr_rc->getHB())+"||"+to_string(cr_rc->getHA()) + "||"+cr_rc->getGrob() + "||" + cr_rc->getUrna();
                    
                    
                }
                else {//Погребение
                    rcInfo = to_string(cr_rc->getType()) + "||" + cr_rc->getClient().getName() + "||" + cr_rc->getClient().getSurname() + "||" + cr_rc->getClient().getNumber() + "||" + cr_rc->getDate() + "||" +
                        to_string(cr_rc->getNBus()) + "||" + to_string(cr_rc->getHB()) + "||" + to_string(cr_rc->getHA()) + "||" + cr_rc->getGrob() + "||" +
                        to_string(cr_rc->getV()) + "||" + to_string(cr_rc->getS()) + "||" + to_string(cr_rc->getA()) + "||" + to_string(cr_rc->getSize());
                }
                out << rcInfo << endl;//Закинули в Файл
            }
            out.close();//Закрываем файл
        }
    }
    void loadFile() {//Загружаем заказы из файла
        ifstream in("orders.txt");//Достаем из файла
        if (in.is_open())//если файл открыт
        {
            string newrc;
            while (getline(in, newrc)) {//Пока берется строчка из файла, заносим ее в newrc
                
                int type = stoi(newrc.substr(0, newrc.find("||")));//Вывели тип заказа
                if (type) {//Кремация
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string name = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string surname = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string number = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string date = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    int heightB = stoi(newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    int heightA = stoi(newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string grob = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string urna = newrc.substr(0, newrc.find("||"));
                    record* newrc = new Cremacia(name, surname, number, date, heightB, heightA, grob, urna);
                    addRcFile(newrc);
                }
                else {//Погребение
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string name = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string surname = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string number = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string date = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    int bus = stoi(newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    int heightB = stoi(newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    int heightA = stoi(newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    string grob = newrc.substr(0, newrc.find("||"));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    bool v = stoi (newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    bool s = stoi(newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    bool a = stoi(newrc.substr(0, newrc.find("||")));
                    newrc = newrc.substr(newrc.find("||") + 2, newrc.length() - newrc.find("||"));
                    int size = stoi(newrc.substr(0, newrc.find("||")));
                    record* newrc = new Pogrebenie(name,surname,number,date,bus,heightB,heightA,grob,v,s,a,size);
                    addRcFile(newrc);
                }  
            }
        }
        in.close();
    }
    void changeRecord(int n) {//изменить заказ
        orders[n - 1]->change();
    }
    int getN() {
        return n;
    }
};