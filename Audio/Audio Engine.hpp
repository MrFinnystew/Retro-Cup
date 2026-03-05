/*
 Audio engine
 by Yu-El Cheong
 */
// Audio.h
#pragma once
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <memory>

class Audio {
public:
    Audio() {
        if (ma_engine_init(NULL, &m_engine) != MA_SUCCESS)
            throw std::runtime_error("Failed to initialize audio engine");
    }

    ~Audio() {
        m_sounds.clear(); // uninit sounds before engine
        ma_engine_uninit(&m_engine);
    }

    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    // Load a sound and give it a name
    void load(const std::string& name, const std::string& filepath) {
        auto sound = std::make_unique<SoundData>();
        if (ma_sound_init_from_file(&m_engine, filepath.c_str(), 0, NULL, NULL, &sound->sound) != MA_SUCCESS)
            throw std::runtime_error("Failed to load: " + filepath);
        m_sounds[name] = std::move(sound);
    }

    // Fire-and-forget (no need to load first)
    void play(const std::string& filepath) {
        ma_engine_play_sound(&m_engine, filepath.c_str(), NULL);
    }

    // Play a loaded sound by name
    void playLoaded(const std::string& name) { get(name).start(); }
    void stop(const std::string& name)       { get(name).stop(); }
    void rewind(const std::string& name)     { ma_sound_seek_to_pcm_frame(&get(name).sound, 0); }

    void setLoop(const std::string& name, bool loop)    { ma_sound_set_looping(&get(name).sound, loop); }
    void setVolume(const std::string& name, float vol)  { ma_sound_set_volume(&get(name).sound, vol); }
    void setPitch(const std::string& name, float pitch) { ma_sound_set_pitch(&get(name).sound, pitch); }

    bool isPlaying(const std::string& name) { return ma_sound_is_playing(&get(name).sound); }
    bool isAtEnd(const std::string& name)   { return ma_sound_at_end(&get(name).sound); }

    void setMasterVolume(float vol) {
        m_volume = vol;
        ma_engine_set_volume(&m_engine, vol);
    }
    float getMasterVolume() const { return m_volume; }

private:
    struct SoundData {
        ma_sound sound;
        ~SoundData() { ma_sound_uninit(&sound); }

        void start() { ma_sound_start(&sound); }
        void stop()  { ma_sound_stop(&sound); }
    };

    SoundData& get(const std::string& name) {
        auto it = m_sounds.find(name);
        if (it == m_sounds.end())
            throw std::runtime_error("Sound not found: " + name);
        return *it->second;
    }

    ma_engine m_engine;
    float m_volume = 1.0f;
    std::unordered_map<std::string, std::unique_ptr<SoundData>> m_sounds;
};
