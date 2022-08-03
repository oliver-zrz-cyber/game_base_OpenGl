//
// Created by zrz-oliver on 2022/8/1.
//

#ifndef OPEN_GL_INSTALL_SPRITE_RENDERER_H
#define OPEN_GL_INSTALL_SPRITE_RENDERER_H

class SpriteRenderer
{
public:
    SpriteRenderer(Shader &shader) {
        this->shader = shader;
        this->initRenderData();
    }
    ~SpriteRenderer();
    void DrawSprite(Texture2D &texture,glm::vec2 Position,
                    glm::vec2 size = glm::vec2(10.0f,10.0f),float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
private:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
};

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}
void SpriteRenderer::initRenderData() {
    unsigned int VBO;
    float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1,&this->quadVAO);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 Position, glm::vec2 size, float rotate, glm::vec3 color) {
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(Position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));
    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
}
#endif //OPEN_GL_INSTALL_SPRITE_RENDERER_H
