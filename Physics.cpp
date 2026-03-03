#include <ctime>
#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& vDust, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        moveDust(vDust),
        collideWithBox(balls);
        collideBalls(balls, vDust);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& vDust) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        bool isColliableA = a->getIsCollidable();
        for (auto b = std::next(a); b != balls.end(); ++b)  {
            if (isColliableA && b->getIsCollidable()) {
                const double distanceBetweenCenters2 =
                    distance2(a->getCenter(), b->getCenter());
                const double collisionDistance = a->getRadius() + b->getRadius();
                const double collisionDistance2 =
                    collisionDistance * collisionDistance;

                if ((distanceBetweenCenters2 < collisionDistance2)) {
                    processCollision(*a, *b, distanceBetweenCenters2);

                        double dx = b->getCenter().x - a->getCenter().x;
                        double dy = b->getCenter().y - a->getCenter().y;
                        double d = std::sqrt(dx*dx + dy*dy);

                        // точка на пересечении центров
                        Point aCenter = a->getCenter();
                        double aRad = a->getRadius();
                        Point pIntersection{aCenter.x + aRad * dx / d, aCenter.y + aRad * dy / d};
                        
                        // рандомная генерация пылинок
                        std::srand(std::time(nullptr));
                        // генерация рандомного количества частиц
                        int numDust = (rand() % MAX_NUM_DUST_COLISION) + 1;

                        for (int i = 0; i < numDust; i++) {
                            // генерация рандомного смещения по x и y
                            double deltaX = (rand() % MAX_NUM_DUST_COLISION);
                            double deltaY = (rand() % MAX_NUM_DUST_COLISION);
                            Point pDelta{deltaX, deltaY};

                            // генерация рандомной скорости для пылинки
                            double vx = (rand() % (MAX_DUST_VELOCITY * 2)) - MAX_DUST_VELOCITY;
                            double vy = (rand() % (MAX_DUST_VELOCITY * 2)) - MAX_DUST_VELOCITY;
                        
                            Dust dust{pIntersection + pDelta, Point{vx, vy}};
                            vDust.push_back(dust);                     
                        }
                }
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if (ball.getIsCollidable()) {
            const Point p = ball.getCenter();
            const double r = ball.getRadius();
            // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
            auto isOutOfRange = [](double v, double lo, double hi) {
                return v < lo || v > hi;
            };

            if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
                Point vector = ball.getVelocity().vector();
                vector.x = -vector.x;
                ball.setVelocity(vector);
            } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
                Point vector = ball.getVelocity().vector();
                vector.y = -vector.y;
                ball.setVelocity(vector);
            }
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::moveDust(std::vector<Dust>& vDust) const{
    for (size_t i = 0; i < vDust.size();) {
        Point newPos =
            vDust[i].getCenter() + vDust[i].getVelocity().vector() * timePerTick;
        vDust[i].setCenter(newPos);
        
        // обновление времени жизни
        vDust[i].decreaseTimeLive(timePerTick);

        // удаление частиц
        if (vDust[i].getTimeLive() < 0) {
            vDust.erase(vDust.begin() + i);
        } else {
            i++;
        }
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}
