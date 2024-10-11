#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Nahraď s tvojim SSID a heslom WiFi siete
const char* ssid = "NAZOV_WIFI_SIETE";
const char* password = "HESLO_WIFI_SIETE";

// Vytvorenie webového servera
AsyncWebServer server(80);

// Premenné pre uloženie dát z Arduina
bool bedOccupied[3] = {false};
bool doNotDisturb[3] = {false};
String currentFeedTime = "";
int currentFeedGrams = 0;

void setup() {
  // Inicializácia sériovej komunikácie
  Serial.begin(9600);

  // Pripojenie k WiFi sieti
  WiFi.begin(TP link 219, TPLINK@219);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Pripájanie k WiFi..");
  }
  Serial.println(WiFi.localIP());

  // Definovanie endpointu pre hlavnú stránku
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<h1>Inteligentný pelech pre mačky</h1>");
  });

  // Endpoint pre získanie stavu obsadenosti
  server.on("/occupancy", HTTP_GET, [](AsyncWebServerRequest *request){
    String occupancy = "";
    for (int i = 0; i < 3; i++) {
      occupancy += bedOccupied[i] ? "1" : "0";
    }
    request->send(200, "text/plain", occupancy);
  });

  // Endpoint pre získanie stavu režimu "nerušiť"
  server.on("/dnd", HTTP_GET, [](AsyncWebServerRequest *request){
    String dnd = "";
    for (int i = 0; i < 3; i++) {
      dnd += doNotDisturb[i] ? "1" : "0";
    }
    request->send(200, "text/plain", dnd);
  });

  // Endpoint pre získanie informácií o kŕmení
  server.on("/feeding", HTTP_GET, [](AsyncWebServerRequest *request){
    String feedingInfo = currentFeedTime + " " + String(currentFeedGrams) + "g";
    request->send(200, "text/plain", feedingInfo);
  });

  // Spustenie webového servera
  server.begin();
}

void loop() {
  // Čítanie dát z Arduina (cez sériovú komunikáciu)

void loop() {
  // Čítanie dát z Arduina cez sériovú komunikáciu
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    // Rozdelenie dát na jednotlivé hodnoty
    int index1 = data.indexOf(';');
    int index2 = data.indexOf(';', index1 + 1);
    int index3 = data.indexOf(';', index2 + 1);
    int index4 = data.indexOf(';', index3 + 1);

    // Uloženie dát do premenných
    for (int i = 0; i < 3; i++) {
      bedOccupied[i] = data.substring(index1 + 1 + i, index1 + 2 + i).toInt();
      doNotDisturb[i] = data.substring(index2 + 1 + i, index2 + 2 + i).toInt();
    }
    currentFeedTime = data.substring(index3 + 1, index4);
    currentFeedGrams = data.substring(index4 + 1).toInt();
  }
}
}
