#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

double WebEarnings = 0;

class Company;
class Candidate;
class FullTimeEmployee;
class Intern;
class ExperiencedEmployee;
class NewEmployee;
class Owner;
class Client;
void OwnerMenu();
vector<Company*> Companies;
vector<Company*> Promoted_Companies;
vector<Candidate*> Candidates;
vector< pair<Candidate*, Company*> > FoundJobs;
vector<Owner*> Owners;
vector<Client*> Clients;
vector <string>JobTitles{ "Database Administator", "Web Developer", "Application Developer", "System Analyst", "System Developer" };
vector <string>Problems{ "Back up the sustem", "Fixing Bugs", "Develop an Application","Defining a Problem", "Develop System" };
int partitions(vector<Candidate*>& Candidates, int low, int high);
void quickSort(vector<Candidate*>& Candidates, int low, int high);



string newE = "new,";         // lines to be appended in file "Candidate"
string expE = "experienced,";



void showJT() {

	cout << "Available Job Positions: \n";
	for (unsigned int i = 0; i < JobTitles.size(); i++) {
		cout << i + 1 << " - " << JobTitles[i] << endl;
	}
}
void showProblems() {
	cout << "What kind of problem are you experiencing: \n";
	for (unsigned int i = 0; i < Problems.size(); i++) {
		cout << i + 1 << " - " << Problems[i] << endl;
	}
}

class Company {

public:
	Company() {
		cName = "";
		cAdress = "";
		cPhone = "";
		hWage = 0;
		accessCode = "";
	}

	Company(string name, string adress, string phone, double wage, string ac) {
		cName = name;
		cAdress = adress;
		cPhone = phone;
		hWage = wage;
		accessCode = ac;
	}

	void setname() {
		cout << "Enter the name of the company: ";
		string name;
		cin.ignore();
		getline(cin, name);
		this->cName = name;
	}

	void setadress() {
		cout << "Enter the adress: ";
		string adress;
		getline(cin, adress);
		this->cAdress = adress;
	}

	void setphone() {
		cout << "Enter phone number: ";
		string phone;
		cin >> phone;
		this->cPhone = phone;
	}

	void sethWage() {
		cout << "Hourly wage offered for employees: ";
		string hw;
		cin >> hw;
		int w = atoi(hw.c_str());

		if (w) { this->hWage = w; }
		else { cout << "\nEnter valid wage!\n"; sethWage(); }
	}

	string getCode() { return accessCode; }
	string getCname() { return cName; }
	string getCadress() { return cAdress; }
	string getCphone() { return cPhone; }
	double getWage() { return hWage; }

	void Info() {
		cout << "Company Overall information\n\n";
		cout << getCname() << " is hiring\n";
		cout << "Location: " << getCadress() << endl;
		cout << "Phone: " << getCphone() << endl;
		cout << "Hourly Wage: " << getWage() << endl;
	}

private:
	string cName;
	string cAdress;
	string cPhone;
	double hWage;
	string accessCode;



};

class Owner {

public:
	Owner() {
		cout << "Fill the information to register \n\n";
		setOname();
		setOadress();
		setOcompany();
		setObudget();
		setID();
		setAcc();
	}

	Owner(string n, string a, int c, int b, string id, string acc) {
		this->name = n;
		this->adress = a;					// constructor to initialize the object reading from the file
		this->budget = b;
		this->ID = id;
		setcompany(c);
		accessCode = acc;
	}


	void setcompany(int c) {
		this->company = Companies[c - 1];
		;
	}

	void setOname() {
		cout << "Full Name: ";
		string n;
		cin.ignore();
		getline(cin, n);
		this->name = n;
		
	}

	void setOadress() {
		cout << "Adress: ";
		string a;
		getline(cin, a);
		this->adress = a;
	}

	void setOcompany() {
		cout << "Which is your your company\n";
		for (unsigned int i = 0; i < Companies.size(); i++) {
			cout << i + 1 << ") " << Companies[i]->getCname() << endl;
		} //points to an already created object of class Company
		string choice;
		cin >> choice;
		unsigned int w = atoi(choice.c_str());

		if (w && w<=Companies.size()) {
			this->company = Companies[w - 1];

		}
		else { cout << "\nInvalid!\n"; setOcompany(); }
		this->comp = w;
	}

	void setObudget() {
		string b;
		cout << "What is your budget: ";
		cin >> b;
		int w = atoi(b.c_str());

		if (w) { this->budget = w; }
		else { cout << "\nEnter valid budget!\n"; setObudget(); }
	}

	void setB(int newB) {
		this->budget = newB;
	}

	void setID() {
		string p;
		cout << "Enter ID: ";
		cin >> p;
		this->ID = p;
	}

	void setAcc() {
		cout << "Access Code: ";
		string a;
		cin >> a;
		accessCode = a;

	}

	string getOname() { return name; }
	string getOadress() { return adress; }
	Company* getCompany() { return company; }					//accessors
	double getObudget() { return budget; }
	string getID() { return ID; }
	int getComp() { return comp; }
	string getAccess() { return accessCode; }

private:
	string name;
	string adress;
	Company *company;
	int budget;					//data slots
	string ID;
	int comp;
	string accessCode;
};

class Candidate {

public:

	Candidate() {
		cout << "Fill the information \n\n ";
		setName();
		setAdress();
		setAge();
		setID();
		setPhone();
		setDesiredWage();
	}

	Candidate(string NAME, string ADRESS, int AGE, string id, string phone, int DW) {
		eName = NAME;
		eAdress = ADRESS;								//constructor to read from the file
		Age = AGE;
		ID = id;
		ePhone = phone;
		DesiredWage = DW;
	}

	void setDesiredWage() {
		cout << "Desired wage: ";
		string s;
		cin >> s;
		int w = atoi(s.c_str());
		if (w) {
			this->DesiredWage = w;
			newE += (s + ",");
			expE += (s + ",");
		}
		else { cout << "\nInvalid!\n"; setDesiredWage(); }
	}

	void setName() {
		cout << "Name of Candidate: ";
		string n;

		cin.ignore();
		getline(cin, n);
		newE += (n + ",");
		expE += (n + ",");
		this->eName = n;
	}

	void setPhone() {
		cout << "Candidate phone: ";
		string p;
		cin.ignore();
		getline(cin, p);
		this->ePhone = p;
		newE += (p + ",");
		expE += (p + ",");
	}
	// mutators
	void setAdress() {											// modifiers
		cout << "Candidate adress: ";
		string a;
		getline(cin, a);
		this->eAdress = a;
		newE += (a + ",");
		expE += (a + ",");
	}

	void setAge() {
		cout << "Candidate age: ";
		string ag;
		cin >> ag;
		unsigned int w = atoi(ag.c_str());
		if (w) {
			this->Age = w;
			newE += (ag + ",");
			expE += (ag + ",");
		}
		else { cout << "\nEnter valid age!\n"; setAge(); }
	}

	void setCompany(Company* object) { company = object; }

	virtual void Information() {
		cout << "Name: " << eName;
		cout << "\nAge: " << Age;
		cout << "\nAdress: " << eAdress;
		cout << "\nPhone: " << ePhone << endl;
	}

	void setID() {
		cout << "Enter the ID: ";
		string p;
		cin >> p;
		this->ID = p;
		newE += (p + ",");
		expE += (p + ",");
	}

	virtual double getDesiredWage() = 0;
	virtual double getTotalCost() = 0;
	virtual string getJobTitle() = 0;       // polymorphic functions
	virtual int getTask() = 0;
	virtual string getUniversity() = 0;
	virtual double getGPA() = 0;

	string getEname() { return eName; }
	string getEadress() { return eAdress; }
	string getEphone() { return ePhone; }          // accessors
	int getage() { return Age; }
	Company* getCompany() { return company; }
	string getID() { return ID; }

private:
	string eName;
	string eAdress;
	string ePhone;
	int Age;			// data slots
	Company *company;
	string ID;

protected:
	double DesiredWage;

};

class FullTimeEmployee : public Candidate {

public:
	FullTimeEmployee() {
		setJobTitle();
		setUniversity();
		setGPA();
	}

								//constructor to read from the file
	FullTimeEmployee(string NAME, string ADRESS, int AGE, string id, string phone, int DW, string JT, string U, double gpa) :
		Candidate(NAME, ADRESS, AGE, id, phone, DW), JobTitle(JT), University(U), UnGPA(gpa) {}


	void setUniversity() {
		cout << "University Graduated: ";
		string u;
		cin >> u;
		this->University = u;
		newE += (u + ",");
		expE += (u + ",");
	}

	void setGPA() {
		cout << "University GPA (0 - 4.0 scale): ";
		string g;
		cin >> g;
		double w = atoi(g.c_str());
		if (w && w >= 0 && w <= 4) {
			this->UnGPA = w;
			newE += (g + ",");
			expE += (g + ",");
		}
		else { cout << "\nInvalid GPA!\n"; setGPA(); }
	}


	void Information() {
		Candidate::Information();
		cout << "Job Title: " << JobTitle << endl;
		cout << "University Graduated: " << University << endl;
		cout << "University GPA: " << UnGPA << endl;
	}

	void setJobTitle() {
		showJT();
		cout << "\nChoose your Job Position: ";
		string p; cin >> p;
		if (isdigit(p[0])) {
			int w = atoi(p.c_str());
			if (w < 6) {
				this->JobTitle = JobTitles[w - 1];
				newE += (JobTitle + ",");
				expE += (JobTitle + ",");
			}
			else { cout << "\nInvalid!\n"; setJobTitle(); }
		}
		else { cout << "\nInvalid!\n"; setJobTitle(); }
	}


	string getUniversity() { return University; }
	string getJobTitle() { return JobTitle; }		//accessors
	double getGPA() { return UnGPA; }

private:
	string University;
	double UnGPA;
	string JobTitle;

};

class NewEmployee : public FullTimeEmployee {

public:
	NewEmployee() {
		setTimeforTask();
	}
												//constructor to read from the file and initialize the object
	NewEmployee(string NAME, string ADRESS, int AGE, string id, string phone, int DW, string JT, string U, double gpa, int time) :
		FullTimeEmployee(NAME, ADRESS, AGE, id, phone, DW, JT, U, gpa),
		TimeForTask(time) {}								

	void setTimeforTask() {
		cout << "Time needed to finsh a task (hours): ";
		string t;
		cin >> t;
		unsigned int w = atoi(t.c_str());
		if (w) { this->TimeForTask = w; newE += (t + "\n"); }
		else { cout << "\nInvalid!\n"; setTimeforTask(); }
	}



	void Information() {
		FullTimeEmployee::Information();
		cout << "Demanded Wage: $" << getDesiredWage() << endl;
		cout << "Time to finish a task (hours): " << getTask() << endl;
	}

	string getUniversity() { FullTimeEmployee::getUniversity(); return 0; }
	double getTotalCost() { return getTask() * getDesiredWage(); }
	double getDesiredWage() {												//accessors
		if (getGPA() >= 3.5) { return DesiredWage - 3; }
		else { return DesiredWage - 7; }
	}
	double getGPA() { FullTimeEmployee::getGPA(); return 0; }
	int getTask() { return TimeForTask; }

private:
	int TimeForTask;
};

class ExperiencedEmployee : public FullTimeEmployee {

public:
	ExperiencedEmployee() {
		setTimeforTask();
		setPreviousEmployerRate();
	}


	ExperiencedEmployee(string NAME, string ADRESS, int AGE, string id, string phone, int DW, string JT, string U, double gpa, int time, int PR) :
		FullTimeEmployee(NAME, ADRESS, AGE, id, phone, DW, JT, U, gpa),
		TimeForTask(time),												//constructor to read from the file
		PreviousEmployerRate(PR) {}

	void setTimeforTask() {
		cout << "Time needed to finsh a task (hours): ";
		string t;
		cin >> t;
		unsigned int w = atoi(t.c_str());
		if (w) { this->TimeForTask = w; expE += (t + ","); }
		else { cout << "\nInvalid!\n"; setTimeforTask(); }
	}																//modifiers

	void Information() {
		FullTimeEmployee::Information();
		cout << "Demanded Wage: $" << getDesiredWage() << endl;
		cout << "Time to finish a task (hours): " << getTimeforTask() << endl;
		cout << "Previous Candidate Rate (0-10): " << PreviousEmployerRate << endl;
	}

	void setPreviousEmployerRate() {
		cout << "Previous Candidate Rate ";
		string w;
		cin >> w;
		int s = atoi(w.c_str());
		if (s && s<11) {
			this->PreviousEmployerRate = s; expE += (w + "\n");
		}
		else { cout << "\nInvalid!\n"; setPreviousEmployerRate(); }
	}

	double getGPA() { FullTimeEmployee::getGPA();return 0; }
	double getDesiredWage() {
		if (getPrevRate() >= 8) { return DesiredWage + 8; }
		else { return DesiredWage + 3; }
	}
	string getUniversity() { FullTimeEmployee::getUniversity(); return 0; }
	double getPrevRate() { return  PreviousEmployerRate; }
	int getTask() { return TimeForTask; }									// accessors
	int getTimeforTask() { return TimeForTask; }
	double getTotalCost() {
		return getTimeforTask() * getDesiredWage();
	}
private:

	int TimeForTask;
	double PreviousEmployerRate;
};

class Intern : public Candidate {

public:
	Intern() {
		setInternshipDuration();
		setTimePerTask();
	}

	Intern(string NAME, string ADRESS, int AGE, string id, string phone, int DW, int IntD, int t) :
		Candidate(NAME, ADRESS, AGE, id, phone, DW), InternshipDuration(IntD), AVGTimePerTask(t) {}

	void setInternshipDuration() {
		cout << "Internship duration (months): ";
		string t;
		cin >> t;
		unsigned int w = atoi(t.c_str());
		if (w) { this->InternshipDuration = w; }
		else { cout << "\nInvalid!\n"; setInternshipDuration(); }
	}

	void setTimePerTask() {
		cout << "Time to finish a task: ";
		string tim;
		cin >> tim;
		unsigned int w = atoi(tim.c_str());
		if (w) { this->AVGTimePerTask = w; }
		else { cout << "\nInvalid\n"; setTimePerTask(); }
	}

	void Information() {
		Candidate::Information();
		cout << "Demanded Wage: $" << getDesiredWage() << endl;
		cout << "Duration (in months): " << InternshipDuration << endl;
		cout << "Average Time per task (in hours): " << AVGTimePerTask << endl;
	}


	double getTotalCost() { return AVGTimePerTask * getDesiredWage(); }
	int getTask() { return AVGTimePerTask; }
	string getUniversity() { return "no"; }
	int getTimePerTask() { return AVGTimePerTask; }
	double getDesiredWage() { return DesiredWage * 0.5; }
	double getGPA() { return 1; }



	double getTotalEarnings() {
		return InternshipDuration * getDesiredWage();
	}
	string getJobTitle() { return "Intern"; }

private:

	int InternshipDuration;
	int AVGTimePerTask;


};

class Client {

public:

	Client() {
		setName();
		setAdress();
		setID();
		setPhone();
		setBudget();
	}


	Client(string n, string ad, string id, string phone, int budget) {
		Name = n;;
		Adress = ad;
		ID = id;
		Phone = phone;
		Budget = budget;
	}


	void setName() {
		cout << "Name: ";
		string n;
		cin.ignore();
		getline(cin, n);
		this->Name = n;
	}

	void setAdress() {
		cout << "Adress: ";
		string a;
		getline(cin, a);
		this->Adress = a;
	}

	void setPhone() {
		cout << "Phone Number: ";
		string p;
		cin >> p;
		this->Phone = p;
	}

	void setBudget() {
		cout << "Budget: ";
		string b;
		cin >> b;
		unsigned int w = atoi(b.c_str());
		if (w) { this->Budget = w; }
		else { cout << "\nInvalid!\n"; setBudget(); }
	}

	void BudgetRemanin(int b) {
		Budget -= b;
	}

	void setCompany(Company *C) {
		comp = C;
		hasComp = true;
	}

	void setID() {
		cout << "ID: ";
		string id;
		cin >> id;
		this->ID = id;
	}

	string getName() { return Name; }
	string getID() { return ID; }
	string getAdress() { return Adress; }
	string getPhone() { return Phone; }
	double getBudget() { return Budget; }
	Company* getCompany() { return comp; }
	bool has() { return hasComp; }

private:
	string Name;
	string Adress;
	string Phone;
	string ID;
	Company *comp;
	double Budget;
	bool hasComp = false;
};




//------------------------------------------------------------Functions------------------------------------------- Functions-------------------------------------------------------------------------------


bool checkClientID(string p) {
	bool found = false;
	for (unsigned int t = 0; t < Clients.size(); t++) {
		if (Clients[t]->getID() == p) { found = true; break; }
	}
	return found;
}

void ClientMenu() {
	cout << "\n\nClient Menu\n\n";
	cout << " 1 - Log in     2 - Register\n choice: ";
	string  ch;
	cin >> ch;
	int w = atoi(ch.c_str());
	if (w && w>0 && w<3) {
		switch (w) {
		case 2: { Clients.push_back(new Client()); cout << "\n\n      Successfully registered\n\n";

			ofstream o;
			string line = "client,";
			string budget = to_string(Clients[Clients.size() - 1]->getBudget());

			line += Clients[Clients.size() - 1]->getName(); line += ",";
			line += Clients[Clients.size() - 1]->getAdress(); line += ",";           // appends the new Client information in the file "Clients"
			line += Clients[Clients.size() - 1]->getID(); line += ",";
			line += Clients[Clients.size() - 1]->getPhone(); line += ",";
			line += budget; line += "\n";

			o.open("Clients", ios_base::app);
			o << line;
			o.close();
			break; }


		case 1: {

			cout << "Enter your ID to log in: "; string id; cin >> id;
			if (checkClientID(id) == false) { cout << "\n\n    No user with this ID\n\n"; }
			else {

				for (unsigned int t = 0; t < Clients.size(); t++) {

					if (Clients[t]->getID() == id) {                                                   // user is prompted to log in

						cout << endl << Clients[t]->getName() << " successfully logged in\n\n";
						if (FoundJobs.size() >0) {

							cout << "1 - Report a problem       2 - Management  \n\n";

							string choice;

							cin >> choice;

							string ProblemSolver;

							if (choice == "1") {

								cout << endl; showProblems();

								cout << "\n Choice: ";

								string c; cin >> c;

								int ch = atoi(c.c_str());

								if (ch && ch <= JobTitles.size()) {

									ProblemSolver = JobTitles[ch - 1];            // look for someone to fix the problem

									if (FoundJobs.size() == 0) { cout << "Sorry, no available " << ProblemSolver << "\n\n"; }

									else {
										for (unsigned int u = 0; u < FoundJobs.size(); u++) {

											if (FoundJobs[u].first->getJobTitle() == ProblemSolver) {
												cout << "\n\n A " << ProblemSolver << " found!\n Company: " << FoundJobs[u].second->getCname() << endl;

												cout << "Cost: " << FoundJobs[u].first->getDesiredWage()*FoundJobs[u].first->getTotalCost() / 10 << " dollars.\n Hire? 1- Yes   2- No\n";       // hire or not

												char c; cout << "Choice: "; cin >> c;

												if (c == '1') {
													WebEarnings += FoundJobs[u].first->getDesiredWage() * 2;
													cout << "\n\nSuccessfully hired.\n Web Commision: $" << FoundJobs[u].first->getDesiredWage() * 2 << endl;
													Clients[t]->setCompany(FoundJobs[u].second);
													Clients[t]->BudgetRemanin(FoundJobs[u].first->getDesiredWage() * 5 + FoundJobs[u].first->getDesiredWage()*FoundJobs[u].first->getTotalCost() / 10);
												}

												else { break; }
											}

											else if (u == FoundJobs.size() - 1) { cout << "\n\n    Sorry, no " << ProblemSolver << " available for the moment\n\n"; break; }
										}
									}
								}
								else { cout << "\nInvalid!\n"; }
							}

							else if (choice == "2") {
								if (!Clients[t]->has()) { cout << "\n No company working with at the moment\n"; }

								else { cout << "\n\n Company working with: " << Clients[t]->getCompany()->getCname() << endl << endl; }
							}
						}
						else { cout << "\n\t No available workers, try again later!\n"; }
					}
				}break;
			} }
		default: break;
		}

	}
	else { cout << "\nInvalid!\n"; }
}

void promotedCompaniesInfo() {
	if (Promoted_Companies.size() == 0) { cout << "\n\n    No promoted Companies\n\n"; }
	else {
		cout << "Promoted Companies:\n";
		for (unsigned int e = 0; e < Promoted_Companies.size(); e++) {
			cout << endl << e + 1 << ") " << Promoted_Companies[e]->getCname() << endl;
		}
		cout << "Choose a company for more information...\n\nchoice: ";
		string  c;
		cin >> c;
		unsigned int w = atoi(c.c_str());
		if (w && w <= Promoted_Companies.size()) {
			Promoted_Companies[w - 1]->Info();
		}
		else { cout << "\nInvalid!\n"; promotedCompaniesInfo(); }
	}
}

void promotedCompanies() {
	if (Promoted_Companies.size() == 0) { cout << "\n\n    No promoted Companies\n\n"; }
	else {

		cout << "Promoted Companies:\n";
		for (unsigned int e = 0; e < Promoted_Companies.size(); e++) {
			cout << endl << e + 1 << ") " << Promoted_Companies[e]->getCname() << endl;
		}
	}
}

void addCompany() {
	cout << "Number of featured Companies: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		Companies.push_back(new Company());
		cout << Companies[i]->getCname() << " successfully added\n";
	}
}

bool checkEmployeeID(string p) {
	bool found = false;
	for (unsigned int t = 0; t < Candidates.size(); t++) {
		if (Candidates[t]->getID() == p) { found = true; break; }
	}
	return found;
}

bool checkOwnerID(string p) {
	bool found = false;
	for (unsigned int t = 0; t < Owners.size(); t++) {
		if (Owners[t]->getID() == p) { found = true; break; }
	}
	return found;
}

void OwnerMenu() {

	cout << "\n\nOwner Menu\n\n";
	cout << " 1 - Log in     2 - Register\n choice: ";
	string ch;
	cin >> ch;
	if (ch == "1") {
		cout << "Enter your ID: "; string pass; cin >> pass;

		if (checkOwnerID(pass) == false) { cout << "\n\n      No user with this ID\n\n"; }
		else {

			for (unsigned int u = 0; u < Owners.size(); u++) {

				if (Owners[u]->getID() == pass) {

					cout << endl << Owners[u]->getOname() << " successfully logged in\n\n   Company owned: " << Owners[u]->getCompany()->getCname();

					cout << "\nChoose an option...\n\n";

					cout << " 1 - Promote Company \n 2 - Remove the company from promotion\n 3 - See Current Budget \n\n choice: ";
					string choice;
					cin >> choice;
					unsigned int w = atoi(choice.c_str());
					if (w) {
						switch (w) {
						case 1:  if (Owners[u]->getObudget() >= 1000)

						{
							WebEarnings += Owners[u]->getObudget()*0.05;  cout << "\n " << Owners[u]->getCompany()->getCname() << " successfully promoted!\n\n";

							cout << "Web commission (5% of budget): " << Owners[u]->getObudget()*0.05 << endl << endl;

							cout << "Current Company budget: $" << Owners[u]->getObudget() - Owners[u]->getObudget()*0.05 << endl << endl;

							Owners[u]->setB(Owners[u]->getObudget() - Owners[u]->getObudget()*0.05);

							Promoted_Companies.push_back(Owners[u]->getCompany());
						}

								 else { cout << "Not enough budget to promote the Company " << Owners[u]->getCompany()->getCname() << endl; }break;

						case 2: int pos; for (unsigned int q = 0; q < Promoted_Companies.size(); q++) {

							if (Promoted_Companies[q]->getCname() == Owners[u]->getCompany()->getCname())

							{
								pos = u; Promoted_Companies.erase(Promoted_Companies.begin() + (pos - 1));
							}break;
						}break;

						case 3: cout << "\nCurrent Budget: $" << Owners[u]->getObudget() << endl; break;

						default: cout << "Invalid Command!"; break;
						}
					}
					else { cout << "\nInvalid!\n"; OwnerMenu(); }break;
				}
			}
		}
	}

	else if (ch == "2") {
		string line = "t,";		// line to be appended in the file
		Owners.push_back(new Owner()); cout << "Successfully registered! \n\n";
		if (Owners[Owners.size() - 1]->getAccess() != Owners[Owners.size() - 1]->getCompany()->getCode()) { cout << "\nUser cannot be registered because of WRONG access code!\n\n"; Owners.pop_back(); }
		else {
			ofstream o;

			string budget = to_string(Owners[Owners.size() - 1]->getObudget());
			string company = to_string(Owners[Owners.size() - 1]->getComp());
			line += Owners[Owners.size() - 1]->getOname(); line += ",";
			line += Owners[Owners.size() - 1]->getOadress(); line += ",";
			line += company; line += ",";
			line += budget; line += ",";										//intitializing the file 
			line += Owners[Owners.size() - 1]->getID(); line += ",";
			line += Owners[Owners.size() - 1]->getAccess(); line += "\n";
			o.open("Owners", ios_base::app);		// ios_base used to only append and not remove the existing information in a file
			o << line;
			o.close();
		}
	}
}

void CandidateMenu() {

	cout << "\n\n\tCandidate Menu\n\n";

	cout << " 1 - Log in\t\t2 - Register\n\n choice: ";

	string choice;
	cin >> choice;
	if (choice == "1") {
		cout << "Enter your ID: "; string pass; cin >> pass;

		if (checkEmployeeID(pass) == false) { cout << "\n\n      No user with this ID\n\n"; }

		else {
			for (unsigned int u = 0; u < Candidates.size(); u++) {

				if (Candidates[u]->getID() == pass) {

					cout << endl << Candidates[u]->getEname() << " successfully logged in\n\n   ";

					cout << "Companies that are hiring(promoted):\n\n";

					promotedCompanies(); // shows companies that are hiring
	
					if (Promoted_Companies.size() == 0) { cout << setw(20) << "Apply Later\n\n"; }

					else {

						cout << "\n\nChoose a company to apply: ";


						string w;

						cin >> w;
						unsigned int a = atoi(w.c_str());
						if (a <= Promoted_Companies.size()) {

							if (Candidates[u]->getDesiredWage() <= Promoted_Companies[a - 1]->getWage()) {		// if requirments are met

								Candidates[u]->setCompany(Promoted_Companies[a - 1]);			// link the candidate with the employee

								FoundJobs.push_back(make_pair(Candidates[u], Companies[a - 1])); // inserts the employee and the company to the vector

								cout << "\n\nCONGRATULATIONS, just hired at " << Promoted_Companies[a - 1]->getCname() << " with a hourly wage of $" << Promoted_Companies[a - 1]->getWage() << endl;
								
								ofstream c;
								c.open("HiringSession", ios_base::app);
								string Line = (Candidates[u]->getEname() + " works at " + Companies[a - 1]->getCname() + " Company. Salary: $" + to_string(Companies[a - 1]->getWage()) + " per hour.\n");
								cout << Line << endl;
								c << Line;
								c.close();

								WebEarnings += Candidates[u]->getDesiredWage() * 8; cout << "\nWeb Commission: $" << Candidates[u]->getDesiredWage() * 8 << endl << endl;
							}

							else {
								cout << "\n\n Yur wage requirement is not fullfilled\n\nYou wanted: " << Candidates[u]->getDesiredWage() << " $/hour" << endl;

								cout << "Company offered: " << Promoted_Companies[a - 1]->getWage() << " $/h\n\n";
							}

						}
						else { cout << "\tInvalid!\n"; }
					}
				}
			}
		}
	}
	else if (choice == "2") {

		cout << "\n1 - Full Time\t\t2 - Intern\n\nchoice: ";

		string o;
		cin >> o;

		if (o == "1") {

			string qs;

			cout << "\n\n 1 - Experienced\t\t2 - New\n\nchoice: ";

			cin >> qs;

			if (qs == "1") {
				expE = "experienced,";       // line to be appended that is fully initialized after creating the object

				Candidates.push_back(new ExperiencedEmployee()); cout << "\n\nNew Experienced Employee successfully registered!\n\n";
				ofstream s;
				s.open("Candidates", ios_base::app);
				s << expE;
				s.close();

				expE = "experienced,";

			}

			else if (qs == "2") {
				newE = "new,";			 // line to be appended that is fully initialized after creating the object

				Candidates.push_back(new NewEmployee()); cout << "\n\nNew Unexperienced Employee successfully registered!\n\n";
				ofstream s;
				s.open("Candidates", ios_base::app);
				s << newE;
				s.close();



				newE = "new,";
			}



			else { cout << "\nInvalid!\n"; CandidateMenu(); }
		}


		else if (o == "2") {

			Candidates.push_back(new Intern()); cout << "\n\nNew intern successfully registered!\n\n";
			ofstream c;
			int p = Candidates.size() - 1;
			c.open("Candidates", ios_base::app);
			string line = "intern,";
			line += Candidates[p]->getEname(); line += ",";
			line += Candidates[p]->getEadress(); line += ",";
			line += to_string(Candidates[p]->getage()); line += ",";
			line += Candidates[p]->getID(); line += ",";
			line += Candidates[p]->getEphone(); line += ",";
			line += to_string(Candidates[p]->getDesiredWage()); line += ",";
			line += to_string(Candidates[p]->getage()); line += ",";
			line += to_string(Candidates[p]->getTask()); line += '\n';
			c << line;
			c.close();
		}
		else { cout << "\nInvalid!\n"; CandidateMenu(); }
	}

}

void Hired() {
	if (FoundJobs.size() == 0) { cout << "\n\n\t\tNo hiring session\n"; }

	else {
																	// show hired candinates
		for (unsigned int i = 0; i < FoundJobs.size(); i++) {
			string Line =(FoundJobs[i].first->getEname() + " works at " + FoundJobs[i].second->getCname() + " Company. Salary: $" + to_string(FoundJobs[i].second->getWage()) + " per hour.\n" );
			cout << Line;
			
		}
	}
}

void EmployeeInfo() {
	if (Candidates.size() == 0) { cout << "\n  No registered employee\n\n"; }
	else {
		quickSort(Candidates, 0, Candidates.size() - 1);
		cout << "Select an candidate to get information:\n";
		for (unsigned int q = 0; q < Candidates.size(); q++) {
			cout << endl << q + 1 << " - " << Candidates[q]->getEname() << endl;
		}
		cout << "Choice: ";

		string c;
		cin >> c;										// shows the employee info

		unsigned int w = atoi(c.c_str());

		if (w && w <= Candidates.size()) {

			cout << "\n\nDisplaying Information...\n\n";
			Candidates[w - 1]->Information();
		}

		else { cout << "\nInvalid command!\n\n"; EmployeeInfo(); }
	}
}

int partitions(vector<Candidate*>& Candidates, int low, int high) {

	Candidate * pivot = Candidates[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (Candidates[j]->getEname() <= pivot->getEname()) {
			i++;
			Candidate* t = Candidates[i];
			Candidates[i] = Candidates[j];					// quick sort
			Candidates[j] = t;		}
	}
	Candidate* q = Candidates[i + 1];
	Candidates[i + 1] = Candidates[high];
	Candidates[high] = q;


	return (i + 1);
}

void quickSort(vector<Candidate*>& Candidates, int low, int high) {

	if (low<high) {

		int p1 = (partitions(Candidates, low, high));
																	// quick sort 
		quickSort(Candidates, low, p1 - 1);
		quickSort(Candidates, p1 + 1, high);


	}
}

void readCompanies() {



	ifstream Database("Available");

	if (Database.fail()) { cout << "\n\n  Failed accessing Companies\n\n\n"; }

	else {


		while (!Database.eof()) {
			string name;
			string adress;
			string phone;
			double hWage;
			string code;

			Database >> name >> adress >> phone >> hWage >> code;
			if (!Database.eof()) { Companies.push_back(new Company(name, adress, phone, hWage, code)); }
		}
		Database.close();
	}
}

void readOwners() {


	ifstream O("Owners");

	if (O.fail()) { cout << "\tProblem importing Owners data!\n\n"; }

	string line;

	while (getline(O, line)) {
		string type, name, adress, company, budget, id, access;
		istringstream ss(line);
		while (getline(ss, type, ',')) {
			getline(ss, name, ',');
			getline(ss, adress, ',');
			getline(ss, company, ',');
			getline(ss, budget, ',');
			getline(ss, id, ',');
			getline(ss, access);
			int compan = atoi(company.c_str());
			int budgets = atoi(budget.c_str());

			Owners.push_back(new Owner(name, adress, compan, budgets, id, access));
		}
	}
	O.close();
}

void readClients() {

	ifstream O("Clients");

	if (O.fail()) { cout << "\tProblem importing Owners data!\n\n"; }

	string line;

	while (getline(O, line)) {
		string type, name, adress, phone, budget, id;
		istringstream ss(line);
		while (getline(ss, type, ',')) {
			getline(ss, name, ',');
			getline(ss, adress, ',');  //Client(string n,string ad,string id,string phone, int budget)
			getline(ss, id, ',');
			getline(ss, phone, ',');
			getline(ss, budget);

			int budgets = atoi(budget.c_str());

			Clients.push_back(new Client(name, adress, id, phone, budgets));
		}
	}
	O.close();




}


void readCandidates() {

	ifstream C;
	C.open("Candidates");

	if (C.fail()) { cout << "Failed accessing Candidates!\n"; }

	string line;
	while (getline(C, line)) {

		string type, name, adress, age, rate, phone, duration, gpa, demandedWage, avgTime, university, id, jobPos;
		istringstream qs(line);

		while (getline(qs, type, ',')) {

			if (type == "intern") {
				getline(qs, name, ',');
				getline(qs, adress, ',');
				getline(qs, age, ',');
				getline(qs, id, ',');
				getline(qs, phone, ',');
				getline(qs, demandedWage, ',');
				getline(qs, duration, ',');
				getline(qs, avgTime);
				int ages = atoi(age.c_str());
				int dw = atoi(demandedWage.c_str());
				int intd = atoi(duration.c_str());
				int t = atoi(avgTime.c_str());

				Candidates.push_back(new Intern(name, adress, ages, id, phone, dw, intd, t));
			}


			else if (type == "experienced") {
				getline(qs, name, ',');
				getline(qs, adress, ',');
				getline(qs, age, ',');
				getline(qs, id, ',');
				getline(qs, phone, ',');
				getline(qs, demandedWage, ',');
				getline(qs, jobPos, ',');
				getline(qs, university, ',');
				getline(qs, gpa, ',');
				getline(qs, avgTime, ',');
				getline(qs, rate);
				int ages = atoi(age.c_str());
				int DW = atoi(demandedWage.c_str());
				int time = atoi(avgTime.c_str());
				int PR = atoi(rate.c_str());
				double gpas = atoi(gpa.c_str());

				Candidates.push_back(new ExperiencedEmployee(name, adress, ages, id, phone, DW, jobPos, university, gpas, time, PR));

			}

			else if (type == "new") {

				getline(qs, name, ',');
				getline(qs, adress, ',');
				getline(qs, age, ',');
				getline(qs, id, ',');
				getline(qs, phone, ',');
				getline(qs, demandedWage, ',');
				getline(qs, jobPos, ',');
				getline(qs, university, ',');
				getline(qs, gpa, ',');
				getline(qs, avgTime);

				int ages = atoi(age.c_str());
				int DW = atoi(demandedWage.c_str());
				int time = atoi(avgTime.c_str());
				int PR = atoi(rate.c_str());
				double gpas = atoi(gpa.c_str());


				Candidates.push_back(new NewEmployee(name, adress, ages, id, phone, DW, jobPos, university, gpas, time));

			}

		}
	}
	C.close();

}


void importData() {

	readClients();
	readCandidates();
}
//-----------------------------------------------Main------------------------------------------------------------Main-------------------------------------------------------------------------------------


int main()
{
	
	cout << "\n\t\t\tPress ENTER to continue...\n";
	cin.ignore();

    importData(); 
	readCompanies();
	readOwners();

	cout << "------------------------\n";
	cout << " Welcome to our website\n";
	cout << "------------------------";
	string choice;


	do {
		cout << "\n\n" << setw(70) << "[:] Current Web Earnings: $" << WebEarnings << endl;
		cout << "\nYou are: " << setw(35) << "More Info:" << "\n\n   1-Company Owner" << setw(44) << "4-Promoted Companies"
			<< "\n\n   2-Client" << setw(49) << "5-Hired Candidates" << "\n\n   3-Looking for a job " << setw(45) << "6-All Candidates\n\nchoice: ";


		cin >> choice;



		if (choice == "0") {
			cout << "\n\nTotal Earnings: $" << WebEarnings << "\n\n Goodbye!\n\n";
			
			ofstream t;
			t.open("totalEarnings", ios_base::app);
			t << "Earnings + $" + to_string(WebEarnings) + "\n";
			t.close();}

		else if (choice == "1") { OwnerMenu(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }

		else if (choice == "2") { ClientMenu(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }

		else if (choice == "3") { CandidateMenu(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }

		else if (choice == "4") { promotedCompaniesInfo(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }

		else if (choice == "5") { Hired(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }

		else if (choice == "6") { EmployeeInfo(); cout << "\nENTER to continue..."; cin.ignore(); cin.ignore(); }

		else { cout << "\nInvalid\n"; }
	} while (choice != "0");
}
