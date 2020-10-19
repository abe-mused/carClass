#include <iostream>
#include <conio.h>
#include <iomanip> 
#include <ctime>
#include <cmath>

using namespace std;

const int UP = 72;
const int ONE = 49;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;

class Car{
	
	private:
		int year;
		string make, model;
		float speed, gasLevel;
		bool status;
		time_t beginingTime;
	public:
		
		Car(int year, string make, string model){
			this->year = year;
			this->make = make;
			this->model = model;
			this->speed = 0;
			this->gasLevel = 10;
			this->status = false;
		}
		
		float getSpeed(){return speed;}
		float getGasLevel(){return this->gasLevel;}
		bool getStatus(){return status;}
		time_t getBeginingTime(){return beginingTime;}
		
		void decreaseGas(double amount){
			if((this->gasLevel - amount) >= 0 && (this->gasLevel - amount) <= 22){
			this->gasLevel -= amount;
			}else if (isEqual(this->gasLevel - amount, 0)){
				this->gasLevel = 0;}
		}
		
		void accelerate(){
			if(this->gasLevel >= 0.5 && this->speed <=185){ // 190 is the top speed for the Audi RS7
			gasLevel -= 0.5; this->speed += 5;}
		}	
		void brake(){
			if(this->speed >= 5 && this->gasLevel >= 0.2){
			speed -= 5; gasLevel -= 0.2;}
		}
		void fillUp(){
			float amount;
			cout<<"\nenter the number of gallon you want to fill into the gas tank: "<<endl;
			cout<<"note: the number can't be more than "<< 22 - gasLevel<<endl;
			cin>>amount;
			
			if((amount + this->gasLevel) <= 22 && (amount + this->gasLevel) >= 0){
			this->gasLevel += amount;
			resetTimer();}
		}
		void startCar(){status = true; beginingTime = time(NULL);}
		
		void resetTimer(){beginingTime = time(NULL);}
		
		void shutOff(){status = false;
		speed = 0;}
		
		void displayData(){
			cout<<setprecision(2)<<fixed;
			system("cls");
			cout<<"year: "<<this->year<<endl;
			cout<<"make: "<<this->make<<endl;
			cout<<"model: "<<this->model<<endl<<endl;
			cout<<"current speed: "<<this->speed<<endl;
			cout<<"current gas level: "<<this->gasLevel<<endl;
			cout<<"engine status: ";
			(status)? cout<<"on"<<endl : cout<<"off"<<endl;
			if(status){
			cout<<"\n\n\tup arrrow = accelerate"<<endl;
			cout<<"\tdown arrrow = brake"<<endl;
			cout<<"\tright arrrow = fill up gas"<<endl;
			cout<<"\tleft arrrow = shut the car off"<<endl;
			} else{
			cout<<"press 1 to start the car or the right arrow to fill up gas: "<<endl;
			}
		}
		bool isEqual(double x, double y){
			if(abs (x - y) < 0.001) 
			return true;
			return false; 
		}
		
}; // end of car.


int main(void){
	Car abesCar(2020, "Audi", "RS7");
	int c, seconds;
	double numberOfGallons;
	while(1){
		
		abesCar.displayData();
		
		c=getch();
		if(abesCar.getStatus()){
			
			if(abesCar.isEqual(abesCar.getGasLevel(), 0.00)){
			abesCar.shutOff();
			}
			
			switch(c){
				case UP:
					abesCar.accelerate();
					abesCar.displayData();
					break;
				case DOWN:
					abesCar.brake();
					abesCar.displayData();
					break;
				case RIGHT:
					abesCar.fillUp();
					abesCar.displayData();
					break;
				case LEFT:
					abesCar.shutOff();
					abesCar.displayData();
					break;
				case 224:
					break;
				default:
					cout<<"invalid key"<<endl;
			}
		}else {
			if(c == ONE && !abesCar.isEqual(abesCar.getGasLevel(), 0)) {
				abesCar.startCar();
			} else if(c== RIGHT){
					abesCar.fillUp();
					abesCar.displayData();
			}
		}
		
		if(abesCar.getStatus()){
			seconds = int (difftime(time(NULL),abesCar.getBeginingTime()));
			abesCar.decreaseGas(seconds*0.05);
			abesCar.resetTimer();
		}
	}
}
