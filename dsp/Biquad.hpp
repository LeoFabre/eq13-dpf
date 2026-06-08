#pragma once
#include <cmath>

namespace eq13 {

class BiquadPeakEQ {
public:
    void reset() { x1 = x2 = y1 = y2 = 0.f; }

    void setCoeffs(float fc, float Q, float gainDb, float fs) {
        if (gainDb == lastGainDb && fc == lastFc) return;
        lastGainDb = gainDb;
        lastFc = fc;

        float A     = std::pow(10.f, gainDb / 40.f);
        float w0    = 2.f * 3.14159265358979f * fc / fs;
        float sinw  = std::sin(w0);
        float cosw  = std::cos(w0);
        float alpha = sinw / (2.f * Q);

        float b0 =  1.f + alpha * A;
        float b1 = -2.f * cosw;
        float b2 =  1.f - alpha * A;
        float a0 =  1.f + alpha / A;
        float a1 = -2.f * cosw;
        float a2 =  1.f - alpha / A;

        float inv = 1.f / a0;
        this->b0 = b0 * inv;
        this->b1 = b1 * inv;
        this->b2 = b2 * inv;
        this->a1 = a1 * inv;
        this->a2 = a2 * inv;
    }

    float process(float x) {
        float y = b0 * x + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
        x2 = x1; x1 = x;
        y2 = y1; y1 = y;
        return y;
    }

private:
    float b0 = 1.f, b1 = 0.f, b2 = 0.f;
    float a1 = 0.f, a2 = 0.f;
    float x1 = 0.f, x2 = 0.f, y1 = 0.f, y2 = 0.f;
    float lastGainDb = 0.f, lastFc = -1.f;
};

} // namespace eq13
