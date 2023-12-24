#include <iostream>
#include "controller.h"
#include <windows.h>
using namespace std;


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    controller ctrl;
    ctrl.execute();
}