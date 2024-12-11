#include "AudioVoice.h"
#include "AudioHelpers.h"
AudioVoice::AudioVoice(int id) : id(id) {
    m_audioHandle = nullptr;
    m_isActive = false;
    attenuation = 1.0f;
    panL = panR = lastPanL = lastPanR = 0.0f;
}

AudioVoice::~AudioVoice() {
 
}

void AudioVoice::setAudioHandle(AudioHandle* audioHandle) {
    m_audioHandle = audioHandle;
}

AudioHandle* AudioVoice::getAudioHandle() {
    return m_audioHandle;
}

bool AudioVoice::isActive() {
    return m_isActive;
}

void AudioVoice::setActive(bool active) {
    m_isActive = active;
}

void AudioVoice::setAttenuation(float att) {
    attenuation = att;
}

float AudioVoice::getAttenuation() {
    return attenuation;
}

void AudioVoice::setPan(float left, float right) {
    lastPanL = panL;
    lastPanR = panR;
    panL = left;
    panR = right;
}

float AudioVoice::getPanL() {
    return panL;
}

float AudioVoice::getPanR() {
    return panR;
}

float AudioVoice::getLastPanL() {
    return lastPanL;
}

float AudioVoice::getLastPanR() {
    return lastPanR;
}
