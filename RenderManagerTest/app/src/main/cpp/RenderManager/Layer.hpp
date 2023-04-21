#include "Object.hpp"

#ifndef LAYER_HPP
#define LAYER_HPP

class Layer {
public:
    Layer(const int _signature);

    ~Layer();

    virtual void SetOrthographic(float size, float windowWidth, float windowHeight, bool landscape = true);
    virtual void Zoom(float size);
    virtual Mesh *RegisterBack(const int signature); // MeshLayer에서만 작동함
    virtual Mesh *RegisterFront(const int signature); // MeshLayer에서만 작동함

protected:
    virtual void Render();
    virtual void CheckMesh();
    virtual void Materialize();
    virtual void ConvertMatrix();
    virtual void ConvertTexcoord();
    virtual void ConvertColor();
    virtual void CreateShader();
    void Trash(Mesh *_trash);
    void ClearTrash();
    Layer *Destroy();
    bool isDestroyed();

    const int signature;

    int memory;
    int meshCount;

    float fieldSize;
    float landscapeRatio;
    float portraitRatio;
    float *vertexData;
    float *texcoordData;
    float *colorData;

    bool needMaterialize;
    bool destroyed;

    Shader::Shader *shader;
    Shader::UniformData *uniformData;
    Layer *next;
    Mesh *mesh;
    Mesh *trash;

    friend class RenderManager;
    friend class Object;
};

class BlendFunc : public Layer{
public:
    BlendFunc(const int _signature, const GLenum _srcValue, const GLenum _dstValue);
    ~BlendFunc();

private:
    void Render();

    const GLenum srcValue;
    const GLenum dstValue;
};

class Stencil : public Layer{
public:
    Stencil(const int signature, GLenum func, GLint ref, GLint mask, GLenum fail, GLenum zfail, GLenum zpass);
    ~Stencil();

private:
    void Render();

    GLenum func;
    GLint ref;
    GLint mask;
    GLenum fail;
    GLenum zfail;
    GLenum zpass;
};

class MeshLayer : public Layer{
public:
    MeshLayer(const int signature, int _memory, std::string fileName, Shader::Shader* shader = nullptr);
    ~MeshLayer();

    void SetOrthographic(float size, float windowWidth, float windowHeight, bool landscape = true);
    void Zoom(float size);

    Mesh *RegisterBack(const int signature);
    Mesh *RegisterFront(const int signature);

private:

    void Render();
    void CheckMesh();
    void Materialize();
    void ConvertMatrix();
    void ConvertTexcoord();
    void ConvertColor();
    void CreateShader();

    friend class RenderManager;
    friend class Object;
};

#endif //LAYER_HPP
