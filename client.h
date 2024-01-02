#include <iostream>
#include <string>
using namespace std;

class client {
private:
	string name, surname, number;
public:
	client(string name, string surname, string number) {
		this->name = name;
		this->surname = surname;
		this->number = number;
	}
	client() {
		name = "Антон";
		surname = "Красов";
		number = "911";
	}
	string getname() {
		return name;
	}
	string getsurname() {
		return surname;
	}
	string getnumber() {
		return number;
	}


	void print() {
		cout << surname << " " << name << " : " << number << endl;;
	}
};
