#include "door.h"

ExternalModel Models::door;

void Models::loadDoor() {
    door.loadModel("models/door/scene.gltf");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}