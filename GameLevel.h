//
// Created by zrz-oliver on 2022/8/1.
//

#ifndef OPEN_GL_INSTALL_GAMELEVEL_H
#define OPEN_GL_INSTALL_GAMELEVEL_H
#include"GameObejct.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include"File_M.h"
#include<iostream>
class GameLevel
{
public:
    std::vector<GameObject> Bricks;
    GameLevel(){ }
    void Load(const char* file,unsigned int w,unsigned int h);
    void Draw(SpriteRenderer &renderer)
    {
        for(auto t:Bricks)if(!t.Destroyed)
                t.Draw(renderer);
    }
    bool IsCompeleted();
private:
    void init(std::vector<std::vector<unsigned int>>tileData,
              unsigned int level_w,unsigned int level_h);
};

bool GameLevel::IsCompeleted() {
        for (GameObject &tile : this->Bricks)
            if (!tile.IsSolid && !tile.Destroyed)
                return false;
        return true;
}
void GameLevel::Load(const char *file,unsigned int w,unsigned int h)
{
    this->Bricks.clear();
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if(fstream)
    {
        while(std::getline(fstream,line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int>row;
            while(sstream>>tileCode)row.push_back(tileCode);
            tileData.push_back(row);
        }
        if(tileData.size()>0)
            this->init(tileData,w,h);
    }
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int level_w, unsigned int level_h) {
    unsigned int h = tileData.size();
    unsigned int w = tileData[0].size();
    float unit_h = level_h/h;
    float unit_w = level_w/static_cast<float>(w);
    for(int y= 0;y<h;++y)
    {
        for(int x = 0;x < w;++x)
        {
            if(tileData[y][x] == 1)
            {
                glm::vec2 pos(unit_w*x,unit_h*y);
                glm::vec2 size(unit_w,unit_h);
                GameObject obj(pos,size,ResourceManager::GetTexture("block_solid"),
                               glm::vec3(0.8,0.8,0.7));
                obj.IsSolid = true;
                this->Bricks.push_back(obj);
            }
            else if(tileData[y][x]>1)
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_w * x, unit_h * y);
                glm::vec2 size(unit_w, unit_h);
                this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color,glm::vec2(0.0f,0.0f)));
                Bricks[Bricks.size()-1].name ="Bricks";
            }
        }
    }


}
#endif //OPEN_GL_INSTALL_GAMELEVEL_H
