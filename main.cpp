#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Gree.h>

// WiFi
const char* ssid = "NOC";
const char* password = "noc2023!";

// WebSocket client
WebSocketsClient webSocket;
const char* host = "192.168.223.68"; // IP Node-RED
const int port = 1880;               // port Node-RED
const char* path = "/ws/ac";         // endpoint Node-RED

// IR LED Pin
const uint16_t kIrLed = 4;
IRGreeAC ac(kIrLed);

// Tombol fisik
#define BTN1 18
#define BTN2 19

int setTemp = 24;  // default suhu

// Kirim status ke Node-RED
void sendState(const char* key, String value) {
  String msg = String("{\"") + key + "\":\"" + value + "\"}";
  webSocket.sendTXT(msg);
}

// Callback saat pesan masuk dari Node-RED
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_TEXT: {
      String message = String((char*)payload);

      if (message.indexOf("setTemp") != -1) {
        int temp = message.substring(message.indexOf(":") + 1).toInt();
        setTemp = temp;
        ac.setTemp(setTemp);
        ac.on();
        ac.send();
        Serial.println("Set suhu dari Node-RED: " + String(setTemp));
      }
      break;
    }
    case WStype_CONNECTED:
      Serial.println("Connected to WebSocket server");
      break;
    case WStype_DISCONNECTED:
      Serial.println("Disconnected from WebSocket server");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);

  ac.begin();
  ac.on();
  ac.setMode(kGreeCool);
  ac.setFan(kGreeFanAuto);
  ac.setTemp(setTemp);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected: " + WiFi.localIP().toString());

  // Setup WebSocket client
  webSocket.begin(host, port, path);
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(1000); // auto reconnect tiap 5 detik
}

void loop() {
  webSocket.loop();

  // Tombol ON
  if (digitalRead(BTN1) == LOW) {
    ac.on();
    ac.setTemp(setTemp);
    ac.send();
    sendState("AC", "ON");
    Serial.print("ON");
    delay(300);
  }

  // Tombol OFF
  if (digitalRead(BTN2) == LOW) {
    ac.off();
    ac.send();
    sendState("AC", "OFF");
    Serial.print("OFF");
    delay(300);
  }
  delay(50);
}
