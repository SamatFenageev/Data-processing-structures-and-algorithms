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
	/*������� � �������*/
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
	/*�����������*/
	Store(string StoreName) {
		try {
			storeName = new string();
			Head = new Section("");
		}
		catch (bad_alloc) {
			cerr << "\n�� ������� �������� ������." << endl;
			return;
		}
		SetStoreName(StoreName);
		Head->SetNext(Head);
		Head->SetPrevious(Head);
	}
	/*����������*/
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
	/*���������� ������ (�� ����������� ��������)*/
	void AddSection(string SectionName) {
		if (Head != nullptr) {
			Section* PTemp;
			try { PTemp = new Section(SectionName); }
			catch (bad_alloc) {
				cerr << "\n�� ������� �������� ������." << endl;
				return;
			}
			//���� ������������ ������, ������� ������ ������������ � ��������� �� ����
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
			//���� �� ������� ������������ ������ ������������, ��������� � �����
			PTemp->SetPrevious(Head->GetPrevious());
			PTemp->SetNext(Head);
			Current->GetPrevious()->SetNext(PTemp);
			Current->SetPrevious(PTemp);
		}
		else {
			cerr << "\n������, ������ �� ���������������." << endl;
		}
	}
	/*������� ������� �������� ������*/
	void SetFirst(string SectionName) {
		Section* PTemp;
		try {
			PTemp = new Section(SectionName);
		}
		catch (bad_alloc) {
			cerr << "\n�� ������� �������� ������." << endl;
			return;
		}
		Head->SetNext(PTemp);
		Head->SetPrevious(PTemp);
		PTemp->SetNext(Head);
		PTemp->SetPrevious(Head);
		
	}
	/*���������� � ��������� �� ���������� �������� ������*/
	void AddSub(string SectionToAddName, string Surname, int Pay, string AfterWhom, int InsertionMode) {
		Section* SectionToAdd = SearchForID(SectionToAddName);
		if (SectionToAdd != Head && SectionToAdd != nullptr) {
			SectionToAdd->Add(Surname, Pay, AfterWhom, InsertionMode);
		}
		else {
			cerr << "\n������ ������ ���� � ������." << endl;
		}
	}
	/*�������� ������ �� ��������� �����*/
	void Delete(string SectionToDeleteName) {
		if (Head != nullptr) {
			Section* ElementToDelete = SearchForID(SectionToDeleteName);
			if (ElementToDelete != nullptr) {
				cout << "\n������ �����: " << ElementToDelete->GetName() << endl;
				ElementToDelete->GetPrevious()->SetNext(ElementToDelete->GetNext());
				ElementToDelete->GetNext()->SetPrevious(ElementToDelete->GetPrevious());
				delete ElementToDelete; //������� ������
				ElementToDelete = nullptr;
			}
			else {
				cerr << "\n������ ������ ���� � ������." << endl;
			}
		}
		else {
			cerr << "\n������, ������ �� ���������������." << endl;
		}
	}
	/*�������� ����������*/
	void DeleteSub(string SectionToDeleteEmp, string EmployeeSurname) {
		Section* SectionToDel = SearchForID(SectionToDeleteEmp);
		if (SectionToDel != nullptr && SectionToDel != Head) {
			SectionToDel->Delete(EmployeeSurname);
		}
		else {
			cerr << "\n������ ������ ���� � ������." << endl;
		}
	}
	/*�����*/
	void Show() {
		if (Head != nullptr) {
			Section* Current = Head->GetNext();
			//������� �������� ��������
			cout << "�������: " << this->GetStoreName() << endl;
			if (Current != Head) {
				while (Current != Head) {
					Current->Show();
					Current = Current->GetNext();
				}
			}
			else {
				cerr << "\n������ ����." << endl;
			}
		}
		else {
			cerr << "\n������, ������ �� ���������������." << endl;
		}
	}
	/*����� ������� ������*/
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
			cerr << "\n������, ������ �� ���������������." << endl;
			return nullptr;
		}
	}
	/*����� ���������� �� �������, ���������� ��������� �� �����, � ������� ������ ���������*/
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
			cerr << "\n������, ������ �� ���������������." << endl;
			return nullptr;
		}
	}
	/*�������� ���� ��������� � ����.*/
	void DownLoad() {
		if (Head != nullptr)
		{
			Section* Current = Head->GetNext();
			if (Current != nullptr)
			{
				ofstream OutputFileStream;		//����������� ����� ������ � ����
				try { OutputFileStream.open("Res.txt", ios::trunc); }		//����������� ���� (��� ���������) �� ���������� ����
				catch (const ofstream::failure) {
					cerr << "�� ������� ������� ����" << endl;
				}
				OutputFileStream << "�������:" << endl;
				OutputFileStream << this->GetStoreName() << endl;
				while (Current != Head)
				{
					OutputFileStream << "\n�����:" << endl;
					OutputFileStream << Current->GetName();
					if (Current->GetHead()->GetNext() != Current->GetHead())
					{
						Employee* CurrentEmpl = Current->GetHead()->GetNext();
						while (CurrentEmpl != Current->GetHead())
						{
							OutputFileStream << "\n����������:" << endl;
							OutputFileStream << CurrentEmpl->GetSurname();
							OutputFileStream << "\n���������� �����:" << endl;
							OutputFileStream << CurrentEmpl->GetPay() << endl;
							CurrentEmpl = CurrentEmpl->GetNext();
						}
					}
					else
					{
						OutputFileStream << "\n� ������ ��� �����������." << endl;
					}
					Current = Current->GetNext();
				}
				OutputFileStream.close();
			}
			else
			{
				cerr << "\n������ ����." << endl;
			}
		}
		else {
			cerr << "\n������, ������ �� ���������������." << endl;
		}
	}

	/*����������, �������� �� ����� �������������� � ����� �������*/
	bool UpLoad() {
		if (Head != nullptr)
		{
			ifstream InputFileStream;
			try { InputFileStream.open("Res.txt", ios::in); }
			catch (const ofstream::failure) {
				cerr << "�� ������� ������� ����." << endl;
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
				if (InputStr == "�������:") {
					getline(InputFileStream, StName);
					if (StName == "") {
						cerr << "������. ����������� ������ �������� ��������." << endl;
						return false;
					}
					this->SetStoreName(StName);
				}
				else if (InputStr == "�����:")
				{
					getline(InputFileStream, SectionName);
					if (SectionName == "") {
						cerr << "������. ����������� ������ �������� ������." << endl;
						return false;
					}
					CurrentSection = SearchForID(SectionName);
					AddSection(SectionName);
				}
				else if (InputStr == "����������:")
				{
					getline(InputFileStream, Surname);
					if (Surname == "") {
						cerr << "������. ����������� ����� ���������." << endl;
						return false;
					}
					CurrentSection = SearchForID(SectionName);
					CurrentSection->AddLast(Surname);
				}
				else if (InputStr == "���������� �����:")
				{
					getline(InputFileStream, StrPay);
					if (StrPay == "") {
						cerr << "������. ����������� ������ ���������� �����." << endl;
						return false;
					}
					CurrentSection = SearchForID(SectionName);
					CurrentSection->GetHead()->GetPrevious()->SetPay(stoi(StrPay));
				}
			}
			InputFileStream.close();
			cout << "��������� ������� ���������." << endl;
			return true;
		}
		else
		{
			cerr << "\n������, ������ �� ���������������." << endl;
			return false;
		}
	}
};