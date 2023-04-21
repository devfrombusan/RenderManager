#include "Layer.hpp"

Camera::Camera(){

    next = nullptr;
    tempPosition[0] = 0.0f;
    tempPosition[1] = 0.0f;
    standPosition[0] = 0.0f;
    standPosition[1] = 0.0f;
    lookAtPosition[0] = 0.0f;
    lookAtPosition[1] = 0.0f;
    elapsedTime = 0.0f;
}

Camera::~Camera() {

}

void Camera::LookAt(float x, float y) {

    tempPosition[0] = x;
    tempPosition[1] = y;
}
