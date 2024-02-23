#pragma once
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <functional>
#include <iomanip>

class VaccinationData {
private:
	string UserName; // User name
	int age;		 // User age
	string VaccineName; // Vaccine name
	string LocationName; // Location name
	int times; // The number of vaccination

public:
	VaccinationData() {//Constuctor (first setting)
		LocationName = "";
		UserName = "";
		times = 0;
	}
	~VaccinationData() {//destructor

	}
	//--NODE information in--
	void SetUserName(string in_name) { UserName = in_name; }//set user name
	void SetVaccineName(string in_name) { VaccineName = in_name; }//set vaccine name
	void SetLocationName(string in_location) { LocationName = in_location; }//set location name
	void SetTimes(int in_times) { times = in_times; }//set times(got a shot)
	void SetAge(int in_age) { age = in_age; }//set age
	void SetTimesInc() { times++; }//set times + 1

	string GetUserName() { return UserName; }//return username
	string GetVaccineName() { return VaccineName; }//return vaccine name
	string GetLocationName() { return LocationName; }//return location name
	int GetTimes() { return times; }//return times got a shot
	int GetAge() { return age; }//return age
};