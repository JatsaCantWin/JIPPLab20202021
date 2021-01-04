#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

typedef pair<string, int> salaryPair;

class Employee
{
	public:
		string id;
		string name;
		string surname;
		string departmentId;
		string position;	
};

class HRMS
{
	vector<Employee> Employees;
	map<string, string> IDMap;
	map<string, double> salaryMap;
	void printEmployee(string);
	public:
		void add(Employee, string, double);
		void printDepartment(string);
		void changeSalary(string, double);
		void printSalaries();
		void printSalariesSorted();
};

void HRMS::printEmployee(string employeeId)
{
	for(Employee i : Employees)
		if (i.id == employeeId)
		{
			cout << i.id << " " << i.name << " " << i.surname << " " << i.departmentId << " " << i.position << " ";
			break;
		}
}

void HRMS::add(Employee employee, string departmentId, double salary)
{
	Employees.push_back(employee);
	IDMap.insert(make_pair(employee.id, departmentId));
	salaryMap.insert(make_pair(employee.id, salary));
}

void HRMS::printDepartment(string departmentID)
{
	for(Employee i : Employees)
		if (i.departmentId == departmentID)
			cout << i.id << " " << i.name << " " << i.surname << " " << i.position << endl;
}

void HRMS::changeSalary(string employeeId, double salary)
{
	map<string,double>::iterator i;
    for(i = salaryMap.begin(); i!=salaryMap.end(); ++i)
	{
		if (i->first==employeeId)
			i->second = salary;
    }
}

void HRMS::printSalaries()
{
	for(Employee i : Employees)
		cout << i.id << " " << i.name << " " << i.surname << " " << i.departmentId << " " << i.position << " " << salaryMap.find(i.id)->second << endl;
}

bool comp (salaryPair i, salaryPair j)
{
	return (i.second > j.second);
}

void HRMS::printSalariesSorted()
{
	vector<salaryPair> sortedSalaryMap;
	map<string,double>::iterator i;
	
	copy(salaryMap.begin(), salaryMap.end(), back_inserter<vector<salaryPair>>(sortedSalaryMap));
	sort(sortedSalaryMap.begin(), sortedSalaryMap.end(), comp);
	for (salaryPair i : sortedSalaryMap) 
	{
		printEmployee(i.first);
		cout << i.second << endl; 
    }
}

int main()
{
	HRMS HRMSMain;
	Employee TestEmployee1;								Employee TestEmployee6;
		TestEmployee1.id = "1";								TestEmployee6.id = "6";
		TestEmployee1.name = "Jan";							TestEmployee6.name = "Janusz";
		TestEmployee1.surname = "Kowalski";					TestEmployee6.surname = "Krenzel";
		TestEmployee1.departmentId = "Departament A";		TestEmployee6.departmentId = "Departament C";
		TestEmployee1.position = "Asystent";				TestEmployee6.position = "Pomocnik";
	Employee TestEmployee2;								Employee TestEmployee7;
		TestEmployee2.id = "2";								TestEmployee7.id = "7";
		TestEmployee2.name = "Jakub";						TestEmployee7.name = "Jagoda";
		TestEmployee2.surname = "Kabaczko";					TestEmployee7.surname = "Kozos";
		TestEmployee2.departmentId = "Departament A";		TestEmployee7.departmentId = "Departament C";
		TestEmployee2.position = "Administrator";			TestEmployee7.position = "Asystent";		
	Employee TestEmployee3;								Employee TestEmployee8;
		TestEmployee3.id = "3";								TestEmployee8.id = "8";
		TestEmployee3.name = "Jaroslaw";					TestEmployee8.name = "Jaroslawa";
		TestEmployee3.surname = "Keler";					TestEmployee8.surname = "Krynska";
		TestEmployee3.departmentId = "Departament B";		TestEmployee8.departmentId = "Departament A";
		TestEmployee3.position = "Analityk";				TestEmployee8.position = "Zarzadca";			
	Employee TestEmployee4;								Employee TestEmployee9;
		TestEmployee4.id = "4";								TestEmployee9.id = "9";
		TestEmployee4.name = "Jerzy";						TestEmployee9.name = "Janina";
		TestEmployee4.surname = "Kaminski";					TestEmployee9.surname = "Klozy";
		TestEmployee4.departmentId = "Departament B";		TestEmployee9.departmentId = "Departament A";
		TestEmployee4.position = "Automatyk";				TestEmployee9.position = "Ksiegowy";			
	Employee TestEmployee5;								Employee TestEmployee10;
		TestEmployee5.id = "5";								TestEmployee10.id = "10";
		TestEmployee5.name = "Jacenty";						TestEmployee10.name = "Joanna";
		TestEmployee5.surname = "Kielik";					TestEmployee10.surname = "Kursa";
		TestEmployee5.departmentId = "Departament A";		TestEmployee10.departmentId = "Departament B";
		TestEmployee5.position = "Ksiegowy";				TestEmployee10.position = "Pomocnik";			
	HRMSMain.add(TestEmployee1, "Departament A", 1000);
	HRMSMain.add(TestEmployee2, "Departament A", 1000);
	HRMSMain.add(TestEmployee3, "Departament B", 900);
	HRMSMain.add(TestEmployee4, "Departament A", 950);
	HRMSMain.add(TestEmployee5, "Departament A", 2000);
	HRMSMain.add(TestEmployee6, "Departament B", 1500);
	HRMSMain.add(TestEmployee7, "Departament A", 300);
	HRMSMain.add(TestEmployee8, "Departament A", 200);
	HRMSMain.add(TestEmployee9, "Departament B", 150);
	HRMSMain.add(TestEmployee10, "Departament A", 100);
	
	HRMSMain.printDepartment("Departament A"); cout << endl;
	HRMSMain.printSalaries(); cout << endl;
	HRMSMain.changeSalary("10", 50); 
	HRMSMain.printSalariesSorted(); 
}
