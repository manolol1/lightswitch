#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Links for light control - Insert the links you got from the Alexa skill here!
const char* lightOnLink = "https://www.example,com";
const char* lightOffLink = "https://www.example.com";

// WiFi credentials - Insert your WiFi credentials here!
const char* wifiSsid = "ExampleSsid";
const char* wifiPassword = "ExamplePassword";

// Pins - If you use other Pins, you need to change them here!
const int onButton = 19;
const int offButton = 18;
const int led = 21;


void initWiFi(){
  digitalWrite(led, HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSsid, wifiPassword);
  Serial.print("\nConnecting to WiFi...");

  int timeoutCounter = 0;
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
    timeoutCounter++;

    if(timeoutCounter >= 500){
      Serial.println("WiFi connection failed. Restarting...");
      ESP.restart();
    }
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void lightOn(){
  // Send a http request to the URL that turns ON the lights (using the "URL Routine Trigger" Alexa skill)
  digitalWrite(led, HIGH);
  HTTPClient http;    
  http.begin(lightOnLink);
  int response = http.GET();
  Serial.println(response);
  http.end();
  Serial.println("Light on");
  delay(100);
  digitalWrite(led, LOW);
}

// Send a http request to the URL that turns OFF the lights (using the "URL Routine Trigger" Alexa skill)
void lightOff(){
  digitalWrite(led, HIGH);
  HTTPClient http;    
  http.begin(lightOffLink);
  int response = http.GET();
  Serial.println(response);
  http.end();
  Serial.println("Light off");
  delay(100);
  digitalWrite(led, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(onButton, INPUT_PULLUP);
  pinMode(offButton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  initWiFi();
}

void loop() {
  digitalWrite(led, LOW);
  // Call the lightOn() function when the corresponding button is pressed
  if(digitalRead(onButton) == LOW){
    delay(300);
    if(digitalRead(onButton) == LOW){
      lightOn();
      delay(200);
    }
  }

  // Call the lightOff() function when the corresponding button is pressed
  if(digitalRead(offButton) == LOW){
    delay(300);
    if(digitalRead(offButton) == LOW){
      lightOff();
      delay(200);
    }
  }
}
