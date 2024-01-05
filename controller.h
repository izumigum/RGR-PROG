#include <iostream>
#include "house.h"
using namespace std;

class controller {
private:
    funeral_home house;
public:
    controller() {
    }
    void execute() {
        int run = 1;
        while (run) {
            menu();
            int var = 0;
            while (var < 1 || var > 7) {
                cout << "Введите номер команды: ";
                cin >> var;
            }
            if (var == 1) {
                house.get_info();
            }
            if (var == 2) {
                house.new_zakaz();
                cout << "Заказ добавлен." << endl;;
            }
            if (var == 3) {
                int n;
                house.get_info();
                cout << "Введите номер заказа для удаления" << endl; 
                cin >> n;
                house.delete_zakaz(n);
            }
            if (var == 4) {
                house.save_file();
                cout << "Заказы сохранены в файл." << endl;
            }
            if (var == 5) {
                house.load_file();
                cout << "Заказы из файла загружены." << endl;
            }
            if (var == 6) {
                cout << "Выберите номер заказа, для редактирования" << endl;
                int k= 0;
                while (k < 1 || k>house.getN()) {
                    house.get_info();
                    cin >> k;

                }
                house.change_zakaz_info(k);
                cout << "Информация заказа изменина.";
            }
            if (var == 7) {
                run = 0;
            }
        }
    }

    void menu() {
        cout << "Commands: " << endl;
        cout << "1. Вывести информацию всех заказов." << endl;
        cout << "2. Создать новый заказ." << endl;
        cout << "3. Удалить заказ." << endl;
        cout << "4. Сохранить заказы в файл." << endl;
        cout << "5. Загрузить заказы из файла." << endl;
        cout << "6. Изменить информацию заказа." << endl;
        cout << "7. Выход из программы." << endl;
    }
};
