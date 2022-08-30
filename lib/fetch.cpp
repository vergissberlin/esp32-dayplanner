
char *fetchAppointment()
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;

    if (!https.begin(client, "https://iot.andrelademann.de/dayplanner"))
    {
        Serial.printf("HTTPClient failure");

        display.setCursor(0, 0);
        display.print("HTTPClient failure");

        https.end();
        return "";
    }

    https.addHeader("Content-Type", "application/json");
    int code = https.GET();
    if (code != 200)
    {
        Serial.printf("HTTPClient failure: %s", https.errorToString(code).c_str());

        https.end();
        return "";
    }

    https.end();

    return "";
}
