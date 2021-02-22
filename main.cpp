#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
#include "character.h"
#define pi 3.14159265358979323846
#define deltaTime .5

using namespace std;
enum behavior: int{ Stop =1, reserved, Seek, Flee, Arrive};
string format(float time, int charID, double posX, double posZ, double velX, double velZ, double linX, double linZ, double orien, int behavior);


int main() {
	//open a data file to write to
	ofstream data;
	data.open("/Users/trevorgarnett/Documents/CS 330/CS 330, Dynamic trajectory data.txt");

	cout << fixed;
	data << fixed;	

	//initialize the simulation
	float time = 0;
	float stopTime = 50;
	double stopSpeed = .01;
	double stopRotate = .01;
	character npc[] = { character(161,0,0,0,0,0,0,0,0,0,Stop,0,0),
						character(164,-50,-75,-6,4,0,0,8,2,pi,Arrive,0,0),
						character(163,50,-25,0,-8,0,0,8,2,pi*3/2,Seek,0,0),
						character(162,-25,50,0,-8,0,0,10,2, pi/4,Flee,0,0) };


	for (time; time <= stopTime; time += deltaTime) {
		
		//writes the data for each character once
		for (int y = 0; y < 4; y++) {
			data << to_string(time) + "," + npc[y].getInfo() << endl;
			npc[y].update();
		}

	}




	//data << format(0, 1, 2, 3, 4, 5, 6, 7, 8, Stop) << endl;
	//for (int i = 0; i < 1000; i++) {
	//	data << format(i*.5, 1, rand()%100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, Flee) << endl;
	//}

	data.close();
	system("pause");
}



string format(float time, int charID, double posX, double posZ, double velX, double velZ, double linX, double linZ, double orien, int behavior) {
	string temp = to_string(time) +","+ to_string(charID)+","+ to_string(posX)+","+ to_string(posZ)+","+ to_string(velX)+","+ to_string(velZ)+","+ to_string(linX)+","+ to_string(linZ)+","+ to_string(orien)+","+ to_string(behavior);
	return temp;
}


	

