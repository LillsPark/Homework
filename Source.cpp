#include<iostream>
#include<fstream>

using std::cin;
using std::cout;

struct Wallet 
{
	char owner[256];
	unsigned int id;
	double fiatMoney;
};

unsigned RandomNumber()
{
	unsigned range = 4294967294 + 1; // the range is from 0 to 4294967294
	return rand() % range;
}


void PrintName(const char* buffer)
{
	for (int i = 0; buffer[i] != '\0'; ++i)
		cout << buffer[i];
	cout << std::endl;
}



char*  copy(char*name, const char* buffer)
{
	int i = 0;
	do
	{
		*name = *buffer;
		*name++;
		*buffer++;
		i++;
	} while (*buffer != '\0');
	*name = '\0';
	PrintName(name - i);
	return name - i;
}

void printName(const Wallet& wallet)
{
	cout << "Wallet's owner name is: " << std::endl;
	for (int i = 0; wallet.owner[i]; ++i)
		cout << wallet.owner[i];
	cout << std::endl; 
}

bool compareString(const char* input, const char* command)
{
	while(*input != ' ' && *input != '\n')
	{
		if (*input == *command)
		{
			*input++;
			*command++;
		}
		else
			return false;
	}
	
	return true;
}
 
bool IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

unsigned int number(const char* s, unsigned int* ptr)
{
	unsigned int result = 0;
	unsigned int i;
	for (i = 0; IsDigit(s[i]); ++i)
	{
		result = result * 10 + (s[i] - '0');
	}

	*ptr = i;//premestvame pointera s edno pole napred

	return result;
}

unsigned int countDigits(unsigned int number)
{
	int count = 0;
	while (number)
	{
		number /= 10;
		++count;
	}
	return count;
}


int power(int num, int exp)
{
	int n = 1;

	if (exp == 0)
		return 1;
	for (int i = exp; i; --i)
	{
		n *= num;
	}

	return n;
}

double fiantMoney(const char* buffer)
{
	double fiatMoney = 0;
	unsigned ptr;
	unsigned int intPart = number(buffer, &ptr);

	buffer += ptr + 1; // propuskame chqlata chast na chisloto i desetichnata tochka
	unsigned int doublePart = number(buffer, &ptr);
	buffer += countDigits(intPart);
	unsigned int cntDigits = countDigits(doublePart);
	fiatMoney = (double)intPart + (double)doublePart / (double)(power(10, cntDigits));

	cout << fiatMoney << std::endl;	

	return fiatMoney;
}

void printWallet(const Wallet& wallet)
{
	cout << wallet.fiatMoney << " "
		<< wallet.id << " "
		<< wallet.owner << std::endl;
	//printName(wallet.owner);
}

//bool Read()
//{
//	std::fstream in;
//
//	if (!in)
//	{
//
//	}
//
//	while (in)
//	{
//		in.read((char*)readSize, );
//	}
//in.close();
//}
//
//bool Write()
//{
//	std::fstream out;
//
//
//}

int main()
{
	char buffer[] = "add-wallet 4453.455 kimyongi";
//	cin.getline(buffer, 301);
	if (compareString(buffer, "add-wallet"))
	{
		Wallet wallet;

		char* ptr = buffer; //vzimam pointer kum buffera
		ptr += sizeof("add-wallet"); //sochi elementa sled intervala
		wallet.fiatMoney = fiantMoney(ptr);
		ptr += countDigits(wallet.fiatMoney);
		if (*ptr == '.' || *ptr == ',')
		{
			++ptr;
			ptr += countDigits(wallet.fiatMoney);
		}

		copy(wallet.owner, ptr);

		wallet.id = RandomNumber();

		printWallet(wallet);
	}
		

//	if(compareString(command, "make-order"))
//	if(compareString(command, "wallet-info"))
//	if(compareString(command, "attract-investors"))
//	if(compareString(command, "quit"))
	return 0;
}