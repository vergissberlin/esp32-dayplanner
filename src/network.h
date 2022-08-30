#include <WiFi.h>
#include <HTTPClient.h>

#include "config.h"

String setupNetwork()
{
    String payload = "";
    Serial.println("Setup: Network");

    WiFi.begin(WIFI_SSID_2, WIFI_PASSWORD_2);
    Serial.print(F("Connecting to WiFi ..."));

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(F("."));
    }

    Serial.println(F("Connected to WiFi network"));

    if ((WiFi.status() == WL_CONNECTED))
    { // Check the current connection status

        HTTPClient http;

        http.begin("https://iot.andrelademann.de/planner");
        int httpCode = http.GET(); // Make the request

        if (httpCode > 0)
        { // Check for the returning code
            payload = http.getString();
            Serial.println(httpCode);
            Serial.println(payload);
        }
        else
        {
            Serial.println("Error on HTTP request");
            payload = "Error on HTTP request";
        }

        http.end(); // Free the resources
        return payload;
    }
}
