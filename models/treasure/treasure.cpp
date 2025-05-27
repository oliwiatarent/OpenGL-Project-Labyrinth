#include "treasure.h"

ExternalModel Models::treasure;

void Models::loadTreasure() {
    treasure.loadModel("models/treasure/scene.gltf");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}