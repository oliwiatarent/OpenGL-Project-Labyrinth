#include "painting.h"

ExternalModel Models::painting;

void Models::loadPainting() {
    painting.loadModel("models/painting/scene.gltf");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}