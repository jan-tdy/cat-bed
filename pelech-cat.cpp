#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// Definovanie pinov
#define SENSOR_PIN_1 2
#define SENSOR_PIN_2 4
#define SENSOR_PIN_3 6
#define HEATER_PIN_1 3
#define HEATER_PIN_2 5
#define HEATER_PIN_3 7
#define MATRIX_I2C_ADDRESS 0x70
#define BUTTON_PIN_1 8
#define BUTTON_PIN_2 9
#define BUTTON_PIN_3 10

// Vytvorenie objektu pre matrixový displej
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Počet miest
const int NUM_BEDS = 3;

// Pole pre stavy senzorov
bool bedOccupied[NUM_BEDS] = {false};

// Pole pre stavy vyhrievania
bool heatingEnabled[NUM_BEDS] = {false};

// Pole pre režim "nerušiť"
bool doNotDisturb[NUM_BEDS] = {false};

void setup() {
  // Inicializácia sériovej komunikácie
  Serial.begin(9600);

  // Nastavenie pinov senzorov ako vstupy
  pinMode(SENSOR_PIN_1, INPUT);
  pinMode(SENSOR_PIN_2, INPUT);
  pinMode(SENSOR_PIN_3, INPUT);

  // Nastavenie pinov vyhrievacích elementov ako výstupy
  pinMode(HEATER_PIN_1, OUTPUT);
  pinMode(HEATER_PIN_2, OUTPUT);
  pinMode(HEATER_PIN_3, OUTPUT);

  // Nastavenie pinov tlačidiel ako vstupy
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(BUTTON_PIN_3, INPUT);

  // Inicializácia matrixového displeja
  matrix.begin(MATRIX_I2C_ADDRESS);
}

void loop() {
  // Čítanie údajov zo senzorov
  bedOccupied[0] = digitalRead(SENSOR_PIN_1);
  bedOccupied[1] = digitalRead(SENSOR_PIN_2);
  bedOccupied[2] = digitalRead(SENSOR_PIN_3);

  // Ovládanie vyhrievania
  for (int i = 0; i < NUM_BEDS; i++) {
    if (bedOccupied[i] && !doNotDisturb[i]) {
      digitalWrite(HEATER_PIN_1 + i * 2, HIGH); // Zapnutie vyhrievania
    } else {
      digitalWrite(HEATER_PIN_1 + i * 2, LOW); // Vypnutie vyhrievania
    }
  }

  // Ovládanie režimu "nerušiť"
  for (int i = 0; i < NUM_BEDS; i++) {
    if (digitalRead(BUTTON_PIN_1 + i) == HIGH) {
      doNotDisturb[i] = !doNotDisturb[i]; // Prepínanie režimu
      delay(200); // Debouncing tlačidla
    }
  }

  // Zobrazenie informácií na matrixovom displeji

  // Čakanie 1 sekundu
  delay(1000);


// Počet kŕmení za deň
const int NUM_FEEDINGS = 5;

// Pole pre časy kŕmenia
String feedTimes[NUM_FEEDINGS] = {"7:00", "12:00", "17:00", "20:00", "22:00"};

// Pole pre množstvá krmiva (v gramoch)
int feedGrams[NUM_FEEDINGS] = {40, 20, 30, 10, 40};

// Index aktuálneho kŕmenia
int currentFeeding = 0;


  // Zobrazenie informácií na matrixovom displeji
  matrix.clear();
  matrix.setCursor(0, 0);

  // Zobrazenie obsadenosti
  for (int i = 0; i < NUM_BEDS; i++) {
    if (bedOccupied[i]) {
      matrix.print("X"); // Zobrazenie "X" pre obsadené miesto
    } else {
      matrix.print("_"); // Zobrazenie "_" pre voľné miesto
    }
  }

  matrix.setCursor(0, 1);

  // Zobrazenie režimu "nerušiť"
  for (int i = 0; i < NUM_BEDS; i++) {
    if (doNotDisturb[i]) {
      matrix.print("!"); // Zobrazenie "!" pre režim "nerušiť"
    } else {
      matrix.print(" "); // Zobrazenie medzery
    }
  }

  matrix.setCursor(0, 2);

  // Zobrazenie informácií o kŕmení
  matrix.print(feedTimes[currentFeeding]);
  matrix.setCursor(0, 3);
  matrix.print(feedGrams[currentFeeding]);
  matrix.writeDisplay();

  // Zvýšenie indexu aktuálneho kŕmenia
  currentFeeding = (currentFeeding + 1) % NUM_FEEDINGS;

// Odoslanie dát na ESP32
String data = "";
for (int i = 0; i < NUM_BEDS; i++) {
  data += bedOccupied[i] ? "1" : "0";
}
data += ";";
for (int i = 0; i < NUM_BEDS; i++) {
  data += doNotDisturb[i] ? "1" : "0";
}
data += ";";
data += feedTimes[currentFeeding];
data += ";";
data += feedGrams[currentFeeding];
Serial.println(data);}
