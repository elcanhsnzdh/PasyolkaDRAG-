#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sstream>
#include <math.h>


#include "drag.hpp"
using namespace std;


int main(){
	
	vector<CAR> cars;
	load_cars(cars, "cars.txt");
	
	
	
	int input;
	
	
	do{
		system("cls");
		MenuList();
		cin >> input;
		
		switch(input){
		
		case 1:
			start_game(cars);
			system("pause");
			break;
		case 2:
			list_cars(cars);
			system("pause");
			break;
		case 3:
			list_latest_result("logfile.txt");
			system("pause");
			break;
		case 4:
			insert_cars(cars);
			system("pause");
			break;
		case 5:
			remove_cars(cars);
			system("pause");
			break;
		case 6:
			cout <<"Quitting..";
			return 0;
		default:
			cout << "Invalid choice! ";
			
		}
		
	}while(input!=6);
}