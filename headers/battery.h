#ifndef FULLBATTERYALERT_HEADER_BATTERY
#define FULLBATTERYALERT_HEADER_BATTERY

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>

int battery_low = 16;
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
	MessageBox(NULL, "Your battery is low. Please plug in your charger.", "Battery Status Update", MB_SYSTEMMODAL);
	while (true) {
		int battery = batteryLevel();
		if (battery > battery_low) {
			return;
		}
		std::this_thread::sleep_for(std::chrono::seconds(check_interval));
	}
}

inline void fullBattery() {
	MessageBox(NULL, "Your battery has charged fully. Please plug out your charger.", "Battery Status Update", MB_SYSTEMMODAL);
}

void displayDialogueBox() {
	while (true) {
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
