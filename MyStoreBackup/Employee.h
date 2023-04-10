
#include <string>
#include <iostream>
using namespace std;
class Employee
{
private:
	int* pay;
	string* surname;
	Employee* Next;
	Employee* Previous;
public:
	/*Инкапсуляция.
	Геттер = возвращает зарплату или фамилию.
	Сеттер задает ЗП или фамилию*/
	void SetNext(Employee* next) {
		Next = next;
	}
	void SetPrevious(Employee* prev) {
		Previous = prev;
	}
	Employee* GetNext() {
		return Next;
	}
	Employee* GetPrevious() {
		return Previous;
	}
	void SetSurname(string Surname) {
		*surname = Surname;
	}
	string GetSurname() {
		return *surname;
	}
	void SetPay(int Pay) {
		*pay = Pay;
	}
	int GetPay() {
		return *pay;
	}
	/*Конструктор*/
	Employee(string Surname, int Pay) {
		pay = new int();
		surname = new string();
		SetSurname(Surname);
		SetPay(Pay);
		SetNext(this);
		SetPrevious(this);
	}
	Employee() {
		try
		{
			pay = new int();
			surname = new string();
		}
		catch (const std::exception&)
		{
			cerr << "\nНе удалось выделить память." << endl;
			return;
		}
		SetSurname("HEAD");
		SetNext(this);
		SetPrevious(this);
		SetPay(0);
	}
	/*Деструктор.
	Если бы не было такой явной очистки памяти, у нас бы после удаления всей структуры память была бы все еще занята*/
	~Employee() {
		delete pay;
		pay = nullptr;
		delete surname;
		surname = nullptr;
		Next = nullptr;
		Previous = nullptr;
	}
};