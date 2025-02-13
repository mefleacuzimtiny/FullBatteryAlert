#ifndef FULLBATTERYALERT_HEADER_BATTERY
#define FULLBATTERYALERT_HEADER_BATTERY

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>

int batteryLevel() {
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

void displayDialogueBox() {
	while (true) {
		int battery = batteryLevel();
		if (battery <= 10) {
			MessageBox(NULL, "Your battery is low. Please plug in your charger.", "Battery Status Update", MB_OK);
		}else if (battery >= 98) {
			MessageBox(NULL, "Your battery has charged fully. Please plug out your charger.", "Battery Status Update", MB_OK);
		}
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

#endif
