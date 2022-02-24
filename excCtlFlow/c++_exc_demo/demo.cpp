#include <iostream>

using namespace std;

void fn4()
{
	const char*	err_msg_4{"error message 4"};

	cout << "fn4:  throwing \"" << err_msg_4 << "\"" << endl;
	throw err_msg_4;
}

void fn3()
{
	fn4();
}

void fn2()
{
	try {
		fn3();
		}
	catch (const char* err_msg) {
		const char*	err_msg_2{"error message 2"};
		cout << "fn2:  caught   \"" << err_msg << "\"" << endl;
		cout << "fn2:  throwing \"" << err_msg_2 << "\"" << endl;
		throw err_msg_2;
		}
}

void fn1()
{
	fn2();
}

int main()
{
	try {
		fn1();
		}
	catch (const char* err_msg) {
		cout << "main: caught   \"" << err_msg << "\"" << endl;
		}
	
	return 0;
}
