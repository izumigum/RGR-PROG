#include <iostream>
#include "orders.h"
using namespace std;

class controller {
private:
    funeral_home current_home;
public:
    controller() {
    }
    void execute() {
        int run = 1;
        while (run) {
            menu();
            int var = 0;
            while (var < 1 || var > 8) {
                cout << "Input variant: ";
                cin >> var;
            }
            if (var == 8) {
                run = 0;
            }
            if (var == 1) {
                current_home.print();
            }
            if (var == 2) {
                current_home.addRc();
                cout << "����� ������� ������!";
            }
            if (var == 3) {
                current_home.print();
                cout << "������� ����� ������, ������� ���� �������:\n";
                int n;
                cin >> n;
                current_home.deleteRc(n);
            }
            if (var == 4) {
                current_home.saveToFile(true);
                cout << "������ ������� ���������!" << endl;
            }
            if (var == 5) {
                current_home.saveToFile(false);
                cout << "���� ������� ����������� � ������ ��������!" << endl;
            }
            if (var == 6) {
                current_home.loadFile();
                cout << "������ �� ����� ������� ���������!" << endl;
            }
            if (var == 7) {
                cout << "�������� �����, ������� ������� ���������������:" << endl;
                int choose= 0;
                while (choose < 1 || choose>current_home.getN() + 1) {
                    current_home.print();
                    cout << "[" << current_home.getN() + 1 << "] " << "������." << endl;
                    cin >> choose;

                }
                if (choose != current_home.getN() + 1)
                {
                    current_home.changeRecord(choose);
                    cout << "����� ��������������!";
                }
                
            }
        }
    }

    void menu() {
        cout << "Commands: " << endl;
        cout << "[1] ������� ��� ������" << endl;
        cout << "[2] ������� ����� ������ � ������" << endl;
        cout << "[3] ������� ������ � ������" << endl;
        cout << "[4] �������� ������� ������ � ����" << endl;
        cout << "[5] ������������ ������� ���� � ��������" << endl;
        cout << "[6] ��������� ������ �� �����" << endl;
        cout << "[7] ��������������� �����" << endl;
        cout << "[8] ����� �� ���������" << endl;
    }
};