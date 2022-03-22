#include <assert.h>
#include <iostream>

using namespace std;

#define LOWER_TEMPERATURE_LIMIT 0
#define UPPER_TEMPERATURE_LIMIT 45
#define LOWER_SOC_LIMIT 20
#define UPPER_SOC_LIMIT 80
#define LOWER_CHARGE_RATE 0.0
#define UPPER_CHARGE_RATE 0.8

std::string TempWarning = "Temperature out of range!";
std::string SocWarning = "State of Charge out of range!";
std::string RateofChargeWarning = "Charge Rate out of range!";

bool CheckTempRange(float temperature) {
   bool TemperatureFlag = (temperature < LOWER_TEMPERATURE_LIMIT || temperature > UPPER_TEMPERATURE_LIMIT)? false: true;
   return TemperatureFlag;
}

bool CheckSOCRange(float soc) {
   bool SOCFlag = (soc < LOWER_SOC_LIMIT || soc > UPPER_SOC_LIMIT)? false: true;
   return SOCFlag;
}

bool CheckChargeRate(float chargeRate) {
   bool ChargeFlag = (chargeRate < LOWER_CHARGE_RATE || chargeRate > UPPER_CHARGE_RATE)? false: true;
   return ChargeFlag;
}

void PrintOnConsole(std::string warning) {
    cout << warning << "\n";
}

bool BatteryValuesisOK(float value, bool (*Validation)(float), std::string Warning) {

   bool Status = Validation(value);
   if(!Status) 
   {
   PrintOnConsole(Warning);
   }
   return Status;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {

   bool BattTemp   =  BatteryValuesisOK(temperature, CheckTempRange, TempWarning);
   bool BattSOC    =  BatteryValuesisOK(soc, CheckSOCRange, SocWarning);
   bool BattCharge =  BatteryValuesisOK(chargeRate, CheckChargeRate, RateofChargeWarning);
   bool IsBattOK   =  BattTemp && BattSOC && BattCharge;
  return IsBattOK;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
  assert(batteryIsOk(25, 70, 0.9) == false);
}
