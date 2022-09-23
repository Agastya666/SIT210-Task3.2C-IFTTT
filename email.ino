#include "arduino_secrets.h"
// BH1750FVI - Version: Latest 
#include <BH1750FVI.h>

// WiFiNINA_Generic - Version: Latest 
#include <WiFiNINA_Generic.h>
WiFiClient client;

BH1750FVI BH1750(BH1750FVI::k_DevModeContLowRes);

//please enter your sensitive data in the Secret tab
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)

char   HOST_NAME[] = "maker.ifttt.com";

String queryString = "?value1=57&value2=25";

bool sunlight = false;

void setup() {
  WiFi.begin(ssid, pass);
  BH1750.begin();
  Serial.begin(9600);
}

void light_received() {
  String PATH_NAME   = "/trigger/light_received/with/key/jhPlpb6TxLwNt2rqezn5b-Qdsj3aQmy28gRzLRrHvLy"; // change your EVENT-NAME and YOUR-KEY
  
    // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header


    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
}

void light_not_received() {
  String PATH_NAME   = "/trigger/light_not_received/with/key/jhPlpb6TxLwNt2rqezn5b-Qdsj3aQmy28gRzLRrHvLy"; // change your EVENT-NAME and YOUR-KEY
  
    // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header


    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
}

void connect() {
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
}

void disconnect() {
  client.stop();
  Serial.println();
  Serial.println("disconnected");
}

void loop() {
  int intensity = BH1750.GetLightIntensity();
  int check = 0;
  
  Serial.println("Light: " + intensity);
// loop is checked 10000 times to avoid any minor errors or unwanted notifications
  if (intensity < 100 && sunlight == true )
  {
    check++;
    if (check>10000) 
    {
    connect();
    light_not_received();
    disconnect();
    sunlight = false;
    check = 0;
    }
  }
  else if (intensity > 100 && sunlight == false)
  {
    check++
    if (check>10000)
    {
    connect();
    light_received();
    disconnect();
    sunlight = true;
    check = 0;
    }
  }
}