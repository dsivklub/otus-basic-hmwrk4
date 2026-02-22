#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>

const int MAX_NUM_DUST_COLISION = 5;
const int MAX_SHIFT_DUST = 10;

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, std::vector<Dust>& vDust, size_t ticks) const;

  private:
    void collideBalls(std::vector<Ball>& balls, std::vector<Dust>& vDust) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void moveDust(std::vector<Dust>& vDust) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
