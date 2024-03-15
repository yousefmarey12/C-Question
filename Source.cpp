#include<iostream>
#include<string.h>

using namespace std;

/*
	Question:
		Suppose we have a custom made String Class with it's constructors' implementations
		defined in part 1, and that we have an implementation for the operator+ overload,
		defined in part 2.

		The Employee class, Part 3, is defined. The main(), part 4, function defines an employee named "Edie".

		We will add the employee's first name to his last name, which is done in part 5.


		According to my textbook, making part 3, the overloaded operator, a const method will return an error as I quote

		"The designer of the employee class has blocked access to the operator+ being called on Employee objectsr by declaring that
		all the string accessors, such as GetFirstName(), return a constant reference. Because operator+ is not (and can't be) a const function
		(it changes the object it is called on), attempting to write the following will cause a compile-time eroror"


		Drumroll please!!!

		I tried to make the `operator+` overload a const function which DID not give me a compile-time error.

		How does `operator+` change the object it is called on? Like I literally made it const and it did not give me a compile-time error?
		Could have the textbook made a mistake and meant `operator=`?

*/

// Part 1
class String
{
public:
	String();
	String(const char* const);
	String(const String&);
	~String();


	char& operator[](int offset);
	char operator[](int offset) const;
	String operator+(const String&);
	void operator+=(const String&);
	String& operator=(const String&);

	int GetLen() const { return itsLen; }
	const char* GetString() const { return itsString; }
	static int ConstructorCount;
private:
	String(int);
	char* itsString;
	unsigned short itsLen;
};

String::String()
{
	itsString = new char[1];
	itsString[0] = '\0';
	itsLen = 0;
}


String::String(int len)
{
	itsString = new char[len + 1];
	for (int i = 0; i <= len; i++) {
		itsString[i] = '\0';
	}
	itsLen = len;
}

String::String(const char* const cString)
{
	itsLen = strlen(cString);
	itsString = new char[itsLen + 1];
	for (int i = 0; i < itsLen; i++) {
		itsString[i] = cString[i];
	};
	itsString[itsLen] = '\0';
}

String::String(const String& rhs)
{
	itsLen = rhs.GetLen();
	itsString = new char[itsLen + 1];
	for (int i = 0; i < itsLen; i++) {
		itsString[i] = rhs[i];
	};
	itsString[itsLen] = '\0';
}

String::~String()
{
	delete[] itsString;
	itsLen = 0;
}

// Part 2
String String::operator+(const String& rhs)
{
	int totalLen = itsLen + rhs.GetLen();
	String temp(totalLen);
	int i, j;
	for (i = 0; i < itsLen; i++)
		temp[i] = itsString[i];
	for (j = 0; j < rhs.GetLen(); j++, i++) {
		temp[i] = rhs[j];
	};
	temp[totalLen] = '\0';
	return temp;
}

class Employee
{
public:
	Employee();
	Employee(const char*, const char*, const char*, long);
	Employee(const Employee&);
	~Employee();
	Employee& operator= (const Employee&);

	const String& GetFirstName() const { return itsFirstName; }
	const String& GetLastName() const { return itsLastName; }
	const String& GetAddress() const { return itsAddress; }
	long GetSalary() const { return itsSalary; }

	void SetFirstName(const String& fName)
	{
		itsFirstName = fName;
	}
	void SetLastName(const String& lName)
	{
		itsLastName = lName;
	}
	void SetAddress(const String& address)
	{
		itsAddress = address;
	}
	void SetSalary(const long salary)
	{
		itsSalary = salary;
	}
private:
	String itsFirstName;
	String itsLastName;
	String itsAddress;
	long itsSalary;

};

int main() {
	Employee Edie("Edie", "Marey", "123 street", 20000);
	String fullName = Edie.GetFirstName() + Edie.GetFirstName();
	return 0;
}