/**
 * Educating game for children
 * Helps to learn colors
 *
 * Has two modes:
 * - Learning
 * - Testing
 *
 * Notes:
 * - PlayerT must have playTrack(),  playTrackNext(), stopPlaying() methods
 * - RGBLED_T must have setColor() method
 * - COLOR_T must have default COLOR_T() constructor
 * - C++11 required
 */


#ifndef SRC_CCOLORSGAME_H
#define SRC_CCOLORSGAME_H


#include <Arduino.h>


/** CColorsGame Mode enum **/
enum class CColorsGameMode{Learn, Test};


template <typename RGBLED_T, typename COLOR_T, typename PlayerT = void>
class CColorsGame {
public:

    CColorsGame(RGBLED_T &_rgbled, uint8_t _colors_count);

    /**
     * @param _rgbled - rgb used to play game
     * @param _colors_count - count of colors to be used in game
     * @param _colors - pointer to colors array
     * @param _colors_commands - pointer to commands array related to colors
     * @param _change_mode_command - command to be used to change game mode
     * @param _rnd_seed - random seed
     */
    void init(const COLOR_T *_colors,
              const char *_colors_commands,
              char _change_mode_command);

    void loadRandomSeed(unsigned long _rnd_seed);

    /** Connects player to the ColorsGame
     * @param _player - player object
     */
    void addPlayer(PlayerT &_player);

    /** Saves soundtracks numbers
     * SHOULD BE USED AFTER addPlayer()!
     * @param _tracks_no - array of tracks associated with colors by index
     * @param _learn_track_no - learning start notification track no
     * @param _test_track_no - testing start notification track no
     * @param _choose_track_no - 'let's choose...' sound track no
     * @param _correct_answ_track_no - correct answer notification track no
     * @param _wrong_answ_track_no - wrong answer notification track no
     */
    void addSoundTracks(const uint8_t *_tracks_no, uint8_t _learn_track_no, uint8_t _test_track_no,
                    uint8_t _choose_track_no, uint8_t _correct_answ_track_no, uint8_t _wrong_answ_track_no);

    /** Creates and enables sound enable/disable command
     * SHOULD BE USED AFTER addPlayer()!
     * @param _command - command code
     */
    void addSoundDisableCommand(char _command);

    /** Add this func to void loop() to play the game
     * @param _command
     */
    bool tick(char _command);

    /**
     * @return Current GameMode
     */
    CColorsGameMode getMode() const;

    /** Sets ColorsGame state to the default:
     *  - mode_: Learning
     *  - rgbled_: default color (COLOR_T())
     */
    void reset();

    /**
     * @return true if sound is enabled, false if disabled
     */
    bool isSoundEnabled() const;

private:
    RGBLED_T *rgbled_;
    uint8_t colors_count_;
    const COLOR_T *colors_;
    const char *colors_commands_;
    char change_mode_command_;

    uint8_t test_mode_color_idx_;
    bool is_last_answer_correct_;
    CColorsGameMode mode_;

    PlayerT *player_;
    const uint8_t *tracks_no_;
    bool sound_enabled_;
    uint8_t learn_track_no_;
    uint8_t test_track_no_;
    uint8_t choose_track_no_;
    uint8_t correct_answ_track_no_;
    uint8_t wrong_answ_track_no_;
    char sound_disable_command_;
    bool sound_disable_command_exist_;

    void changeMode();

    void handleColorCommand(uint8_t _color_idx);

    void changeColor(char _color_idx);

    void testModeCheck(uint8_t _color_idx);

    void testModeNewColor();

};


template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
CColorsGame<RGBLED_T, COLOR_T, PlayerT>::CColorsGame(RGBLED_T &_rgbled, uint8_t _colors_count)
        : rgbled_{&_rgbled}
        , colors_count_{_colors_count}
        , colors_{nullptr}
        , colors_commands_{nullptr}
        , change_mode_command_{0}
        , mode_{CColorsGameMode::Learn}
        , player_{nullptr}
        , tracks_no_{nullptr}
        , sound_disable_command_{0}
        , sound_enabled_{false}
        , learn_track_no_{0}
        , test_track_no_{0}
        , choose_track_no_{0}
        , correct_answ_track_no_{0}
        , wrong_answ_track_no_{0}
        , sound_disable_command_exist_{false}
        , test_mode_color_idx_{0}
        , is_last_answer_correct_{false}
{    }

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void
CColorsGame<RGBLED_T, COLOR_T, PlayerT>::init(const COLOR_T *_colors,
                                              const char *_colors_commands, char _change_mode_command) {
    colors_ = _colors;
    colors_commands_ = _colors_commands;
    change_mode_command_ = _change_mode_command;
    rgbled_->setColor(COLOR_T());
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::addPlayer(PlayerT &_player) {
    player_ = &_player;
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::addSoundTracks(const uint8_t *_tracks_no, uint8_t _learn_track_no,
                                                             uint8_t _test_track_no, uint8_t _choose_track_no,
                                                             uint8_t _correct_answ_track_no,
                                                             uint8_t _wrong_answ_track_no) {
    if (player_ != nullptr) {
        tracks_no_ = _tracks_no;
        learn_track_no_ = _learn_track_no;
        test_track_no_ = _test_track_no;
        choose_track_no_ = _choose_track_no;
        correct_answ_track_no_ = _correct_answ_track_no;
        wrong_answ_track_no_ = _wrong_answ_track_no;
        sound_enabled_ = true;
    }
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::addSoundDisableCommand(char _command) {
    if (player_ != nullptr) {
        sound_disable_command_ = _command;
        sound_disable_command_exist_ = true;
    }
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
bool CColorsGame<RGBLED_T, COLOR_T, PlayerT>::tick(char _command) {
    if (rgbled_ == nullptr) {
        return false;
    }
    if (_command == change_mode_command_) {
        changeMode();
        return true;
    }

    if (player_ != nullptr && sound_disable_command_exist_ && _command == sound_disable_command_) {
        sound_enabled_ = !sound_enabled_;
        return true;
    }

    for (int i = 0; i < colors_count_; ++i) {
        if (colors_commands_[i] == _command) {
            handleColorCommand(i);
            return true;
        }
    }
    return false;
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
CColorsGameMode CColorsGame<RGBLED_T, COLOR_T, PlayerT>::getMode() const {
    return mode_;
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::reset() {
    mode_ = CColorsGameMode::Learn;
    rgbled_->setColor(COLOR_T());
    player_->stopPlaying();
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
bool CColorsGame<RGBLED_T, COLOR_T, PlayerT>::isSoundEnabled() const {
    return sound_enabled_;
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::changeMode() {
    if (mode_ == CColorsGameMode::Learn) {
        mode_ = CColorsGameMode::Test;
        if (tracks_no_ != nullptr && sound_enabled_) {
            player_->playTrack(test_track_no_);
        }
        testModeNewColor();
        return;
    }

    if (mode_ == CColorsGameMode::Test) {
        mode_ = CColorsGameMode::Learn;
        if (tracks_no_ != nullptr && sound_enabled_) {
            player_->playTrack(learn_track_no_);
        }
    }
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::handleColorCommand(uint8_t _color_idx) {
    if (mode_ == CColorsGameMode::Learn) {
        changeColor(_color_idx);
        return;
    }

    if (mode_ == CColorsGameMode::Test) {
        testModeCheck(_color_idx);
    }
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::changeColor(char _color_idx) {
    rgbled_->setColor(colors_[_color_idx]);
    if (tracks_no_ != nullptr && sound_enabled_) {
        player_->playTrack(tracks_no_[_color_idx]);
    }
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::testModeCheck(uint8_t _color_idx) {
    if (_color_idx == test_mode_color_idx_) {
        is_last_answer_correct_ = true;
        if (tracks_no_ != nullptr) {
            player_->playTrack(correct_answ_track_no_);
        }

        testModeNewColor();
    }
    else {
        is_last_answer_correct_ = false;
        if (tracks_no_ != nullptr) {
            player_->playTrack(wrong_answ_track_no_);
        }
    }
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::testModeNewColor() {
    test_mode_color_idx_= random(colors_count_);
    rgbled_->setColor(colors_[test_mode_color_idx_]);

    if (tracks_no_ != nullptr) {
        player_->playTrackNext(choose_track_no_);
        player_->playTrackNext(tracks_no_[test_mode_color_idx_]);
    }
}

template<typename RGBLED_T, typename COLOR_T, typename PlayerT>
void CColorsGame<RGBLED_T, COLOR_T, PlayerT>::loadRandomSeed(unsigned long _rnd_seed) {
    randomSeed(_rnd_seed);
}

#endif //SRC_CCOLORSGAME_H
