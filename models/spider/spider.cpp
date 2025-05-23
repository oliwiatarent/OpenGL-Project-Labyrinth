#include "spider.h"

ExternalModel Models::spider;

void Models::loadSpider() {
    spider.loadModel("models/spider/scene.gltf");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}