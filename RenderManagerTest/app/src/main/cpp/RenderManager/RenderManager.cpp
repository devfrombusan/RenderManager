#include "RenderManager.hpp"

// 렌더러를 책임지는 클래스이며
// 현재는 연구되지 않았지만 씬으로 나누어서 활용도 가능
// 로딩화면 등 새로운 랜더러가 필요한 경우는 다수의 매니저를 생성하도록 할수있다

RenderManager::RenderManager() {

    layer = nullptr;
    trash = nullptr;
    camera = nullptr;
    trashCamera = nullptr;
}

RenderManager::~RenderManager() {

    if (layer) {
        Layer *temp = nullptr;

        while (layer != nullptr) {
            temp = layer->next;
            delete layer;
            layer = temp;
        }
    }

    if (trash) {
        Layer *temp = nullptr;

        while (trash != nullptr) {
            temp = trash->next;
            delete trash;
            trash = temp;
        }
    }

    if (camera) {
        Camera *temp = nullptr;

        while (camera) {
            temp = camera->next;
            delete camera;
            camera = temp;
        }
    }


    if (trashCamera) {
        Camera *temp = nullptr;

        while (trashCamera) {
            temp = trashCamera->next;
            delete trashCamera;
            trashCamera = temp;
        }
    }
}

void RenderManager::SetOrthographic(const int signature, float size, float windowWidth,
                                    float windowHeight, bool landscape) {

    Layer *temp = isExisted(signature);
    if (temp) temp->SetOrthographic(size, windowWidth, windowHeight, landscape);

    return;
}

void RenderManager::SetAllMeshColor(float r, float g, float b, float a) {
    Layer *layer = this->layer;

    while (layer) {
        Mesh *temp = layer->mesh;

        while (temp) {
            temp->SetColorData(r, g, b, a);
            temp->ConvertColor();

            temp = temp->next;
        }

        layer = layer->next;
    }

}


void RenderManager::CreateBlend(const int signature, const GLenum glSrcValue,
                                const GLenum glDstValue) {
    Layer *prev = nullptr;
    Layer *temp = isExisted(signature);

    if (temp) return;


    temp = layer;

    if (!layer) {
        layer = new BlendFunc(signature, glSrcValue, glDstValue);
        return;
    }

    while (temp) {

        if (temp->signature > signature) {
            if (!prev) {
                layer = new BlendFunc(signature, glSrcValue, glDstValue);
                layer->next = temp;
                return;
            }

            prev->next = new BlendFunc(signature, glSrcValue, glDstValue);
            prev->next->next = temp;
            return;
        }

        if (!temp->next) {
            temp->next = new BlendFunc(signature, glSrcValue, glDstValue);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

void RenderManager::CreateStencil(const int signature, GLenum func, GLint ref, GLint mask,
                                  GLenum fail, GLenum zfail, GLenum zpass) {
    Layer *prev = nullptr;
    Layer *temp = isExisted(signature);

    if (temp) return;


    temp = layer;

    if (!layer) {
        layer = new Stencil(signature, func, ref, mask, fail, zfail, zpass);
        return;
    }

    while (temp) {

        if (temp->signature > signature) {
            if (!prev) {
                layer = new Stencil(signature, func, ref, mask, fail, zfail, zpass);
                layer->next = temp;
                return;
            }

            prev->next = new Stencil(signature, func, ref, mask, fail, zfail, zpass);
            prev->next->next = temp;
            return;
        }

        if (!temp->next) {
            temp->next = new Stencil(signature, func, ref, mask, fail, zfail, zpass);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

void RenderManager::CreateMeshLayer(const int signature, int memory, std::string fileName, Shader::Shader* shader) {


    Layer *prev = nullptr;
    Layer *temp = isExisted(signature);

    if (temp) return;

    temp = layer;

    if (!layer) {
        layer = new MeshLayer(signature, memory, fileName, shader);
        return;
    }

    while (temp) {

        if (temp->signature > signature) {
            if (!prev) {
                layer = new MeshLayer(signature, memory, fileName, shader);
                layer->next = temp;
                return;
            }

            prev->next = new MeshLayer(signature, memory, fileName, shader);
            prev->next->next = temp;
            return;
        }

        if (!temp->next) {
            temp->next = new MeshLayer(signature, memory, fileName, shader);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

Object *RenderManager::CreateObject(const int signature, Object *object, bool front) {

    Layer *temp = isExisted(signature);

    if (!temp) {
        return object;
    }

    if (object->mesh) {
        return object;
    }

    if (front) object->mesh = temp->RegisterFront(signature);
    else object->mesh = temp->RegisterBack(signature);
    object->mesh->layer = temp;

    return object;
}

Camera *RenderManager::CreateCamera() {

    if (!camera) {
        camera = new Camera();
        return camera;
    }

    Camera *temp = camera;

    while (temp->next) temp = temp->next;

    temp->next = new Camera();

    return temp->next;

}


void RenderManager::CheckLayer() {

    Layer *prev = nullptr;
    Layer *temp = layer;

    while (temp != nullptr) {

        if (temp->isDestroyed()) {

            if (!prev) {
                layer = layer->next;
                SendTrash(temp);
                temp = layer;

            } else {
                prev->next = temp->next;
                SendTrash(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

bool RenderManager::CheckSignature(const int signature) {

    Layer *temp = layer;

    while (temp != nullptr) {
        if (temp->signature == signature) if (!temp->isDestroyed()) return true;
        temp = temp->next;
    }

    return false;

}

int RenderManager::CheckMeshCount(const int signature) {

    Layer *temp = isExisted(signature);

    if (temp) return temp->meshCount;

    return 0;

}

void RenderManager::CheckCamera() {
    Camera *temp = camera;

    while (temp) {
        temp->lookAtPosition[0] = temp->tempPosition[0] + temp->standPosition[0];
        temp->lookAtPosition[1] = temp->tempPosition[1] + temp->standPosition[1];
        temp = temp->next;
    }
}

void RenderManager::ClearLayer() {

    Layer *temp = nullptr;

    while (layer) {
        temp = layer->next;
        SendTrash(layer);
        layer = temp;
    }

    Camera *tempCamera = nullptr;

    while (camera) {
        tempCamera = camera->next;
        SendTrash(camera);
        camera = tempCamera;
    }
}

void RenderManager::ClearCamera() {

    Camera *temp = nullptr;

    while (camera) {
        temp = camera->next;
        SendTrash(camera);
        camera = temp;
    }
}

void RenderManager::ClearTrash() {

    Layer *temp = nullptr;

    while (trash != nullptr) {
        temp = trash->next;
        delete trash;
        trash = temp;
    }

    Camera *tempCamera = nullptr;

    while (trashCamera != nullptr) {
        tempCamera = trashCamera->next;
        delete trashCamera;
        trashCamera = tempCamera;
    }
}

void RenderManager::SendTrash(Layer *_trash) {

    Layer *temp = trash;
    _trash->next = nullptr;
    trash = _trash;
    trash->next = temp;
}

void RenderManager::SendTrash(Camera *_trash) {

    Camera *temp = trashCamera;
    _trash->next = nullptr;
    trashCamera = _trash;
    trashCamera->next = temp;
}

void RenderManager::DeleteLayer(const int signature) {

    Layer *temp = isExisted(signature);

    if (temp) temp->Destroy();

    CheckLayer();

}

void RenderManager::Render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearStencil(0);

    CheckCamera();

    glEnable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST); // 현재는 사용하지 않음
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    //glDisable(GL_DEPTH_TEST);

    DrawLayer();

    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_STENCIL_TEST);

    ClearTrash();
}


void RenderManager::DrawLayer() {

    Layer *temp = layer;

    while (temp != nullptr) {
        if (!temp->isDestroyed()) temp->Render();
        temp = temp->next;
    }
}

void RenderManager::Zoom(const int signature, float size) {

    Layer *temp = isExisted(signature);
    if (temp) temp->Zoom(size);

    return;
}

bool RenderManager::isData() {

    if (!layer && !trash && !camera && !trashCamera) return false;
    return true;

}

Object *RenderManager::CopyObject(Object *standard, Object *target) {

    if (!standard) return target;

    int signature = standard->mesh->signature;

    CreateObject(signature, target);

    for (int i = 0; i < 8; i++) target->mesh->vertexData[i] = standard->mesh->vertexData[i];
    for (int i = 0; i < 8; i++)
        target->mesh->texcoordData[i] = standard->mesh->texcoordData[i];
    for (int i = 0; i < 4; i++) target->mesh->colorData[i] = standard->mesh->colorData[i];
    for (int i = 0; i < 2; i++) target->mesh->localPosition[i] = standard->mesh->localPosition[i];
    for (int i = 0; i < 8; i++) target->mesh->matrix[i] = standard->mesh->matrix[i];

    return target;
}

Layer *RenderManager::isExisted(const int signature) {

    Layer *temp = layer;

    while (temp != nullptr) {
        if (temp->signature == signature) if (!temp->isDestroyed()) return temp;
        temp = temp->next;
    }

    return nullptr;
}

RenderManager *renderManager = nullptr;
