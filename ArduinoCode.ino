
// your Blynk Credentials.
#define BLYNK_TEMPLATE_ID "*******"
#define BLYNK_TEMPLATE_NAME "*******"
#define BLYNK_AUTH_TOKEN "*****************"

// Your WiFi Credentials.
// Set password to "" for open networks.
char ssid[] = "*******";
char pass[] = "********";

// define the GPIO connected with Sensors & LEDs
#define MQ2_SENSOR    35
#define GREEN_LED     14
#define RED_LED       25
#define WIFI_LED      2
//#define Buzzer        4 //If need

//#define BLYNK_PRINT Serial
#include<Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

int MQ2_SENSOR_Value = 0;
int Tree_Pos_Value = 0;
bool isconnected = false;
char auth[] = BLYNK_AUTH_TOKEN;

#define VPIN_BUTTON_0    V0
#define VPIN_BUTTON_2    V2

void checkBlynkStatus() { // called every 2 seconds by SimpleTimer
  isconnected = Blynk.connected();
  if (isconnected == true) {
    digitalWrite(WIFI_LED, HIGH);
    sendData();
    Serial.println("Blynk Connected");
  }
  else {
    digitalWrite(WIFI_LED, LOW);
    Serial.println("Blynk Not Connected");
  }
}

void getMPUData() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  if (((x <= 40) || (320 <= x)) && ((y <= 40) || (320 <= y))) {
    Serial.println("Normal");
    digitalWrite(GREEN_LED, LOW);
    Tree_Pos_Value =0;
  } else {
    Serial.println("Alert");
    Tree_Pos_Value=1;
    digitalWrite(GREEN_LED, HIGH);
  }
}

void getSensorData()
{
  MQ2_SENSOR_Value = map(analogRead(MQ2_SENSOR), 0, 4095, 0, 100);
  Serial.println(MQ2_SENSOR_Value);
  if (MQ2_SENSOR_Value > 50 ) { 
    digitalWrite(RED_LED, HIGH);
  }
  else {
    digitalWrite(RED_LED, LOW);
  }
}

void sendData()
{
  Blynk.virtualWrite(VPIN_BUTTON_0, MQ2_SENSOR_Value);
  if (MQ2_SENSOR_Value > 50 )
  {
    Blynk.logEvent("smoke", "Alert!!! Smoke Detected....");
  }
  else if (Tree_Pos_Value == 1 )
  {
    Blynk.logEvent("tree_1", "Alert!!! Tree1 Down...");
    Blynk.virtualWrite(VPIN_BUTTON_2,Tree_Pos_Value );
  }
  else if (Tree_Pos_Value == 0 )
  {
    Blynk.virtualWrite(VPIN_BUTTON_2,Tree_Pos_Value );
  }
}

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  pinMode(MQ2_SENSOR, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(WIFI_LED, LOW);

  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
  Blynk.config(auth);
  delay(1000);
}

void loop()
{
  getSensorData();
  getMPUData();
  Blynk.run();
  timer.run();
}
