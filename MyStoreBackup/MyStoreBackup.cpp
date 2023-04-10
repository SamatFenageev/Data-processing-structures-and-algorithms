#include <iostream>
#include "Store.cpp"
#include <string>
#include <Windows.h>
#include <sstream>
using namespace std;

void NewStore();
void AddSection();
void AddEmployee();
void Show();
void DeleteSection();
void DeleteEmployee();
void Upload();
void DownLoad();
void SearchSection();
void SearchEmployee();
void ClearList();
int GetInt(string Str);
string GetString(string Str);

Store* CurrentStore;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");

	bool Stop = false;
	while (!Stop) {
		flush(cout);
		int Act = GetInt("\n1 - Новый магазин(удалив старый)\n2 - Добавить отдел\n3 - Добавить сотрудника\n4 - Вывести весь список\n5 - Удалить отдел\n6 - Удалить сотрудника\n7 - Поиск отдела\n8 - Поиск сотрудника\n9 - Загрузить из файла \"Res.txt\"\n10 - Выгрузка в файл\n11 - Удалить структуру\n12 - Выход\n");
		switch (Act)
		{
		case 1:			//новый магазин
			system("cls");
			NewStore();
			break;
		case 2:			//Добавить отдел
			system("cls");
			AddSection();
			break;
		case 3:			//Добавить сотрудника
			system("cls");
			AddEmployee();
			break;
		case 4:			//Вывод
			system("cls");
			Show();
			break;
		case 5:			//Удалить отдел
			system("cls");
			DeleteSection();
			break;
		case 6:			//Удалить сотрудника
			system("cls");
			DeleteEmployee();
			break;
		case 7:			//Найти отдел
			system("cls");
			SearchSection();
			break;
		case 8:			//Найти сотрудника
			system("cls");
			SearchEmployee();
			break;
		case 9:			//Загрузка из файла
			system("cls");
			Upload();
			break;
		case 10:			//Выгрузка в файл
			system("cls");
			DownLoad();
			break;
		case 11:			//Выход
			system("cls");
			ClearList();
			break;
		case 12:
			Stop = true;
			break;
		default:
			break;
		}
	}

}

/*GetString - функция, которая выводит строку Str на консоль и запрашивает
у пользователя ввод. Он будет невалидным, если есть символ отличный от буквы или пробела.
В этом случае запрос повторяется*/
string GetString(string Str) {
	string String;
	while (1) {
		cout << Str << endl;
		getline(cin, String);
		bool BReject = false;
		for (unsigned int i = 0; i < String.length() && !BReject; i++) {
			if (!isdigit(String[i])) { continue; }
			if (isspace(String[i])) { continue; }
			BReject = true;
		}
		if (!BReject) break;
	}
	return String;
}
/*Аналогично GetString функция GetInt проверяет ввод на цифры.
Если в вводе присутствует символ, запрос повторяется*/
int GetInt(string Str) {
	string String;
	int Val;
	while (1) {
		cout << Str << endl;
		getline(cin, String);
		bool BReject = false;
		for (unsigned int i = 0; i < String.length() && !BReject; i++) {
			if (isdigit(String[i])) continue;
			BReject = true;
		}
		if (!BReject) break;
	}
	std::stringstream StrStream;
	StrStream << String;
	StrStream >> Val;
	return Val;
}
void NewStore() {
	if (CurrentStore != nullptr) {
		ClearList();
	}
	if (CurrentStore == nullptr) {
		CurrentStore = new Store(GetString("\nВведите название нового магазина: "));
	}
}
void AddSection() {
	if (CurrentStore != nullptr) {
		if (CurrentStore->GetHead()->GetNext() != CurrentStore->GetHead()) {
			CurrentStore->AddSection(GetString("\nВведите название нового отдела: "));
		}
		else {
			CurrentStore->SetFirst(GetString("\nВведите название первого отдела: "));
		}
	}
	else {
		cerr << "Список не инициализирован." << endl;
	}
}
void AddEmployee() {
	int Act;
	if (CurrentStore != nullptr)
	{
		string SectName = GetString("\nВведите название отдела, в который хотите добавить сотрудника: ");
		Section* WhatSection = CurrentStore->SearchForID(SectName);
		if (WhatSection == nullptr)
		{
			cerr << "\nТакого отдела не существует";
		}
		else {
			if (WhatSection->isEmpty())
			{
				string EmployeeSurname = GetString("\n Введите фамилию сотрудника, которого нужно добавить: ");
				int EmployeeSalary = GetInt("\n Введите зарплату сотрудника: ");
				CurrentStore->AddSub(SectName, EmployeeSurname, EmployeeSalary, "", 3);
				return;
			}
			string WhatEmployee = GetString("\n Введите фамилию сотрудника, до/после которого нужно добавить: ");
			if (WhatSection->Search(WhatEmployee) != nullptr)
			{

				int InsertionMode = GetInt("\n Добавить до(1)/после(2) него? ");
				if (InsertionMode != 1 && InsertionMode != 2)
				{
					cerr << "\nНет такого варианта";
				}
				else {
					string EmployeeSurname = GetString("\n Введите фамилию сотрудника, которого нужно добавить: ");
					int EmployeeSalary = GetInt("\n Введите зарплату сотрудника: ");
					CurrentStore->AddSub(SectName, EmployeeSurname, EmployeeSalary, WhatEmployee, InsertionMode);
				}
			}
			else
			{
				cerr << "\nТакого сотрудника не существует";
			}
		}
	}
	else {
		cerr << "Список не инициализирован." << endl;
	}
}
void Show() {
	if (CurrentStore != nullptr) {
		CurrentStore->Show();
	}
	else {
		cerr << "Список не инициализирован." << endl;
	}
}
void DeleteSection() {
	if (CurrentStore != nullptr) {
		if (CurrentStore->GetHead()->GetNext() == CurrentStore->GetHead() && CurrentStore->GetHead()->GetPrevious() == CurrentStore->GetHead()) {
			cerr << "Список пуст." << endl;
			return;
		}
		string SectionDel = GetString("Введите название отдела для удаления: ");
		if (CurrentStore->SearchForID(SectionDel) != nullptr) {
			CurrentStore->Delete(SectionDel);
		}
		else {
			cerr << "В списке нет такого отдела." << endl;
		}
	}
	else {
		cerr << "Список не инициализирован." << endl;
	}
}
void DeleteEmployee() {
	if (CurrentStore != nullptr) {
		if (CurrentStore->GetHead()->GetNext() == CurrentStore->GetHead() && CurrentStore->GetHead()->GetPrevious() == CurrentStore->GetHead()) {
			cerr << "Список пуст." << endl;
			return;
		}
		string SectionToDelSub = GetString("Введите название отдела в котором нужно удалить сотрудника: ");
		if (CurrentStore->SearchForID(SectionToDelSub) != nullptr) {
			string EmployeeSurname = GetString("Введите фамилию удаляемого сотрудника: ");
			if (CurrentStore->SearchForID(SectionToDelSub)->Search(EmployeeSurname) != nullptr)
			{
				CurrentStore->DeleteSub(SectionToDelSub, EmployeeSurname);
			}
			else {
				cerr << "Такого сотрудника не существует." << endl;
			}
		}
		else {
			cerr << "В списке нет такого отдела." << endl;
		}
	}
	else {
		cerr << "Список не инициализирован." << endl;
	}
}
void ClearList() {
	if (CurrentStore == nullptr) {
		cerr << "База данных пустая." << endl;
		return;
	}
	if (GetInt("1 - Подтвердить удаление текущей структуры\n2 - Отмена") == 1) {
		delete CurrentStore;
		CurrentStore = nullptr;
	}
}
void Upload() {
	delete CurrentStore;
	CurrentStore = new Store("");
	if (CurrentStore->UpLoad())
	{
		cout << "Загрузка успешна!";
	}
	else
	{
		cout << "Не получилось загрузить из файла(";
	}

}
void DownLoad() {
	if (CurrentStore == nullptr) {
		cerr << "Ошибка, список не инициализирован." << endl;
		return;
	}
	CurrentStore->DownLoad();
}
void SearchSection() {
	if (CurrentStore != nullptr) {
		if (CurrentStore->GetHead()->GetNext() == CurrentStore->GetHead() && CurrentStore->GetHead()->GetPrevious() == CurrentStore->GetHead()) {
			cerr << "Список пуст." << endl;
			return;
		}
		if (CurrentStore->SearchForID(GetString("Введит название отдела: ")) != nullptr) {
			cout << "Отдел найден." << endl;
		}
		else
		{
			cout << "Отдел не найден." << endl;
		}
	}
	else {
		cerr << "Список не инициализирован." << endl;
	}
}
void SearchEmployee() {
	if (CurrentStore != nullptr) {
		if (CurrentStore->GetHead()->GetNext() == CurrentStore->GetHead() && CurrentStore->GetHead()->GetPrevious() == CurrentStore->GetHead()) {
			cerr << "Список пуст." << endl;
			return;
		}
		Section* Sect = CurrentStore->GlobalSearch(GetString("Введите фамилию сотрудника: "));
		if (Sect != nullptr) {
			cout << "Сотрудник найден:\nОтдел: " << Sect->GetName() << endl;
		}
		else {
			cerr << "Сотрудник не найден." << endl;
		}
	}
	else {
		cerr << "Список не инициализирован." << endl;
	}
}
