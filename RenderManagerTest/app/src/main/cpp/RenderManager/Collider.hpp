#ifndef COLLIDER_HPP
#define COLLIDER_HPP

class Mesh;

class Collider {
public:
    Collider();
    ~Collider();

private:
    void SetCollisionVertex(float width, float height);
    void Collide(Mesh *mesh, Collider *collider, Mesh *targetMesh, bool slide = false);
    void Look(Mesh *mesh, Mesh *targetMesh);
    void InitCollider();
    bool isCollided();

    float vertex[8];
    float velocity;
    float maxDistance;

    vec::vec2 direction;
    vec::vec2 position;
    bool collided;

    friend class Object;
};

#endif //COLLIDER_HPP
