#ifndef MESH_H
#define MESH_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"shader.h"
#include<string>
#include<vector>
using namespace std;
#define MAX_BONE_INFLUENCE 4

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    Vertex();
    Vertex(glm::vec3 a,glm::vec3 b,glm::vec2 c,glm::vec3 d)
    {
        Position = a;
        Normal = b;
        TexCoords = c;
        Tangent = d;
    }
};
struct Texture{
    unsigned int id;
    string type;
    string path;
};

class Mesh{
public:
    vector<Vertex> vertices;
    vector<unsigned int>indices;
    vector<Texture> textures;
    unsigned int VAO;

    Mesh(vector<Vertex>v,vector<unsigned int>i,vector<Texture>t)
    {
        this->vertices = v;
        this->indices = i;
        this->textures = t;
        setupMesh();
    }
    void Draw(Shader shader)
    {
        unsigned int diffuseNr =1,specularNr = 1;
        for(int i=0;i<textures.size();++i)
        {
            glActiveTexture(GL_TEXTURE0+i);
            string number;
            string name = textures[i].type;
            if(name[8]=='d')
                number = std::to_string(diffuseNr++);
            else if(name[8] == 's')
                number = std::to_string(specularNr++);
            glBindTexture(GL_TEXTURE_2D,textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
    }

private:
    unsigned int VBO,EBO;
    void setupMesh()
    {
        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1,&VBO);
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*) offsetof(Vertex,Normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        glBindVertexArray(0);
    }
};
#endif