/*  This class is made spesifically for the IOT-clapSensor
    ADRESSES
    version and others {0, 9}
    deviceGuid         {10, 19}
    deviceName         {20, 69}
    deviceLocation     {70, 119}
    SSID               {120, 269}
    Password           {270, 219}
*/
#include "Arduino.h"
#include "memoryAccess.h"
#include <EEPROM.h>

void memoryAccess::init() {
    EEPROM.begin(512);
}

struct memoryAdress memoryAccess::getAdress(String varName) {
    memoryAdress tmp;
    if      ((String) "version" == varName)        { tmp = {0, 4}; }
    else if ((String) "deviceId" == varName)       { tmp = {10, 19}; }
    else if ((String) "deviceName" == varName)     { tmp = {20, 69}; }
    else if ((String) "deviceLocation" == varName) { tmp = {70, 119}; }
    else if ((String) "SSID" == varName)           { tmp = {120, 269}; }
    else if ((String) "Password" == varName)       { tmp = {270, 319}; }
    else {
        Serial.println("");
        Serial.print("UNKNOWN MEMNAME: ");
        Serial.println(varName);
    }
    return tmp;
}

void memoryAccess::write(int location, byte val) {
    EEPROM.write(location, val);
}

bool memoryAccess::writeAscii(String varName, String data) {
    /* Write ascii string to EEPROM */
    struct memoryAdress memAdress = this->getAdress(varName);
    int LString = data.length() - 1;
    int LMemory = memAdress.endPos - memAdress.startPos;

    if (LString > LMemory) { return false; }

    int o = 0;
    for (int i = memAdress.startPos; i <= memAdress.endPos; i++) {
        byte cChar = data.charAt(o);
        if (EEPROM.read(i) != cChar) {
            EEPROM.write(i, cChar);
        }
        o++;
    }
    return true;
}

String memoryAccess::readAscii(String varName) {
    /* Read ascii string from EEPROM */
    struct memoryAdress memAdress = this->getAdress(varName);
    String buffer = "";

    for (int i = memAdress.startPos; i <= memAdress.endPos; i++) {
        char tmpByte = EEPROM.read(i);
        if (tmpByte != '\0') {
            buffer += tmpByte;
        }
    }

    return buffer;
}

void memoryAccess::commit() {
    EEPROM.commit();
}

void memoryAccess::dump() {
    Serial.println("");
    Serial.println("EEPROM DUMP:");
    for (int i = 0; i < 512; i++) {
        char cChar = EEPROM.read(i);
        String cStr = String(cChar);
        Serial.print("[" + String(i) + "]: ");
        Serial.println(String(cStr));
    }
}
