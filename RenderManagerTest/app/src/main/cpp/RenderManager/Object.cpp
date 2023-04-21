#include "Layer.hpp"


Object::Object() {
    mesh = nullptr;
    collider = nullptr;
}

Object::~Object(){
    if (mesh){
        mesh->Destroy();
    }

    if (collider) {
        delete collider;
        collider = nullptr;
    }
}

Object * Object::SetVertexData(float left, float right, float bottom, float top) {
    if (mesh) mesh->SetVertexData(left, right, bottom, top);
    return this;
}

Object * Object::SetVertexData(vec::vec2 width, vec::vec2 height) {
    if (mesh) mesh->SetVertexData(width, height);
    return this;
}

Object * Object::SetTexcoordData(float left, float right, float bottom, float top) {
    if (mesh) mesh->SetTexcoordData(left, right, bottom, top);
    return this;
}

Object * Object::SetTexcoordData(vec::vec2 width, vec::vec2 height) {
    if (mesh) mesh->SetTexcoordData(width, height);
    return this;
}

Object * Object::SetColorData(float red, float green, float blue, float alpha) {
    if (mesh) mesh->SetColorData(red, green, blue, alpha);
    return this;
}

Object * Object::SetDepth(float depth) {
    if (mesh) mesh->SetDepth(depth);
    return this;
}

Object * Object::SetPosition(float x, float y) {
    if (mesh) mesh->SetPosition(x, y);
    return this;
}

Object * Object::SetPosition(vec::vec2 position) {
    if (mesh) mesh->SetPosition(position);
    return this;
}

Object * Object::SetLocalPosition(float x, float y) {
    if (mesh) mesh->SetLocalPosition(x, y);
    return this;
}

Object * Object::SetColor(float red, float green, float blue) {
    if (mesh) mesh->SetColor(red, green, blue);
    return this;
}

Object * Object::SetColor(int red, int green, int blue) {
    if (mesh) mesh->SetColor(red, green, blue);
    return this;
}

Object * Object::SetColor(vec::vec3 color) {
    if (mesh) mesh->SetColor(color);
    return this;
}

Object * Object::SetAlpha(float alpha) {
    if (mesh) mesh->SetAlpha(alpha);
    return this;
}

Object * Object::SetCulling(MeshType::Culling type) {
    if (mesh) mesh->SetCulling(type);
    return this;
}

Object * Object::SetSize(float size, bool childrenToo) {
    if (mesh) mesh->SetSize(size, childrenToo);
    return this;
}

Object * Object::SetAngle(float angle) {
    if (mesh) mesh->SetAngle(angle);
    return this;
}

Object * Object::SetAxis(float x, float y) {
    if (mesh) mesh->SetAxis(x, y);
    return this;
}

Object * Object::SetDirection(float x, float y) {
    if (mesh) mesh->SetDirection(x, y);
    return this;
}

Object * Object::SetDirection(vec::vec2 position) {
    if (mesh) mesh->SetDirection(position);
    return this;
}

Object * Object::SetVelocity(float velocity) {
    if (mesh) mesh->SetVelocity(velocity);
    return this;
}

Object * Object::SetHierarchy(Object *object, int depthPriority, float x, float y) {
    if (mesh) if (object) mesh->SetHierarchy(object->mesh, depthPriority, x, y);
    return this;
}

Object * Object::SetClickType(MeshType::Click type) {
    if (mesh) mesh->SetClickType(type);
    return this;
}

Object * Object::SetClickRange(float radius) {
    if (mesh) mesh->SetClickRange(radius);
    return this;
}

Object * Object::SetClickRange(float width, float height) {
    if (mesh) mesh->SetClickRange(width, height);
    return this;
}

float Object::GetDepth() {
    if (mesh) return mesh->GetDepth();

    return 0.0f;
}

vec::vec2 Object::GetPosition() {
    if (mesh) return mesh->GetPosition();

    return vec::vec2(0.0f, 0.0f);
}

MeshType::Culling Object::GetCulling() {
    if (mesh) return mesh->GetCulling();
    return MeshType::Culling::CW;
}

vec::vec2 Object::GetDirection() {
    if(mesh) return mesh->GetDirection();

    return vec::vec2(0.0f, 0.0f);
}

float Object::GetVelocity() {
    if (mesh) return mesh->GetVelocity();

    return 0.0f;
}

Camera * Object::GetCamera() {
    if (mesh) return mesh->GetCamera();
    return nullptr;
}

Object * Object::Move() {
    if (mesh) mesh->Move();
    return this;
}

Object * Object::Scale(float size, bool childrenToo) {
    if (mesh) mesh->Scale(size, childrenToo);
    return this;
}

Object * Object::Extend(float width, float height, bool childrenToo) {
    if(mesh) mesh->Extend(width, height, childrenToo);
    return this;
}

Object * Object::Rotation(float angle) {
    if (mesh) mesh->Rotation(angle);
    return this;
}

Object * Object::Brightness(float value) {
    if (mesh) mesh->Brightness(value);
    return this;
}

Object * Object::Opacity(float value) {
    if(mesh) mesh->Opacity(value);
    return this;
}

Object * Object::Flip() {
    if (mesh) mesh->Flip();
    return this;
}

Object * Object::LookForward() {
    if (mesh) mesh->LookForward();
    return this;
}

Object * Object::PutBack() {
    if (mesh) mesh->PutBack();
    return this;
}

Object * Object::Focus(Camera *camera) {
    if (camera) if (mesh) mesh->Focus(camera);
    return this;
}

Object * Object::ConvertMatrix() {
    if (mesh) mesh->ConvertMatrix();
    return this;
}

Object * Object::ConvertTexcoord() {
    if (mesh) mesh->ConvertTexcoord();
    return this;
}

Object * Object::ConvertColor() {
    if (mesh) mesh->ConvertColor();
    return this;
}

Object * Object::ReleaseHierarchy(bool childrenToo) {
    if (mesh) mesh->ReleaseHierarchy(childrenToo);
    return this;
}

Object * Object::DetachCamera() {
    if (mesh) mesh->DetachCamera();
    return this;
}

void Object::CopyVertex(Object *target) {
    if(mesh) mesh->CopyVertex(target->mesh);
}

void Object::CopyTexcoord(Object *target) {
    if(mesh) mesh->CopyTexcoord(target->mesh);
}

void Object::CopyColor(Object *target) {
    if(mesh) mesh->CopyColor(target->mesh);
}

bool Object::ClickCheck(float x, float y) {
    if(mesh) return mesh->ClickCheck(x, y);
    return false;
}

bool Object::Click(float x, float y) {
    if (mesh) return mesh->Click(x, y);
    return false;
}

void Object::ClickInit() {
    if (mesh) mesh->ClickInit();
}

bool Object::ClickUp(float x, float y) {
    if (mesh) return mesh->ClickUp(x, y);
    return false;
}

bool Object::isClicked() {
    if (mesh) return mesh->isClicked();
    return false;
}

bool Object::isCollided() {
    if (collider) return collider->isCollided();

    return false;
}

Object *Object::Visible() {

    if (!mesh) return this;

    mesh->activated = true;
    mesh->layer->needMaterialize = true;

    Mesh::Children *temp = mesh->children;

    while (temp != nullptr) {
        if (temp->mesh) {
            temp->mesh->activated = true;
            temp->mesh->layer->needMaterialize = true;
        }
        temp = temp->next;
    }

    return this;
}

Object *Object::Invisible() {

    if (!mesh) return this;

    mesh->activated = false;
    mesh->layer->needMaterialize = true;


    Mesh::Children *temp = mesh->children;

    while (temp != nullptr) {
        if (temp->mesh) {
            temp->mesh->activated = false;
            temp->mesh->layer->needMaterialize = true;
        }
        temp = temp->next;
    }

    return this;
}

Object * Object::ActivateCollider() {
    if (!collider) collider = new Collider();
    return this;
}

Object * Object::SetCollisionVertex(float width, float height) {
    if (collider) collider->SetCollisionVertex(width, height);
    return this;
}

Object * Object::Collide(Object *object, bool slide) {
    if (collider)
        if (mesh)
            if (object)
                if (object->collider) {
                    collider->Collide(mesh, object->collider, object->mesh, slide);
                    mesh->SetDirection(collider->direction[0], collider->direction[1]);
                    mesh->SetVelocity(collider->velocity);
                }

    return this;
}

Object * Object::Look(Object *object) {
    if (collider)
        if (mesh)
            if (object)
                if (object->collider) {
                    collider->Look(mesh, object->mesh);
                    mesh->SetDirection(collider->direction[0], collider->direction[1]);
                }

    return this;
}

void Object::InitCollider() {
    if (collider) collider->InitCollider();
}

void Object::Destroy() {
    if (mesh) {
        mesh->Destroy();
        mesh = nullptr;
    }
}