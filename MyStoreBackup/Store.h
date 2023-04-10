#include <string>
#include "Section.cpp"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Store {
private:
	string* storeName;
	Section* Head;
public:
	/*Геттеры и сеттеры*/
	Section* GetHead() {
		return Head;
	}
	void SetHead(Section* head) {
		Head = head;
	}
	string GetStoreName() {
		return *storeName;
	}
	void SetStoreName(string StoreName) {
		*this->storeName = StoreName;
	}
	/*Конструктор*/
	Store(string StoreName) {
		try {
			storeName = new string();
			Head = new Section("");
		}
		catch (bad_alloc) {
			cerr << "\nНе удалось выделить память." << endl;
			return;
		}
		SetStoreName(StoreName);
		Head->SetNext(Head);
		Head->SetPrevious(Head);
	}
	/*деструктор*/
	~Store() {
		unsigned int Counter = 0;
		Section* Current = Head;
		do {
			Current = Current->GetNext();
			Counter++;
		} while (Current != Head);
		for (unsigned int i = 0; i < Counter; i++) {
			Current = Head;
			Head = Head->GetNext();
			delete Current;
			Current = nullptr;
		}
		delete storeName;
		storeName = nullptr;
	}
	/*добавление отдела (по возрастанию названия)*/
	void AddSection(string SectionName) {
		if (Head != nullptr) {
			Section* PTemp;
			try { PTemp = new Section(SectionName); }
			catch (bad_alloc) {
				cerr << "\nНе удалось выделить память." << endl;
				return;
			}
			//Ищем наименование отдела, которое больше добавляемого и добавляем ДО него
			Section* Current = Head->GetNext();
			do
			{
				if (SectionName < Current->GetName())
				{
					PTemp->SetPrevious(Current->GetPrevious());
					PTemp->SetNext(Current);
					Current->GetPrevious()->SetNext(PTemp);
					Current->SetPrevious(PTemp);
					return;
				}
				Current = Current->GetNext();
			} while (Current != Head);
			//если не нашлось наименования больше добавляемого, добавляем в конец
			PTemp->SetPrevious(Head->GetPrevious());
			PTemp->SetNext(Head);
			Current->GetPrevious()->SetNext(PTemp);
			Current->SetPrevious(PTemp);
		}
		else {
			cerr << "\nОшибка, список не инициализирован." << endl;
		}
	}
	/*задание первого элемента списка*/
	void SetFirst(string SectionName) {
		Section* PTemp;
		try {
			PTemp = new Section(SectionName);
		}
		catch (bad_alloc) {
			cerr << "\nНе удалось выделить память." << endl;
			return;
		}
		Head->SetNext(PTemp);
		Head->SetPrevious(PTemp);
		PTemp->SetNext(Head);
		PTemp->SetPrevious(Head);
		
	}
	/*Добавление в подсписок по указанному названию отдела*/
	void AddSub(string SectionToAddName, string Surname, int Pay, string AfterWhom, int InsertionMode) {
		Section* SectionToAdd = SearchForID(SectionToAddName);
		if (SectionToAdd != Head && SectionToAdd != nullptr) {
			SectionToAdd->Add(Surname, Pay, AfterWhom, InsertionMode);
		}
		else {
			cerr << "\nТакого отдела нету в списке." << endl;
		}
	}
	/*Удаление отдела по заданному имени*/
	void Delete(string SectionToDeleteName) {
		if (Head != nullptr) {
			Section* ElementToDelete = SearchForID(SectionToDeleteName);
			if (ElementToDelete != nullptr) {
				cout << "\nУдален отдел: " << ElementToDelete->GetName() << endl;
				ElementToDelete->GetPrevious()->SetNext(ElementToDelete->GetNext());
				ElementToDelete->GetNext()->SetPrevious(ElementToDelete->GetPrevious());
				delete ElementToDelete; //очистка памяти
				ElementToDelete = nullptr;
			}
			else {
				cerr << "\nТакого отдела нету в списке." << endl;
			}
		}
		else {
			cerr << "\nОшибка, список не инициализирован." << endl;
		}
	}
	/*удаление сотрудника*/
	void DeleteSub(string SectionToDeleteEmp, string EmployeeSurname) {
		Section* SectionToDel = SearchForID(SectionToDeleteEmp);
		if (SectionToDel != nullptr && SectionToDel != Head) {
			SectionToDel->Delete(EmployeeSurname);
		}
		else {
			cerr << "\nТакого отдела нету в списке." << endl;
		}
	}
	/*Вывод*/
	void Show() {
		if (Head != nullptr) {
			Section* Current = Head->GetNext();
			//Выводим название магазина
			cout << "Магазин: " << this->GetStoreName() << endl;
			if (Current != Head) {
				while (Current != Head) {
					Current->Show();
					Current = Current->GetNext();
				}
			}
			else {
				cerr << "\nСписок пуст." << endl;
			}
		}
		else {
			cerr << "\nОшибка, список не инициализирован." << endl;
		}
	}
	/*Поиск нужного отдела*/
	Section* SearchForID(string SectionName) {
		if (Head != nullptr) {
			Section* Current = Head->GetNext();
			while (Current != Head) {
				if (Current->GetName() == SectionName) {
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
	/*Поиск сотрудника по фамилии, возврашает указатель на отдел, в котором найден сотрудник*/
	Section* GlobalSearch(string SearchSurName) {
		if (Head != nullptr) {
			Section* Current = Head->GetNext();
			while (Current != Head) {
				if (Current->Search(SearchSurName)) {
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
	/*Выгрузка всей структуры в файл.*/
	void DownLoad() {
		if (Head != nullptr)
		{
			Section* Current = Head->GetNext();
			if (Current != nullptr)
			{
				ofstream OutputFileStream;		//обьявляется поток записи в файл
				try { OutputFileStream.open("Res.txt", ios::trunc); }		//Открывается файл (или создается) по указанному пути
				catch (const ofstream::failure) {
					cerr << "Не удалось открыть файл" << endl;
				}
				OutputFileStream << "Магазин:" << endl;
				OutputFileStream << this->GetStoreName() << endl;
				while (Current != Head)
				{
					OutputFileStream << "\nОтдел:" << endl;
					OutputFileStream << Current->GetName();
					if (Current->GetHead()->GetNext() != Current->GetHead())
					{
						Employee* CurrentEmpl = Current->GetHead()->GetNext();
						while (CurrentEmpl != Current->GetHead())
						{
							OutputFileStream << "\nСотрутдник:" << endl;
							OutputFileStream << CurrentEmpl->GetSurname();
							OutputFileStream << "\nЗаработная плата:" << endl;
							OutputFileStream << CurrentEmpl->GetPay() << endl;
							CurrentEmpl = CurrentEmpl->GetNext();
						}
					}
					else
					{
						OutputFileStream << "\nВ отделе нет сотрудников." << endl;
					}
					Current = Current->GetNext();
				}
				OutputFileStream.close();
			}
			else
			{
				cerr << "\nСписок пуст." << endl;
			}
		}
		else {
			cerr << "\nОшибка, список не инициализирован." << endl;
		}
	}

	/*Аналогично, загрузка из файла расположенного в папке проекта*/
	bool UpLoad() {
		if (Head != nullptr)
		{
			ifstream InputFileStream;
			try { InputFileStream.open("Res.txt", ios::in); }
			catch (const ofstream::failure) {
				cerr << "Не удалось открыть файл." << endl;
				return false;
			}
			string InputStr;
			string SectionName;
			Section* CurrentSection;
			string StName;
			stringstream StrCountStream;
			string Surname;
			string StrPay;
			stringstream StreamPay;
			while (InputFileStream)
			{
				getline(InputFileStream, InputStr);
				if (InputStr == "Магазин:") {
					getline(InputFileStream, StName);
					if (StName == "") {
						cerr << "Ошибка. Неправильно задано название магазина." << endl;
						return false;
					}
					this->SetStoreName(StName);
				}
				else if (InputStr == "Отдел:")
				{
					getline(InputFileStream, SectionName);
					if (SectionName == "") {
						cerr << "Ошибка. Неправильно задано название отдела." << endl;
						return false;
					}
					CurrentSection = SearchForID(SectionName);
					AddSection(SectionName);
				}
				else if (InputStr == "Сотрутдник:")
				{
					getline(InputFileStream, Surname);
					if (Surname == "") {
						cerr << "Ошибка. Неправильно задан сотрудник." << endl;
						return false;
					}
					CurrentSection = SearchForID(SectionName);
					CurrentSection->AddLast(Surname);
				}
				else if (InputStr == "Заработная плата:")
				{
					getline(InputFileStream, StrPay);
					if (StrPay == "") {
						cerr << "Ошибка. Неправильно задана заработная плата." << endl;
						return false;
					}
					CurrentSection = SearchForID(SectionName);
					CurrentSection->GetHead()->GetPrevious()->SetPay(stoi(StrPay));
				}
			}
			InputFileStream.close();
			cout << "Структура успешно загружена." << endl;
			return true;
		}
		else
		{
			cerr << "\nОшибка, список не инициализирован." << endl;
			return false;
		}
	}
};