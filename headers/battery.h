#ifndef FULLBATTERYALERT_HEADER_BATTERY
#define FULLBATTERYALERT_HEADER_BATTERY

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>

int battery_low = 15;
int battery_full = 98;
int check_interval = 3;

inline int batteryLevel() {
	SYSTEM_POWER_STATUS status;
	int toReturn;
	if (GetSystemPowerStatus(&status)) {
		toReturn = status.BatteryLifePercent;
	} else {
		std::cerr << "Unable to retrieve battery status." << std::endl;
		return -1;
	}
	return toReturn;
}

inline bool isCharging() {
	SYSTEM_POWER_STATUS status;
	bool toReturn;
	if (GetSystemPowerStatus(&status)) {
		toReturn = status.ACLineStatus == AC_LINE_ONLINE;
	} else {
		std::cerr << "Unable to retrieve battery status." << std::endl;
		return false;
	}
	return toReturn;
}

void lowBattery() {
	// prints message, empty (sub)loop runs while battery is low. Sub-loop exits to main-loop when battery not low
	MessageBox(NULL, "Your battery is low. Please plug in your charger.", "Battery Status Update", MB_SYSTEMMODAL);
	while (batteryLevel() <= battery_low) {		// idle sub-loop: this sub-loop locks the program in this while block until battery is not low to prevent it from repeating the message box every 3 seconds
		std::this_thread::sleep_for(std::chrono::seconds(check_interval));
	}
}

inline void fullBattery() {
	MessageBox(NULL, "Your battery has charged fully. Please plug out your charger.", "Battery Status Update", MB_SYSTEMMODAL);
}

void displayDialogueBox() {
	while (true) {			// main-loop
		int battery = batteryLevel();
		bool charging = isCharging();
		
		if (battery <= battery_low and not charging) {
			lowBattery();
		} else if (battery >= battery_full and charging) {
			fullBattery();
		}
		std::this_thread::sleep_for(std::chrono::seconds(check_interval));
	}
}

#endif
