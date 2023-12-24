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
                cout << "Заказ успешно создан!";
            }
            if (var == 3) {
                current_home.print();
                cout << "Введите номер заказа, которой надо удалить:\n";
                int n;
                cin >> n;
                current_home.deleteRc(n);
            }
            if (var == 4) {
                current_home.saveToFile(true);
                cout << "Заказы успешно сохранены!" << endl;
            }
            if (var == 5) {
                current_home.saveToFile(false);
                cout << "Файл успешно перезаписан с новыми заказами!" << endl;
            }
            if (var == 6) {
                current_home.loadFile();
                cout << "Заказы из файла успешно загружены!" << endl;
            }
            if (var == 7) {
                cout << "Выберите заказ, который следует отредактировать:" << endl;
                int choose= 0;
                while (choose < 1 || choose>current_home.getN() + 1) {
                    current_home.print();
                    cout << "[" << current_home.getN() + 1 << "] " << "Отмена." << endl;
                    cin >> choose;

                }
                if (choose != current_home.getN() + 1)
                {
                    current_home.changeRecord(choose);
                    cout << "Заказ отредактирован!";
                }
                
            }
        }
    }

    void menu() {
        cout << "Commands: " << endl;
        cout << "[1] Вывести все заказы" << endl;
        cout << "[2] Создать новую запись о заказе" << endl;
        cout << "[3] Удалить запись о заказе" << endl;
        cout << "[4] Добавить текущие заказы в файл" << endl;
        cout << "[5] Перазаписать текущий файл с заказами" << endl;
        cout << "[6] Загрузить заказы из файла" << endl;
        cout << "[7] Отредактировать заказ" << endl;
        cout << "[8] Выход из программы" << endl;
    }
};