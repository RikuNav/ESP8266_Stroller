#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <UrlEncode.h>

const char* ssid = "XXXXXXXXXXX";
const char* password = "XXXXXX";

// Number Strings
String phoneNumber = "XXXXXXXXXXXXX";
String apiKey = "XXXXXX";

void connectToWiFi() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  digitalWrite(LED_BUILTIN, HIGH);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (LOW is the voltage level)
}

void sendMessage(String);

void setup() {
  connectToWiFi();
  sendMessage("Hello from ESP8266!");
}

void loop() {
}

void sendMessage(String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&text=" + urlEncode(message) + "&apikey=" + apiKey;

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.begin(client, url);

  //http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.println("Message sent successfully");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
    Serial.print("URL: ");
    Serial.println(url);
  }

  http.end();
}
