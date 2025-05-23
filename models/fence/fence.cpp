#include "fence.h"

ExternalModel Models::fence;

void Models::loadFence() {
    fence.loadModel("models/fence/scene.gltf");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}