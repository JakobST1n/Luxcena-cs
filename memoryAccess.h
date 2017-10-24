/*
    memoryAccess.h - Library for easy writing to the IOT-ClapSensor EEPROM
*/
#ifndef memoryAccess_h
#define memoryAccess_h

#include "Arduino.h"

class memoryAccess {
    public:
        void init();
        void write(int location, byte val);
        void commit();
        bool writeAscii(String varName, String data);
        String readAscii(String varName);
        void dump();
    private:
        struct memoryAdress getAdress(String varName);
};

struct memoryAdress {
    int startPos;
    int endPos;
};

#endif
