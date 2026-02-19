#pragma once

#if defined(ESP8266)

#include <Arduino.h>
#include <SinricPro.h>
#include <SinricProTemperaturesensor.h>
#include "CroasterCore.h"
#include "Constants.h"

#define SINRIC_APP_KEY    "5d8ef972-0170-4f0e-a401-166d88060d9f"
#define SINRIC_APP_SECRET "bf491935-faea-4d08-a6e2-0de3764fb0b3-e2cbd5bd-124f-4d6d-862d-066e3c75505f"
#define SINRIC_DEVICE_ID  "699707f0c2dbd7108b295dee"

/**
 * @class SinricManager
 * @brief Sends ET (Ambient) temperature to Sinric Pro / Google Home.
 * Implemented as header-only to avoid duplicate symbol errors with
 * SinricPro's header-only library architecture.
 */
class SinricManager
{
private:
    CroasterCore *croaster;
    unsigned long lastSend = 0;
    const unsigned long sendInterval = 10000; // Send every 10 seconds

public:
    SinricManager(CroasterCore &croaster) : croaster(&croaster) {}

    void begin()
    {
        SinricProTemperaturesensor &tempSensor = SinricPro[SINRIC_DEVICE_ID];
        (void)tempSensor; // Register device with SinricPro
        SinricPro.begin(SINRIC_APP_KEY, SINRIC_APP_SECRET);
        debugln(F("# SinricPro initialized"));
    }

    void loop()
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
};

#endif // ESP8266
