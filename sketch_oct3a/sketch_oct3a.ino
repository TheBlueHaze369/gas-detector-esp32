#include <WiFi.h>
#include <ESP32Servo.h>


const char* ssid = "sample";
const char* password = "sample";


const int mq2Pin = 34;      
const int redLedPin = 22;   
const int greenLedPin = 21; 
const int buzzerPin = 23;   
const int servoPin = 18;   


const int threshold = 220; 


Servo safetyServo;


WiFiServer server(80);

void setup() {
 
  Serial.begin(115200);
  
  
  pinMode(mq2Pin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  
  safetyServo.attach(servoPin);
  safetyServo.write(0); 
  
  
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(buzzerPin, LOW);
  
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected successfully!");
  Serial.print("Local IP Address: http://");
  Serial.println(WiFi.localIP());
  
  
  server.begin();
  Serial.println("Web server started!");
}

void loop() {

  WiFiClient client = server.available();   
  
 
  int sensorValue = analogRead(mq2Pin);
  bool isDanger = (sensorValue > threshold);
  
  
  Serial.print("Gas Sensor Value: ");
  Serial.println(sensorValue);

  
  if (isDanger) {
    Serial.println("️ WARNING: Gas pokunnundddd!");
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    safetyServo.write(90); 
  } else {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    safetyServo.write(0);  

 
  if (client) {
    Serial.println("New Web Client Connected.");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          
          if (currentLine.length() == 0) {
            // Send HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // HTML Web Page Content 
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"3\">");
            client.println("<title>ESP32 Gas & Smoke Monitor</title>");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f4f4f9; }");
            client.println(".card { background: white; padding: 30px; border-radius: 12px; box-shadow: 0px 4px 12px rgba(0,0,0,0.1); display: inline-block; }");
            client.println("h2 { color: #333; }");
            client.println(".safe { color: #28a745; font-size: 20px; font-weight: bold; }");
            client.println(".danger { color: #dc3545; font-size: 20px; font-weight: bold; }");
            client.println("</style></head>");
            client.println("<body><div class=\"card\">");
            client.println("<h2>ESP32 Gas & Smoke Detector Dashboard</h2>");
            client.println("<p>Live Sensor Value: <strong>" + String(sensorValue) + "</strong></p>");
            
            if (isDanger) {
              client.println("<p class=\"danger\">STATUS: OODIPOKKO(VENT OPEN)</p>");
            } else {
              client.println("<p class=\"safe\">STATUS:  ENVIRONMENT SAFE (VENT CLOSED)</p>");
            }
            
            client.println("</div></body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Web Client Disconnected.");
  }
  
  delay(1000); 
}