#pragma once

#if defined(ESP8266)

#include <Arduino.h>
#include <SinricPro.h>
#include <SinricProTemperaturesensor.h>
#include "CroasterCore.h"

#define SINRIC_APP_KEY    "5d8ef972-0170-4f0e-a401-166d88060d9f"
#define SINRIC_APP_SECRET "bf491935-faea-4d08-a6e2-0de3764fb0b3-e2cbd5bd-124f-4d6d-862d-066e3c75505f"
#define SINRIC_DEVICE_ID  "699707f0c2dbd7108b295dee"

/**
 * @class SinricManager
 * @brief Sends ET (Ambient) temperature to Sinric Pro / Google Home.
 */
class SinricManager
{
private:
    CroasterCore *croaster;
    unsigned long lastSend = 0;
    const unsigned long sendInterval = 10000; // Send every 10 seconds

public:
    /**
     * @brief Constructs a SinricManager instance.
     * @param croaster Reference to the CroasterCore instance.
     */
    SinricManager(CroasterCore &croaster);

    /**
     * @brief Initializes Sinric Pro connection.
     */
    void begin();

    /**
     * @brief Handles Sinric Pro updates in the main loop.
     */
    void loop();
};

#endif // ESP8266
