// #include <iomanip>


#include "../headers/consoleInterface/ConsoleInterface.hpp"
#include "../headers/Duel.hpp"
#include "../headers/enums/Color.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {


    Duel duel = Duel();
    ConsoleInterface interface = ConsoleInterface();
    duel.addInterface(&interface);



	Color f = Blue;

	if (f == Blue){
		cout << "hello Gael et Simo" << endl;
	}



	return 0;
}

