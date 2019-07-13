/**
 * Educating game for children
 * Helps to learn animals' names and sounds
 *
 * Has two modes:
 * - Educating
 * - Teting
 *
 * Notes:
 *  - PlayerT must have playTrack(),  playTrackNext(), stopPlaying() methods
 *  - C++11 required
 */

#ifndef SRC_CANIMALSGAME_H
#define SRC_CANIMALSGAME_H


#include <Arduino.h>
#include <EEPROM.h>


/** CColorsGame Mode enum **/
enum class CAnimalsGameMode{Learn, Test};


template <typename PlayerT>
class CAnimalsGame {
public:

    /** Connects player to the ColorsGame
     * @param _player - player object
     * @param _animals_count
     * @param _learn_soundpacks_cnt - count of soundpacks to be used while game playing in Learn mode
     * @param _test_soundpacks_cnt - count of soundpacks to be used while game playing in Teach mode
     * @param _eeprom_addr - EEPROM index to save soundpack indexes (TWO BYTES REQUIRED: _eeprom_addr, _eeprom_addr + 1)
     */
    CAnimalsGame(PlayerT &_player, uint8_t _animals_count, uint8_t _learn_soundpacks_cnt,
            uint8_t _test_soundpacks_cnt, int16_t _eeprom_addr = -1);

    ~CAnimalsGame();

    /** Restores saved data from EEPROM
     */
    void loadDataFromEEPROM();

    /** Clears eeprom memory to be used to save data
     * (memory cells will be filled by zeroes)
     */
    void eepromClear();
    /**
     * @param _animals_commands - array of char commands related with sounds by index
     * @param _switch_mode_cmd - use this command to switch gameMode
     * @param _switch_soundpack_cmd - use this command to change loaded soundpack
     */
    void loadCommands(const char *_animals_commands, char _switch_mode_cmd, char _switch_soundpack_cmd);

    /** Saves soundtracks for basic actions
     * @param _learn_track_no - learning start notification track no
     * @param _test_track_no - testing start notification track no
     * @param _correct_answ_track_no - correct answer notification track no
     * @param _wrong_answ_track_no - wrong answer notification track no
     */
    void loadBasicSounds(uint8_t _learn_track_no, uint8_t _test_track_no, uint8_t _correct_answ_track_no,
            uint8_t _wrong_answ_track_no);

    /** Enables sound notification while changing learn soundpack
     * @param _tracklist - array of sounds related with soundpacks by indexes
     */
    void loadLearnSoundpackSwitchTracks(const uint8_t *_tracklist);

    /** Enables sound notification while changing test soundpack
     * @param _tracklist - array of sounds related with soundpacks by indexes
    */
    void loadTestSoundpackSwitchTracks(const uint8_t *_tracklist);

    /**
     * @param _track_nums - array of tracks for learn mode
     * @param _pack_no - pack number
     */
    void addLearnSoundPack(uint8_t _pack_no, const uint8_t *_track_nums);

    /**
     * @param _track_nums - array of tracks for test mode
     * @param _pack_no - pack number
     * @param _choose_soundtrack_no - sound will be played before animal sound from _track_nums
     */
    void addTestSoundPack(uint8_t _pack_no, const uint8_t *_track_nums, uint8_t _choose_soundtrack_no);

    void loadRandomSeed(unsigned long _seed);

    /** Call this method after commands and sounpacks loading
     */
    void init();

    /** Add this func to void loop() to play the game
     * @param _command
     */
    bool tick(char _command);

    /**
     * @return Current GameMode
     */
    CAnimalsGameMode getMode() const;

    /** Sets AnimalsGame state to the default:
     *  - mode_: Learning
     */
    void reset();


private:
    PlayerT *player_;
    uint8_t animals_cnt_;
    bool ready_to_play_;

    int16_t eeprom_address_;

    const char *animals_commands_;
    char switch_mode_command_;
    char switch_soundpack_command_;

    uint8_t learn_soundpacks_cnt_;
    bool *learn_soundpacks_loaded_flags_;
    uint8_t **learn_soundpacks_;
    const uint8_t *switch_learn_soundpack_tracks_;
    uint8_t curr_learn_soundpack_;

    uint8_t test_soundpacks_cnt_;
    bool *test_soundpacks_loaded_flags_;
    uint8_t **test_soundpacks_;
    uint8_t *test_choose_sounds_;
    const uint8_t *switch_test_soundpack_tracks;
    uint8_t curr_test_soundpack_;

    uint8_t test_mode_animal_idx_;

    bool is_last_answer_correct_;
    CAnimalsGameMode mode_;

    uint8_t learn_track_no_;
    uint8_t test_track_no_;
    uint8_t correct_answ_track_no_;
    uint8_t wrong_answ_track_no_;


    void switchMode();

    void switchSoundpack();

    void handleAnimalCommand(uint8_t _animal_idx);

    void learnModeHandleCommand(uint8_t _animal_idx);

    void testModeCheck(uint8_t _animal_idx);

    void testModeNewAnimal();

};

template<typename PlayerT>
CAnimalsGame<PlayerT>::CAnimalsGame(PlayerT &_player, uint8_t _animals_count, uint8_t _learn_soundpacks_cnt,
                                    uint8_t _test_soundpacks_cnt, int16_t _eeprom_addr)
        : player_{&_player}
        , eeprom_address_{_eeprom_addr}
        , animals_cnt_{_animals_count}
        , animals_commands_{nullptr}
        , switch_mode_command_{0}
        , switch_soundpack_command_{0}
        , ready_to_play_{false}
        , learn_soundpacks_cnt_{_learn_soundpacks_cnt}
        , learn_soundpacks_loaded_flags_{new bool[_learn_soundpacks_cnt]}
        , switch_learn_soundpack_tracks_{nullptr}
        , learn_soundpacks_{new uint8_t*[_learn_soundpacks_cnt]}
        , curr_learn_soundpack_{0}
        , test_soundpacks_cnt_{_test_soundpacks_cnt}
        , test_soundpacks_loaded_flags_{new bool[_test_soundpacks_cnt]}
        , test_soundpacks_{new uint8_t*[_test_soundpacks_cnt]}
        , test_choose_sounds_{new uint8_t[_test_soundpacks_cnt]}
        , switch_test_soundpack_tracks{nullptr}
        , curr_test_soundpack_{0}
        , test_mode_animal_idx_{0}
        , is_last_answer_correct_{false}
        , learn_track_no_{0}
        , test_track_no_{0}
        , correct_answ_track_no_{0}
        , wrong_answ_track_no_{0}
        , mode_{CAnimalsGameMode::Learn}
{
    for (uint8_t i = 0; i < learn_soundpacks_cnt_; ++i) {
        test_soundpacks_loaded_flags_[i] = false;
    }

    for (uint8_t i = 0; i < test_soundpacks_cnt_; ++i) {
        learn_soundpacks_loaded_flags_[i] = false;
    }
}

template<typename PlayerT>
CAnimalsGame<PlayerT>::~CAnimalsGame() {
    delete[] learn_soundpacks_;
    delete[] test_soundpacks_;
    delete[] test_choose_sounds_;
}

template<typename PlayerT>
void
CAnimalsGame<PlayerT>::loadCommands(const char *_animals_commands, char _switch_mode_cmd, char _switch_soundpack_cmd) {
    animals_commands_ = _animals_commands;
    switch_mode_command_ = _switch_mode_cmd;
    switch_soundpack_command_ = _switch_soundpack_cmd;
}

template<typename PlayerT>
void
CAnimalsGame<PlayerT>::loadBasicSounds(uint8_t _learn_track_no, uint8_t _test_track_no, uint8_t _correct_answ_track_no,
                                       uint8_t _wrong_answ_track_no) {
    learn_track_no_ = _learn_track_no;
    test_track_no_ = _test_track_no;
    correct_answ_track_no_ = _correct_answ_track_no;
    wrong_answ_track_no_ = _wrong_answ_track_no;
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::loadLearnSoundpackSwitchTracks(const uint8_t *_tracklist) {
    switch_learn_soundpack_tracks_ = _tracklist;
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::loadTestSoundpackSwitchTracks(const uint8_t *_tracklist) {
    switch_test_soundpack_tracks = _tracklist;
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::addLearnSoundPack(uint8_t _pack_no, const uint8_t *_track_nums) {
    if (learn_soundpacks_loaded_flags_[_pack_no]) {
        return;
    }
    learn_soundpacks_[_pack_no] = const_cast<uint8_t*>(_track_nums);
    learn_soundpacks_loaded_flags_[_pack_no] = true;
}

template<typename PlayerT>
void
CAnimalsGame<PlayerT>::addTestSoundPack(uint8_t _pack_no, const uint8_t *_track_nums, uint8_t _choose_soundtrack_no) {
    if (test_soundpacks_loaded_flags_[_pack_no]) {
        return;
    }
    test_soundpacks_[_pack_no] = const_cast<uint8_t*>(_track_nums);
    test_choose_sounds_[_pack_no] =  _choose_soundtrack_no;
    test_soundpacks_loaded_flags_[_pack_no] = true;
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::loadRandomSeed(unsigned long _seed) {
    randomSeed(_seed);
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::init() {
    ready_to_play_ = true;
}

template<typename PlayerT>
bool CAnimalsGame<PlayerT>::tick(char _command) {
    if (!ready_to_play_) {
        return false;
    }

    if (_command == switch_mode_command_) {
        switchMode();
        return true;
    }

    if (_command == switch_soundpack_command_) {
        switchSoundpack();
        return true;
    }

    for (uint8_t i = 0; i < animals_cnt_; ++i) {
        if (_command == animals_commands_[i]) {
            handleAnimalCommand(i);
            return true;
        }
    }
    return false;
}

template<typename PlayerT>
CAnimalsGameMode CAnimalsGame<PlayerT>::getMode() const {
    return mode_;
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::reset() {
    mode_ = CAnimalsGameMode::Learn;
    player_->stopPlaying();
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::switchMode() {
    if (mode_ == CAnimalsGameMode::Learn) {
        mode_ = CAnimalsGameMode::Test;
        player_->playTrack(test_track_no_);
        testModeNewAnimal();
        return;
    }

    if (mode_ == CAnimalsGameMode::Test) {
        mode_ = CAnimalsGameMode::Learn;
        player_->playTrack(learn_track_no_);
    }
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::switchSoundpack() {
    if (mode_ == CAnimalsGameMode::Learn) {
        ++curr_learn_soundpack_;
        if (curr_learn_soundpack_ == learn_soundpacks_cnt_) {
            curr_learn_soundpack_ = 0;
        }
        if (eeprom_address_ != -1) {
            EEPROM.update(eeprom_address_, curr_learn_soundpack_);
        }
        player_->playTrack(switch_learn_soundpack_tracks_[curr_learn_soundpack_]);
        return;
    }

    if (mode_ == CAnimalsGameMode::Test) {
        ++curr_test_soundpack_;
        if (curr_test_soundpack_ == test_soundpacks_cnt_) {
            curr_test_soundpack_ = 0;
        }
        if (eeprom_address_ != -1) {
            EEPROM.update(eeprom_address_ + 1, curr_test_soundpack_);
        }
        player_->playTrack(switch_test_soundpack_tracks[curr_test_soundpack_]);
        testModeNewAnimal();
    }
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::handleAnimalCommand(uint8_t _animal_idx) {
    if (mode_ == CAnimalsGameMode::Learn) {
        learnModeHandleCommand(_animal_idx);
        return;
    }

    if (mode_ == CAnimalsGameMode::Test) {
        testModeCheck(_animal_idx);
    }
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::learnModeHandleCommand(uint8_t _animal_idx) {
    player_->playTrack(learn_soundpacks_[curr_learn_soundpack_][_animal_idx]);
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::testModeCheck(uint8_t _animal_idx) {
    if (_animal_idx == test_mode_animal_idx_) {
        is_last_answer_correct_ = true;
        player_->playTrack(correct_answ_track_no_);

        testModeNewAnimal();
    }
    else {
        is_last_answer_correct_ = false;
        player_->playTrack(wrong_answ_track_no_);
    }
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::testModeNewAnimal() {
    test_mode_animal_idx_= random(animals_cnt_);
    player_->playTrackNext(test_choose_sounds_[curr_test_soundpack_]);
    player_->playTrackNext(test_soundpacks_[curr_test_soundpack_][test_mode_animal_idx_]);
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::loadDataFromEEPROM() {
    if (eeprom_address_ != -1) {
        EEPROM.get(eeprom_address_, curr_learn_soundpack_);
        EEPROM.get(eeprom_address_ + 1, curr_test_soundpack_);
    }
}

template<typename PlayerT>
void CAnimalsGame<PlayerT>::eepromClear() {
    if (eeprom_address_ == -1) {
        return;
    }
    EEPROM.update(eeprom_address_, 0);
    EEPROM.update(eeprom_address_ + 1, 0);
}


#endif //SRC_CANIMALSGAME_H
