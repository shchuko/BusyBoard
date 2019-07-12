#include <Arduino.h>
#include <EEPROM.h>
#include <DFMiniMp3.h>
#include <Keypad.h>
#include <CRGBLED.h>
#include <CColorsGame.h>
#include <CAnimalsGame.h>


/**
 * KEYPAD PREFERENCES
 */

// five rows and five columns
constexpr uint8_t ROWS = 5;
constexpr uint8_t COLS = 5;

// symbols related to the buttons of the keypad
constexpr char KEYPAD_KEYS[ROWS][COLS] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'J'},
        {'K', 'L', 'M', 'N', 'O'},
        {'P', 'Q', 'R', 'S', 'T'},
        {'U', 'V', 'W', 'X', 'Y'}
};

uint8_t ROW_PINS[ROWS] = {2, 3, 4, 5, 6};
uint8_t COL_PINS[COLS] = {7, 8, 12, 14, 15};


/**
 * DFPLAYER LIB COMPILE TEST
 */

class Mp3Notify {
public:
    static void OnError(uint16_t errorCode) {
//        Serial.print("Com Error ");
//        Serial.println(errorCode);
    }
    static void OnPlayFinished(uint16_t track) {
//        Serial.print("Play finished for #");
//        Serial.println(track);
    }
    static void OnCardOnline(uint16_t code) {
//        Serial.println("Card online ");
    }
    static void OnUsbOnline(uint16_t code) {
//        Serial.println("USB Disk online ");
    }
    static void OnCardInserted(uint16_t code) {
//        Serial.println("Card inserted ");
    }
    static void OnUsbInserted(uint16_t code) {
//        Serial.println("USB Disk inserted ");
    }
    static void OnCardRemoved(uint16_t code) {
//        Serial.println("Card removed ");
    }
    static void OnUsbRemoved(uint16_t code) {
//        Serial.println("USB Disk removed ");
    }
};

// comment this define if you need to write default dfplayer volume level into EEPROM
#define DF_VOLUME_EEPROM_WRITTEN
constexpr uint8_t DF_VOLUME_EEPROM_IDX = 0;

// default volume level
uint8_t df_volume_lvl = 15;

/* Service sounds tracks no */
constexpr uint8_t NUMBERS_TRACKS_NO[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
constexpr uint8_t FATAL_ERROR_TRACK_NO = 11;
constexpr uint8_t CORRECT_ANSW_TRACK_NO = 12;
constexpr uint8_t WRONG_ANSW_TRACK_NO = 12;
constexpr uint8_t GAME_START_TRACK_NO = 14;
constexpr uint8_t LEARN_START_TRACK_NO = 15;
constexpr uint8_t SWITCH_SOUND_TRACK_NO = 16;

/**
 * COLORS GAME PREFERENCES
 */

/* INDICATION LED PINS */
constexpr uint8_t COLORS_MODE_LED_GREEN_PIN = 17;
constexpr uint8_t COLORS_MODE_LED_RED_PIN = 18;
constexpr uint8_t COLORS_SOUND_LED_PIN = 19;

constexpr uint8_t COLORS_COUNT = 11;
const CRGBLED::Color colors[COLORS_COUNT] = {
        {0, 0, 0},      // disabled
        {60, 0, 100},   // violet
        {100, 0, 15},   // crimson
        {100, 0, 0},    // red
        {100, 20, 0},   // orange
        {100, 100, 0},  // yellow
        {0, 100, 0},    // green
        {20, 100, 20},  // turquoise
        {0, 50, 100},   // blue
        {0, 0, 100},    // dark blue
        {90, 100, 100} // corrected white
//        {100, 100, 100} // white
};

constexpr uint8_t COLORS_TRACKS_NO[COLORS_COUNT] = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

constexpr char COLORS_KEYS[COLORS_COUNT] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'K', 'L', 'M'};
constexpr char COLORS_GAME_MODE_KEY = 'I';
constexpr char COLORS_GAME_SOUND_KEY = 'J';


/**
 * ANIMALS GAME PREFERENCES
 */

/* INDICATION LED PINS */
constexpr uint8_t ANIMALS_MODE_LED_GREEN_PIN = 13;
constexpr uint8_t ANIMALS_MODE_LED_RED_PIN = 16;

constexpr uint8_t ANIMALS_COUNT = 6;

constexpr char ANIMALS_KEYS[ANIMALS_COUNT] = {'P', 'Q', 'R', 'S', 'T', 'Y'};
constexpr char ANIMALS_GAME_MODE_KEY = 'U';
constexpr char ANIMALS_SWITCH_TRACKLIST_KEY = 'X';

constexpr uint8_t ANIMALS_TRACKS_NO[ANIMALS_COUNT] = {28, 29, 30, 31, 32, 33};
constexpr uint8_t ANIMALS_ADDITIONAL_TRACKS_NUMS[ANIMALS_COUNT] = {34, 35, 36, 37, 38, 39};

/**
 * OTHER
 */
enum class BoardFocus {CColorsGame, CAnimalsGame, None};

Keypad keypad(makeKeymap(KEYPAD_KEYS), ROW_PINS, COL_PINS, ROWS, COLS);
DFMiniMp3<HardwareSerial, Mp3Notify> df_player(Serial);
CRGBLED rgb_led(9, 10, 11);
BoardFocus board_focus;


void setup() {
    // indication LEDs setup
    pinMode(ANIMALS_MODE_LED_GREEN_PIN, OUTPUT);
    pinMode(ANIMALS_MODE_LED_RED_PIN, OUTPUT);

    digitalWrite(ANIMALS_MODE_LED_GREEN_PIN, HIGH);
    digitalWrite(ANIMALS_MODE_LED_RED_PIN, HIGH);

    pinMode(COLORS_MODE_LED_GREEN_PIN, OUTPUT);
    pinMode(COLORS_MODE_LED_RED_PIN, OUTPUT);
    pinMode(COLORS_SOUND_LED_PIN, OUTPUT);

    digitalWrite(COLORS_MODE_LED_GREEN_PIN, HIGH);
    digitalWrite(COLORS_MODE_LED_RED_PIN, HIGH);
    digitalWrite(COLORS_SOUND_LED_PIN, HIGH);

    // DFPlayer setup
    df_player.begin();
#ifndef DF_VOLUME_EEPROM_WRITTEN
    EEPROM.put(DF_VOLUME_EEPROM_IDX, df_volume_lvl);
#endif

#ifdef DF_VOLUME_EEPROM_WRITTEN
    EEPROM.get(DF_VOLUME_EEPROM_IDX, df_volume_lvl);
#endif
    df_player.setVolume(df_volume_lvl);

    // RGB LED setup
    rgb_led.setColor(colors[0]);

    // Set board focus to None
    board_focus = BoardFocus::None;
}

void loop() {
    // Simple test for keypad, DFPlayer and RGB LED
    char key = keypad.getKey();

    if (key == 'A') {
        df_player.playMp3FolderTrack(1);
        rgb_led.setColor(colors[3]);
    }

    if (key == 'B') {
        df_player.pause();
        rgb_led.setColor(colors[2]);
    }

    if (key == 'C') {
        df_player.start();
        rgb_led.setColor(colors[1]);
    }
}