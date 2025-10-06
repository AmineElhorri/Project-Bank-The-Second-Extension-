
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include<cctype>
#include<Cmath>
using namespace std;
enum EnChoose { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, transaction = 6, Manage = 7, Logout=8};
enum EnTransaction { Deposit = 1, Withdraw = 2, TotalBalance = 3, Finish = 4};
enum EnManage {ListUsers=1,addUser=2,DeleteUser=3,UpdateUser=4,FindUser=5,mainmenue=6};
struct SClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool TheMark = false;
};
struct stAdmin
{
	string UserName = "";
	int Password = 0;
    int Permission = 0;
	bool IndexMark = false;
};
string ReadAccountNumber()
{
	string AccountNumber;
	cout << "\n Please Enter AccountNumber  ? : ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
void GoBackToMainMenueUsers(stAdmin);
void ManageUsers(stAdmin);
vector<stAdmin> vAdmin();
stAdmin ConvertLineToDataUser(vector<string>);
void Login();
void ShowTheMenu(stAdmin);
void TransactionMenuScreen(stAdmin);
string ConvertDataUserToLine(stAdmin, string);
void LogOut();
void GoBackToMainMenu(stAdmin User)
{
	cout << "\n Press Any Key To Go Bcak To The Main Menu . ";
	system("pause>0");
	ShowTheMenu(User);
}
void GoBackToMenuTransaction(stAdmin User)
{
	cout << "\n Press any Key To Go Back The Menu Transaction . ";
	system("pause>0");
	TransactionMenuScreen(User);
}
vector<string>Split(string Line, string Delim)
{
	vector<string> split;
	string word = "";
	int Pos = 0;

	while ((Pos = Line.find(Delim)) != std::string::npos)
	{
		word = Line.substr(0, Pos);

		if (word != " ")
		{
			split.push_back(word);
		}

		Line.erase(0, Pos + Delim.length());
	}
	if (Line != " ")
	{
		split.push_back(Line);
	}

	return split;
}
SClient ConvertLineToDataClient(vector<string> split)
{
	SClient Client;
	Client.AccountNumber = split[0];
	Client.PinCode = split[1];
	Client.Name = split[2];
	Client.Phone = split[3];
	Client.AccountBalance = stod(split[4]);

	return Client;
}
vector<SClient> vClient()
{
	vector<SClient> vclient;
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::in);
	if (Houssam.is_open())
	{
		string Line;
		SClient Client;
		while (getline(Houssam, Line))
		{
			Client = ConvertLineToDataClient(Split(Line, "#//#"));
			vclient.push_back(Client);
		}

		Houssam.close();
	}

	return vclient;
}
void PrintDataClient(SClient Client)
{
	cout << "| " << left << setw(18) << Client.AccountNumber << "| " << left << setw(17) << Client.PinCode << "| " << left << setw(40) << Client.Name << "| " << left << setw(20) << Client.Phone << "| " << left << setw(14) << Client.AccountBalance;
}
bool HavingPermissionToShowClientList(stAdmin User)
{
	int Condition = pow(2, 0);
	int Permission = 0;
	Permission = User.Permission & Condition;

	if (Permission == Condition || User.Permission == -1)
		return true;
	else
		return false;

}
void ShowClientList(stAdmin User)
{
	if (!HavingPermissionToShowClientList(User))
	{
		cout << "\n__________________________________________\n";
		cout << " Access Denied \n";
		cout << " You Don't Have Permission To Do This \n";
		cout << " Please Contact Your Admin , \n";
		cout << "____________________________________________\n";

		return;
	}
		


	vector<SClient> vclient = vClient();
	cout << "\n\n \t\t\t\t\t Client List (" << vclient.size() << ") Client(s) . \n\n";
	cout << "________________________________________________________________________________________________________________________\n";
	cout << "| " << left << setw(18) << "Account Number " << "| " << left << setw(17) << "Pin Code " << "| " << left << setw(40) << "Client Name " << "| " << left << setw(20) << "Phone " << "| " << left << setw(14) << "Balance \n";
	cout << "___________________________________________________________________________________________________________________\n";

	for (SClient& Client : vclient)
	{
		PrintDataClient(Client);
		cout << endl;
	}
	cout << "________________________________________________________________________________________________________________________\n";
}
bool IsAccountNumberIsThere(string AccountNumber)
{
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::in);
	if (Houssam.is_open())
	{
		string Line;
		SClient Client;
		while (getline(Houssam, Line))
		{
			Client = ConvertLineToDataClient(Split(Line, "#//#"));
			if (Client.AccountNumber == AccountNumber)
			{
				Houssam.close();
				return true;
			}

		}

		Houssam.close();
	}

	return false;

}
SClient  AddClient()
{
	SClient Client;
	cout << "_______________________________________________\n";
	cout << "\t\t Adding New Client : \n";
	cout << "_______________________________________________\n";
	cout << " Enter Account Number : ";
	getline(cin >> ws, Client.AccountNumber);
	while (IsAccountNumberIsThere(Client.AccountNumber))
	{
		cout << " Client With (" << Client.AccountNumber << ") Already Exist , Enter Another Account Number : ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << " Enter Pin Code : ";
	getline(cin, Client.PinCode);
	cout << " Enter Name : ";
	getline(cin, Client.Name);
	cout << " Enter Phone : ";
	getline(cin, Client.Phone);
	cout << " Enter Account Balance : ";
	cin >> Client.AccountBalance;

	return Client;

}
string ConvertDataClientToLine(SClient Client, string Separater)
{
	string Line = "";
	Line += Client.AccountNumber + Separater;
	Line += Client.PinCode + Separater;
	Line += Client.Name + Separater;
	Line += Client.Phone + Separater;
	Line += to_string(Client.AccountBalance);

	return Line;
}
bool HavingPermissionToAddNewClient(stAdmin User)
{
	int Condition = pow(2, 1);
	int Permission = 0;
	Permission = User.Permission & Condition;
	if (Permission == Condition || User.Permission == -1)
		return true;
	else
		return false;
}
void AddNewClient(stAdmin User)
{
	if (!HavingPermissionToAddNewClient(User))
	{
		cout << "\n__________________________________________\n";
		cout << " Access Denied \n";
		cout << " You Don't Have Permission To Do This \n";
		cout << " Please Contact Your Admin , \n";
		cout << "____________________________________________\n";

		return;
	}


	char AddMore = 'Y';
	do
	{
		SClient Client = AddClient();
		fstream Houssam;
		Houssam.open("Houssam.txt", ios::out | ios::app);
		if (Houssam.is_open())
		{
			string Line = ConvertDataClientToLine(Client, "#//#");
			Houssam << Line << endl;
			Houssam.close();

			cout << "\n Client Added Successfully Do You Want to Add More ClientS ? [Y or N ] . ";
			cin >> AddMore;
		}
	} while (toupper(AddMore) == 'Y');

}
bool FindClientByAccountNumber(SClient& Client, vector<SClient>vclient, string AccountNumber)
{
	for (SClient& C : vclient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void PrintClient(SClient client)
{
	cout << "\n The Following Are The Client Details : \n";
	cout << "______________________________________________________\n";
	cout << " Account Number : " << client.AccountNumber << endl;
	cout << " Pin Code : " << client.PinCode << endl;
	cout << " Name : " << client.Name << endl;
	cout << " Phone : " << client.Phone << endl;
	cout << " Account Balance : " << client.AccountBalance << endl;
	cout << "______________________________________________________\n";
}
bool MarkToDoSomeThing(vector<SClient>& vclient, string AccountNumber)
{
	for (SClient& C : vclient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.TheMark = true;
			return true;
		}
	}
	return false;
}
void SaveDataToFile(vector<SClient>& vclient)
{
	fstream Houssam;
	Houssam.open("Houssam.txt", ios::out);
	if (Houssam.is_open())
	{
		string Line = "";

		for (SClient& C : vclient)
		{
			if (C.TheMark == false)
			{
				Line = ConvertDataClientToLine(C, "#//#");
				Houssam << Line << endl;
			}
		}

		Houssam.close();
	}
}
bool HavingPermissionToDeleteClients(stAdmin User)
{
	int Condition = pow(2, 2);
	int Permission = User.Permission & Condition;
	if (Permission == Condition || User.Permission == -1)
		return true;
	else
		return false;
}
bool DeleteClientS(vector<SClient> vclient,stAdmin User)
{

	if (!HavingPermissionToDeleteClients(User))
	{
		cout << "\n__________________________________________\n";
		cout << " Access Denied \n";
		cout << " You Don't Have Permission To Do This \n";
		cout << " Please Contact Your Admin , \n";
		cout << "____________________________________________\n";

		return false;
	}


	cout << "______________________________________________\n";
	cout << "\t\t Delete Client Screen \n";
	cout << "______________________________________________\n";
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	char Delete = 'Y';
	SClient Client;
	if (FindClientByAccountNumber(Client, vclient, AccountNumber))
	{
		PrintClient(Client);
		cout << "\n\n Are You Sure You Want To Delete This Client [Y or N] ?  ";
		cin >> Delete;
		if (toupper(Delete) == 'Y')
		{
			MarkToDoSomeThing(vclient, AccountNumber);
			SaveDataToFile(vclient);

			cout << "\n Client Deleted Successfully . \n\n";
			return true;
		}
	}
	else
	{
		cout << "\n\n Client With (" << AccountNumber << ") is Not Found . \n\n";
		return false;
	}
}

SClient ChangeClientInfo()
{

	SClient Client;

	cout << " Enter Pin Code  : ";
	getline(cin >> ws, Client.PinCode);
	cout << " Enter Name : ";
	getline(cin, Client.Name);
	cout << " Enter Phone : ";
	getline(cin, Client.Phone);
	cout << " Enter Account Balance : ";
	cin >> Client.AccountBalance;

	return Client;

}
bool HavingPermissionToUpdateClientInfo(stAdmin User)
{
	int Condition = pow(2, 3);
	int Permission = 0;
	Permission = User.Permission & Condition;
	if (Permission == Condition || User.Permission == -1)
		return true;
	else
		return false;
}
bool UpdateClientInfo(vector<SClient>vclient,stAdmin User)
{
	if (!HavingPermissionToUpdateClientInfo(User))
	{
		cout << "\n__________________________________________\n";
		cout << " Access Denied \n";
		cout << " You Don't Have Permission To Do This \n";
		cout << " Please Contact Your Admin , \n";
		cout << "____________________________________________\n";

		return false;
	}
	cout << "_________________________________________________\n";
	cout << "\t\t Update Client Info Screen \n";
	cout << "_________________________________________________\n";
	string AccountNumber = ReadAccountNumber();
	SClient Client;
	char Update = 'Y';

	if (FindClientByAccountNumber(Client, vclient, AccountNumber))
	{
		SClient client;
		PrintClient(Client);
		cout << "\n\n Are You Sure You want To Update This Client ? [Y or N] .  ";
		cin >> Update;
		if (toupper(Update) == 'Y')
		{
			for (SClient& C : vclient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientInfo();
				}
			}

			SaveDataToFile(vclient);

			cout << "\n Client Updated Successfully . \n";
			return true;
		}
	}
	else
	{
		cout << "\n Client With (" << AccountNumber << ") is Not Found . \n";
		return false;
	}
}
bool HavingPermissionToFindClientInfo(stAdmin User)
{
	int Condition = pow(2, 4);
	int Permission = 0;
	Permission = User.Permission & Condition;
	if (Permission == Condition || User.Permission == -1)
		return true;
	else
		return false;
}
bool FindClientInfo(vector<SClient> vclient,stAdmin User)
{
	if (!HavingPermissionToFindClientInfo(User))
	{
		cout << "\n__________________________________________\n";
		cout << " Access Denied \n";
		cout << " You Don't Have Permission To Do This \n";
		cout << " Please Contact Your Admin , \n";
		cout << "____________________________________________\n";

		return false;
	}


	
	cout << "_________________________________________________________\n";
	cout << "\t\t\t Find Client Screen \n";
	cout << "_________________________________________________________\n";
	string AccountNumber = ReadAccountNumber();
	SClient Client;
	if (FindClientByAccountNumber(Client, vclient, AccountNumber))
	{
		PrintClient(Client);
		return true;
	}
	else
	{
		cout << "\n Client With (" << AccountNumber << ") is Not Found .\n";
		return false;
	}
}
void LogOut()
{
	Login();
}
EnTransaction YourChoose(string Message)
{
	int Choose = 0;
	do
	{
		cout << Message << "   ";
		cin >> Choose;

	} while (Choose < 1 || Choose>4);

	return (EnTransaction)Choose;
}
double ReadNumber(string Message)
{
	double Number;
	cout << Message << "   ";
	cin >> Number;
	return Number;
}
bool PerfomTransactionToDeposit(vector<SClient>& vclient, SClient Client, string AccountNumber)
{
	double Number = ReadNumber("Please Enter Deposit Amount ? ");
	double N = 0;
	char Answer = 'Y';
	cout << " \nAre you sure you want to perfom this transaction [Y or N]?   ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		for (SClient& C : vclient)
		{
			if (C.AccountNumber == Client.AccountNumber)
			{
				C.AccountBalance = C.AccountBalance + Number;
				N = C.AccountBalance;
				break;
			}
		}

		SaveDataToFile(vclient);
		cout << "\n  Done Successfully New Balance : " << N << endl;

		return true;
	}

	return false;

}
void FindDepositClient()
{
	SClient Client;
	vector<SClient>vclient = vClient();
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(Client, vclient, AccountNumber))
	{
		cout << " Client With (" << AccountNumber << ") Do Not Exist . \n";
		cout << " Please Enter Account Number :  ";
		getline(cin >> ws, AccountNumber);
	}
	PrintClient(Client);
	PerfomTransactionToDeposit(vclient, Client, AccountNumber);
}
void DepositChoose()
{
	cout << "_________________________________________________\n";
	cout << "\t\t Deposit Screen \n";
	cout << "_________________________________________________\n";
	FindDepositClient();
}
void PrintBalances(SClient Client)
{
	cout << "| " << left << setw(17) << Client.AccountNumber << "| " << left << setw(40) << Client.Name << "| " << left << setw(30) << Client.AccountBalance;
}
void TotalBalances()
{
	vector<SClient>vclient = vClient();
	double Total = 0;
	cout << "\n \t\t\t Balances List (" << vclient.size() << ") Client(s) .\n\n";
	cout << "___________________________________________________________________________________________________\n";
	cout << "| " << left << setw(17) << "Account Number " << "| " << left << setw(40) << "Client Name " << "| " << left << setw(30) << "Balance \n";
	cout << "______________________________________________________________________________\n";

	for (SClient& Client : vclient)
	{
		Total = Total + Client.AccountBalance;
		PrintBalances(Client);
		cout << endl;
	}
	cout << "___________________________________________________________________________________________________\n\n";
	cout << "\t\t\t\t Total Balances : " << Total << endl;
}
void CheckAboutTheClientBalance(double& Number, double AccountBalance)
{
	while (Number > AccountBalance)
	{
		cout << "\n Amount Exceeds The Balance , you can withdraw up to : ";
		cout << AccountBalance << endl;
		cout << " Please Enter Another Amount ?  ";
		cin >> Number;
	}
	cout << "\n";
}
bool PerformTransactionToWithdraw(vector<SClient>& vclient, SClient Client, string AccountNumber)
{
	double Number = ReadNumber("Please Enter Withdraw Amount ? ");
	CheckAboutTheClientBalance(Number, Client.AccountBalance);
	double N = 0;
	char Answer = 'Y';
	cout << " \nAre you sure you want to perfom this transaction [Y or N]?   ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		for (SClient& C : vclient)
		{
			if (C.AccountNumber == Client.AccountNumber)
			{
				C.AccountBalance = C.AccountBalance - Number;
				N = C.AccountBalance;
				break;
			}
		}

		SaveDataToFile(vclient);

		cout << "\n  Done Successfully New Balance : " << N << endl;

		return true;
	}

	return false;

}
void FindWithdrawClient()
{
	SClient Client;
	vector<SClient>vclient = vClient();
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(Client, vclient, AccountNumber))
	{
		cout << " Client With (" << AccountNumber << ") Do Not Exist . \n";
		cout << " Please Enter Account Number :  ";
		getline(cin >> ws, AccountNumber);
	}
	PrintClient(Client);
	PerformTransactionToWithdraw(vclient, Client, AccountNumber);
}
void WithdrowChoose()
{
	cout << "__________________________________________________\n";
	cout << "\t\t Withdraw Screen \n";
	cout << "__________________________________________________\n";
	FindWithdrawClient();
}
void GoBackToPrincipleMainMenu(stAdmin User)
{
	ShowTheMenu(User);
}
void TrasactionSwitchCase(EnTransaction Choose,stAdmin User)
{
	switch (Choose)
	{
	case::EnTransaction::Deposit:
		system("cls");
		DepositChoose();
		GoBackToMenuTransaction(User);
		break;

	case::EnTransaction::TotalBalance:
		system("cls");
		TotalBalances();
		GoBackToMenuTransaction(User);
		break;

	case::EnTransaction::Withdraw:
		system("cls");
		WithdrowChoose();
		GoBackToMenuTransaction(User);
		break;

	case::EnTransaction::Finish:
		system("cls");
		GoBackToPrincipleMainMenu(User);
		break;
	}
}
bool HavingPermissionToTransactions(stAdmin User)
{
	int Condition = pow(2, 5);
	int Permission = 0;
	Permission = User.Permission & Condition;
	if (Permission == Condition || User.Permission == -1)
		return true;
	else
		return false;
}
void TransactionMenuScreen(stAdmin User)
{
	if (!HavingPermissionToTransactions(User))
	{
		cout << "\n__________________________________________\n";
		cout << " Access Denied \n";
		cout << " You Don't Have Permission To Do This \n";
		cout << " Please Contact Your Admin , \n";
		cout << "____________________________________________\n";

		return;
	}


	system("cls");
	cout << "=============================================================\n";
	cout << "\t\t Transactions Menue Screen \n";
	cout << "=============================================================\n";
	cout << "\t [1] Deposit  \n";
	cout << "\t [2] Withdrow  \n";
	cout << "\t [3] Total Balances  \n";
	cout << "\t [4] Main Menue  \n";
	cout << "=============================================================\n";
	EnTransaction Choose = YourChoose("Choose What Do you Want to Do ? [1 to 4]");
	TrasactionSwitchCase(Choose,User);

}
void GoBackToMainMenueUsers(stAdmin User)
{
	system("pause>0");
	system("cls");
	ManageUsers(User);
}
void PrintUsersList(stAdmin User)
{
	cout << "| " << setw(10) << User.UserName << " | " << setw(10) << User.Password << " | " << setw(40) << User.Permission;
}
void ShowListUsers()
{
	vector<stAdmin>vadmin = vAdmin();
	cout << "\t\t\t\t Users List " << vadmin.size() << " User(s). \n";
	cout << "______________________________________________________________________________\n";
	cout << "| " << setw(10) << "User Name " << "| " << setw(10) << "PassWord " << "| " << setw(40) << "Permissions \n";
	cout << "______________________________________________________________________________\n";

	for (stAdmin& User : vadmin)
	{
		PrintUsersList(User);
		cout << "\n";
	}
	cout << "______________________________________________________________________________\n";
}
bool IsUserNameInFile(vector<stAdmin>vadmin, string UserName)
{
	for (stAdmin& U : vadmin)
	{
		if (U.UserName == UserName)
			return false;
	}

	return true;
}
stAdmin ReadUser()
{
	vector<stAdmin> vadmin = vAdmin();
	stAdmin User;
	cout << " Enter UserName : ";
	getline(cin >> ws, User.UserName);
	while (!IsUserNameInFile(vadmin, User.UserName))
	{
		cout.clear();
		cin.clear();
		cout << " User With [" << User.UserName << "] already Exist , Enter another UserName ? ";
		getline(cin >> ws, User.UserName);
	}

	cout << " Enter PassWord ? ";
	cin >> User.Password;
	return User;
}
void AddUserScreen()
{
	cout << "_______________________________________\n";
	cout << "\t\t\t Add New User Screen \n";
	cout << "_______________________________________\n";
}
string ConvertDataUserToLine(stAdmin User, string Separater)
{
	string Line = "";
	Line += User.UserName + Separater;
	Line += to_string(User.Password) + Separater;
	Line += to_string(User.Permission);

	return Line;
}
void ThePermissionsGiving(stAdmin& User)
{
	char Show = 'y', Add = 'y', DeLete = 'y', Update, Find = 'y', Transactions = 'y', Manage = 'y';
	cout << " show Client List ? ";
	cin >> Show;
	if (Show == 'y')
		User.Permission+= pow(2, 0);

	cout << "\n Add New Client ? ";
	cin >> Add;
	if (Add == 'y')
		User.Permission += pow(2, 1);

	cout << "\n Delete Client ?  ";
	cin >> DeLete;
	if (DeLete == 'y')
		User.Permission += pow(2, 2);

	cout << "\n Update Client ? ";
	cin >> Update;
	if (Update == 'y')
		User.Permission += pow(2, 3);

	cout << "\n Find Client ?  ";
	cin >> Find;
	if (Find == 'y')
		User.Permission += pow(2, 4);

	cout << "\n Transactions ?  ";
	cin >> Transactions;
	if (Transactions == 'y')
		User.Permission += pow(2, 5);

	cout << "\n Manage Users ? ";
	cin >> Manage;
	if (Manage == 'y')
		User.Permission += pow(2, 6);


	return;
}
bool AddingFullAccess(stAdmin& User)
{
	char Access = 'Y';
	cout << " Do you want To Give Full Access y/n  ";
	cin >> Access;
	if (toupper(Access) == 'Y')
	{
		User.Permission = -1;
		return true;
	}
	else
	{
		cout << "\n\n Do You Want To Give Access To : \n\n";
		ThePermissionsGiving(User);
		return false;
	}
}
void AddNewUserToFile()
{

	AddUserScreen();

	char AddMore = 'Y';
	do
	{
		stAdmin User = ReadUser();
		AddingFullAccess(User);
		fstream Admin;
		Admin.open("Admin.txt", ios::out | ios::app);
		if (Admin.is_open())
		{
			
			string Line = ConvertDataUserToLine(User, "#//#");
			Admin << Line << endl;
			Admin.close();

			cout << "\n User Added Successfully Do You Want to Add More Users ? [Y or N ] . ";
			cin >> AddMore;
		}
	} while (toupper(AddMore) == 'Y');

}
void DeleteUserScreen()
{
	cout << "___________________________________________\n";
	cout << "\t\t Delete Users Screen \n";
	cout << "___________________________________________\n";
}
bool IsUserNameExistInFile(stAdmin& User,vector<stAdmin>vadmin, string UserName)
{
	for (stAdmin& U : vadmin)
	{
		if (U.UserName == UserName)
			User = U;
			return true;
	}

	return false;
}
void PrintUserInformation(stAdmin User)
{
	cout << "\n The Following Are The User Details : \n";
	cout << "__________________________________________\n";
	cout << " UserName     : " << User.UserName << "\n";
	cout << " PassWord     : " << User.Password << "\n";
	cout << " Permissions  : " << User.Permission << "\n";
	cout << "__________________________________________\n";
}
void SaveUserInformationToFile(vector<stAdmin>& vadmin)
{
	fstream Admin;
	Admin.open("Admin.txt", ios::out);
	if (Admin.is_open())
	{
		string Line = "";

		for (stAdmin& U : vadmin)
		{
			if (U.IndexMark == false)
			{
				Line = ConvertDataUserToLine(U, "#//#");
				Admin << Line << endl;
			}
		}

		Admin.close();
	}
}
bool MarkIndex(vector<stAdmin>& vadmin, string UserName)
{
	for (stAdmin& U : vadmin)
	{
		if (U.UserName == UserName)
		{
			U.IndexMark = true;
			return true;
		}
	}
	return false;
}
bool DeleteUserFromFile()
{
	DeleteUserScreen();

	char Delete = 'y';
	vector<stAdmin> vadmin = vAdmin();
	string UserName;
	stAdmin user;
	cout << " Please Enter UserName ?  ";
	getline(cin >> ws, UserName);


	if (UserName == "Admin")
	{
		cout << "\n You Cannot Delete This User \n";
		return false;
	}


	if (IsUserNameExistInFile(user,vadmin, UserName))
	{
		PrintUserInformation(user);

		cout << "\n\n Are You Sure You Want To Delete This User  y/n ? ";
		cin >> Delete;
		if (toupper(Delete) == 'Y')
		{
			MarkIndex(vadmin, UserName);
			SaveUserInformationToFile(vadmin);

			cout << "\n User Deleted SuccessFully \n";
			return true;
		}
	}
	else
	{
		cout << "User With UserName (" << UserName << ") is Not Found ! \n";
		return false;
	}
}
void UpdateUsersScreen()
{
	cout << "_____________________________________________\n";
	cout << "\t\t\t Update Users Screen \n";
	cout << "_____________________________________________\n\n";
}
string ReadUserName()
{
	string UserName;
	cout << " Please Enter UserName ? ";
	getline(cin >> ws, UserName);

	return UserName;
}
stAdmin ChangeUserInfo(string UserName)
{
	stAdmin User;
	User.UserName = UserName;
	cout << " Enter PassWord ? ";
	cin >> User.Password;

	AddingFullAccess(User);

	return User;
}
bool UpdateUserInfo()
{
	UpdateUsersScreen();

	vector<stAdmin> vadmin = vAdmin();
	string UserName = ReadUserName();
	stAdmin User;
	char Update = 'Y';
	

	if (IsUserNameExistInFile(User,vadmin,UserName))
	{
		
		PrintUserInformation(User);

		cout << "\n\n Are You Sure You want To Update This User ? [Y or N] .  ";
		cin >> Update;
		if (toupper(Update) == 'Y')
		{
			for (stAdmin& U : vadmin)
			{
				if (U.UserName == UserName )
				{
					U = ChangeUserInfo(UserName);
				}
			}

			SaveUserInformationToFile(vadmin);

			cout << "\n User Updated Successfully . \n";
			return true;
		}
	}
	else
	{
		cout << "\n User With (" << UserName << ") is Not Found . \n";
		return false;
	}
}
void FindUserScreen()
{
	cout << "_________________________________________________\n";
	cout << "\t\t Find Users Screen \n";
	cout << "_________________________________________________\n\n";
}
bool FindUsersInfo()
{
	FindUserScreen();

	vector<stAdmin>vadmin = vAdmin();
	stAdmin User;
	string UserName = ReadUserName();
	if (IsUserNameExistInFile(User, vadmin, UserName))
	{
		PrintUserInformation(User);
		return true;
	}
	else
	{
		cout << " User With UserName (" << UserName << ") is Not Found ! \n";
		return false;
	}
}
void MainMenue(stAdmin User)
{
	ShowTheMenu(User);
}

EnManage WhatDoYouWantToChoose(string Message)
{
	short Choose;
	do
	{
		cout << Message << "   ";
		cin >> Choose;
	} while (Choose < 1 || Choose>6);

	return (EnManage)Choose;
}
void ManageSwitchCase(EnManage Choose,stAdmin User)
{
	switch (Choose)
	{
	case::EnManage::ListUsers:
		system("cls");
		ShowListUsers();
		GoBackToMainMenueUsers(User);
		break;

	case::EnManage::addUser:
		system("cls");
		AddNewUserToFile();
		GoBackToMainMenueUsers(User);
		break;

	case::EnManage::DeleteUser:
		system("cls");
		DeleteUserFromFile();
		GoBackToMainMenueUsers(User);
		break;

	case::EnManage::UpdateUser:
		system("cls");
		UpdateUserInfo();
		GoBackToMainMenueUsers(User);
		break;

	case::EnManage::FindUser:
		system("cls");
		FindUsersInfo();
		GoBackToMainMenueUsers(User);
		break;

	case::EnManage::mainmenue:
		system("cls");
		MainMenue(User);
		break;
	}
}
bool HavingPermissionToManageUsers(stAdmin User)
{
	int Condition = pow(2, 6);
	int Permission = 0;
	Permission = User.Permission & Condition;
	if (Permission == Condition || User.Permission == -1)
		return true;
	else
		return false;
}
void ManageUsers(stAdmin User)
{
	if (HavingPermissionToManageUsers(User))
	{
		cout << "\n__________________________________________\n";
		cout << " Access Denied \n";
		cout << " You Don't Have Permission To Do This \n";
		cout << " Please Contact Your Admin , \n";
		cout << "____________________________________________\n";

		return;
	}



	cout << "===================================================================\n";
	cout << "\t\t\t Manage Users Menue Screen \n";
	cout << "===================================================================\n";
	cout << "\t[1] List Users \n";
	cout << "\t[2] Add New User \n";
	cout << "\t[3] Delete User \n";
	cout << "\t[4] Update User \n";
	cout << "\t[5] Find User \n";
	cout << "\t[6] Main Menue \n";
	cout << "===================================================================\n";
	EnManage choose = WhatDoYouWantToChoose("Choose What Do You Want To Do ?");
	ManageSwitchCase(choose,User);

}

EnChoose ChooseWhatDoYouWantToDo(string Message)
{
	int Choose;
	do
	{
		cout << Message << "  ";
		cin >> Choose;
	} while (Choose < 1 || Choose > 8);

	return (EnChoose)Choose;
}
void ShowAllScreans(EnChoose Choose,stAdmin User)
{
	switch (Choose)
	{
	case EnChoose::Show:
		system("cls");
		ShowClientList(User);
		GoBackToMainMenu(User);
		break;

	case EnChoose::Add:
		system("cls");
		AddNewClient(User);
		GoBackToMainMenu(User);
		break;

	case EnChoose::Delete:
		system("cls");
		DeleteClientS(vClient(),User);
		GoBackToMainMenu(User);
		break;

	case::EnChoose::Update:
		system("cls");
		UpdateClientInfo(vClient(),User);
		GoBackToMainMenu(User);
		break;

	case::EnChoose::Find:
		system("cls");
		FindClientInfo(vClient(),User);
		GoBackToMainMenu(User);
		break;

	case::EnChoose::transaction:
		system("cls");
		TransactionMenuScreen(User);
		break;

	case::EnChoose::Manage:
		system("cls");
		ManageUsers(User);
		break;

	case::EnChoose::Logout:
		system("cls");
		LogOut();
		break;
	}
}
void ShowTheMenu(stAdmin User)
{
	system("cls");
	cout << "======================================================================================\n";
	cout << "\t\t\t\t Main Manue Screen\n";
	cout << "======================================================================================\n";
	cout << "\t[1] Show Client List  \n";
	cout << "\t[2] Add NewClient  \n";
	cout << "\t[3] Delete Client  \n";
	cout << "\t[4] Update Client Info  \n";
	cout << "\t[5] Find Client  \n";
	cout << "\t[6] Transaction  \n";
	cout << "\t[7] Manager Users  \n";
	cout << "\t[8] Logout  \n";
	cout << "=======================================================================================\n\n";
	EnChoose Choose = ChooseWhatDoYouWantToDo("Choose What Do you Want To Do ? [1 To 8]");
	cout << "\n\n";
	ShowAllScreans(Choose,User);

}
bool IsUserInFile(stAdmin User , vector <stAdmin> vadmin)
{
	for (stAdmin& U : vadmin)
	{
		if (U.UserName == User.UserName)
			if (U.Password == User.Password)
				return true;
	}
	
	return false;
}
stAdmin ConvertLineToDataUser(vector<string> split)
{
	stAdmin User;
	User.UserName = split[0];
	User.Password = stoi(split[1]);
	User.Permission = stoi(split[2]);

	return User;
}

vector<stAdmin> vAdmin()
{
	vector<stAdmin> vadmin;
	fstream Admin;
	Admin.open("Admin.txt", ios::in);
	if (Admin.is_open())
	{
		string Line;
		stAdmin User;
		while (getline(Admin, Line))
		{
			User = ConvertLineToDataUser(Split(Line, "#//#"));
			vadmin.push_back(User);
		}

		Admin.close();
	}

	return vadmin;
}

stAdmin FindTheAdmin()
{
	vector<stAdmin>vadmin = vAdmin();
	stAdmin User;

	cout << " Enter UserName? ";
	getline(cin >> ws, User.UserName);
	cout << " Enter PassWord? ";
	cin >> User.Password;

	while (!IsUserInFile(User, vadmin))
	{
		cout.clear();
		cin.clear();
		cout << " Invalid UserName / Password! \n";

		cout << " Enter UserName? ";
		getline(cin >> ws, User.UserName);
		cout << " Enter PassWord? ";
		cin >> User.Password;
	}

	return User;
}
void LoginScreen()
{
	cout << "______________________________\n";
	cout << "\t\t\t Login Screen \n";
	cout << "______________________________\n";
}
void Login()
{
	LoginScreen();
	stAdmin User = FindTheAdmin();
	ShowTheMenu(User);
}
int main()
{
	Login();
}