// Mohammadreza Abolhassani 2034569
// Ariel Martin Cohen 

#include <iostream>
#include"ContactTree.h"
using namespace std;

int main()
{
	ContactTree ct;
	ct.AddPatient0("Michelle");
	ct.AddContact("Michelle", "Moe");
	ct.AddContact("Michelle", "Ariel");
	ct.AddContact("Michelle", "Sean");
	ct.AddContact("Michelle", "Savva");
	ct.AddContact("Moe", "Dani");
	ct.AddContact("Moe", "Roxy");
	ct.AddContact("Sean", "Mel");
	ct.AddContact("Ariel", "Baby");
	ct.AddContact("Moe", "John");
	ct.AddContact("John", "Yanni");
	ct.AddContact("Sean", "Cat");
	ct.AddContact("John", "Alanna");

	ct.PrintContactTree();
	ct.TraceSource("Yanni");

	ct.DeleteContact("John");

	//ct.DeleteContact("Michelle");
	ct.PrintContactTree();

	cout << "\nThe size of the tree is: " << ct.GetSize() << endl;
	ct.DisplayContact("Ariel");
	return 0;
}

