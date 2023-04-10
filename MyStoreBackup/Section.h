#include "Employee.cpp"
#include <string>
#include <iostream>
using namespace std;

class Section {
private:
	/*поля*/
	string* name;
	Section* Next;
	Section* Previous;
	Employee* Head;
public:
	/*геттеры сеттеры*/
	Employee* GetHead() {
		return Head;
	}
	Section* GetNext() {
		return Next;
	}
	Section* GetPrevious() {
		return Previous;
	}
	void SetHead(Employee* head) {
		Head = head;
	}
	void SetNext(Section* next) {
		Next = next;
	}
	void SetPrevious(Section* prev) {
		Previous = prev;
	}
	string GetName() {
		return *name;
	}
	void SetName(string Name) {
		*name = Name;
	}
	/*Конструктор*/
	Section(string Name) {
		try {
			name = new string();
			Head = new Employee();
		}
		catch (bad_alloc) {
			cerr << "\nНе удалось выделить память." << endl;
			return;
		}
		SetName(Name);
		Head->SetNext(Head);
		Head->SetPrevious(Head);
	}
	/*Деструктор*/
	~Section() {
		delete name;
		name = nullptr;
		while (!isEmpty())
		{
			Employee* temp = Head->GetNext();
			Head->SetNext(temp->GetNext());
			delete temp;
		}
		delete Head;
	}

	/*проверка на пустоту*/
	bool isEmpty() { return Head->GetNext() == Head; }

	/*добавление сотрудника*/
	void Add(string Surname, int Pay, string AfterWhom, int InsertionMode) {
		if (isEmpty() && InsertionMode == 3)
		{
			Employee* NewEmployee = new Employee(Surname, Pay);
			Head->SetNext(NewEmployee);
			Head->SetPrevious(NewEmployee);
			NewEmployee->SetNext(Head);
			NewEmployee->SetPrevious(Head);
		}
		else {
			if (Search(AfterWhom))
			{
				Employee* Current = Search(AfterWhom);
				Employee* newEmployee = new Employee(Surname, Pay);
				//Добавление до
				if (InsertionMode == 1)
				{
					Current->GetPrevious()->SetNext(newEmployee);
					newEmployee->SetPrevious(Current->GetPrevious());
					Current->SetPrevious(newEmployee);
					newEmployee->SetNext(Current);
				}
				//Добавление после
				else if (InsertionMode == 2)
				{
					Current->GetNext()->SetPrevious(newEmployee);
					newEmployee->SetNext(Current->GetNext());
					Current->SetNext(newEmployee);
					newEmployee->SetPrevious(Current);
				}
			}
			else {
				cerr << "В отделе нет такого сотрудника";
			}
		}
	}
	/*удаление сотрудника*/
	void Delete(string EmployeeSurname) {
		if (Head != nullptr)
		{
			Employee* EmployeeToDelete = Search(EmployeeSurname);
			if (EmployeeToDelete != nullptr) {
				cout << "\nУдален сотрудник: " << EmployeeToDelete->GetSurname() << " с заработной платой " << EmployeeToDelete->GetPay() << endl;
				EmployeeToDelete->GetPrevious()->SetNext(EmployeeToDelete->GetNext());
				EmployeeToDelete->GetNext()->SetPrevious(EmployeeToDelete->GetPrevious());
				delete EmployeeToDelete; //тут происходит очистка памяти
				EmployeeToDelete = nullptr;
			}
			else {
				cerr << "\nТакого отдела нету в списке." << endl;
			}
		}
		else
		{
			cerr << "\nОшибка, список не инициализирован." << endl;
		}
	}
	/*добавление в конец (для загрузки ИЗ файла)*/
	void AddLast(string Surname) {
		if (Head != nullptr)
		{
			Employee* NewEmployee = new Employee();
			NewEmployee->SetSurname(Surname);

			Head->GetPrevious()->SetNext(NewEmployee);
			NewEmployee->SetPrevious(Head->GetPrevious());
			NewEmployee->SetNext(Head);
			Head->SetPrevious(NewEmployee);
		}
		else
		{
			cerr << "\nОшибка, список не инициализирован." << endl;
		}
	}
	/*Вывод*/
	void Show() {
		cout << "\nНазвание отдела: " << this->GetName() << endl;
		if (Head->GetNext() != Head) {
			Employee* Current = Head->GetNext();
			while (Current != Head) {
				cout << "\n    Сотрутдник: " << Current->GetSurname() << " " << "Заработная плата: "
					<< Current->GetPay() << endl;
				Current = Current->GetNext();
			}
			return;
		}
		else {
			cerr << "\n    В отделе нет сотрудников." << endl;
		}
	}
	/*Ф-я поиска по фамилии*/
	Employee* Search(string SurName) {
		if (Head != nullptr) {
			Employee* Current = Head->GetNext();
			while (Current != Head) {
				if (Current->GetSurname() == SurName) {
					return Current;
				}
				Current = Current->GetNext();
			}
			return nullptr;
		}
		else {
			cerr << "\nОшибка, список не инициализирован." << endl;
			return nullptr;
		}
	}
};