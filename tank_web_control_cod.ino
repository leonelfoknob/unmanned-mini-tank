#include <ESP8266WiFi.h>
const char* ssid = "Mf-mustafa";    //  Your Wi-Fi Name
const char* password = "Leonel01@";   // Wi-Fi Password
int LED = 2;   // led connected to GPIO2 (D4)
WiFiServer server(80);

/*******************************/

#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

int speedCar = 200;
int speed_Coeff = 3;

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

/*********************************/



void setup()
{

 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
  
Serial.begin(115200); //Default Baudrate
pinMode(LED, OUTPUT);
digitalWrite(LED, LOW);
Serial.print("Connecting to the Newtork");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("WiFi connected"); 
server.begin();  // Starts the Server
Serial.println("Server started");
Serial.print("IP Address of network: "); // will IP address on Serial Monitor
Serial.println(WiFi.localIP());
Serial.print("Copy and paste the following URL: https://"); // Will print IP address in URL format
Serial.print(WiFi.localIP());
Serial.println("/");
}
void loop()
{
WiFiClient client = server.available();
if (!client)
{
return;
}
Serial.println("Waiting for new client");
while(!client.available())
{
delay(1);
 }
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
int value = LOW;
if(request.indexOf("/LED=ON") != -1)
{
  digitalWrite(LED, HIGH); // Turn LED ON
value = HIGH;
  }
  if(request.indexOf("/LED=OFF") != -1)
 {
    digitalWrite(LED, LOW); // Turn LED OFF
   value = LOW;
 }

 //******************************* leonel's cod 
 
 if(request.indexOf("/state=foward") != -1)
 {
    goAhead();
 }

 if(request.indexOf("/state=back") != -1)
 {
    goBack();
 }

 if(request.indexOf("/state=left") != -1)
 {
    goLeft();
 }
 if(request.indexOf("/state=right") != -1)
 {
    goRight();
 }
 if(request.indexOf("/state=stop") != -1)
 {
    stopRobot();
 }
 
//*------------------HTML Page Code-------------------
client.println("HTTP/1.1 200 OK"); //
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.print("<center>");
client.println("<body><h1> WELL-COME TO MICRODIGISOFT TUTORIAL</h1>");
client.println("");
client.println("<body><h1>NodeMCU-ESP8266 As a  WIFI Webserver to Control LED</h1>");
client.println(" CONTROL LED: ");
  if(value == HIGH)
  {
    client.print("ON");
  }
 else
  {
    client.print("OFF");
 }
 client.println("<br><br>");
 client.println("<a href=\"/LED=ON\"\"><button\">ON</button></a>");
 client.println("<a href=\"/LED=OFF\"\"><button\">OFF</button></a><br />");
 
 client.println("<a href=\"/state=foward\"\"><button\">Forward</button></a><br />");
 client.println("<a href=\"/state=back\"\"><button\">Back</button></a><br />");
 client.println("<a href=\"/state=left\"\"><button\">Left</button></a><br />");
 client.println("<a href=\"/state=right\"\"><button\">Right</button></a><br />");
 client.println("<a href=\"/state=stop\"\"><button\">Stop</button></a><br />");
 
client.print("</center>");
  client.println("</html>");
 delay(1);
 Serial.println("Client disonnected");
 Serial.println("");
}
