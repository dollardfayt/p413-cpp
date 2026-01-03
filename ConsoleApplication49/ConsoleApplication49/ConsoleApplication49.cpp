#include <iostream>
#include <string>

using namespace std;

void prettyPrintYarina(const string& name = "Марина купи энергос позязя") {
	string frame(name.length() + 6, '*');

	cout << frame << endl;
	cout << "*  " << name << "  *" << endl;
	cout << frame << endl;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	prettyPrintYarina();

	return 0;
}
