1. Príprava hardvéru
a) Schéma zapojenia:
Pred samotným zapojením si nakresli schému. To ti pomôže lepšie si predstaviť, ako budú
komponenty prepojené. V schéme by mali byť:
● Arduino Mega 2560
● ESP32
● 3x kapacitný senzor TTP223
● 3x vyhrievacia fólia/kábel
● 3x tlačidlo
● 8x8 LED matrix
● Napájací adaptér 12V/5A
● Napäťový regulátor LM7805
b) Zapojenie komponentov:
● Senzory: Pripoj každý senzor TTP223 k Arduino Mega. Signálny pin senzora pripoj k
digitálnemu pinu na Arduine (v kóde sú použité piny 2, 4 a 6). Napájacie piny senzora pripoj k
5V a GND na Arduine.
● Vyhrievacie elementy: Pripoj každý vyhrievací element k Arduino Mega. Jeden koniec
elementu pripoj k digitálnemu pinu na Arduine (v kóde sú použité piny 3, 5 a 7) a druhý
koniec k GND. Dôležité: Uisti sa, že vyhrievacie elementy sú vhodné pre napájanie z
Arduina (5V) a majú dostatočne nízku spotrebu, aby nedošlo k preťaženiu Arduina. Ak je
spotreba príliš vysoká, použi externý zdroj napájania a relé na ovládanie vyhrievania.
● Tlačidlá: Pripoj každé tlačidlo k Arduino Mega. Jeden pin tlačidla pripoj k digitálnemu pinu na
Arduine (v kóde sú použité piny 8, 9 a 10) a druhý pin k GND.
● Matrixový displej: Pripoj displej k Arduino Mega pomocou I2C komunikácie. SDA pin
displeja pripoj k SDA pinu na Arduine a SCL pin displeja k SCL pinu na Arduine. Napájacie
piny displeja pripoj k 5V a GND.
● ESP32: Pripoj ESP32 k napájaniu (5V a GND). Pripoj TX pin ESP32 k RX pinu na Arduine a
RX pin ESP32 k TX pinu na Arduine. To zabezpečí sériovú komunikáciu medzi Arduinom a
ESP32.
● Napájanie: Pripoj napájací adaptér 12V/5A k napäťovému regulátoru LM7805. Výstup z
regulátora (5V) použi na napájanie Arduino Mega a ESP32.
c) Umiestnenie komponentov:
● Umiestni Arduino Mega, ESP32 a ostatné elektronické komponenty do vhodnej krabice alebo
krytu, aby boli chránené pred mačkami a poveternostnými vplyvmi.
● Uisti sa, že všetky káble sú bezpečne upevnené a izolované.
● Umiestni vankúše a pelechy do konštrukcie pelechu.
● Senzory umiestni pod vankúše/pelechy tak, aby dokázali detekovať prítomnosť mačky.
● Vyhrievacie elementy umiestni pod vankúše/pelechy tak, aby rovnomerne vyhrievali plochu.
● Tlačidlá umiestni na dostupné miesto, aby sa dali ľahko ovládať.
● Matrixový displej umiestni na viditeľné miesto.

2. Inštalácia softvéru
a) Arduino IDE:
● Stiahni a nainštaluj Arduino IDE z oficiálnej stránky: https://www.arduino.cc/en/software
● Nainštaluj knižnice pre matrixový displej:
○ Otvor Arduino IDE a prejdi do Sketch > Include Library > Manage Libraries...
○ Vyhľadaj "Adafruit_GFX" a "Adafruit_LEDBackpack" a nainštaluj ich.
● Otvor kód pelech-cat.cpp v Arduino IDE.
● Pripoj Arduino Mega k počítaču pomocou USB kábla.
● Vyber správny typ dosky (Arduino Mega 2560) a port v Tools > Board a Tools > Port.
● Nahraj kód na Arduino Mega kliknutím na tlačidlo "Upload".
b) ESP32:
● V Arduino IDE prejdi do File > Preferences.
● V poli "Additional Boards Manager URLs" pridaj nasledujúci link: [neplatná webová adresa
bola odstránená]
● Klikni na "OK".
● Prejdi do Tools > Board > Boards Manager...
● Vyhľadaj "esp32" a nainštaluj "ESP32 by Espressif Systems".
● Otvor kód pelech-cat-esp32.cpp v Arduino IDE.
● Pripoj ESP32 k počítaču pomocou USB kábla.
● Vyber správny typ dosky (ESP32 Dev Module) a port v Tools > Board a Tools > Port.
● Nahraď NAZOV_WIFI_SIETE a HESLO_WIFI_SIETE s údajmi tvojej WiFi siete v kóde
pelech-cat-esp32.cpp.
● Nahraj kód na ESP32 kliknutím na tlačidlo "Upload".
● Nainštaluj knižnicu pre SPIFFS:
○ Otvor Arduino IDE a prejdi do Sketch > Include Library > Manage Libraries...
○ Vyhľadaj "SPIFFS" a nainštaluj ju.
● Otvor SPIFFS upload tool v Arduino IDE (Tools > ESP32 Sketch Data Upload).
● Vytvor súbor index.html s kódom, ktorý sme si ukázali.
● Nahraj súbor index.html do ESP32.
c) Python skript:
● Nainštaluj Python na zariadenie, kde bude skript bežať.
● Nainštaluj knižnicu pyPetKit: pip install pyPetKit
● Vytvor Python skript petkit_server.py s kódom, ktorý sme si ukázali.
● Nahraď email@example.com a password s tvojimi prihlasovacími údajmi do aplikácie Petkit.
● Spusti Python skript: python petkit_server.py

3. Spustenie a testovanie

● Odpoj Arduino Mega a ESP32 od počítača.
● Pripoj Arduino Mega a ESP32 k napájaniu.
● Uisti sa, že ESP32 a zariadenie s Python skriptom sú pripojené k rovnakej WiFi sieti.
● Otvor webové rozhranie v prehliadači zadaním IP adresy ESP32.
● Otestuj funkčnosť senzorov:
○ Keď mačka leží na pelechu, mal by sa na displeji zobraziť symbol "X" a malo by sa zapnúť
vyhrievanie.
○ Keď mačka vstane z pelechu, symbol "X" by mal zmiznúť a vyhrievanie by sa malo
vypnúť.
● Otestuj funkčnosť tlačidiel:
○ Stlačením tlačidla by sa mal aktivovať/deaktivovať režim "nerušiť" pre daný pelech.
○ Na displeji by sa mal zobraziť symbol "!" pre aktívny režim "nerušiť".
● Otestuj dávkovanie krmiva:
○ Zadaj množstvo krmiva na webovom rozhraní a klikni na tlačidlo "Dávkovať".
○ Dávkovač Petkit by mal vysypať zadané množstvo krmiva.

4. Záverečné úpravy a tipy
● Ak narazíš na nejaké problémy, skontroluj zapojenie, kód a nastavenia WiFi.
● Môžeš upraviť kód a webové rozhranie podľa svojich potrieb a pridať ďalšie funkcie.
● Pravidelne kontroluj funkčnosť a stav pelechu.
