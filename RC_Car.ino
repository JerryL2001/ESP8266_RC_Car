#include <ESP8266WiFi.h>
#include <Servo.h>
#define LD 30      //rear LEDs' brightness when head leds are on
#define relay1 D7//左舵机  left servo attaches to pin D7
#define relay2 D8//右舵机  right servo attaches to pin D8
#define frontled D1     //front LEDs' positive terminal connect to D1
#define backled D0      //back LEDs' positive terminal connect to D0
const int RT=(-1);//右舵机转速调平   //variable used to adjust the speed of the right servo, it should be adjusted according to the actual situation of the servo 
const int LT=0;//左舵机转速调平    //variable used to adjust the speed of the left servo, it should be adjusted according to the actual situation of the servo 

Servo s1;
Servo s2;
int V = 5;    //velocity gradient when changing speed
int Lm = 0;   //brightness of LEDs
int LV = V + LT;//左舵机速度  velocity of the left servo while going straight (0~180 if LV=90, the servo will stop. if LV<90, the servo will rotate in reverse)
int RV = V + RT;//右舵机速度  velocity of the right servo while going straight

const char *ssid = "";        //enter the name of your mobile WiFi hotspot here 
const char *password = "";    //enter password
const char *host = "8266";      
WiFiClient client;    //ESP8266 will work as a TCP client
const int tcpPort = 8266;

void connectWiFi()     //function of connecting your ESP8266 to the wifi
{
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.println(WiFi.localIP());
}


void setup()
{
  V = 45;
  Lm = 0;
  Serial.begin(9600);
    
  pinMode(frontled, OUTPUT);
  digitalWrite(frontled,LOW);  
  pinMode(backled, OUTPUT);  
  digitalWrite(backled,LOW);
  s1.attach(relay1);    //s1 refers to the left servo
  s1.write(90);         //left servo will stop at start
  s2.attach(relay2);    //s2 refers to the right servo
  s2.write(90);         //right servo will stop at start
  
  connectWiFi();
}

void loop()
{
    while(!client.connected())
    {
      if(!client.connect(host,tcpPort))
      {
        Serial.println("Connecting...");
        delay(500);
      }
    }
    while(client.available())
    {
      char command = client.read();  //read data from your mobile app, which is the TCP server
      /* if the data sent to servo is 90, the servo will stop; if it's lower than 90, the servo will rotate to let the car run backward; if it's higher than 90, the servo will rotate to let the car run forward */
      if (command == 'E' )      {analogWrite(backled,Lm); s1.write((90+LV)); s2.write((90-RV)); client.write("OK!");}//前进   run forward
      else if (command == 'K' ) {analogWrite(backled,Lm); s1.write((90-LV)); s2.write((90+RV)); client.write("OK!");}//后退   run backward
      else if (command == 'H')  {digitalWrite(backled,HIGH); s1.write(90); s2.write(90); client.write("OK!");}//停止          stop
      else if (command == 'G')  {analogWrite(backled,Lm); s1.write(90+(LV/2)); s2.write((90-RV)); client.write("OK!");}//左转 turn left
      else if (command == 'I')  {analogWrite(backled,Lm); s1.write((90+LV)); s2.write(90-(RV/2)); client.write("OK!");}//右转 turn right
      else if (command == 'J')  {analogWrite(backled,Lm); s1.write((90-LV)); s2.write((90-RV)); client.write("OK!");}//左掉头 turn left on the spot
      else if (command == 'L')  {analogWrite(backled,Lm); s1.write((90+LV)); s2.write((90+RV)); client.write("OK!");}//右掉头 turn rhght on the spot
      else if (command == 'A')  {analogWrite(backled,Lm); {if(V<90) {V+=5;}} LV = V + LT; RV = V + RT; client.write("OK!");}//加速，最高九挡 speed up, up to nine gears
      else if (command == 'D')  {analogWrite(backled,Lm); {if(V>0) {V-=5;}} LV = V + LT; RV = V + RT; client.write("OK!");}//减速，最高九挡  speed down, up to nine gears
      else if (command == 'C')  {Lm = LD; digitalWrite(frontled,HIGH); analogWrite(backled,Lm); client.write("OK!");}//开前灯和行车灯    turn on front LEDs and rear warning LEDs
      else if (command == 'F')  {Lm = 0; digitalWrite(frontled,LOW); analogWrite(backled,Lm); client.write("OK!");}//关前灯和行车灯      turn off all LEDs
      else if (command == 'B')  {Lm = 0; digitalWrite(frontled,LOW); analogWrite(backled,Lm); s1.write(90); s2.write(90); V=45; LV = V + LT; RV = V + RT; client.write("OK!");}//初始化  initialize
    }
}
