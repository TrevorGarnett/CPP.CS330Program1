#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>        // std::abs

class character {
private:
	int charID;
	double posX;
	double posZ;
	double velX;
	double velZ;
	double linX;
	double linZ;
	double maxSpd;
	double maxAcc;
	double orien;
	int behavior;
	double time = .5;

	double targetX;
	double targetZ;

	//void steering() {
	//	if (behavior == 1) {
	//		return; //Stop function
	//	}
	//	if (behavior == 2) {
	//		//movement.reserved();
	//		return;
	//	}
	//	if (behavior == 3) {
	//		//Seek();
	//		return;
	//	}
	//	if (behavior == 4) {
	//		//Flee();
	//		return;
	//	}
	//	if (behavior == 5) {
	//		//Arrive();
	//		return;
	//	}
	//}
public:
	character(int charID, double posX, double posZ, double velX, double velZ, double linX, double linZ, double maxSpd, double maxAcc, double orien, int behavior, double targetX, double targetZ) {
		this->charID= charID;
		this->posX = posX;
		this->posZ = posZ;
		this->velX = velX;
		this->velZ = velZ;
		this->linX = linX;
		this->linZ = linZ;
		this->maxSpd = maxSpd;
		this->maxAcc = maxAcc;
		this->orien = orien;
		this->behavior = behavior;
		this->targetX = targetX;
		this->targetZ = targetZ;
	}
	std::string getInfo() {
		std::string temp = std::to_string(charID) + "," + std::to_string(posX) + "," + std::to_string(posZ) + "," + std::to_string(velX) + "," + std::to_string(velZ) + "," + std::to_string(linX) + "," + std::to_string(linZ) + "," + std::to_string(orien) + "," + std::to_string(behavior);
		return temp;
	}
	void update() {
		//updates position
		posX += velX * time;
		posZ += velZ * time;
		if (behavior == 1) {
			return; //Stop function
		}
		if (behavior == 2) {
			//reserved();
		}
		if (behavior == 3) {
			velX += linX * time;
			velZ += linZ * time;
			//checks if speed greater than max velocity and sets to max 
			if (length(velX, velZ) > maxSpd) {
				velX = velX / length(velX, velZ)* maxSpd;
				velZ = velZ / length(velX, velZ)* maxSpd;
			}
			Seek();
		}
		if (behavior == 4) {
			velX += linX * time;
			velZ += linZ * time;
			//checks if speed greater than max velocity and sets to max 
			if (length(velX, velZ) > maxSpd) {
				velX = velX / length(velX, velZ)* maxSpd;
				velZ = velZ / length(velX, velZ)* maxSpd;
			}
			Flee();
		}
		if (behavior == 5) {
			velX += linX * time;
			velZ += linZ * time;
			Arrive();
		}



		return;
	}
	void Seek() {
		// Setting the acceleration vector to 0
		linX = 0;
		linZ = 0;
		// Finding the desired vector to accelerate towards
		double deltaX = targetX - posX;
		double deltaZ = targetZ - posZ;
		double size = length(deltaX, deltaZ);
		double unitX = deltaX / size;
		double unitZ = deltaZ / size;
		linX = unitX * maxAcc;
		linZ = unitZ * maxAcc;
		orien = tan(unitX / unitZ);
	}

	void Flee() {
		// Setting the acceleration vector to 0
		linX = 0;
		linZ = 0;
		// Creating a vector, which acts as the target
		double deltaX = posX - targetX;
		double deltaZ = posZ - targetZ;
		double size = length(deltaX, deltaZ);
		double unitX = deltaX / size;
		double unitZ = deltaZ / size;
		linX = unitX * maxAcc;
		linZ = unitZ * maxAcc;
		orien = tan(unitX / unitZ);
	}
	
	void Arrive() {
		// Setting the acceleration vector to 0
		linX = 0;
		linZ = 0;
		// Calculating new vector to target
		double deltaX = targetX - posX;
		double deltaZ = targetZ - posZ;
		double size = length(deltaX, deltaZ);
		
		double slowZone = 80;
		double arriveZone = 1;


		double unitX = deltaX / size;
		double unitZ = deltaZ / size;
        linX = unitX * maxAcc;
		linZ = unitZ * maxAcc;
		if(size < arriveZone) {
			velX = 0;
			velZ = 0;
		}
		else if (size > slowZone) {
			velX += unitX * linX;
			velZ += unitZ * linZ;

			//checks if speed greater than max velocity and sets to max 
			if (length(velX, velZ) > maxSpd) {
				velX = velX / length(velX, velZ)* maxSpd;
				velZ = velZ / length(velX, velZ)* maxSpd;
			}
		}
		else {
			//THE BELLOW CODE IS SUCCESFUL
			double idealVX = unitX * maxSpd * size / slowZone;
			double idealVZ = unitZ * maxSpd * size / slowZone;
			double neededXAcc = (idealVX - velX) * 2;
			double neededZAcc = (idealVZ - velZ) * 2;
			double neededAcc = length(neededXAcc, neededZAcc);
			if(neededAcc > maxAcc){
				neededXAcc = neededXAcc / neededAcc * maxAcc;
				neededZAcc = neededZAcc / neededAcc * maxAcc;
			}
			linX = neededXAcc;
			linZ = neededZAcc;
		}
		orien = tan(unitX / unitZ);
	}




	//void updateVars(double posX, double posZ, double velX, double velZ, double linX, double linZ, double orien) {
	//	this->posX = posX;
	//	this->posZ = posZ;
	//	this->velX = velX;
	//	this->velZ = velZ;
	//	this->linX= linX;
	//	this->linZ = linZ;
	//	this->orien = orien;
	//}
	
	double length(double x, double y) {
		return sqrt(x*x + y*y);
	}
			

};

