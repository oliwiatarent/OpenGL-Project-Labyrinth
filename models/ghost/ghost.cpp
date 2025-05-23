#include "ghost.h"

ExternalModel Models::ghost;

void Models::loadGhost() {
    ghost.loadModel("models/ghost/scene.gltf");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}