#ifndef OPEN_GL_INSTALL_COLLISION_DETECTION_H
#define OPEN_GL_INSTALL_COLLISION_DETECTION_H
#include<iostream>
#include "BallObject.h"
#include "GameObejct.h"
#include <glm/glm.hpp>
#include<math.h>
float clamp(float value,float min,float max)
{
    return std::max(min,std::min(max,value));
}
bool CheckCollision(BallObject &one , GameObject &two)
{
    glm::vec2 center(one.Position+one.Radius);
    glm::vec2 aabb_half_extents(two.Size.x/2.0f,two.Size.y/2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x,
                          two.Position.y + aabb_half_extents.y);
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;

    if(glm::length(difference) < one.Radius)
    {
        if(two.name!="paddle") {
            if ((closest.x <= two.Position.x+5 && closest.x >= two.Position.x )||(closest.x <= two.Position.x+two.Size.x+5 && closest.x >= two.Position.x+two.Size.x )) {
                one.Velocity.x = -one.Velocity.x;
                float penetration = one.Radius - std::abs(difference.x);
                if(closest.x <= two.Position.x+5 && closest.x >= two.Position.x )one.Position.x-=penetration;
                else one.Position.x+=penetration;
            } else{
                one.Velocity.y = -one.Velocity.y;
                float penetration = one.Radius - std::abs(difference.y);
                if(closest.y <= two.Position.y+5 && closest.y >= two.Position.y )one.Position.y-=penetration;
                else one.Position.y+=penetration;
            }
        }
        else
        {
            if(closest.x<=two.Position.x+two.Size.x/2){
                one.Velocity.x = -std::abs(100)*
                        std::abs(closest.x-two.Position.x-two.Size.x/2)/(two.Size.x/2)*1.5;
            }
            else one.Velocity.x = std::abs(100)*
                                  std::abs(closest.x-two.Position.x-two.Size.x/2)/(two.Size.x/2)*1.5;
            one.Velocity.y = -one.Velocity.y;
            one.Position.y = two.Position.y-two.Size.y;
        }

        return true;
    }
    return false;
}


#endif //OPEN_GL_INSTALL_COLLISION_DETECTION_H
