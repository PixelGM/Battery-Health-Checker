#include <iostream>
#include <windows.h>
#include <powrprof.h>

// Function to get the current battery percentage
int getBatteryPercentage() {
    SYSTEM_POWER_STATUS sps;
    GetSystemPowerStatus(&sps);
    return sps.BatteryLifePercent;
}

// Function to calculate Wh lost per minute
double calculateWhLostPerMinute(int initialPercentage, int currentPercentage, int batteryCapacityWh) {
    return (initialPercentage - currentPercentage) * batteryCapacityWh / 100.0;
}

// Function to predict projected battery loss
double predictBatteryLoss(int currentPercentage, double whLostPerMinute) {
    return currentPercentage * whLostPerMinute;
}

// Function to determine battery health
double determineBatteryHealth(double whLostPerMinute, int factoryStandardWh) {
    return (whLostPerMinute / factoryStandardWh) * 100;
}

int main() {
    const int factoryStandardWh = 50; // Assuming 50Wh as the factory standard for a new laptop
    int initialPercentage = getBatteryPercentage();
    Sleep(60000); // Wait for 1 minute
    int currentPercentage = getBatteryPercentage();

    double whLostPerMinute = calculateWhLostPerMinute(initialPercentage, currentPercentage, factoryStandardWh);
    double projectedLoss = predictBatteryLoss(currentPercentage, whLostPerMinute);
    double batteryHealth = determineBatteryHealth(whLostPerMinute, factoryStandardWh);

    std::cout << "Wh lost per minute: " << whLostPerMinute << std::endl;
    std::cout << "Projected battery loss: " << projectedLoss << std::endl;
    std::cout << "Battery health: " << batteryHealth << "%" << std::endl;

    return 0;
}
