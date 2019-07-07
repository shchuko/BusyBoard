#include <Arduino.h>
#include <DFMiniMp3.h>
#include <Keypad.h>


#include "User_Setup.h"


/**
 * KEYPAD LIB COMPILE TEST
 */
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
        {'0','1','2','3'},
        {'4','5','6','7'},
        {'8','9','A','B'},
        {'C','D','E','F'}
};
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

/**
 * DFPLAYER LIB COMPILE TEST
 */
class Mp3Notify
{
public:
    static void OnError(uint16_t errorCode)
    {
        // see DfMp3_Error for code meaning
        Serial.print("Com Error ");
        Serial.println(errorCode);
    }
    static void OnPlayFinished(uint16_t track)
    {
        Serial.print("Play finished for #");
        Serial.println(track);
    }
    static void OnCardOnline(uint16_t code)
    {
        Serial.println("Card online ");
    }
    static void OnUsbOnline(uint16_t code)
    {
        Serial.println("USB Disk online ");
    }
    static void OnCardInserted(uint16_t code)
    {
        Serial.println("Card inserted ");
    }
    static void OnUsbInserted(uint16_t code)
    {
        Serial.println("USB Disk inserted ");
    }
    static void OnCardRemoved(uint16_t code)
    {
        Serial.println("Card removed ");
    }
    static void OnUsbRemoved(uint16_t code)
    {
        Serial.println("USB Disk removed ");
    }
};

DFMiniMp3<HardwareSerial, Mp3Notify> mp3(Serial);

void setup(){
    mp3.begin();
    customKeypad.getKey();
}

void loop(){

}