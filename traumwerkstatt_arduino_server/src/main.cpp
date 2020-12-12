#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* ESP network SSID. ESP is in AP mode! */
const char* ssid = "ReachOut-ESP8266"; 
/* Network password */
const char* password = "12345678";

ESP8266WebServer server(80);

const char * userId[] =
{
  "0xF0",
  "0xF1",
  "0xF2",
  "0xF3",
  "0xF4",
  "0xFA",
  "0xFB",
  "0xFC"
};

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
        "background: radial-gradient(circle, rgba(238,174,202,1) 0%, rgba(148,187,233,1) 100%);"
        "width: 100%;"
        "height: 100%;"
        "margin: 0px;"
        "border: none;"
      "}"
      ".button {"
        "background: radial-gradient(circle, #a1c4fd 0%, #c2e9fb 100%);"
        "border: none;"
        "color: cornsilk;"
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
  Serial.println(userId[0]);

  /* Forward back to root path */
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
  
  return;
}
