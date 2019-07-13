/**
 * Helper-class created to specify DFPlayer library by Makuna (https://github.com/Makuna/DFMiniMp3)
 * Doesn't handle feedback commands from player!
 */


#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H


#include <Arduino.h>
#include <DFMiniMp3.h>
#include <EEPROM.h>


class Mp3Notify;

class CPlayer : public DFMiniMp3<HardwareSerial, Mp3Notify> {
public:
    /** Creates DFPlayer remote object
     * @param _play_next_interval - time interval between playTrack() and playTrackNext() in milliseconds
     * @param _eeprom_idx - index of eeprom cell to save/load volume level
     */
    CPlayer(uint32_t _play_next_interval, uint32_t _eeprom_idx);

    ~CPlayer();

    /** Play track + clear play queue
     * @param _track_no
     */
    void playTrack(uint8_t _track_no);

    /** Play next (maximum interval was set in the constructor)
     * @param _track_no
     */
    void playTrackNext(uint8_t _track_no);

    /** Put this method into void loop()
     *
     */
    void tick();

    void updateVolume(uint8_t _volume_level);

    bool incVolume();

    bool decVolume();

    void loadVolumeFromEEPROM();

    void saveVolumeToEEPROM(uint8_t _volume_lvl);

    void stopPlaying();

private:
    static constexpr uint8_t VOLUME_LVL_MAX = 24;
    static constexpr uint8_t VOLUME_LVL_MIN = 1;

    struct Node {
        Node *next_;
        uint8_t val_;

        explicit Node(uint8_t _val) : next_{nullptr}, val_{_val} { }
        Node() : Node(0) { }
    };

    Node *play_queue_head_;
    Node *play_queue_tail_;

    uint64_t time_counter_;
    uint32_t play_next_interval_;

    uint8_t volume_level_;
    uint8_t eeprom_idx_volume_;

    void destroyPlayQueue() {
        while (play_queue_head_ != nullptr) {
            Node *temp = play_queue_head_;
            play_queue_head_ = play_queue_head_->next_;
            delete temp;
        }
        play_queue_head_ = nullptr;
        play_queue_tail_ = nullptr;
    }

};

class Mp3Notify {
public:
    static void OnError(uint16_t errorCode) { }
    static void OnPlayFinished(uint16_t track) { }
    static void OnCardOnline(uint16_t code) { }
    static void OnUsbOnline(uint16_t code) { }
    static void OnCardInserted(uint16_t code) { }
    static void OnUsbInserted(uint16_t code) { }
    static void OnCardRemoved(uint16_t code) { }
    static void OnUsbRemoved(uint16_t code) { }
};


#endif //SRC_PLAYER_H
