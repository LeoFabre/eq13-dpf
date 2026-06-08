#include "Eq13Plugin.hpp"

START_NAMESPACE_DISTRHO

Eq13Plugin::Eq13Plugin() : Plugin(kNumBands, 0, 0) {}

void Eq13Plugin::initParameter(uint32_t index, Parameter& p) {
    if (index >= (uint32_t)kNumBands) return;
    p.hints      = kParameterIsAutomatable;
    p.name       = kBandNames[index];
    p.symbol     = kBandSymbols[index];
    p.unit       = "dB";
    p.ranges.min = -12.f;
    p.ranges.max =  12.f;
    p.ranges.def =   0.f;
}

float Eq13Plugin::getParameterValue(uint32_t index) const {
    return index < (uint32_t)kNumBands ? gainDb_[index] : 0.f;
}

void Eq13Plugin::setParameterValue(uint32_t index, float value) {
    if (index >= (uint32_t)kNumBands) return;
    gainDb_[index] = value;
    updateCoeffs();
}

void Eq13Plugin::activate() {
    sampleRate_ = float(getSampleRate());
    for (int ch = 0; ch < 2; ++ch)
        for (int b = 0; b < kNumBands; ++b)
            bands_[ch][b].reset();
    updateCoeffs();
}

void Eq13Plugin::updateCoeffs() {
    for (int ch = 0; ch < 2; ++ch)
        for (int b = 0; b < kNumBands; ++b)
            bands_[ch][b].setCoeffs(kBandFreqs[b], kQ, gainDb_[b], sampleRate_);
}

void Eq13Plugin::run(const float** inputs, float** outputs, uint32_t frames) {
    for (int ch = 0; ch < 2; ++ch) {
        const float* in  = inputs[ch];
        float*       out = outputs[ch];
        for (uint32_t n = 0; n < frames; ++n) {
            float x = in[n];
            for (int b = 0; b < kNumBands; ++b)
                x = bands_[ch][b].process(x);
            out[n] = x;
        }
    }
}

Plugin* createPlugin() { return new Eq13Plugin(); }

END_NAMESPACE_DISTRHO
