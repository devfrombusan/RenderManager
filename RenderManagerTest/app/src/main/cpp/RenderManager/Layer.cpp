#include "Layer.hpp"

/*
    쉐이더 하나를 공유하는 모든 메쉬는 한 Layer에 담겨서 관리됨
    Layer의 수는 드로우콜의 수와 동일함
    텍스처 아틀라스를 사용하는 경우 한 Layer에 텍스처 데이터가 들어가야 한다
    Layer는 블랜딩만 사용하거나 메쉬를 관리하거나 다양하게 사용됨
*/

Layer::Layer(const int _signature)
        : signature(
        _signature) {

    memory = 0;

    vertexData = nullptr;
    texcoordData = nullptr;
    colorData = nullptr;

    next = nullptr;

    fieldSize = 1.0f;
    landscapeRatio = 1.0f;
    portraitRatio = 1.0f;

    mesh = nullptr;
    trash = nullptr;
    shader = nullptr;

    meshCount = 0;
    needMaterialize = false;

    destroyed = false;

    uniformData = nullptr;
}

Layer::~Layer(){

    if (shader) {
        delete shader;
        shader = nullptr;
    }

    if (vertexData) {
        delete[] vertexData;
        vertexData = nullptr;
    }

    if (texcoordData) {
        delete[] texcoordData;
        texcoordData = nullptr;
    }

    if (colorData) {
        delete[] colorData;
        colorData = nullptr;
    }

    if (uniformData) {
        delete uniformData;
        uniformData = nullptr;
    }

    Mesh *temp = nullptr;

    while (mesh != nullptr) {
        temp = mesh->next;
        delete mesh;
        mesh = temp;
    }

    temp = nullptr;

    while (trash != nullptr) {
        temp = trash->next;
        delete trash;
        trash = temp;
    }
}

void Layer::SetOrthographic(float size, float windowWidth, float windowHeight, bool landscape) {

}

void Layer::Zoom(float size) {

}

Mesh * Layer::RegisterBack(const int signature) {
    return nullptr;
}

Mesh * Layer::RegisterFront(const int signature) {
    return nullptr;
}

void Layer::Trash(Mesh *_trash) {
    Mesh *temp = trash;
    _trash->next = nullptr;
    trash = _trash;
    trash->activated = false;
    trash->next = temp;
}

void Layer::ClearTrash() {
    Mesh *temp = nullptr;

    while (trash != nullptr) {
        temp = trash->next;
        delete trash;
        trash = temp;
    }
}

Layer * Layer::Destroy() {
    if (!destroyed) destroyed = true;
    return this;
}

bool Layer::isDestroyed() {
    return destroyed;
}


void Layer::Render(){}
void Layer::CheckMesh(){}
void Layer::Materialize(){}
void Layer::ConvertMatrix(){}
void Layer::ConvertTexcoord(){}
void Layer::ConvertColor(){}
void Layer::CreateShader(){}
