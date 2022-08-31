#include <WiFi.h>
#include <HTTPClient.h>

void setupDeepSleep(bool isTimeInSync)
{
    Serial.println("✅  Setup: DeepSleep");

    int minutesToSleep = 10;

    // Check is Wifi is connected
    if (WiFi.status() == WL_CONNECTED)
    {
        // Check if time is in sync
        if (isTimeInSync == false)
        {
            Serial.println("🤖  Set minutes to sleep initialised.");
            // HTTP get request
            HTTPClient http;
            http.begin(API_URL_MINUTESTOSLEEP);
            int httpCode = http.GET();
            if (httpCode == 200)
            {
                if (http.getString().toInt() != 10)
                {
                    minutesToSleep = http.getString().toInt();
                    Serial.println("🤖  Set minutes to sleep to " + http.getString());
                }
                else
                {
                    Serial.println("🤖  Luckely its the correct time. Minutes shift: " + http.getString());
                }
                http.end();
                isTimeInSync = true;
            }
            else
            {
                Serial.printf("\n❌  [HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
        }
        else
        {
            Serial.println("🤖  Time is allready in sync");
        }
    }
    else
    {
        Serial.println(F("❌  WiFi is not connected. Cannot set minutes to sleep."));
    }

    // Deep sleep
    Serial.println("🤖  Going to deep sleep for " + String(minutesToSleep) + " minutes.");
    esp_sleep_enable_timer_wakeup(minutesToSleep * 60 * 1000000);
    esp_deep_sleep_start();
}
