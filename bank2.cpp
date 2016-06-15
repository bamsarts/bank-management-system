//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<stdlib.h>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//fungsi menhambil data user
	void show_account() const;	//fungsi menampilkan data user
	void dep(int);	//fungsi setor tunai
	void draw(int);	//fungsi tarik tunai
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account
};         //class ends here

void account::create_account()
{
	cout<<"\nMasukkan No. Akun :";
	cin>>acno;
	cout<<"\n\nMasukkan nama anda : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nMasukkan type akun(C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nMasukkan jumlah saldo awal (>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\n Akun berhasil dibuat..";
}

void account::show_account() const
{
	cout<<"\nMasukkan No.Akun. : "<<acno;
	cout<<"\nMasukkan Nama Anda : ";
	cout<<name;
	cout<<"\nTipe Akun : "<<type;
	cout<<"\nSisa Saldo   : "<<deposit;

}

void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. Buat Akun";
		cout<<"\n\n\t02. Setor ";
		cout<<"\n\n\t03. Tarik";
		cout<<"\n\n\t04. Tutup Akun";
		cout<<"\n\n\t05. EXIT";
		cout<<"\n\n\tSelect Your Option (1-6) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tMasukkan Akun anda : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tMasukkan Akun anda : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tMasukkan akun anda : "; cin>>num;
			delete_account(num);
			break;
		
		 case '5':
			cout<<"\n\n\tTerima kasih telah menggunakan bank Management system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nDetail Saldo\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAkun tidak ditemukan";
}



//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}



//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************


void intro()
{
	cout<<"\n\n     ( BAMBANG S )";
	cout<<"\n Bank Management System";
	cout<<"\n\n\n\nCreated by : Bambang Supriadi";
	cout<<"\n\n""Visit : www.bamsarts.id";
	cin.get();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
