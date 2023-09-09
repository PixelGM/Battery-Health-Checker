#include <iostream>
#include <windows.h>
#include <powrprof.h>

// Function to get the current battery percentage
int getBatteryPercentage() {
    SYSTEM_POWER_STATUS sps;
    GetSystemPowerStatus(&sps);
    return sps.BatteryLifePercent;
}

// Function to calculate mAh lost per minute
double calculateMahLostPerMinute(int initialPercentage, int currentPercentage, int batteryCapacity) {
    return (initialPercentage - currentPercentage) * batteryCapacity / 100.0;
}

// Function to predict projected battery loss
double predictBatteryLoss(int currentPercentage, double mahLostPerMinute) {
    return currentPercentage * mahLostPerMinute;
}

// Function to determine battery health
double determineBatteryHealth(double mahLostPerMinute, int factoryStandard) {
    return (mahLostPerMinute / factoryStandard) * 100;
}

int main() {
    const int factoryStandard = 5000; // Assuming 5000mAh as the factory standard for a new laptop
    int initialPercentage = getBatteryPercentage();
    Sleep(60000); // Wait for 1 minute
    int currentPercentage = getBatteryPercentage();

    double mahLostPerMinute = calculateMahLostPerMinute(initialPercentage, currentPercentage, factoryStandard);
    double projectedLoss = predictBatteryLoss(currentPercentage, mahLostPerMinute);
    double batteryHealth = determineBatteryHealth(mahLostPerMinute, factoryStandard);

    std::cout << "mAh lost per minute: " << mahLostPerMinute << std::endl;
    std::cout << "Projected battery loss: " << projectedLoss << std::endl;
    std::cout << "Battery health: " << batteryHealth << "%" << std::endl;

    return 0;
}
