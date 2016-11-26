#include <ESP8266WiFi.h>
 
const char* ssid = "XT1562 9667";
const char* password = "password";
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D5, LOW);// at start turn off the GPIO 
  digitalWrite(D6, LOW);// at start turn off the GPIO
  digitalWrite(D7, LOW);// at start turn off the GPIO 
  digitalWrite(D8, LOW);// at start turn off the GPIO
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
    
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request

  
    if (request.indexOf("/ROBOT=FORWARD") != -1) { //checks if you clicked FORWARD
        digitalWrite(D5, HIGH);
      digitalWrite(D6, LOW);
      digitalWrite(D7, LOW);
      digitalWrite(D8, HIGH);
      //Serial.println("You clicked FORWARD");
    }
  

  if (request.indexOf("/ROBOT=BACKWARD") != -1) { //checks if you clicked BACKWARD
       digitalWrite(D5, LOW);
      digitalWrite(D6, HIGH);
      digitalWrite(D7, HIGH);
      digitalWrite(D8, LOW);
  
     // Serial.println("You clicked BACKWARD");
     
  }

     
    if (request.indexOf("/ROBOT=LEFT") != -1) { //checks if you clicked LEFT
       digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);
      digitalWrite(D7, LOW);
      digitalWrite(D8, HIGH);
      //Serial.println("You clicked LEFT");
      }


      
    if (request.indexOf("/ROBOT=RIGHT") != -1) { //checks if you clicked RIGHT
        digitalWrite(D5, HIGH);
      digitalWrite(D6, LOW);
      digitalWrite(D7, LOW);
      digitalWrite(D8, LOW);
      //Serial.println("You clicked RIGHT");
      }




      
    if (request.indexOf("/ROBOT=STOP") != -1) { //checks if you clicked STOP
        digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);
      digitalWrite(D7, LOW);
      digitalWrite(D8, LOW);
      //Serial.println("You clicked STOP");
    
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
   
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  //client.print("ROBOT IS NOW: ");
   
  /*if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");*/
  
  client.println("<br><br>");
  client.println("Click <a href=\"/ROBOT=FORWARD\">here</a> to move the ROBOT FORWARD<br>");
  client.println("Click <a href=\"/ROBOT=BACKWRD\">here</a> to move the ROBOT BACKWARD<br>");
  client.println("Click <a href=\"/ROBOT=LEFT\">here</a> to move the ROBOT LEFT<br>");
  client.println("Click <a href=\"/ROBOT=RIGHT\">here</a> to move the ROBOT RIGHT<br>");
  client.println("Click <a href=\"/ROBOT=STOP\">here</a> to move the ROBOT STOP<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
    
    
    }
