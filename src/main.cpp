/**
 * The code sends a message to a phone number using the CallMeBot API.
 * The message is sent using the WhatsApp service.
 * 
 * Author:  @RikuNav
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <UrlEncode.h>

// WiFi credentials
const char* ssid = "XXXXXXXXX"; // The SSID of the internet
const char* password = "XXXXXX"; // The password of internet

// Number Strings
String phoneNumber = "XXXXXXXXXXX"; // The phone number displayed by the API
String apiKey = "XXXXXXX"; // The API key (DO NOT SHARE IT!!!!)

// Function prototypes
void connectToWiFi();
void sendMessage(String);

void setup() {
  connectToWiFi();
  sendMessage("Hello from ESP8266!");
}

void loop() {
}

void connectToWiFi() {
  /**
   * Connects to the WiFi network
  */
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


void sendMessage(String message) {
  /**
   * Sends a message to the phone number using the CallMeBot API
   * 
   * @param message The message to send
  */
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