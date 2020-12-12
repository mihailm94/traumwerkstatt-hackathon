#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Your WiFi Soft Access Point settings */
const char* ssid = "ReachOut-ESP8266";          //this will be the network name
const char* password = "12345678";  //this will be the network password

ESP8266WebServer server(80);

//Server handler for root address
void handleRootPath();  

void setup()
{
  delay(1000);

  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Configuring WiFi access point...");

  boolean result = WiFi.softAP(ssid, password);
  
  if(result==true)
  {
    IPAddress myIP = WiFi.softAPIP();

    Serial.println("done!");
    Serial.println("");
    Serial.print("WiFi network name: ");
    Serial.println(ssid);
    Serial.print("WiFi network password: ");
    Serial.println(password);
    Serial.print("Host IP Address: ");
    Serial.println(myIP);
    Serial.println("");

    //Associate the handler function to the path
    server.on("/", handleRootPath);  
    
    //Start the server
    server.begin();
  }
  else
  {
    Serial.println("error! Something went wrong...");
  }
}

void loop()
{
  server.handleClient();
}

void handleRootPath()
{
  char temp[1024];

  snprintf(temp, 1024,

  "<html>\
    <head>\
      <title>ReachOut</title>\
      <style>\
      </style>\
    </head>\
    <body>\
      <p>Hey Meeha</p>\
    </body>\
  </html>"
  );

  server.send(200, "text/html", temp);
}
