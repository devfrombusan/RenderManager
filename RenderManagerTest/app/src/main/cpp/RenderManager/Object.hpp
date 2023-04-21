#include "Mesh.hpp"
#include "Collider.hpp"

#ifndef OBJECT_HPP
#define OBJECT_HPP

class mesh;

class Object {
public:
    Object();
    ~Object();

    Object *SetVertexData(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f);
    Object *SetVertexData(vec::vec2 width, vec::vec2 height);
    Object *SetTexcoordData(float left = 0.0f, float right = 1.0f, float bottom = 0.0f, float top = 1.0f);
    Object *SetTexcoordData(vec::vec2 width, vec::vec2 height);
    Object *SetColorData(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f);
    Object *SetDepth(float depth);
    Object *SetPosition(float x, float y);
    Object *SetPosition(vec::vec2 position);
    Object *SetLocalPosition(float x, float y);
    Object *SetColor(float red, float green, float blue);
    Object *SetColor(int red, int green, int blue);
    Object *SetColor(vec::vec3 color);
    Object *SetAlpha(float alpha);
    Object *SetCulling(MeshType::Culling type);
    Object *SetSize(float size, bool childrenToo = false);
    Object *SetAngle(float angle);
    Object *SetAxis(float x, float y);
    Object *SetDirection(float x, float y);
    Object *SetDirection(vec::vec2 position);
    Object *SetVelocity(float velocity);
    Object *SetHierarchy(Object *object, int depthPriority = 0, float x = 0.0f, float y = 0.0f);
    Object *SetClickType(MeshType::Click type);
    Object *SetClickRange(float radius);
    Object *SetClickRange(float width, float height);

    float GetDepth();
    vec::vec2 GetPosition();
    MeshType::Culling GetCulling();
    vec::vec2 GetDirection();
    float GetVelocity();
    Camera *GetCamera();

    Object *Move();
    Object *Scale(float size, bool childrenToo = false);
    Object *Extend(float width, float height, bool childrenToo = false);
    Object *Rotation(float angle);
    Object *Brightness(float value);
    Object* Opacity(float value);
    Object *Flip();
    Object *LookForward();
    Object *PutBack();
    Object *Focus(Camera *camera);

    Object *ConvertMatrix();
    Object *ConvertTexcoord();
    Object *ConvertColor();

    Object *ReleaseHierarchy(bool childrenToo = false);
    Object *DetachCamera();

    void CopyVertex(Object* target);
    void CopyTexcoord(Object* target);
    void CopyColor(Object* target);

    bool ClickCheck(float x, float y);
    bool Click(float x, float y);
    void ClickInit();
    bool ClickUp(float x, float y);

    bool isClicked();
    bool isCollided();

    Object *Visible();
    Object *Invisible();

    Object *ActivateCollider();
    Object *SetCollisionVertex(float width, float height);
    Object *Collide(Object *object, bool slide = false);
    Object *Look(Object *object);
    void InitCollider();

private:
    void Destroy();

    Mesh *mesh;
    Collider *collider;

    friend class RenderManager;
};

#endif //OBJECT_HPP
