#include "Layer.hpp"

Collider::Collider() {
    collided = false;
    velocity = 0.0f;
    maxDistance = 0.0f;
}

Collider::~Collider() {

}

void Collider::SetCollisionVertex(float width, float height) {


    //메쉬를 구성하는 버텍스가 아닌 충돌에 사용될 버텍스를 구성해서 전달해야 한다


    vertex[0] = -width / 2.0f;
    vertex[1] = -height / 2.0f;

    vertex[2] = -width / 2.0f;
    vertex[3] = height / 2.0f;

    vertex[4] = width / 2.0f;
    vertex[5] = height / 2.0f;

    vertex[6] = width / 2.0f;
    vertex[7] = -height / 2.0f;

    maxDistance = Tools::Distance(0.0f, 0.0f, width / 2.0f, height / 2.0f);
}

void Collider::Collide(Mesh *mesh, Collider *collider, Mesh *targetMesh, bool slide) {

    /*
        충돌처리를 하는 메쉬는 Collider를 자체적으로 생성을 하도록 지정해야 한다
        Collider == null 인 Mesh는 충돌처리 대상에서 애초에 제외가 된다
    */

    vec::vec2 destination; // 도착지점

    vec::vec2 targetPosition; // 검사 대상의 위치
    vec::vec2 targetOrigin; // 두 점을 연결한 직선의 첫번째 점(시계방향)
    vec::vec2 targetPoints; // 두 점을 연결한 직선의 두번째 점(시계방향)
    vec::vec2 targetNormalVector; // 두 점을 연결한 직선의 법선벡터

    float targetVertex[8];

    vec::vec2 vector1;
    vec::vec2 vector2;

    vec::vec2 meet;

    float dot;
    float space;

    velocity = mesh->velocity;

    if(velocity <= 0.0f) return;

    position[0] = mesh->position[0];
    position[1] = mesh->position[1];

    direction[0] = mesh->direction[0];
    direction[1] = mesh->direction[1];
    // 벡터 계산을 위해서 진행방향을 설정

    destination[0] = position[0] + (velocity * direction[0]);
    destination[1] = position[1] + (velocity * direction[1]);
    // 도착 지점은 현재 위치에서 속력과 진행방향을 곱한 값

    targetPosition[0] = targetMesh->position[0];
    targetPosition[1] = targetMesh->position[1];
    // 대상의 위치는 대상이 가진 메쉬의 위치와 동일하도록 함

    float distance = Tools::Distance(position[0], position[1], targetPosition[0], targetPosition[1]);
    // 대상의 메쉬를 통과하는지 확인하기 위해 우선 거리를 미리 측정함

    if (distance - (maxDistance + collider->maxDistance + velocity) > 0.001f) { 
        /*
            한 프레임에서 이동을 할 때 검사 대상의 거리를 측정하고
            속력(이동거리)를 더해서 지나가지 않는다고 판단될 때는 애초에 검사대상에서 제외하도록
            첫번째 최적화를 진행
        */
        velocity = mesh->velocity;
        // 속력을 검사하고 검사대상에서 제외되는 경우에는 기존의 속도로 계속 이동을 하도록 한다
        return;
    }

    for(int i = 0; i < 4; i++){
        // 두 충돌 범위를 서로 비교하지 않고
        // 대상의 충돌 버텍스에 자신의 충돌 버텍스를 더해서 하나의 메쉬로 합치도록 한다
        targetVertex[2 * i] = collider->vertex[2 * i] + vertex[2 * i];
        targetVertex[2 * i + 1] = collider->vertex[2 * i + 1] + vertex[2 * i + 1];
    }

    for (int i = 0; i < 4; i++) {

        targetOrigin[0] = targetVertex[2 * i] + targetPosition[0];
        targetOrigin[1] = targetVertex[2 * i + 1] + targetPosition[1];

        // 시계방향으로 n번째와 n+1번째의 점을 연결하여 하나의 직선으로 만든다
        // 만약 마지막 번째의 경우 첫번째 점을 연결하도록 한다

        if (i == 3) {
            targetPoints[0] = targetVertex[0] + targetPosition[0];
            targetPoints[1] = targetVertex[1] + targetPosition[1];
        } else {
            targetPoints[0] = targetVertex[2 * i + 2] + targetPosition[0];
            targetPoints[1] = targetVertex[2 * i + 3] + targetPosition[1];
        }
        

        targetNormalVector = Tools::NormalVector(targetOrigin, targetPoints); 
        // 검사 대상인 직선의 법선벡터
        dot = Tools::Dot(direction, targetNormalVector); 
        // 자신이 진행하는 뱡항과 법선벡터의 코사인
        if (dot >= 0.0f) continue; 
        // 코사인 값이 음수인 경우는 직선과 진행방향과 마주 보고 있음을 나타낸다
        // 0보다 큰 경우는 마주 보고 있지 않기 때문에 검사 대상에서 제외 하고 최적화를 진행


        vector1 = Tools::Normalization(targetOrigin, position); 
        // 검사 대상의 첫번째 점과 자신의 중심점 단위벡터(크기를 1로 하기 위함)
        dot = Tools::Dot(targetNormalVector, vector1); 
        // 대상 직선의 법선벡터와 vector1의 코사인
        if (dot < -0.001f) continue;
        // 코사인 값이 0보다 큰 경우는 중심점이 직선을 지나갔음을 의미함
        // 충돌을 확인해야 할 점이 이미 대상 직선을 통과 한 경우는 서로 마주보는 경우일지라도 제외를 시켜야 함

        vector1 = Tools::Normalization(targetOrigin, destination);
        // 검사 대상의 첫번째 점과 자신의 도착점 단위벡터
        dot = Tools::Dot(targetNormalVector, vector1);
        // 도착점과 vector1의 코사인
        if (dot > 0.001f) continue;
        // 코사인값이 음수인 경우는 도착점이 대상의 직선을 통과했음을 의미함
        // 도착점이 대상점을 지나지 않는 경우는 충돌을 안 할 것임을 의미하므로 검사를 제외시킴
 
        vector1 = Tools::NormalVector(position, targetOrigin);
        // 자신의 위치와 대상의 첫번째 점의 법선벡터
        dot = Tools::Dot(vector1, direction);
        // 방향과 vector1의 코사인
        // 코사인 값이 양수인 경우는 자신이 진행하는 방향의 범위가 직선 범위 내에 포함된다는 의미
        // 양수가 아닌경우는 0 또는 음수 두가지를 검사 해야 함
        if (dot <= 0.001f){
            vector1 = Tools::Normalization(targetOrigin, targetPosition);
            dot = Tools::Dot(vector1, direction);
            // 모서리 충돌을 판단하며 코사인이 음수인 경우는 모서리와 충돌하지 않음을 뜻함
            if(dot < 0.001f) continue;
        }

        vector1 = Tools::NormalVector(position, targetPoints);
        // 대상 직선의 두번째 점을 검사하고
        // 첫번째 점과 같은 검사를 실시함
        // 단 방향이 다르므로 내적값도 그 반대가 된다
        dot = Tools::Dot(vector1, direction);
        if (dot >= -0.001f){
            vector1 = Tools::Normalization(targetPoints, targetPosition);
            dot = Tools::Dot(vector1, direction);
            if(dot < 0.001f) continue;
        }


        // 충돌검사를 위한 최적화가 모두 진행되었으므로
        // 이제부터는 충돌되었다고 판단하고
        // 실제 이동을 해야 하는 거리를 계산해서
        // 자신의 위치를 결정하도록 한다

        vector1 = Tools::Normalization(targetOrigin, position); // 자신의 위치와 대상의 첫번째 점의 단위벡터
        vector2 = Tools::Normalization(targetOrigin, targetPoints); // 대상의 직선의 단위 벡터
        dot = Tools::Dot(vector1, vector2);
        space = Tools::Distance(targetOrigin, position) * (1.0f - dot);
        // 대상의 첫번째 점과 자신의 위치의 거리를 구함
        // 거리에 해당하는 직선과 대상의 직선의 각도가 vector1과 vector2의 코사인 값에 해당
        // (1 - 코사인) 값으로 좌표상 y에 해당하는 값을 구함
        // 구한 y가 실제 직선(평면)과 자신의 위치의 거리가 된다
        vector1 = Tools::ReverseVector(targetNormalVector);
        // 공간의 방향은 대상 직선의 법선벡터의 반대에 해당
        dot = Tools::Dot(vector1, direction);
        // 실제로 자신은 자신의 진행방향으로 속력을 곱해서 이동하게 됨
        // 진행방향과 공간의 방향의 코사인 값을 한번더 구함
        space = space / dot;
        // 실제 공간은 자신의 진행방향에 대한 거리값이 됨

        collided = true; // 충돌되었음을 알리는 flag var

        if (velocity - space > 0.001f) velocity = space - 0.001f;
        if (velocity <= 0.001f) velocity = 0.0f;

        /* 
        if (slide) {
            if(velocity > 0.0f) continue;

            vector1 = Tools::Normalization(targetOrigin, targetPosition);
            vector2 = Tools::Normalization(position, targetOrigin);
            dot = Tools::Dot(vector1, vector2);
            if(dot >= 0.999f) continue;

            vector1 = Tools::Normalization(targetPoints, targetPosition);
            vector2 = Tools::Normalization(position, targetPoints);
            dot = Tools::Dot(vector1, vector2);
            if(dot >= 0.999f) continue;

            velocity = mesh->velocity;

            vector1 = Tools::ProjectionVector(direction, velocity);
            dot = Tools::Dot(vector1, targetNormalVector);

            vector2 = Tools::ProjectionVector(targetNormalVector, dot);
            vector1 = Tools::SubtractionVector(vector1, vector2);

            vector2 = Tools::ReverseVector(vector1);
            vector1 = Tools::Normalization(vector2);
            velocity = Tools::Distance(vector2);
            direction = vector1;
        }*/
    }
}

void Collider::Look(Mesh *mesh, Mesh *targetMesh) {

    // 대상위 위치와 자신의 위치의 단위벡터를 구해서 방향을 설정하도록 함

    vec::vec2 targetPosition;

    position[0] = mesh->position[0];
    position[1] = mesh->position[1];

    targetPosition[0] = targetMesh->position[0];
    targetPosition[1] = targetMesh->position[1];

    direction = Tools::Normalization(position, targetPosition);
}

void Collider::InitCollider() {
    collided = false;
}

bool Collider::isCollided() {
    return collided;
}