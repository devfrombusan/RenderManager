#include "Layer.hpp"

#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

class RenderManager {
public:
    RenderManager();
    ~RenderManager();

    void SetOrthographic(const int signature, float size, float windowWidth, float windowHeight, bool landscape = true);
    void SetAllMeshColor(float r, float g, float b, float a);

    void CreateBlend(const int signature, const GLenum glSrcValue, const GLenum glDstValue);
    void CreateStencil(const int signature, GLenum func, GLint ref, GLint mask, GLenum fail, GLenum zfail, GLenum zpass);
    void CreateMeshLayer(const int signature, int memory, std::string fileName, Shader::Shader* _shader = nullptr);
    Object *CreateObject(const int signature, Object *object, bool front = false);
    Camera *CreateCamera();

    void CheckLayer();
    bool CheckSignature(const int signature);
    int CheckMeshCount(const int signature);
    void CheckCamera();

    void ClearLayer();
    void ClearCamera();
    void ClearTrash();

    void SendTrash(Layer *_trash);
    void SendTrash(Camera *_trash);
    void DeleteLayer(const int signature);

    void Render();
    void DrawLayer();
    void Zoom(const int signature, float size);
    bool isData();

    Object *CopyObject(Object *standard, Object *target);

private:
    Layer *isExisted(const int signature);

    Layer *layer;
    Layer *trash;
    Camera *camera;
    Camera *trashCamera;
};

extern RenderManager *renderManager;

#endif //RENDERMANAGER_HPP
