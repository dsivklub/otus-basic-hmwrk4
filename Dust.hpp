#pragma once
#include "Ball.hpp"

const double DEFAULT_DUST_LIVE_TIME{1.};
const Color DEFAULT_DUST_COLOR{0., 0., 0.};
const double DEFAULT_DUST_RADIUS{10.};
const int MAX_DUST_VELOCITY{385};

class Dust : public Ball {
public:
    Dust(Point center, Point velocity):
        Ball{center, velocity, DEFAULT_DUST_COLOR, DEFAULT_DUST_RADIUS, false},
        m_liveTime{DEFAULT_DUST_LIVE_TIME}
        {};

    inline void decreaseTimeLive(double time) {
        m_liveTime -= time;
    }

    inline double getTimeLive() {
        return m_liveTime;
    }

    ~Dust() = default;
private:
    double m_liveTime;
};