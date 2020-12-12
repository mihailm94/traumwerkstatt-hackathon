#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* ESP network SSID. ESP is in AP mode! */
const char* ssid = "ReachOut-ESP8266"; 
/* Network password */
const char* password = "12345678";

ESP8266WebServer server(80);

/* Server handler function prototypes */
void handleRootPath();  
void handleButtonPress();

/* Main page */
const char * htmlMessage =
" <!DOCTYPE html> "
"<html> "
  "<head>"
    "<title>ReachOut</title>"
    "<style>"
      "html, body {"
        "background: linear-gradient(0deg, rgba(34,193,195,1) 0%, rgba(253,187,45,1) 100%);"
        "width: 100%;"
        "height: 100%;"
        "margin: 0px;"
      "}"
      ".button {"
        "background: radial-gradient(circle, rgba(2,0,36,1) 0%, rgba(9,9,121,1) 40%, rgba(0,212,255,1) 100%);"
        "border: none;"
        "color: white;"
        "font-size: 30px;"
        "cursor: pointer;"
        "border-radius: 50%;"
        "height: 300px;"
        "width: 300px;"
        "}"
      ".parentDiv {"
        "text-align: center;"
        "height: 100%;"
        "width: 100%;"
      "}"
      ".childDiv {"
        "position: relative;"
        "top: 50%;"
        "margin-top: -150px"
      "}"
    "</style>"
  "</head>"
  "<body> "
    "<div class=\"parentDiv\">"
        "<div class=\"childDiv\">"
          "<a href=\"buttonPress\"><button class='button'>Reach Out</button></a>"
        "</div>"
    "</div>"
  "</body> "
"</html> ";

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

    /* Execute handleRootPath() when usr visits <IP>/ */
    server.on("/", handleRootPath);  

    /* Handler for when the user presses the button */
    server.on("/buttonPress", handleButtonPress);  


    server.begin();
  }
  else
  {
    Serial.println("error! Something went wrong...");
  }
}

void loop()
{
  /* Handle incoming client requests */
  server.handleClient();
}

void handleRootPath()
{
  /* Gets called when user visits <IP>/ (root path) */
  server.send(200, "text/html", htmlMessage);

  return;
}

void handleButtonPress()
{
  static int i = 0;
  Serial.println(i);
  i = i + 1;


  /* Forward back to root path */
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
  
  return;
}
