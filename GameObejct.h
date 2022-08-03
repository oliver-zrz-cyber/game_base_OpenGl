#ifndef OPEN_GL_INSTALL_GAMEOBEJCT_H
#define OPEN_GL_INSTALL_GAMEOBEJCT_H
#include<glad/glad.h>
#include<glm/glm.hpp>
#include"Texture.h"
#include"sprite_renderer.h"

class GameObject
{
public:
    std::string name;
    glm::vec2 Position,Size,Velocity;
    glm::vec3 Color;
    float Rotation;
    bool IsSolid;
    bool Destroyed;
    Texture2D Sprite;
    GameObject();
    GameObject(glm::vec2 pos,glm::vec2 size,Texture2D sprite,glm::vec3 color = glm::vec3(1.0f),glm::vec2 velocity = glm::vec2(0.0f)){
        this->Position = pos,this->Sprite = sprite,this->Size = size,this->Color = color,this->Velocity = velocity,this->Sprite = sprite,this->IsSolid=false,this->Destroyed=false;};
    virtual void Draw(SpriteRenderer &renderer)
    {
        renderer.DrawSprite(this->Sprite,this->Position,this->Size,this->Rotation,this->Color);
    }
};
GameObject::GameObject():Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) { }




#endif //OPEN_GL_INSTALL_GAMEOBEJCT_H
