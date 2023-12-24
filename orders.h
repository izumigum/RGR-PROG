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
        n = 1;//����� �������
        setlocale(LC_ALL, "ru");
        orders = new record*[n];
        for (int j = 0; j < n; j++) {
            int choose = 0;
            cout << "�������� ��� ������:\n";
            cout << "[1] ����������\n";
            cout << "[2] ��������" << endl;
            while (choose < 1 || choose>2) {
                cin >> choose;
            }
            if (choose ==  1) {
                
                record* newrc = new Pogrebenie;
                newrc->create();//��������� ����� �������
                orders[j] = newrc;//��������� ����� � ������
            }
            else {
                record* newrc= new Cremacia;
                newrc->create();//��������� ����� �������
                orders[j] = newrc;//��������� ����� � ������
            }
        }
    }

    void print() { //����� ������
        setlocale(LC_ALL, "ru");
        for (int i = 0; i < n; i++) {
            record* current_record = orders[i];
            cout << "[" << i + 1 << "] ";
            current_record->print();//�������� ����� �� ������� ������� �����
        }
    }
    void addRc() { //�������� ����� �������
        int choose = 0;
        cout << "�������� ��� ������:\n";
        cout << "[1] ����������\n";
        cout << "[2] ��������" << endl;
        record* newrc; //��������� ��� ����� �����
        while (choose < 1 || choose>2) {
            cin >> choose;
        }
        if (choose == 1) {

            newrc = new Pogrebenie;
            newrc->create(); //�������� ������� �������� �� ����������
        }
        else {
            newrc = new Cremacia;
            newrc->create(); //�������� ������� �������� �� ��������
        }
        record** newor = new record*[n + 1];
        for (int i = 0; i < n; i++) {
            newor[i] = orders[i];
        } //�������� ������ �� ������� � �����
        newor[n] = newrc; //��������� ����� �����, ������� ����� �� 61 ��� 65
        n++; //����������� ����� ����� �������
        orders = newor; //���������� ����� � ����� ������� ���� � ����������� ������ �������
    }
    void addRcFile(record * newrc) {//��������� ����� �� ����� � ������ ������� (126-180) 
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
        for (int i = 0,j=0; i < n; i++,j++) {// i-����������� ������, j-����� ������ � ������� ������
            if (i == (k - 1))i++;//������� ������� ������� ����� �������
            if (i<n)newor[j] = orders[i];//�������� ������ �������� ������� � �����
        }
        n--;
        orders = newor;//������� ����� � �������� ������
    }
    void saveToFile(bool app) {//��������� � ���� (��� ������)
        ofstream out;
        try {
            if (app)
                out.open("orders.txt", ios::app);//ios::app-�������� �����
            else out.open("orders.txt");//���������� �����
        }
        catch (const char* error_message) {//���� ����� ������, �������.
            cout << error_message << endl;
            return;
        }
        if (out.is_open())
        {
            string rcInfo;
            for (int i = 0; i < n; i++) {
                record* cr_rc = orders[i];
               
                if (cr_rc->getType()) {//��������� ��� (���������� ��� ��������)
                    //��������
                    rcInfo = to_string(cr_rc->getType()) + "||" + cr_rc->getClient().getName() + "||" + cr_rc->getClient().getSurname()+"||" + cr_rc->getClient().getNumber() + "||" + cr_rc->getDate() + "||" + to_string(cr_rc->getHB())+"||"+to_string(cr_rc->getHA()) + "||"+cr_rc->getGrob() + "||" + cr_rc->getUrna();
                    
                    
                }
                else {//����������
                    rcInfo = to_string(cr_rc->getType()) + "||" + cr_rc->getClient().getName() + "||" + cr_rc->getClient().getSurname() + "||" + cr_rc->getClient().getNumber() + "||" + cr_rc->getDate() + "||" +
                        to_string(cr_rc->getNBus()) + "||" + to_string(cr_rc->getHB()) + "||" + to_string(cr_rc->getHA()) + "||" + cr_rc->getGrob() + "||" +
                        to_string(cr_rc->getV()) + "||" + to_string(cr_rc->getS()) + "||" + to_string(cr_rc->getA()) + "||" + to_string(cr_rc->getSize());
                }
                out << rcInfo << endl;//�������� � ����
            }
            out.close();//��������� ����
        }
    }
    void loadFile() {//��������� ������ �� �����
        ifstream in("orders.txt");//������� �� �����
        if (in.is_open())//���� ���� ������
        {
            string newrc;
            while (getline(in, newrc)) {//���� ������� ������� �� �����, ������� �� � newrc
                
                int type = stoi(newrc.substr(0, newrc.find("||")));//������ ��� ������
                if (type) {//��������
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
                else {//����������
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
    void changeRecord(int n) {//�������� �����
        orders[n - 1]->change();
    }
    int getN() {
        return n;
    }
};