#pragma once
#include "DistrhoPlugin.hpp"
#include "Biquad.hpp"

START_NAMESPACE_DISTRHO

inline constexpr int kNumBands = 13;

inline constexpr float kBandFreqs[kNumBands] = {
    31.f, 40.f, 50.f, 63.f, 80.f, 125.f, 250.f,
    500.f, 1000.f, 2000.f, 4000.f, 8000.f, 16000.f
};

inline constexpr const char* kBandNames[kNumBands] = {
    "31 Hz","40 Hz","50 Hz","63 Hz","80 Hz","125 Hz","250 Hz",
    "500 Hz","1 kHz","2 kHz","4 kHz","8 kHz","16 kHz"
};

inline constexpr const char* kBandSymbols[kNumBands] = {
    "gain_31","gain_40","gain_50","gain_63","gain_80","gain_125","gain_250",
    "gain_500","gain_1k","gain_2k","gain_4k","gain_8k","gain_16k"
};

class Eq13Plugin : public Plugin {
public:
    Eq13Plugin();

    const char* getLabel()       const override { return "EQ13"; }
    const char* getDescription() const override { return "13-band graphic EQ"; }
    const char* getMaker()       const override { return "Nexus"; }
    const char* getHomePage()    const override { return "https://github.com/lfabre/eq13-dpf"; }
    const char* getLicense()     const override { return "GPL-3.0-or-later"; }
    uint32_t    getVersion()     const override { return d_version(0, 1, 0); }
    int64_t     getUniqueId()    const override { return d_cconst('E','Q','1','3'); }

    void initParameter(uint32_t index, Parameter& parameter) override;
    float getParameterValue(uint32_t index) const override;
    void  setParameterValue(uint32_t index, float value) override;

    void activate() override;
    void run(const float** inputs, float** outputs, uint32_t frames) override;

private:
    static constexpr float kQ = 2.0f;

    eq13::BiquadPeakEQ bands_[2][kNumBands];
    float gainDb_[kNumBands] {};
    float sampleRate_ = 44100.f;

    void updateCoeffs();

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Eq13Plugin)
};

END_NAMESPACE_DISTRHO
