#include <Arduino.h>
#include <EEPROM.h>
#include <CPlayer.h>
#include <Keypad.h>
#include <CRGBLED.h>
#include <CColorsGame.h>
#include <CAnimalsGame.h>


/**
 * MACRO
 */
#define RANDOM_SEED     analogRead(A6)
#define LED_ON(PIN)     digitalWrite((PIN), LOW)
#define LED_OFF(PIN)    digitalWrite((PIN), HIGH)
#define LED_ENABLE_IF(EXPR, PIN)    { if ((EXPR)) LED_ON(PIN); else LED_OFF(PIN); }


/**
 * KEYPAD PREFERENCES
 */
// five rows and five columns
constexpr uint8_t KEYPAD_ROWS = 5;
constexpr uint8_t KEYPAD_COLS = 5;

// symbols related to the buttons of the keypad
constexpr char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'J'},
        {'K', 'L', 'M', 'N', 'O'},
        {'P', 'Q', 'R', 'S', 'T'},
        {'U', 'V', 'W', 'X', 'Y'}
};

uint8_t ROW_PINS[KEYPAD_ROWS] = {2, 3, 4, 5, 6};
uint8_t COL_PINS[KEYPAD_COLS] = {7, 8, 12, 14, 15};


/**
 * DFPLAYER PREFERENCES
 */
// uncomment this define if you need to write default volume level into EEPROM
//#define PLAYER_VOLUME_LEVEL_DEFAULT 15

constexpr uint32_t PLAYER_EEPROM_CELL_IDX = 0;

/* Volume change keys */
constexpr char PLAYER_INC_VOL_KEY = 'N';
constexpr char PLAYER_DEC_VOL_KEY = 'O';

/* Basic sounds tracks */
constexpr uint8_t PLAYER_NUMBERS_TRACKS_NO[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
constexpr uint8_t PLAYER_CHOOSE_TRACK_NO = 12;
constexpr uint8_t PLAYER_CORRECT_ANSW_TRACK_NO = 13;
constexpr uint8_t PLAYER_WRONG_ANSW_TRACK_NO = 14;
constexpr uint8_t PLAYER_TESTING_START_TRACK_NO = 15;
constexpr uint8_t PLAYER_LEARN_START_TRACK_NO = 16;
constexpr uint8_t PLAYER_SYSTEM_SOUND_TRACK_NO = 17;

/* Time intervals settings */
constexpr uint32_t PLAYER_WAIT_BEFORE_PLAY_NEXT_MILLIS = 2000;


/**
 * COLORS GAME PREFERENCES
 */
/* Indication LED pins */
constexpr uint8_t COLORS_MODE_LED_GREEN_PIN = 17;
constexpr uint8_t COLORS_MODE_LED_RED_PIN = 18;
constexpr uint8_t COLORS_SOUND_LED_PIN = 19;

/* Colors settings */
constexpr uint8_t COLORS_COUNT = 11;
const CRGBLED::Color COLORS_CLRS[COLORS_COUNT] = {
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

/* Soundtracks */
constexpr uint8_t COLORS_TRACKS_NO[COLORS_COUNT] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

/* Keys commands settings */
constexpr char COLORS_COMMANDS[COLORS_COUNT] = {'A', 'L', 'D', 'C', 'G', 'M', 'K', 'H', 'F', 'E', 'B'};
constexpr char COLORS_GAME_MODE_CMD = 'I';
constexpr char COLORS_GAME_SOUND_CMD = 'J';


/**
 * ANIMALS GAME PREFERENCES
 */
/* Indication LED pins */
constexpr uint8_t ANIMALS_MODE_LED_GREEN_PIN = 13;
constexpr uint8_t ANIMALS_MODE_LED_RED_PIN = 16;

constexpr uint8_t ANIMALS_COUNT = 6;

/* Keys commands */
constexpr char ANIMALS_COMMAND[ANIMALS_COUNT] = {'P', 'Q', 'R', 'S', 'T', 'Y'};
constexpr char ANIMALS_GAME_MODE_CMD = 'U';
constexpr char ANIMALS_SWITCH_TRACKLIST_CMD = 'X';

/* Soundtracks */
constexpr uint8_t ANIMALS_TRACKLST1[ANIMALS_COUNT] = {29, 30, 31, 32, 33, 34};
constexpr uint8_t ANIMALS_TRACKLST2[ANIMALS_COUNT] = {35, 36, 37, 38, 39, 40};


Keypad keypad(makeKeymap(KEYPAD_KEYS), ROW_PINS, COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);
CPlayer player(PLAYER_WAIT_BEFORE_PLAY_NEXT_MILLIS, PLAYER_EEPROM_CELL_IDX);
CRGBLED rgb_led(9, 10, 11);
CColorsGame<CRGBLED, CRGBLED::Color, CPlayer> colors_game;


CColorsGameMode colors_game_mode;
bool colors_game_sound;


void setup() {
    int *x = new int;
    delete(x);
    // indication LEDs setup
    pinMode(ANIMALS_MODE_LED_GREEN_PIN, OUTPUT);
    pinMode(ANIMALS_MODE_LED_RED_PIN, OUTPUT);

    LED_OFF(ANIMALS_MODE_LED_GREEN_PIN);
    LED_OFF(ANIMALS_MODE_LED_RED_PIN);

    pinMode(COLORS_MODE_LED_GREEN_PIN, OUTPUT);
    pinMode(COLORS_MODE_LED_RED_PIN, OUTPUT);
    pinMode(COLORS_SOUND_LED_PIN, OUTPUT);

    LED_OFF(COLORS_MODE_LED_GREEN_PIN);
    LED_OFF(COLORS_MODE_LED_RED_PIN);
    LED_OFF(COLORS_SOUND_LED_PIN);

    // DFPlayer setup
    player.begin();
#ifdef PLAYER_VOLUME_LEVEL_DEFAULT
    player.saveVolumeToEEPROM(PLAYER_VOLUME_LEVEL_DEFAULT);
#else
    player.loadVolumeFromEEPROM();
#endif

    // ColorsGame setup
    colors_game.init(rgb_led, COLORS_COUNT, COLORS_CLRS, COLORS_COMMANDS, COLORS_GAME_MODE_CMD, RANDOM_SEED);
    colors_game.addPlayer(player);
    colors_game.addSoundTracks(COLORS_TRACKS_NO, PLAYER_LEARN_START_TRACK_NO, PLAYER_TESTING_START_TRACK_NO,
            PLAYER_CHOOSE_TRACK_NO, PLAYER_CORRECT_ANSW_TRACK_NO, PLAYER_WRONG_ANSW_TRACK_NO);
    colors_game.addSoundDisableCommand(COLORS_GAME_SOUND_CMD);

    colors_game_mode = colors_game.getMode();
    colors_game_sound = colors_game.isSoundEnabled();
    LED_ON((colors_game_mode == CColorsGameMode::Learn) ? COLORS_MODE_LED_GREEN_PIN : COLORS_MODE_LED_RED_PIN);
    LED_OFF((colors_game_mode == CColorsGameMode::Learn) ? COLORS_MODE_LED_RED_PIN : COLORS_MODE_LED_GREEN_PIN);
    LED_ENABLE_IF(colors_game_sound, COLORS_SOUND_LED_PIN);

}

void loop() {
    player.tick();

    char key = keypad.getKey();
    if (!key) {
        return;
    }

    if (colors_game.tick(key)) {
        if (colors_game_mode != colors_game.getMode()) {
            colors_game_mode = colors_game.getMode();
            LED_ON((colors_game_mode == CColorsGameMode::Learn) ? COLORS_MODE_LED_GREEN_PIN : COLORS_MODE_LED_RED_PIN);
            LED_OFF((colors_game_mode == CColorsGameMode::Learn) ? COLORS_MODE_LED_RED_PIN : COLORS_MODE_LED_GREEN_PIN);
        }

        if (colors_game_sound != colors_game.isSoundEnabled()) {
            colors_game_sound = colors_game.isSoundEnabled();
            LED_ENABLE_IF(colors_game_sound, COLORS_SOUND_LED_PIN);
        }
    }

    if (key == PLAYER_INC_VOL_KEY && player.incVolume()) {
        player.playTrack(PLAYER_SYSTEM_SOUND_TRACK_NO);
    }

    if (key == PLAYER_DEC_VOL_KEY && player.decVolume()) {
        player.playTrack(PLAYER_SYSTEM_SOUND_TRACK_NO);
    }

}