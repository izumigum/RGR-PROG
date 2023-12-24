#include <iostream>
#include <string>
using namespace std;

class people {
private:
	string name, surname, number;
public:
	string getName() {
		return name;
	}
	string getSurname() {
		return surname;
	}
	string getNumber() {
		return number;
	}
	people() {
		name = "Ваня";
		surname = "Иванов";
		number = "88005553535";
	}
	people(string name, string surname, string number) {
		this->name = name;
		this->surname = surname;
		this->number = number;
	}
	void print() {
		cout << surname << " " << name << " - " << number << endl;;
	}
};
