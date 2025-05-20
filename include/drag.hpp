#ifndef DRAG_HPP
#define DRAG_HPP

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <sstream>
#include <math.h>

using namespace std;

struct CAR {
	string name;
	int torque;
	int maxSpeed;
	float acceleration_km_h;
	float acceleration_second;
	int weight;
	int horsePower;
	

};
	void start_game(vector<CAR>& cars);
	void insert_cars(vector<CAR>& cars); //
	void remove_cars(vector <CAR>& cars); //
	void list_latest_result(const string& filename);//
	void list_cars(const vector<CAR>& cars); //
	void MenuList(); //
	pair<CAR, CAR> select_car(const vector<CAR>& cars); //
	void save_cars(vector <CAR>& cars, const string& filename);
	void load_cars(vector<CAR>& cars, const string& filename);//
	float compute_effective_acceleration(const CAR& car);//
	void log_result(const string& winner);//
	int getIntInput(const string& prompt);
	float getFloatInput(const string& prompt);
	string get_valid_input(const string& prompt);


#endif
