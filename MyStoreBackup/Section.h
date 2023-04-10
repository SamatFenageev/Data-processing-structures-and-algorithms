#include "Employee.cpp"
#include <string>
#include <iostream>
using namespace std;

class Section {
private:
	/*����*/
	string* name;
	Section* Next;
	Section* Previous;
	Employee* Head;
public:
	/*������� �������*/
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
	/*�����������*/
	Section(string Name) {
		try {
			name = new string();
			Head = new Employee();
		}
		catch (bad_alloc) {
			cerr << "\n�� ������� �������� ������." << endl;
			return;
		}
		SetName(Name);
		Head->SetNext(Head);
		Head->SetPrevious(Head);
	}
	/*����������*/
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

	/*�������� �� �������*/
	bool isEmpty() { return Head->GetNext() == Head; }

	/*���������� ����������*/
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
				//���������� ��
				if (InsertionMode == 1)
				{
					Current->GetPrevious()->SetNext(newEmployee);
					newEmployee->SetPrevious(Current->GetPrevious());
					Current->SetPrevious(newEmployee);
					newEmployee->SetNext(Current);
				}
				//���������� �����
				else if (InsertionMode == 2)
				{
					Current->GetNext()->SetPrevious(newEmployee);
					newEmployee->SetNext(Current->GetNext());
					Current->SetNext(newEmployee);
					newEmployee->SetPrevious(Current);
				}
			}
			else {
				cerr << "� ������ ��� ������ ����������";
			}
		}
	}
	/*�������� ����������*/
	void Delete(string EmployeeSurname) {
		if (Head != nullptr)
		{
			Employee* EmployeeToDelete = Search(EmployeeSurname);
			if (EmployeeToDelete != nullptr) {
				cout << "\n������ ���������: " << EmployeeToDelete->GetSurname() << " � ���������� ������ " << EmployeeToDelete->GetPay() << endl;
				EmployeeToDelete->GetPrevious()->SetNext(EmployeeToDelete->GetNext());
				EmployeeToDelete->GetNext()->SetPrevious(EmployeeToDelete->GetPrevious());
				delete EmployeeToDelete; //��� ���������� ������� ������
				EmployeeToDelete = nullptr;
			}
			else {
				cerr << "\n������ ������ ���� � ������." << endl;
			}
		}
		else
		{
			cerr << "\n������, ������ �� ���������������." << endl;
		}
	}
	/*���������� � ����� (��� �������� �� �����)*/
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
			cerr << "\n������, ������ �� ���������������." << endl;
		}
	}
	/*�����*/
	void Show() {
		cout << "\n�������� ������: " << this->GetName() << endl;
		if (Head->GetNext() != Head) {
			Employee* Current = Head->GetNext();
			while (Current != Head) {
				cout << "\n    ����������: " << Current->GetSurname() << " " << "���������� �����: "
					<< Current->GetPay() << endl;
				Current = Current->GetNext();
			}
			return;
		}
		else {
			cerr << "\n    � ������ ��� �����������." << endl;
		}
	}
	/*�-� ������ �� �������*/
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
			cerr << "\n������, ������ �� ���������������." << endl;
			return nullptr;
		}
	}
};