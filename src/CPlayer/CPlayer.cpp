#include "CPlayer.h"

CPlayer::CPlayer(uint32_t _play_next_interval, uint32_t _eeprom_idx)
        : DFMiniMp3(Serial)
        , play_queue_head_{nullptr}
        , play_queue_tail_{nullptr}
        , time_counter_{0}
        , play_next_interval_{_play_next_interval}
        , eeprom_idx_volume_{_eeprom_idx}
{ }

void CPlayer::playTrack(uint8_t _track_no) {
    playMp3FolderTrack(_track_no);
    time_counter_ = millis();
    destroyPlayQueue();
}

void CPlayer::playTrackNext(uint8_t _track_no) {
    if (play_queue_head_ == nullptr) {
        play_queue_head_ = new Node(_track_no);
        play_queue_tail_ = play_queue_head_;
    }
    else {
        play_queue_tail_->next_ = new Node{_track_no};
        play_queue_tail_ = play_queue_tail_->next_;
    }
}

void CPlayer::tick() {
    if (play_queue_head_ == nullptr) {
        return;
    }

    if (millis() - time_counter_> play_next_interval_) {
        time_counter_ = millis();

        playMp3FolderTrack(play_queue_head_->val_);
        if (play_queue_head_ == play_queue_tail_) {
            play_queue_tail_ = nullptr;
        }

        Node *temp = play_queue_head_;
        play_queue_head_ = play_queue_head_->next_;
        delete temp;
    }
}

void CPlayer::loadVolumeFromEEPROM() {
    EEPROM.get(eeprom_idx_volume_, volume_level_);
}

void CPlayer::updateVolume(uint8_t _volume_level) {
    if (_volume_level > VOLUME_LVL_MAX) {
        _volume_level = VOLUME_LVL_MAX;
    }

    if (_volume_level < VOLUME_LVL_MIN) {
        _volume_level = VOLUME_LVL_MIN;
    }

    setVolume(_volume_level);
    volume_level_ = _volume_level;
    EEPROM.update(eeprom_idx_volume_, volume_level_);
}

bool CPlayer::incVolume() {
    if (volume_level_ == VOLUME_LVL_MAX) {
        return false;
    }
    setVolume(++volume_level_);
    EEPROM.update(eeprom_idx_volume_, volume_level_);
    return true;
}

bool CPlayer::decVolume() {
    if (volume_level_ == VOLUME_LVL_MIN) {
        return false;
    }
    setVolume(--volume_level_);
    EEPROM.update(eeprom_idx_volume_, volume_level_);
    return true;
}

void CPlayer::saveVolumeToEEPROM(uint8_t _volume_lvl) {
    EEPROM.update(eeprom_idx_volume_, volume_level_);
}

void CPlayer::stopPlaying() {
    stop();
}
