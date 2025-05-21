#include <iostream>
#include "drag.hpp"
using namespace std;

void start_game(vector<CAR>& cars){
	
     int distance = 402;
	 int trackLength = 40; //fictional distance. builded with '='
	 auto [car1, car2] = select_car(cars);
	 float x = compute_effective_acceleration(car1);
	 float y = compute_effective_acceleration(car2);
	
	 float tfad_car1 = sqrt (2*distance / x); // time for whole distance -> car1
	 float tfad_car2 = sqrt (2*distance / y); // time for whole distance -> car2
	
	
	
	
	 for (int i = 3; i >= 1; --i) {
        
			system("cls");
		
			cout << "Race starts in: " << i << "sec" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
	
    
        system("cls");
    
	
		cout << "GO!\n";
		this_thread::sleep_for(chrono::seconds(1));
	
	
		int progress1, progress2;
		progress1 = 0; progress2 =0;
		float elapsed = 0;
		float time_step = 0.05f;
	
		while (progress1 < trackLength || progress2 < trackLength){
		
		 if (elapsed >= ((tfad_car1 / trackLength) * progress1)) progress1++;
		 if (elapsed >= ((tfad_car2 / trackLength) * progress2)) progress2++;
		
		
			system("cls");
		
	     cout << "      ========================================\n";

		 for (int j = 0; j < trackLength; ++j) {
			  if (j == static_cast<int>(progress1)) cout << "-*-";
			  else cout << " ";
		    }
		  cout << '\n';
		
		
		  cout << "      ----------------------------------------\n";
		

		 for (int j = 0; j < trackLength; ++j) {
			  if (j == static_cast<int>(progress2)) cout << "-*-";
			  else cout << " ";
		    }
		 cout << '\n';

		 cout << "      ========================================\n";
		
		 this_thread::sleep_for(chrono::milliseconds(int(time_step * 1000)));
		
		 elapsed+=time_step;
	    }
	
	  system ("cls");
	
	  if (progress1 > progress2){
		  cout << car1.name << " WINS!";
		  log_result(car1.name);
	    }
	
	 else if(progress2 > progress1) {
		  cout << car2.name << " WINS!";
		  log_result(car2.name);
	    }
	
	 else {
		  cout << "DRAW";
		  log_result("DRAW");
	    }
	}

float compute_effective_acceleration(const CAR& car) {
     float acceleration_m = car.acceleration_km_h * 1000;
	 float base_speed = acceleration_m / 3600;  // km/h -> m/s
	 
     float a_from_acc = base_speed / car.acceleration_second;

     // Power / Weight 
     float power_weight_ratio = static_cast<float>(car.horsePower) / car.weight;

     // Normalized torque factor
     float torque_factor = static_cast<float>(car.torque) / 500.0f; // örnek skalalama

     // Common acceleration + factor
     float effective_a = a_from_acc * (1 + power_weight_ratio + torque_factor);

     return effective_a;
    }

void insert_cars(vector<CAR>& cars){
	 CAR newCar;
	
	 cin.ignore();
	
	 newCar.name = get_valid_input("Enter name of the car: ");
	 newCar.torque = getIntInput("Enter torque: ");
	 newCar.maxSpeed = getIntInput("Enter Max speed: ");
	 newCar.acceleration_km_h = getFloatInput("Enter acceleration (km/h): ");
	 newCar.acceleration_second = getFloatInput("Enter acceleration (sec): ");
	 newCar.weight = getIntInput("Enter weight: ");
	 newCar.horsePower = getIntInput("Enter horse power: ");

	 cars.push_back(newCar);
	 save_cars(cars, "cars.txt");
    }



void load_cars(vector<CAR>& cars, const string& filename) {
		ifstream dosya(filename);
			if (!dosya.is_open()) {
				cout << "Dosya acilamadi.\n";
				return;
			}

     string satir;
     while (getline(dosya, satir)) {
         if (satir.empty()) continue;

         CAR car;
         stringstream ss(satir);
         string parca;

         getline(ss, car.name, '#');
         getline(ss, parca, '#'); car.torque = stoi(parca);
         getline(ss, parca, '#'); car.maxSpeed = stoi(parca);
         getline(ss, parca, '#'); car.acceleration_km_h = stof(parca);
		 getline(ss, parca, '#'); car.acceleration_second = stof(parca);
         getline(ss, parca, '#'); car.weight = stoi(parca);
         getline(ss, parca, '#'); car.horsePower = stoi(parca);

         cars.push_back(car);
        }

     dosya.close();
    }

void save_cars(vector<CAR>& cars, const string& filename) {
		ofstream dosya(filename);
		if (!dosya.is_open()) {
			cout << "File not opened. ";
			
			return;
		}
     for (const auto& car : cars) {
            dosya << car.name << '#'
              << car.torque << '#' << car.maxSpeed << '#'
              << car.acceleration_km_h << '#' << car.acceleration_second << '#' << car.weight << '#'
              << car.horsePower << '\n';
        }
	
	 dosya.close();
    }

void remove_cars(vector<CAR>& cars){
	 string silinecekIsim;
		cin.ignore();
		cout << "Enter the name of car: ";
		getline(cin, silinecekIsim);
		

	 auto it = find_if(cars.begin(), cars.end(),
     [&silinecekIsim](const CAR& car) {
		 
         return car.name == silinecekIsim;
		});

	 if (it != cars.end()) {
		 cars.erase(it);
		 cout << "Car has been removed.\n";
	    } 	
	 else {
		 cout << "Car not found.\n";
	    }
	
	 save_cars(cars, "cars.txt");
	}

void MenuList(){
	 cout <<"1. Play"<<'\n';
	 cout <<"2. Garage" << '\n';
	 cout <<"3. List result of the latest race" << '\n';
	 cout <<"4. Insert car" << '\n';
	 cout <<"5. Remove car" << '\n';
	 cout <<"6. Quit" << '\n';
	 cout <<"> ";
    }

void list_cars(const vector<CAR>& cars){
	
	 if(cars.empty()){
				
		 cout <<"There's no car in garage." << '\n';
				
		 return;
	    } 
	
	 for (auto i=0u; i < cars.size(); i++){
			
			cout << cars[i].name << '\n';
			
	    }
    }


pair<CAR, CAR> select_car(const vector<CAR>& cars){
	
	 string name1,name2;
	
	 cin.ignore();
	 
	 while (true){
	 name1=get_valid_input("Select first one (enter the name): ");
		
	 auto thisOne = find_if(cars.begin(), cars.end(), [&name1](const CAR& car) {
		 return car.name == name1;
	    });
	
	
	 name2=get_valid_input("Select another one (enter the name): ");
	
	 auto anotherOne = find_if(cars.begin(), cars.end(), [&name2](const CAR& car){
		 return car.name == name2;
	    });
	
	  if (thisOne != cars.end() && anotherOne != cars.end()) {
         
		 return {*thisOne, *anotherOne};
        }
		
		cout << "One or both cars not found. Try again\n";
	
	}

void log_result(const string& winner){
	   ofstream dosya("logfile.txt", ios::app);
		if (!dosya.is_open()) {
			cout << "File not opened.\n";
			return;
		}
		
		if (winner == "DRAW") {
			dosya << "DRAW\n";
		}
	  dosya << winner << "WINS!" << '\n';
	
	 dosya.close();
    }

void list_latest_result(const string& filename){
	 ifstream dosya(filename);
	  if (!dosya.is_open()){
		 cout << "File not opened.\n";
		 return;
	    }
	
	 string satir;
     string son_satir;
	
	 while (getline(dosya, satir)) {
         son_satir = satir;
	    }

      cout << son_satir << '\n';
	}

int getIntInput(const string& prompt){
	 string input;
     int value;
     while (true) {
         cout << prompt;
         getline(cin, input);
         stringstream ss(input);
         if (ss >> value && ss.eof() && !prompt.empty()) break;
         cout << "Invalid input. Please enter a valid integer.\n";
        }
     return value;
    }

float getFloatInput(const string& prompt){
		string input;
		float value;
	 while (true) {
         cout << prompt;
         getline(cin, input);
         stringstream ss(input);
         if (ss >> value && ss.eof() && !prompt.empty()) break;
         cout << "Invalid input. Please enter a valid number.\n";
        }
    
	  return value;
	}

string get_valid_input(const string& prompt) {
     string input;
     while (true) {
         cout << prompt;
         getline(cin, input);
         if (!input.empty()) break;
         cout << "Input cannot be empty! Try again.\n";
        }
     return input;
	}