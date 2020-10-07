#include <ESP8266WebServer.h>  // Include the WebServer library
#include <ESP8266WiFi.h>
ESP8266WebServer server;  // Create a webserver object that listens for HTTP request
const char username[]="Wifi Name"; //Name of the network or SSID(SERVICE SET IDENTIFIER)
const char password[]="radheradhe"; //Password of the wifi to connect i.e. wifi of nodemcu server
#define pin 14 // Digital pin 5 on nodemcu
bool LEDstatus = LOW;
IPAddress local_IP(192,168,4,22); //local_ip - IP address of the soft access point
IPAddress gateway(192,168,4,22); //gateway - gateway IP address
IPAddress subnet(255,255,255,0); //subnet - subnet mask
void setup() {
    pinMode(pin,OUTPUT);
    Serial.begin(115200);
  Serial.println("Eh oh");
    WiFi.softAP(username,password);//create access point
    /*The ESP8266 that creates its own WiFi network and acts 
    as a hub (Just like WiFi router) for one or more stations
     is called Access Point (AP).*/
    Serial.println("Connected");
    /*IPAddress myIP=WiFi.softAPIP(); //It  provide IP address of ESP8266’s soft-AP
    //Here IPAddress acts as a datatype like int
    Serial.print("Soft-AP IP address= ");
    Serial.println(myIP);*/
  WiFi.softAPConfig(local_IP,gateway,subnet);
  delay(100);
  //WiFi.begin(username,password);
  Serial.print("Changed IP Address");
  Serial.println(local_IP);
    server.begin();   // Actually start the server
    server.on("/led",led); // Call the 'led' function when a client requests URI "/"
   // server.on("/led?state=0",handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  //server.on("/led?state=1",handleLEDoff);
}
void loop() {
    server.handleClient(); //Listen for HTTP requests from clients
    // Acts as a guy whether he/she will accept an instagram request or not
}
void led() {
    String myhtml="<!DOCTYPE html><head><title>LED Control</title></head><body style=\"background-color:powderblue;\"><h1 style=\"font-size:22;color:black;\"><center>ESP8266 Web Server</center></h1><h2 style=\"font-size:16;color:black;font-family:Tahoma;\"><center>Using Access Point(AP) Mode</center></h2><form><center>What do you want to do?<br><button style=\"font-size:15;background-color:mediumvioletred;border-color:black;color:burlywood;font-family:Georgia;border-radius:4px;\" type=\"submit\" name=\"state\" value=\"0\"> ON </button> <br> <br><button style=\"font-size:15;background-color:mediumvioletred;border-color:black;color:burlywood;font-family:Georgia,;border-radius:4px;\" type=\"submit\" name=\"state\" value=\"1\">OFF</button></center><br></form>\n";
    
server.send(200,"text/html",myhtml); //Send HTTP status 200 (Ok) and send some text to the browser/client
if(server.arg("state")=="0") //The data of the POST body can be accessed using server.arg("key")
    {
      digitalWrite(pin,HIGH);
      myhtml+="LED State:ON<br>\n";
      server.send(200,"text/html",myhtml);
    }
    else
    {
      digitalWrite(pin,LOW);
      myhtml+="LED State:OFF<br>\n";
      server.send(200,"text/html",myhtml);
    }
    myhtml+="</body></html>";
}
/*void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(pin,HIGH); //LED is connected in reverse
 server.send(200, "text/html",SendHTML(true)); //Send ADC value only to client ajax request
}
 
void handleLEDoff() { 
 Serial.println("LED off page");
 digitalWrite(pin,LOW); //LED off
 server.send(200, "text/html",SendHTML(false)); //Send ADC value only to client ajax request
}
String SendHTML(uint8_t led1stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head>\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="</head>\n";
  ptr += "<body style=\"background-color:powderblue;\">\n";
  ptr +="<h1 style=\"font-size:22;color:black;\"><center>ESP8266 Web Server</center></h1>\n";
  ptr +="<h2 style=\"font-size:16;color:black;font-family:Tahoma;\"><center>Using Access Point(AP) Mode</center></h2>\n";
  ptr +="<form>\n";
  ptr +="<center>   What do you want to do?<br>\n";
  ptr +="<button style=\"font-size:15;background-color:mediumvioletred;border-color:black;color:burlywood;font-family:Georgia;border-radius:4px;\" type=\"submit\" name-\"state\" value=\"0\"> ON </button> <br> <br>\n";
  ptr +="<button style=\"font-size:15;background-color:mediumvioletred;border-color:black;color:burlywood;font-family:Georgia;border-radius:4px;\" type=\"submit\" name=\"state\" value=\"1\">OFF</button> <br><br>\n";
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p>\n";}
  ptr +="</center>\n";
  ptr +="</form>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}*/
