#include "Shader.hpp"

#ifndef MESH_HPP
#define MESH_HPP

class Layer;

namespace MeshType {

    enum Click {
        NON, CIRCLE, RECT
    };

    enum Culling {
        CW = 1, CCW = -1
    };
}

class Camera {
public:
    Camera();
    ~Camera();

    void LookAt(float x, float y);

    float tempPosition[2];
    float lookAtPosition[2];
    float standPosition[2];
    float elapsedTime;
    Camera *next;
};

class Mesh {
public:
    Mesh(const int _signature);
    ~Mesh();

private:
    class Children {
    public:
        Children(Mesh *standard, Mesh *_mesh, int depthPriority = 0, float x = 0.0f, float Y = 0.0f);
        ~Children();

        float position[2];
        float distance;
        float angle;
        float depth;

        Mesh *mesh;
        Children *next;
    };

    void SetVertexData(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f);
    void SetVertexData(vec::vec2 width, vec::vec2 height);
    void SetTexcoordData(float left = 0.0f, float right = 1.0f, float bottom = 0.0f, float top = 1.0f);
    void SetTexcoordData(vec::vec2 width, vec::vec2 height);
    void SetColorData(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 0.0f);
    void SetDepth(float _depth);
    void SetPosition(float x, float y);
    void SetPosition(vec::vec2 _position);
    void SetLocalPosition(float x, float y);
    void SetColor(float red, float green, float blue);
    void SetColor(int red, int green, int blue);
    void SetColor(vec::vec3 color);
    void SetAlpha(float alpha);
    void SetCulling(MeshType::Culling _type);
    void SetSize(float _size, bool childrenToo = false);
    void SetAngle(float _angle);
    void SetAxis(float x, float y);
    void SetDirection(float x, float y);
    void SetDirection(vec::vec2 _position);
    void SetVelocity(float _velocity);
    void SetHierarchy(Mesh *_mesh, int depthPriority = 0, float x = 0.0f, float y = 0.0f);
    void SetClickType(MeshType::Click type);
    void SetClickRange(float radius);
    void SetClickRange(float width, float height);

    float GetDepth();
    vec::vec2 GetPosition();
    MeshType::Culling GetCulling();
    vec::vec2 GetDirection();
    float GetVelocity();
    Camera *GetCamera();

    void Move();
    void Push(float x, float y);
    void Scale(float _size, bool childrenToo = false);
    void Extend(float _width, float _height, bool childrenToo = false);
    void Rotation(float _angle);
    void Brightness(float value);
    void Opacity(float value);
    void Flip();
    void LookForward();
    void PutBack();
    void Focus(Camera *_camera);
    void Destroy();

    void ConvertMatrix();
    void ConvertTexcoord();
    void ConvertColor();

    void ReleaseHierarchy(bool childrenToo = false);
    void DetachCamera();

    void CopyVertex(Mesh *target);
    void CopyTexcoord(Mesh *target);
    void CopyColor(Mesh *target);

    bool ClickCheck(float x, float y);
    bool Click(float x, float y);
    void ClickInit();
    bool ClickUp(float x, float y);

    bool isClicked();
    bool isDestroyed();


    const int signature;

    float vertexData[8];
    float texcoordData[8];
    float colorData[4];
    float depth;
    float position[2];
    float localPosition[2];
    float size;
    float angle;
    float axis[2];
    float valve;
    float direction[2];
    float velocity;
    float brightness;
    float opacity;
    float width, height;
    float matrix[8];
    float clickRadius;
    float clickRectWidth, clickRectHeight;

    bool convertMatrix;
    bool convertTexcoord;
    bool convertColor;
    bool destroy;
    bool clicked;
    bool activated;

    MeshType::Click clickType;
    MeshType::Culling cullingType;

    Mesh *next;
    Children *children;
    Layer *layer;
    Camera *camera;

    friend class Layer;
    friend class MeshLayer;
    friend class RenderManager;
    friend class Object;
    friend class Collider;
};

#endif //MESH_HPP