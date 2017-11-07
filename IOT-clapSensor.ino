#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <EEPROM.h>
#include "memoryAccess.h"

#include "style.h"     // custom stylesheet, get it from stylesheet
#include "script.h"
#include "index.h"     // Index page html, get it from MAIN_page
#include "settings.h"  // Settings page html, get it from SETTINGS_page

// User variables
const String MemoryAccessVersion = "cp-a1";
const String deviceType = "clapSensor";           // This is what kind of device it is, crucial for the homeServer when determing which API to use
const int wifiConnectionTimeout = 5;              // n*1 sec
char ssid[30];
char password[30];
char APssid[30];
String deviceName;
String deviceLocation;
String deviceId;

memoryAccess MemoryAccess;

const int lampPin = 14;   // Pin the appliance is connected to
const int sensorPin = 5;  // Pin the sensor is connected to

bool lampOn;        // Is the appliance turned on?
bool sensorActive;  // Should we care about sensor input?
bool buttonState;   // Used to make button not flash indefinetly

int sensorvalue=0;
int eventstatus = 0;
int sensorthresholdhigh = 870;
int sensorthresholdlow = 500;

ESP8266WebServer server ( 80 );  // webServer on port 80

void setup ( void ) {
    // Activate serial
    Serial.begin ( 115200 );
    //Serial.setDebugOutput(true);
    SPIFFS.begin();
    MemoryAccess.init();


    if (MemoryAccess.readAscii("version") == MemoryAccessVersion) {
        deviceName = MemoryAccess.readAscii("deviceName");
        deviceLocation = MemoryAccess.readAscii("deviceLocation");
        deviceId = MemoryAccess.readAscii("deviceId");
        MemoryAccess.readAscii("SSID").toCharArray(ssid, 30);
        MemoryAccess.readAscii("Password").toCharArray(password, 30);
        (deviceType + "-" + deviceId).toCharArray(APssid, 30);
    } else {
        // SET TO DEFAULT VALUES
        String _uniqId = uniqId();
        MemoryAccess.writeAscii("version", MemoryAccessVersion);
        MemoryAccess.writeAscii("deviceName", "clapSensor" + _uniqId);
        MemoryAccess.writeAscii("deviceLocation", "Milky way");
        MemoryAccess.writeAscii("deviceId", _uniqId);
        MemoryAccess.writeAscii("SSID", ".");
        MemoryAccess.writeAscii("Password", "");
        MemoryAccess.commit();
        Serial.println("Have set default values.");
        hardReset();
    }

    Serial.print("ssid: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);
    Serial.print("deviceName: ");
    Serial.println(deviceName);
    Serial.print("deviceLocation: ");
    Serial.println(deviceLocation);
    Serial.print("deviceId: ");
    Serial.println(deviceId);


    // Setup pins and set default values
    pinMode ( lampPin, OUTPUT );
    pinMode ( sensorPin, INPUT );
    lampOn = false; // Vil at denne skal bli husket, altså være samme etter boot
    sensorActive = true;
    digitalWrite(lampPin, lampOn);

    // Try to connect to WiFi
    WiFi.begin ( ssid, password );

    // Wait for connection
    int connTime = 0;
    while ( WiFi.status() != WL_CONNECTED ) {
        if (connTime >= wifiConnectionTimeout) { break; }
        delay ( 1000 );
        Serial.print ( "." );
        connTime++;
    }

    Serial.println ( "" );

    if ( WiFi.status() == WL_CONNECTED ) {
        Serial.print ( "Connected to " );
        Serial.println ( ssid );
        Serial.print ( "IP address: " );
        Serial.println ( WiFi.localIP() );
    } else {
        WiFi.disconnect();
        WiFi.softAP(APssid);  // add password here as second parameter, currently just a open hotspot
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("APssid: ");
        Serial.println(APssid);
        Serial.print("AP IP address: ");
        Serial.println(myIP);
    }

    if ( MDNS.begin ( "esp8266" ) ) {
        Serial.println ( "MDNS responder started" );
    }

    // Gui
    server.on ( "/", handleRoot );
    server.on ( "/settings", handleSettings );
    // Json
    server.on ( "/j/", handleJson );
    server.on ( "/j", handleJson );
    // Others
    server.on ( "/style.css", handleStylesheet );
    server.on ( "/script.js", handleScript );
    server.serveStatic("/bootstrap.css", SPIFFS, "/bootstrap.css");
    server.onNotFound ( handleNotFound );
    server.begin();
    Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  server.handleClient();

  //Serial.print("SENSOR VAL: ");
  Serial.println(analogRead(A0));
  if (sensorActive) {
    if (analogRead(A0) > 500) {
        setLamp("TOGGLE");
    }
  }

}

String uniqId() {
    randomSeed(analogRead(0));
    String _uniqId = "";
    for (int i = 0; i < 10; i++) {
        int currSet = random(1,3);
        if (currSet == 1) {
            char chr = random(48, 57);
            _uniqId += String(chr);
        } else if (currSet == 2) {
            char chr = random(65, 90);
            _uniqId += String(chr);
        } else {
            char chr = random(97, 122);
            _uniqId += String(chr);
        }
    }
    return(_uniqId);
}

void setLamp(String action) {
    if (action == "ON") {
        lampOn = true;
    } else if (action == "OFF") {
        lampOn = false;
    } else if (action == "TOGGLE") {
        lampOn = !lampOn;
    }
    digitalWrite(lampPin, lampOn);
}

void setSensor(String action) {
    if (action == "ON") {
        sensorActive = true;
    } else if (action == "OFF") {
        sensorActive = false;
    }
}

void handleRoot() {

    String bootstrapLink = "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css\" integrity=\"sha384-PsH8R72JQ3SOdhVi3uxftmaW6Vc51MKb0q5P2rRUpPvrszuE4W1povHYgTpBfshb\" crossorigin=\"anonymous\">";

    for (int i = 0; i < server.args(); i++) {
        String argKey = server.argName(i);
        String argVal = server.arg(i);
        if (argKey == "l") { bootstrapLink = "<link rel=\"stylesheet\" href=\"./bootstrap.css\">"; }
    }

    String htmlPage = MAIN_page;
    htmlPage.replace("{{NAME}}", deviceName);
    htmlPage.replace("{{Location}}", deviceLocation);
    htmlPage.replace("{{BOOTSTRAPLINK}}", bootstrapLink);
    if (lampOn) {
        htmlPage.replace("{{LAMPACTIVECHECKED}}", "checked");
    } else {
        htmlPage.replace("{{LAMPACTIVECHECKED}}", "");
    }
    if (sensorActive) {
        htmlPage.replace("{{SENSORCHECKED}}", "checked");
    } else {
        htmlPage.replace("{{SENSORCHECKED}}", "");
    }
    server.send ( 200, "text/html", htmlPage);
}

void handleJson() {
    // escape dobbel tøddler med en \ slik \" for å ha dobbel tøddler i en string

    for (int i = 0; i < server.args(); i++) {
        String argKey = server.argName(i);
        String argVal = server.arg(i);

        if (argKey == "lamp") {
            if (argVal == "1" || argVal == "true") { setLamp("ON"); }
            else if (argVal == "0" || argVal == "false") { setLamp("OFF"); }
            else if (argVal == "toggle" || argVal == "TOGGLE"){ setLamp("TOGGLE"); }
        } else if (argKey == "sens") {
            if (argVal == "1" || argVal == "true") { setSensor("ON"); }
            else { setSensor("OFF"); }
        }
    }

    String jsonAnswer = "{";
    jsonAnswer += "\"deviceName\":\"";
    jsonAnswer += deviceName;
    jsonAnswer += "\",\"deviceId\":\"";
    jsonAnswer += deviceId;
    jsonAnswer += "\",\"deviceType\":\"";
    jsonAnswer += deviceType;
    jsonAnswer += "\",\"deviceLocation\":\"";
    jsonAnswer += deviceLocation;
    jsonAnswer += "\",\"lampOn\":\"";
    jsonAnswer += (String)lampOn;
    jsonAnswer += "\",\"sensorOn\":\"";
    jsonAnswer += (String)sensorActive;
    jsonAnswer += "\"}";
    server.send ( 200, "text/html", jsonAnswer);
}

void handleSettings() {
    bool settingsSaved = false;
    String successMsg = "";
    String bootstrapLink = "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css\" integrity=\"sha384-PsH8R72JQ3SOdhVi3uxftmaW6Vc51MKb0q5P2rRUpPvrszuE4W1povHYgTpBfshb\" crossorigin=\"anonymous\">";
    String type, _deviceName, _deviceLocation, _ssid, _password;

    for (int i = 0; i < server.args(); i++) {
        String argKey = server.argName(i);
        String argVal = stripString(server.arg(i));

        if (argKey == "txtDeviceName") {
            _deviceName = argVal;
        } else if (argKey == "txtDeviceLocation") {
            _deviceLocation = argVal;
        } else if (argKey == "txtSSID") {
            _ssid = argVal;
        } else if (argKey == "txtPassword") {
            _password = argVal;
        } else if (argKey == "type") {
            type = argVal;
        } else if (argKey == "l") {
            bootstrapLink = "<link rel=\"stylesheet\" href=\"./bootstrap.css\">";
        }
    }

    if (type == "settings") {
        if (_deviceName != "") {
            MemoryAccess.writeAscii("deviceName", _deviceName);
        } else if (_deviceLocation != "") {
            MemoryAccess.writeAscii("deviceLocation", _deviceLocation);
        } else if (_ssid != "") {
            MemoryAccess.writeAscii("SSID", _ssid);
            MemoryAccess.writeAscii("Password", _password);
        }
        MemoryAccess.commit();
        successMsg = "Settings updated!";
        settingsSaved = true;
    } else {
        Serial.println("Type undefined...");
    }

    String htmlResponse = SETTINGS_page;
    htmlResponse.replace("{{NAME}}", deviceName);
    htmlResponse.replace("{{SUCCESSMSG}}", successMsg);
    htmlResponse.replace("{{DEVICENAME}}", deviceName);
    htmlResponse.replace("{{DEVICELOCATION}}", deviceLocation);
    htmlResponse.replace("{{BOOTSTRAPLINK}}", bootstrapLink);
    server.send( 200, "text/html", htmlResponse );

    if (settingsSaved) { hardReset(); }
}

void handleStylesheet() {
    String style = stylesheet;
    server.send ( 200, "text/css", style);
}

void handleScript() {
    server.send( 200, "text/javascript", main_script);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}

String stripString(String _string) {
    _string.replace("\n", "");
    return _string;
}

void hardReset() {
    Serial.println("Triggering Watchdog hard reset in 1 sec...");
    ESP.wdtDisable();
    delay(1000);
    while (1);
}
