#include <Wire.h>
#include <Adafruit_MSA301.h>
#include <Adafruit_Sensor.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <MD5Builder.h>


//constantes
int clientId = 138;//client example
IPAddress server_addr(185,xx,xx,xx); //185.xx.xx.xx
char user[] = "xx";
char passwordDb[] = "xxxx"; 
char * ssid  = "iPhone de Daniel";
char * password = "hellotheworld";
char mqttServer[] = "broker.hivemq.com";
char ntpServer[] = "time.windows.com";
#define MQTTPORT 1883
#define MP3_RX 13 // to TX
#define MP3_TX 15 // to RX
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 


//commandes MP3
// Select storage device to TF card
static int8_t select_SD_card[] = {0x7e, 0x03, 0x35, 0x01, 0xef}; // 7E 03 35 01 EF
//select first
static int8_t soundConfig[] = {0x7e, 0x03, 0x31, 0x1e, 0xef};//7E 03 31 1E EF
static int8_t bienvenue[] = {0x7e, 0x04, 0x42, 0x01, 0x01, 0xEF};//7E 04 42 01 01 EF
//select second
static int8_t configurationWifiSound[] = {0x7e, 0x04, 0x42, 0x01, 0x02, 0xEF};//7E 04 42 01 02 EF
//select third
static int8_t connecteWifi[] = {0x7e, 0x04, 0x42, 0x01, 0x03, 0xEF};//7E 04 42 01 03 EF
//select fourth
static int8_t chuteDetectee[] = {0x7e, 0x04, 0x42, 0x01, 0x04, 0xEF};//7E 04 42 01 04 EF
//select fifth
static int8_t centraleInforme[] = {0x7e, 0x04, 0x42, 0x01, 0x05, 0xEF};//7E 04 42 01 05 EF
//select sixth
static int8_t questionBouton[] = {0x7e, 0x04, 0x42, 0x01, 0x06, 0xEF};//7E 04 42 01 06 EF
//select seventh
static int8_t informonsCentrale[] = {0x7e, 0x04, 0x42, 0x01, 0x07, 0xEF};//7E 04 42 01 07 EF
//select eighth
static int8_t alert[] = {0x7e, 0x04, 0x42, 0x01, 0x08, 0xEF};//7E 04 42 01 08 EF
static int8_t bugI2c[] = {0x7e, 0x04, 0x42, 0x01, 0x09, 0xEF};//7E 04 42 01 09 EF
static int8_t stop[] = {0x7e, 0x02, 0x0e, 0xef}; //7E 02 0E EF

//mes variables
bool alertSoundBool = false;
int numberOfTimeLoop = 0;
bool stateValue[5] = {0,0,0,0,0};
char heure[] = "00:00";
int nextMinuteHour;
int prevz;

//instanciations
Adafruit_MSA301 msa;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, 3600, 60000);
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
SoftwareSerial MP3(MP3_RX, MP3_TX);
HTTPClient http;
MySQL_Connection conn(&espClient);
MySQL_Cursor* cursor;
MD5Builder _md5;
