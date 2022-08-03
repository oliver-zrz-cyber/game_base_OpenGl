
#ifndef OPEN_GL_INSTALL_GAME_H
#define OPEN_GL_INSTALL_GAME_H

#include"sprite_renderer.h"
#include"GameLevel.h"
#include<vector>
#include<iostream>
#include"File_M.h"
#include <GLFW/glfw3.h>
#include"BallObject.h"
#include"Collision_detection.h"
//---------------------------------
bool check(std::vector<GameObject>&q) {
    for(auto &t:q){
        if(t.Destroyed==false&&t.IsSolid== false)
            return false;
    }
    return true;
}
SpriteRenderer  *Renderer;
//---------------------------------------------------------写一个开头的选择画面-------------------------------------------------

//-------paddle-----paddle----------------------
const glm::vec2 PLAYER_SIZE(100.0f,20.0f);
const float PLAYER_VECLOCITY(500.0f);
GameObject *player;
//---------------ball-----------ball-----------
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f,-350.0f);
const float BALL_RADIUS = 12.5f;
BallObject *Ball;
//-----------初始量------------------------------------------------------
glm::vec2 I_B_P;


//----------------------------------------------------------------------
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};
class Game
{
public:
    GameState State;
    bool keys[1024];
    unsigned int W,H;
    unsigned int level;
    std::vector<GameLevel> Levels;
    Game(unsigned W,unsigned int H);
    ~Game();
    void init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void Collision();
    void ResetLevel();
    void ResetPlayer();
    void next_level()
    {
        ++level;
        if(level==4)level=0;
        this->ResetLevel();
        this->ResetPlayer();
    }
};
void Game::ResetLevel()
{
    if (this->level == 0)
        this->Levels[0].Load("/Users/code/game/one.txt", this->W, this->H / 2);
    else if (this->level == 1)
        this->Levels[1].Load("/Users/code/game/two.txt", this->W, this->H / 2);
    else if (this->level == 2)
        this->Levels[2].Load("/Users/code/game/three.txt", this->W, this->H / 2);
    else if (this->level == 3)
        this->Levels[3].Load("/Users/code/game/four.txt", this->W, this->H / 2);
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    player->Size = PLAYER_SIZE;
    player->Position = glm::vec2(this->W / 2.0f - PLAYER_SIZE.x / 2.0f, this->H - PLAYER_SIZE.y);
    Ball->Reset(player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}
void Game::Collision() {
    for(auto &t:this->Levels[this->level].Bricks)
    {
        if(!t.Destroyed)
        {
            if(CheckCollision(*Ball,t))
            {
                if(!t.IsSolid)
                    t.Destroyed = true;
                break;
            }
        }
    }
    CheckCollision(*Ball,*player);
}
Game::Game(unsigned int width, unsigned int height)
        : State(GAME_ACTIVE), keys(), W(width), H(height)
{

}

Game::~Game()
{

}

void Game::init()
{
    ResourceManager::LoadShader("/Users/code/1.txt","/Users/code/2.txt", nullptr,"sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->W),
                                      static_cast<float>(this->H), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader shader = (ResourceManager::GetShader("sprite"));
    Renderer = new SpriteRenderer(shader);
//-----------------------LOAD_TEXTURE--------------------------
    ResourceManager::LoadTexture("/Users/code/game/background3.jpg",false,"background");
    ResourceManager::LoadTexture("/Users/code/game/block_solid.png", false,"block_solid");
    ResourceManager::LoadTexture("/Users/code/game/block.png",false,"block");
    ResourceManager::LoadTexture("/Users/code/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("/Users/code/game/paddle.png",true,"paddle");
    ResourceManager::LoadTexture("/Users/code/game/ball_vcc.png",true,"ball_texture");
//------------------------------------------------------------------------

    GameLevel one,two,three,four,five,final;
    one.Load("/Users/code/game/One.txt",this->W,this->H/2);
    two.Load("/Users/code/game/two.txt",this->W,this->H/2);
    three.Load("/Users/code/game/three.txt",this->W,this->H/2);
    four.Load("/Users/code/game/four.txt",this->W,this->H/2);
//    five.Load("five.txt",this->W,this->H/2);
//    final.Load("final.txt",this->W,this->H/2);
//-------paddle-----paddle----------------------
    glm::vec2 playerPos = glm::vec2(this->W/2.0f-PLAYER_SIZE.x/2.0f,this->H-PLAYER_SIZE.y);
    player = new GameObject(playerPos,PLAYER_SIZE,ResourceManager::GetTexture("paddle"));
    player->name = "paddle";
//---------------ball-----------ball-----------
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x/2.0f-BALL_RADIUS,-BALL_RADIUS*2.0f);
    Ball = new BallObject(ballPos,BALL_RADIUS,INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("ball_texture"));
    I_B_P.y = ballPos.y;
    Ball->name ="ball";
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
//    this->Levels.push_back(five);
//    this->Levels.push_back(final);
    this->level = 1;
}

void Game::Update(float dt) {
    std::cout<<dt;
    Ball->Move(dt, this->W);
    this->Collision();
//如果已经通过了这一关，我们可以进入下一关。
    if(check(this->Levels[this->level].Bricks))
        this->next_level();
//如果这一关失败了。。。。
    if(Ball->Position.y>=this->H){
        this->ResetLevel();
        this->ResetPlayer();
    }
}

void Game::ProcessInput(float dt)
{
    if(this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VECLOCITY*dt;
        if(Ball->Stuck)
        {
            if(this->keys[GLFW_KEY_LEFT])Ball->Velocity.x = -INITIAL_BALL_VELOCITY.x;
            else if(this->keys[GLFW_KEY_RIGHT])Ball->Velocity.x = INITIAL_BALL_VELOCITY.x;
        }
        if(this->keys[GLFW_KEY_A])
        {
            if(player->Position.x>=0.0f)
            {
                player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if(this->keys[GLFW_KEY_D])
        {
            if(player->Position.x<= this->W-player->Size.x) {
                player->Position.x += velocity;
                if (Ball->Stuck) {
                    Ball->Position.x += velocity;
                }
            }
        }
        if(this->keys[GLFW_KEY_SPACE])Ball->Stuck = false;
        if(this->keys[GLFW_KEY_UP]&&this->keys[GLFW_KEY_DOWN] &&CheckCollision(*Ball,*player))
            Ball->Position.y = I_B_P.y,Ball->Stuck = true,Ball->Velocity.x = INITIAL_BALL_VELOCITY.x,Ball->Velocity.y=INITIAL_BALL_VELOCITY.y;
    }
}

void Game::Render()
{
    if(this->State == GAME_ACTIVE)
    {
        auto c=ResourceManager::GetTexture("background");
        Renderer->DrawSprite(c,
                             glm::vec2(0.0f, 0.0f), glm::vec2(this->W, this->H), 0.0f
        );
        this->Levels[this->level].Draw(*Renderer);
        player->Draw(*Renderer);
        Ball->Draw(*Renderer);
    }
}




#endif //OPEN_GL_INSTALL_GAME_H
