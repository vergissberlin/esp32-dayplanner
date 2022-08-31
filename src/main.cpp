#include <Arduino.h>

/*
@TODO:
- Aktualisieren der Anzeige (DeepSleep) von der Zeit des nächsten Termin (Zeitpunkt des nächsten Termin - aktuelle Zeit) abhängig machen
- Appointments API Anfrage nur einmalig machen (Inklusive WiFi Verbindung))
*/

#include "config.h"
#include "fetch.h"
#include "deepSleep.h"
#include "network.h"
#include "visualize.h"

bool isTimeInSync = false;
bool isInitialStart = true;
String appointmentJSON;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        continue;
    Serial.println();

    // Logo
    Serial.println("__________.__");
    Serial.println("\\______   \\  | _____    ____   ____   ___________ ");
    Serial.println("|     ___/  | \\__  \\  /    \\ /    \\_/ __ \\_  __ \\\\");
    Serial.println("|    |   |  |__/ __ \\|   |  \\   |  \\  ___/|  | \\/");
    Serial.println("|____|   |____(____  /___|  /___|  /\\___  >__|");
    Serial.println("                    \\/     \\/     \\/     \\/");

    if (isInitialStart)
    {
        delay(1000);
        appointmentJSON = setupNetwork();
        setupFetch();
    }
    else
    {
        delay(500);
    }
    setupVisualize(appointmentJSON);
    setupDeepSleep(isTimeInSync);
}

void loop()
{
}
