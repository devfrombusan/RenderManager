#include "Layer.hpp"

Mesh::Mesh(const int _signature) : signature(_signature) {

    float vertexInit[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f};
    for(int i = 0; i < 8; i++) vertexData[i] = vertexInit[i];

    float texcoordInit[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
    for(int i = 0; i < 8; i++) texcoordData[i] = texcoordInit[i];

    for (int i = 0; i < 3; i++) colorData[i] = 1.0f;
    colorData[3] = 0.0f;

    for (int i = 0; i < 8; i++) matrix[i] = vertexData[i];

    brightness = 1.0f;
    opacity = 1.0f;

    localPosition[0] = 0.0f;
    localPosition[1] = 0.0f;

    depth = 0.0f;

    position[0] = 0.0f;
    position[1] = 0.0f;

    direction[0] = 1.0f;
    direction[1] = 0.0f;

    velocity = 0.0f;

    axis[0] = 0.0f;
    axis[1] = 0.0f;

    size = 1.0f;
    angle = 0.0f;
    valve = 0.0f;

    width = 1.0f;
    height = 1.0f;

    destroy = false;
    next = nullptr;
    children = nullptr;
    layer = nullptr;
    camera = nullptr;

    convertMatrix = false;
    convertTexcoord = false;
    convertColor = false;

    clickType = MeshType::Click::NON;
    cullingType = MeshType::Culling::CW;

    clickRadius = 1.0f;
    clickRectWidth = 1.0f;
    clickRectHeight = 1.0f;

    clicked = false;
    activated = false;
}

Mesh::~Mesh(){

    while (children) {
        Children *temp = children->next;
        delete children;
        children = temp;
    }
}

void Mesh::SetVertexData(float left, float right, float bottom, float top) {

    float init[] =
            {left + localPosition[0], bottom + localPosition[1],
             left + localPosition[0], top + localPosition[1],
             right + localPosition[0], top + localPosition[1],
             right + localPosition[0], bottom + localPosition[1]};

    for (int i = 0; i < 8; i++) vertexData[i] = init[i];
    for (int i = 0; i < 8; i++) matrix[i] = vertexData[i];
}

void Mesh::SetVertexData(vec::vec2 width, vec::vec2 height) {

    float init[] =
            {width[0] + localPosition[0], height[0] + localPosition[1],
             width[0] + localPosition[0], height[1] + localPosition[1],
             width[1] + localPosition[0], height[1] + localPosition[1],
             width[1] + localPosition[0], height[0] + localPosition[1]};

    for (int i = 0; i < 8; i++) vertexData[i] = init[i];
    for (int i = 0; i < 8; i++) matrix[i] = vertexData[i];
}

void Mesh::SetTexcoordData(float left, float right, float bottom, float top) {

    float init[] =
            {left, bottom, left, top, right, top, right, bottom};

    for(int i = 0; i < 8; i++) texcoordData[i] = init[i];
}

void Mesh::SetTexcoordData(vec::vec2 width, vec::vec2 height) {

    float init[] =
            {width[0], height[0], width[0], height[1], width[1], height[1], width[1], height[0]};

    for(int i = 0; i < 8; i++) texcoordData[i] = init[i];
}

void Mesh::SetColorData(float red, float green, float blue, float alpha) {
    colorData[0] = red;
    colorData[1] = green;
    colorData[2] = blue;
    colorData[3] = alpha;
}

void Mesh::SetDepth(float _depth) {

    depth = _depth;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetDepth(_depth);
        temp->mesh->depth += temp->depth;
        temp = temp->next;
    }
}

void Mesh::SetPosition(float x, float y) {

    float tempX, tempY;

    tempX = x - position[0];
    tempY = y - position[1];

    position[0] = x;
    position[1] = y;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->Push(tempX, tempY);
        temp = temp->next;
    }
}

void Mesh::SetPosition(vec::vec2 _position) {

    float tempX, tempY;

    tempX = _position[0] - position[0];
    tempY = _position[1] - position[1];

    position[0] = _position[0];
    position[1] = _position[1];

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->Push(tempX, tempY);
        temp = temp->next;
    }
}

void Mesh::SetLocalPosition(float x, float y) {

    localPosition[0] = x;
    localPosition[1] = y;

    for(int i = 0; i < 4; i++){
        vertexData[2 * i] += x;
        vertexData[2 * i + 1] += y;
    }

    for (int i = 0; i < 8; i++) matrix[i] = vertexData[i];
}

void Mesh::SetColor(float red, float green, float blue) {

    colorData[0] = red;
    colorData[1] = green;
    colorData[2] = blue;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetColor(red, green, blue);
        temp = temp->next;
    }
}

void Mesh::SetColor(int red, int green, int blue) {

    if(red < 0) red = 0;
    if(red > 255) red = 255;

    if(green < 0) green = 0;
    if(green > 255) green = 255;

    if(blue < 0) blue = 0;
    if(blue > 255) blue = 255;


    colorData[0] = (float)red / (float)255;
    colorData[1] = (float)green / (float)255;
    colorData[2] = (float)blue / (float)255;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetColor(red, green, blue);
        temp = temp->next;
    }
}

void Mesh::SetColor(vec::vec3 color) {

    colorData[0] = color[0];
    colorData[1] = color[1];
    colorData[2] = color[2];

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetColor(color);
        temp = temp->next;
    }
}

void Mesh::SetAlpha(float alpha) {

    colorData[3] = alpha;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetAlpha(alpha);
        temp = temp->next;
    }
}

void Mesh::SetCulling(MeshType::Culling _type) {

    if (cullingType == _type) return;

    cullingType = _type;

    Children *temp = children;

    while (temp != nullptr) {
        temp->angle = Tools::YAxisSymmetryAngle(temp->angle);
        temp->position[0] =
                cos((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;
        temp->position[1] =
                sin((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;


        temp->mesh->SetPosition(position[0] + temp->position[0],
                                position[1] + temp->position[1]);
        temp->mesh->SetCulling(cullingType);
        temp->mesh->ConvertTexcoord();

        temp = temp->next;
    }
}

void Mesh::SetSize(float _size, bool childrenToo) {

    size = _size;

    if(childrenToo){
        Children *temp = children;

        while (temp != nullptr) {
            temp->position[0] = Tools::Normalization(temp->angle)[0] * temp->distance * size;
            temp->position[1] = Tools::Normalization(temp->angle)[1] * temp->distance * size;
            temp->mesh->SetPosition(position[0] + temp->position[0],
                                    position[1] + temp->position[1]);

            temp->mesh->SetSize(_size, true);
            temp = temp->next;
        }
    }
}

void Mesh::SetAngle(float _angle) {

    angle = _angle;
    valve = 0.0f;

    Children *temp = children;

    while (temp != nullptr) {

        temp->position[0] =
                cos((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;
        temp->position[1] =
                sin((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;

        temp->mesh->SetPosition(position[0] + temp->position[0],
                                position[1] + temp->position[1]);

        temp = temp->next;
    }
}

void Mesh::SetAxis(float x, float y) {
    axis[0] = x;
    axis[1] = y;
}

void Mesh::SetDirection(float x, float y) {

    float length = sqrtf((x * x) + (y * y));

    direction[0] = x / length;
    direction[1] = y / length;
}

void Mesh::SetDirection(vec::vec2 _position) {

    float length = sqrtf((_position[0] * _position[0]) + (_position[1] * _position[1]));

    direction[0] = _position[0] / length;
    direction[1] = _position[1] / length;
}

void Mesh::SetVelocity(float _velocity) {
    velocity = _velocity;
}

void Mesh::SetHierarchy(Mesh *_mesh, int depthPriority, float x, float y) {

    if (!_mesh) return;
    Children *temp = children;
    children = new Children(this, _mesh, depthPriority, x, y);
    _mesh->SetPosition(x, y);
    _mesh->SetDepth(depth);
    children->next = temp;
}

void Mesh::SetClickType(MeshType::Click type) {
    clickType = type;
}

void Mesh::SetClickRange(float radius) {
    clickRadius = radius;
}

void Mesh::SetClickRange(float width, float height) {
    clickRectWidth = width;
    clickRectHeight = height;
}

float Mesh::GetDepth() {
    return depth;
}

vec::vec2 Mesh::GetPosition() {
    vec::vec2 result = vec::vec2(position[0], position[1]);

    return result;
}

MeshType::Culling Mesh::GetCulling() {
    return cullingType;
}

vec::vec2 Mesh::GetDirection() {
    return vec::vec2(direction[0], direction[1]);
}

float Mesh::GetVelocity() {
    return velocity;
}

Camera * Mesh::GetCamera() {
    return camera;
}

void Mesh::Move() {

    position[0] += (velocity * direction[0]);
    position[1] += (velocity * direction[1]);

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetDirection(direction[0], direction[1]);
        temp->mesh->SetVelocity(velocity);
        temp->mesh->Push((velocity * direction[0]), (velocity * direction[1]));
        temp = temp->next;
    }
}

void Mesh::Push(float x, float y) {

    position[0] += x;
    position[1] += y;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetDirection(direction[0], direction[1]);
        temp->mesh->SetVelocity(velocity);
        temp->mesh->Push(x, y);
        temp = temp->next;
    }
}

void Mesh::Scale(float _size, bool childrenToo) {

    size += _size;

    if(childrenToo){
        Children *temp = children;

        while (temp != nullptr) {
            temp->mesh->Scale(_size, true);
            temp = temp->next;
        }
    }
}

void Mesh::Extend(float _width, float _height, bool childrenToo) {

    width = _width;
    height = _height;

    if(childrenToo){
        Children *temp = children;

        while (temp != nullptr) {
            temp->mesh->Extend(_width, _height, true);
            temp = temp->next;
        }
    }
}

void Mesh::Rotation(float _angle) {

    angle += _angle;

    Children *temp = children;

    while (temp != nullptr) {

        temp->position[0] =
                cos((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;
        temp->position[1] =
                sin((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;

        temp->mesh->SetPosition(position[0] + temp->position[0],
                                position[1] + temp->position[1]);

        temp = temp->next;
    }
}

void Mesh::Brightness(float value) {

    brightness = value;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->Brightness(value);
        temp = temp->next;
    }
}

void Mesh::Opacity(float value) {

    if(value < 0.0f) value = 0.0f;
    if(value > 1.0f) value = 1.0f;
    opacity = value;
}

void Mesh::Flip() {

    if (cullingType == MeshType::Culling::CW) cullingType = MeshType::Culling::CCW;
    else cullingType = MeshType::Culling::CW;

    Children *temp = children;

    while (temp != nullptr) {
        temp->angle = Tools::YAxisSymmetryAngle(temp->angle);
        temp->position[0] =
                cos((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;
        temp->position[1] =
                sin((temp->angle + cullingType * angle) * 0.017453f) * temp->distance;
        temp->mesh->SetPosition(position[0] + temp->position[0],
                                position[1] + temp->position[1]);
        temp->mesh->Flip();
        temp->mesh->ConvertTexcoord();
        temp = temp->next;
    }
}

void Mesh::LookForward() {

    if (direction[0] >= 0.0f) SetCulling(MeshType::Culling::CW);
    else SetCulling(MeshType::Culling::CCW);
}

void Mesh::PutBack() {

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->SetPosition(position[0] + temp->position[0],
                                position[1] + temp->position[1]);
        temp->mesh->PutBack();
        temp = temp->next;
    }
}

void Mesh::Focus(Camera *_camera) {

    camera = _camera;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->Focus(camera);
        temp = temp->next;
    }
}

void Mesh::Destroy() {
    if (!destroy) destroy = true;
}

void Mesh::ConvertMatrix() {

    if (!convertMatrix) convertMatrix = true;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->ConvertMatrix();
        temp = temp->next;
    }
}

void Mesh::ConvertTexcoord() {

    if (!convertTexcoord) convertTexcoord = true;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->ConvertTexcoord();
        temp = temp->next;
    }
}

void Mesh::ConvertColor() {

    if (!convertColor) convertColor = true;

    Children *temp = children;

    while (temp != nullptr) {
        temp->mesh->ConvertColor();
        temp = temp->next;
    }
}

void Mesh::ReleaseHierarchy(bool childrenToo) {

    Children *temp = nullptr;

    while (children != nullptr) {
        temp = children->next;
        if(childrenToo) if(temp) temp->mesh->ReleaseHierarchy();
        delete children;
        children = temp;
    }
}

void Mesh::DetachCamera() {
    camera = nullptr;
}

void Mesh::CopyVertex(Mesh *target) {
    for (int i = 0; i < 8; i++) target->vertexData[i] = vertexData[i];
}

void Mesh::CopyTexcoord(Mesh *target) {
    for (int i = 0; i < 8; i++) target->texcoordData[i] = texcoordData[i];
}

void Mesh::CopyColor(Mesh *target) {
    for (int i = 0; i < 4; i++) target->colorData[i] = colorData[i];
}

bool Mesh::ClickCheck(float x, float y) {

    switch (clickType) {
        case MeshType::Click::NON:
            return false;
        case MeshType::Click::CIRCLE:
            if (Tools::Distance(position[0], position[1], x, y) < clickRadius) return true;
            return false;
        case MeshType::Click::RECT:
            if (x > (-clickRectWidth / 2.0f + position[0]) &&
                x < (clickRectWidth / 2.0f + position[0]) &&
                y > (-clickRectHeight / 2.0f + position[1]) &&
                y < (clickRectHeight / 2.0f + position[1]))
                return true;

            return false;
    }
}

bool Mesh::Click(float x, float y) {

    if (isClicked()) return false;

    switch (clickType) {
        case MeshType::Click::NON:
            return false;
        case MeshType::Click::CIRCLE:
            if (Tools::Distance(position[0], position[1], x, y) < clickRadius) {
                clicked = true;
                return true;
            }
            return false;
        case MeshType::Click::RECT:
            if (x > (-clickRectWidth / 2.0f + position[0]) &&
                x < (clickRectWidth / 2.0f + position[0]) &&
                y > (-clickRectHeight / 2.0f + position[1]) &&
                y < (clickRectHeight / 2.0f + position[1])) {
                clicked = true;
                return true;
            }
            return false;
    }
}

void Mesh::ClickInit() {

    if (!isClicked()) return;

    clicked = false;
}

bool Mesh::ClickUp(float x, float y) {

    if (!isClicked()) return false;

    clicked = false;

    switch (clickType) {
        case MeshType::Click::NON:
            return false;
        case MeshType::Click::CIRCLE:
            if (Tools::Distance(position[0], position[1], x, y) < clickRadius) {
                return true;
            }
            return false;
        case MeshType::Click::RECT:
            if (x > (-clickRectWidth / 2.0f + position[0]) &&
                x < (clickRectWidth / 2.0f + position[0]) &&
                y > (-clickRectHeight / 2.0f + position[1]) &&
                y < (clickRectHeight / 2.0f + position[1])) {
                return true;
            }
            return false;
    }
}

bool Mesh::isClicked() {
    return clicked;
}

bool Mesh::isDestroyed() {
    return destroy;
}

Mesh::Children::Children(Mesh *standard, Mesh *_mesh, int depthPriority, float x, float Y) {

    mesh = _mesh;
    next = nullptr;
    position[0] = x + standard->localPosition[0];
    position[1] = Y + standard->localPosition[1];

    _mesh->SetLocalPosition(-_mesh->axis[0], -_mesh->axis[1]);
    _mesh->SetAxis(0.0f, 0.0f);

    depth = -0.01f * (float) depthPriority;

    distance = Tools::Distance(standard->axis[0], standard->axis[1], position[0],
                               position[1]);

    vec::vec2 direction = Tools::Normalization(standard->axis[0], standard->axis[1],
                                               position[0],
                                               position[1]);

    angle = atan2(direction[1], direction[0]) *
            57.295780f;
}

Mesh::Children::~Children() {
    mesh = nullptr;
}