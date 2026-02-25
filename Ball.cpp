#include "Ball.hpp"
#include <cmath>

const double PI = 3.1415;

Ball::Ball(Point center, Velocity v, Color color, double radius, bool isCollidable):
    m_velocity{v}, m_center{center}, m_radius{radius}, m_color{color}, m_isCollidable{isCollidable}
    {
        calculateMass();    
    }
/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    m_velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return m_velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(m_center, m_radius, m_color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    m_center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return m_center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return m_radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
void Ball::calculateMass() {
    m_mass = 4./3. * PI * m_radius * m_radius * m_radius;
}

 double Ball::getMass() const {
    return m_mass;
}

bool Ball::getIsCollidable() const {
    return m_isCollidable;
}

std::istream& operator>>(std::istream& stream, Ball& ball) {
    stream >> ball.m_center >> ball.m_velocity >> ball.m_color >> ball.m_radius >> std::boolalpha >> ball.m_isCollidable;
    ball.calculateMass();
    return stream;
}