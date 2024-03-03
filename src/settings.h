#ifndef SETTINGS_H
#define SETTINGS_H
#include <Arduino.h>
#include <EncButton.h>
#include <TFT_eSPI.h>
#include <Audio.h>
#include <EEPROM.h>
#include <settings.h>
#include <WiFiManager.h>
#include <Update.h>
// #include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <GyverNTP.h>
#include <HTTPClient.h>
#include <ArduinoJSON.h>
// #include <ESP32Time.h>
#include <UnixTime.h>
#include "../lib/Bahamas14.h"
#include "../lib/fonts.h"
#include "../lib/CourierCyr10.h"
#include "../lib/Bahamas18.h"
#include "../lib/CourierCyr12.h" //для меню станций
#include "../lib/Free_Fonts.h"
#include <ImgWea60.h>

#define RU10 &FreeSansBold10pt8b
#define BAHAMAS &Bahamas14pt8b
#define DIG20 &DIG_Bold_20
#define RU8 &FreeMonoBold8pt8b

#define FIRMWARE_VERSION "2.0.1"

int currentVersion = 0; // increment currentVersion in each release
String baseUrl = "https://raw.githubusercontent.com/runo4938/esp32-s3_st7789/main/";
String checkFile = "src/update.json";
int fwVersion = 0;
bool fwCheck = false;
String fwUrl = "", fwName = "";
#define LED_BRIGHTNESS 90 // яркость дисплея при старте
#define LED_BUILT 5       // управление яркостью дисплея

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite txtSprite = TFT_eSprite(&tft);  // Create Sprite
TFT_eSprite WeatherSpr = TFT_eSprite(&tft); // Create Sprite

Audio audio;
#define I2S_DOUT 16 // 27 // 18 // DIN connection
#define I2S_BCLK 17 // // Bit clock
#define I2S_LRC 18  //  // Left Right Clock
//int volume = 15;    // end audio

// encoder
#define CLK 4 // 35 //
#define DT 3  //  //
#define SW 8  //  //
EncButton enc1(CLK, DT, SW);

WiFiManager wifiManager;
HTTPClient http;
WiFiClient client;

// Radio
uint8_t NEWStation = 0;
uint8_t OLDStation = 1;
int numbStations = 30;     // количество радиостанций
String displayStations[8]; // Массив для станций на дисплее
String StationList[30];    // Всего станций
String nameStations[30];   // Наименования станций

// Weather
String apikey = F("30a9767f8d62e95546ea92a956457507"); // API key
String Latitude = F("44.0511");                        //
String Longitude = F("44.5408");                       //
String lang = F("&lang=ru");      // this is your language

String sliderValue;
const char *PARAM_INPUT = "value";

UnixTime stamp(3);

const char *apikeyPath = "/apikey";
const char *LatitudePath = "/Latitude";
const char *LongitudePath = "/Longitude";
// ESP32Time rtc;
// ESP32Time rtc(10800); // offset in seconds GMT+3
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 10800;
const int daylightOffset_sec = 10800;

// Scrolling
String MessageToScroll_1 = F(" 1-> For scrolling text 23 23 23 45 2-> ");
String MessageToScroll_2 = F("It's two string for scrolling");
int16_t width_txt;
int16_t width_txtW;

int x_scroll_L;
int x_scroll_R;

int x_scroll_LW;
int x_scroll_RW;

GyverNTP ntp(3);

AsyncWebServer server(80);
TaskHandle_t Task1;
TaskHandle_t myTaskHandle = NULL;

bool first = true; // Вывести дату и день недели
// bool http_acp = true;
// int y1_random;
// int y2_random;

String CurrentDate;
uint8_t CurrentWeek;
String days[8] = {"Воскресенье", "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ", "ВС"};
uint16_t ind;
String newSt;
bool rnd = true; // для случ числа
                 // Прошлое значение индикатора
int x1_lev;
int x2_lev;
int x1_prev = 162;
int x2_prev = 162;
int y_show = 122;
int y1_prev = 210;
int y1_lev = 210;
int y2_prev = 210;
int y2_lev = 210;
bool f_startProgress = true; // for initial values

bool stations;                 // Станция вверх или вниз (true or false)
bool showRadio = true;         // show radio or menu of station,
bool getClock = true;          // Получать время только при запуске
unsigned long currentMillis;   // To return from the menu after the time has expired
unsigned long intervalForMenu; // Для возврата из меню по истечении времении

unsigned long lastTime = 0;
unsigned long lastTime_ssid = 0;
unsigned long timerDelay_ssid = 4000;

uint32_t targetTime_clock = 0; // update clock every second

uint32_t vumetersDelay = 250;
const String space = " ";

//--filesystem --------------
String filelist = "";
size_t content_len;
File file;
bool opened = false;
const char *PARAM_INPUT_1 = "ApiKey";
const char *PARAM_INPUT_2 = "Latitude";
const char *PARAM_INPUT_3 = "Longitude";

String listRadio; // радиостанции на странице
const char *PARAM = "file";
const char *host = "esp32";
#define U_PART U_SPIFFS //

static void rebootEspWithReason(String reason);
//-------OTA---
/* this info will be read by the python script */
#define FORMAT_SPIFFS_IF_FAILED true

int ypos = 190; // position title
int xpos = 0;
String bitrate;
/*----- Weather Json -----*/
typedef struct
{
    float lon;          // 37.71
    float lat;          // 51.84
    String description; // "небольшая облачность"
    String icon;        // "03n"
    float temp;         // 12.56
    float feels_like;   // 11.96
    int pressure;       // 1022     // приведённое к уровню моря давление.
    int humidity;       // 80
    int grnd_level;     // 1001   // давление на местности
    int visibility;     // 10000
    float speed;        // 2.1
    int deg;            // 354
    float gust;         // 2.15
    long dt;            // 1686079705
    String country;     // "RU"
    long sunrise;       // 1686013976
    long sunset;        // 1686073370
    long id;            // 540121
    String name;        // "Кшенский"
} weather_t;
weather_t weather;

// Ветер
const String Wind_N = F("Северный");
const String Wind_NE = F("Северо-Восточный");
const String Wind_E = F("Восточный");
const String Wind_SE = F("Юго-Восточный");
const String Wind_S = F("Южный");
const String Wind_SW = F("Юго-Западный");
const String Wind_W = F("Западный");
const String Wind_NW = F("Северо-Западный");

void initSpiffs();
void readEEprom();
void initWiFi();
void menuStation();
void listStaton();
String make_str(String str);
void newVer();
void clock_on_core0();
void onMenu();
void onMenuOn();
void onMenuOFf();

// weather
void Get_Weather_http(String &MSG_http);
void getWeather();
String WindDeg_Direction(int Wind_direction);
unsigned long timerDelay = 30; // минуты -таймер обновления погоды
unsigned long timer_prev = 0;
unsigned long timer_prev_w = 0;

void scrollMainWeather(bool directTo, int left_coner_x, int left_coner_y, int speed_scroll);
void scrollMain(bool directTo, int left_coner_x, int left_coner_y, int speed_scroll);

bool decode_json(Stream &jsonStr);
bool downloadFirmware();
bool checkFirmware();
void updateFromFS(fs::FS &fs);
bool decode_json(Stream &jsonStr);
void myEncoder();
void soundShow();
void soundShow2();
void drawlineClock();
void lineondisp();
void wifiLevel();
void print_Img(int x, int y, String WeaIcon);
void printCodecAndBitrate();
void printCodecAndBitrate1();
void printStation(uint8_t indexOfStation);
void nextStation(bool stepStation);
void stationDisplay(int st);
void filePosition();
void serverOn();
void messageOn();


String readFile(fs::FS &fs, const char *path);
void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void handleDoUpdate(AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final);
void handleDoUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
void printProgress(size_t prg, size_t sz);
void notFound(AsyncWebServerRequest *request);
void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void deleteFile(fs::FS &fs, const String &path);
String processor_update(const String &var);
String processor_playlst(const String &var);
String processor(const String &var);
String utf8rus(String source);
void Task1code(void *pvParameters);
#endif
