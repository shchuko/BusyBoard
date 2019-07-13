#include <Arduino.h>
#include <EEPROM.h>
#include <CPlayer.h>
#include <Keypad.h>
#include <CRGBLED.h>
#include <CColorsGame.h>
#include <CAnimalsGame.h>


/**
 * MACRO 5200
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
        {'U', 'X', 'X', 'X', 'Y'}
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
constexpr uint8_t PLAYER_NUMBERS_TRACKS_NO[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
constexpr uint8_t PLAYER_NOTIFY_TRACK_NO = 11;
constexpr uint8_t PLAYER_CHOOSE_TRACK_NO = 12;
constexpr uint8_t PLAYER_CORRECT_ANSW_TRACK_NO = 13;
constexpr uint8_t PLAYER_WRONG_ANSW_TRACK_NO = 14;
constexpr uint8_t PLAYER_TEST_START_TRACK_NO = 15;
constexpr uint8_t PLAYER_LEARN_START_TRACK_NO = 16;
constexpr uint8_t PLAYER_BEEP_TRACK_NO = 17;

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
constexpr char ANIMALS_COMMANDS[ANIMALS_COUNT] = {'P', 'Q', 'R', 'S', 'T', 'Y'};
constexpr char ANIMALS_GAME_MODE_CMD = 'U';
constexpr char ANIMALS_SWITCH_TRACKLIST_CMD = 'X';

/* Soundpacks size constants */
constexpr uint8_t ANIMALS_LEARN_SOUNDPACKS_CNT = 2;
constexpr uint8_t ANIMALS_TEST_SOUNDPACKS_CNT = 2;

/* Soundtracks */
constexpr uint8_t ANIMALS_LEARN_TRACKLST1[ANIMALS_COUNT] = {29, 30, 31, 32, 33, 34};
constexpr uint8_t ANIMALS_LEARN_TRACKLST2[ANIMALS_COUNT] = {35, 36, 37, 38, 39, 40};
constexpr uint8_t ANIMALS_TEST_TRACKLIST1[ANIMALS_COUNT] = {41, 42, 43, 44, 45, 46};
constexpr uint8_t ANIMALS_TEST1_CHOOSE_SOUND = 47;
constexpr uint8_t ANIMALS_TEST2_CHOOSE_SOUND = 48;

// uncomment this define for the first time arduino flash
//#define ANIMALS_CLEAR_EEPROM
constexpr uint8_t ANIMALS_EEPROM_ADRESS = 2;


/**
 * OTHER
 */
/* Global variables and functions */
constexpr uint32_t RESET_TIME_INTERVAL = 120000;
enum class BoardFocus{Wait, Animals, Colors};

CColorsGameMode colors_game_mode;
bool colors_game_sound;
void colorsIndicationUpd() {
    LED_ENABLE_IF(colors_game_mode == CColorsGameMode::Learn, COLORS_MODE_LED_GREEN_PIN);
    LED_ENABLE_IF(colors_game_mode == CColorsGameMode::Test, COLORS_MODE_LED_RED_PIN);
    LED_ENABLE_IF(colors_game_sound, COLORS_SOUND_LED_PIN);
}

CAnimalsGameMode animals_game_mode;
void animalsIndicationUpd() {
    LED_ENABLE_IF(animals_game_mode == CAnimalsGameMode::Learn, ANIMALS_MODE_LED_GREEN_PIN);
    LED_ENABLE_IF(animals_game_mode == CAnimalsGameMode::Test, ANIMALS_MODE_LED_RED_PIN);
}

/* Global objects */
Keypad keypad(makeKeymap(KEYPAD_KEYS), ROW_PINS, COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);
CPlayer player(PLAYER_WAIT_BEFORE_PLAY_NEXT_MILLIS, PLAYER_EEPROM_CELL_IDX);
CRGBLED rgb_led(9, 10, 11);
CColorsGame<CRGBLED, CRGBLED::Color, CPlayer> colors_game(rgb_led, COLORS_COUNT);
CAnimalsGame<CPlayer> animals_game(player, ANIMALS_COUNT, ANIMALS_LEARN_SOUNDPACKS_CNT, ANIMALS_TEST_SOUNDPACKS_CNT,
        ANIMALS_EEPROM_ADRESS);
BoardFocus board_focus;

/**
 * MAIN
 */
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
    colors_game.init(COLORS_CLRS, COLORS_COMMANDS, COLORS_GAME_MODE_CMD);
    colors_game.addPlayer(player);
    colors_game.addSoundTracks(COLORS_TRACKS_NO, PLAYER_LEARN_START_TRACK_NO, PLAYER_TEST_START_TRACK_NO,
            PLAYER_CHOOSE_TRACK_NO, PLAYER_CORRECT_ANSW_TRACK_NO, PLAYER_WRONG_ANSW_TRACK_NO);
    colors_game.addSoundDisableCommand(COLORS_GAME_SOUND_CMD);
    colors_game.loadRandomSeed(RANDOM_SEED);

    colors_game_mode = colors_game.getMode();
    colors_game_sound = colors_game.isSoundEnabled();

    // AnimalsGame setup
    animals_game.loadCommands(ANIMALS_COMMANDS, ANIMALS_GAME_MODE_CMD, ANIMALS_SWITCH_TRACKLIST_CMD);
    animals_game.loadBasicSounds(PLAYER_LEARN_START_TRACK_NO, PLAYER_TEST_START_TRACK_NO, PLAYER_CORRECT_ANSW_TRACK_NO,
            PLAYER_WRONG_ANSW_TRACK_NO);
    animals_game.addLearnSoundPack(0, ANIMALS_LEARN_TRACKLST1);
    animals_game.addLearnSoundPack(1, ANIMALS_LEARN_TRACKLST2);
    animals_game.addTestSoundPack(0, ANIMALS_LEARN_TRACKLST1, ANIMALS_TEST1_CHOOSE_SOUND);
    animals_game.addTestSoundPack(1, ANIMALS_TEST_TRACKLIST1, ANIMALS_TEST2_CHOOSE_SOUND);
    animals_game.loadLearnSoundpackSwitchTracks(PLAYER_NUMBERS_TRACKS_NO);
    animals_game.loadTestSoundpackSwitchTracks(PLAYER_NUMBERS_TRACKS_NO);
#ifdef ANIMALS_CLEAR_EEPROM
    animals_game.eepromClear();
#else
    animals_game.loadDataFromEEPROM();
#endif
    animals_game.init();
    animals_game_mode = animals_game.getMode();

    board_focus = BoardFocus::Wait;
}

void loop() {
    player.tick();

    uint64_t curr_time = millis();
    static uint64_t reset_time_counter = curr_time;

    if (curr_time - reset_time_counter > RESET_TIME_INTERVAL) {
        reset_time_counter = curr_time;
        board_focus = BoardFocus::Wait;

        colors_game.reset();
        colors_game_mode = colors_game.getMode();
        colors_game_sound = colors_game.isSoundEnabled();
        LED_OFF(COLORS_SOUND_LED_PIN);
        LED_OFF(COLORS_MODE_LED_RED_PIN);
        LED_ON(COLORS_MODE_LED_GREEN_PIN);

        animals_game.reset();
        animals_game_mode = animals_game.getMode();
        LED_OFF(ANIMALS_MODE_LED_RED_PIN);
        LED_ON(ANIMALS_MODE_LED_GREEN_PIN);

        player.playTrack(PLAYER_NOTIFY_TRACK_NO);
    }

    char key = keypad.getKey();
    if (!key) {
        return;
    }

    reset_time_counter = curr_time;
    if (board_focus == BoardFocus::Wait) {
        colorsIndicationUpd();
        animalsIndicationUpd();
        board_focus = BoardFocus::Animals;
    }

    if (colors_game.tick(key)) {
        if (board_focus != BoardFocus::Colors) {
            animals_game.reset();
            animals_game_mode = animals_game.getMode();
            animalsIndicationUpd();
            board_focus = BoardFocus::Colors;
        }
        if (colors_game_mode != colors_game.getMode()) {
            colors_game_mode = colors_game.getMode();
            colorsIndicationUpd();
        }

        if (colors_game_sound != colors_game.isSoundEnabled()) {
            colors_game_sound = colors_game.isSoundEnabled();
            colorsIndicationUpd();
        }
        return;
    }

    if (animals_game.tick(key)) {
        if (board_focus != BoardFocus::Animals) {
            colors_game.reset();
            colors_game_mode = colors_game.getMode();
            colors_game_sound = colors_game.isSoundEnabled();
            colorsIndicationUpd();
            board_focus = BoardFocus::Animals;
        }

        if (animals_game_mode != animals_game.getMode()) {
            animals_game_mode = animals_game.getMode();
            animalsIndicationUpd();
        }
    }

    if (key == PLAYER_INC_VOL_KEY && player.incVolume()) {
        player.playTrack(PLAYER_BEEP_TRACK_NO);
        return;
    }

    if (key == PLAYER_DEC_VOL_KEY && player.decVolume()) {
        player.playTrack(PLAYER_BEEP_TRACK_NO);
        return;
    }
}