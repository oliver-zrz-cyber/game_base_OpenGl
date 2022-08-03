#ifndef OPEN_GL_INSTALL_BALLOBJECT_H
#define OPEN_GL_INSTALL_BALLOBJECT_H
#include"GameObejct.h"
class BallObject : public GameObject
{
public:
    float Radius;
    bool Stuck;
    BallObject()
            : GameObject(), Radius(12.5f), Stuck(true) { }

    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
            : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity), Radius(radius), Stuck(true) { }
    glm::vec2 Move(float dt,unsigned int window_width);
    void Reset(glm::vec2 position, glm::vec2 velocity)
    {
        this->Position = position;
        this->Velocity = velocity;
        this->Stuck = true;
    }
};
glm::vec2 BallObject::Move(float dt, unsigned int window_width) {
    if(!this->Stuck)
    {
        this->Position += this->Velocity*dt;
        if(this->Position.x<=0) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if(this->Position.x+this->Size.x>=window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if(this->Position.y<=0)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }

}
#endif //OPEN_GL_INSTALL_BALLOBJECT_H
