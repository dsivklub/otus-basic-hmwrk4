#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(const Point& center, const Velocity& v, const Color& color, double radius, bool isCollidable);
    Ball() = default;
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getIsCollidable() const;

    friend std::istream& operator>>(std::istream& stream, Ball& ball);
private:
    Velocity m_velocity;
    Point m_center;
    double m_radius{0.};
    Color m_color;
    bool m_isCollidable{false};
    double m_mass{0.};

    void calculateMass();
};

std::istream& operator>>(std::istream& stream, Ball& ball);