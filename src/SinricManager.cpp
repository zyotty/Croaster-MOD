#if defined(ESP8266)

#include "SinricManager.h"
#include "Constants.h"

SinricManager::SinricManager(CroasterCore &croaster)
    : croaster(&croaster)
{
}

void SinricManager::begin()
{
    SinricProTemperaturesensor &tempSensor = SinricPro[SINRIC_DEVICE_ID];

    SinricPro.begin(SINRIC_APP_KEY, SINRIC_APP_SECRET);

    debugln(F("# SinricPro initialized"));
}

void SinricManager::loop()
{
    SinricPro.handle();

    unsigned long now = millis();

    if (now - lastSend < sendInterval)
        return;

    lastSend = now;

    double ambientTemp = croaster->tempEt;

    if (isnan(ambientTemp))
        return;

    SinricProTemperaturesensor &tempSensor = SinricPro[SINRIC_DEVICE_ID];
    tempSensor.sendTemperatureEvent(ambientTemp);

    debugln("# Sinric: sent ambient temp " + String(ambientTemp, 1));
}

#endif // ESP8266
