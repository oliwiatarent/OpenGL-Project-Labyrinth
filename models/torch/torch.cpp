#include "torch.h"

ExternalModel Models::torch;

void Models::loadTorch() {
    torch.loadModel("models/torch/scene.gltf");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}