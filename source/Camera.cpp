#include "Camera.h"
#include <iostream>

const float Camera::DEFAULT_SENSITIVITY = 0.1f;
const float Camera::DEFAULT_SPEED = 2.5f;
const float Camera::DEFAULT_PITCH = 0.0f;
const float Camera::DEFAULT_ZOOM = 60.0f;
const float Camera::DEFAULT_YAW = -90.0f;

Camera::Camera() {
    // initialize member variables to defaults
    position = glm::vec3(1.0f, 1.0f, 1.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    sensitivity = DEFAULT_SENSITIVITY;
    movementSpeed = DEFAULT_SPEED;
    pitch = DEFAULT_PITCH;
    zoom = DEFAULT_ZOOM;
    yaw = DEFAULT_YAW;
    
    // update camera vectors based off of this
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    updateCameraVectors();
}

void Camera::setSensitivity(float newSensitivity) {
    sensitivity = newSensitivity;
}

void Camera::setMovementSpeed(float speed) {
    movementSpeed = speed;
}

void Camera::setPitch(float newPitch) {
    pitch = newPitch;
    updateCameraVectors();
}

void Camera::setZoom(float newZoom) {
    zoom = newZoom;
    updateCameraVectors();
}

void Camera::setYaw(float newYaw) {
    yaw = newYaw;
    updateCameraVectors();
}

glm::vec3 Camera::getPosition() const { return position; }
float Camera::getMovementSpeed() const { return movementSpeed; }
float Camera::getSensitivity() const { return sensitivity; }
float Camera::getPitch() const { return pitch; }
float Camera::getZoom() const { return zoom; }
float Camera::getYaw() const { return yaw; }

void Camera::processKeyboardInput(Direction direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    switch(direction) {
        case FRONT:
            position += front * velocity;
            break;
        case RIGHT:
            position += right * velocity;
            break;
        case BACK:
            position -= front * velocity;
            break;
        case LEFT:
            position -= right * velocity;
            break;
        case UP:
            position += worldUp * velocity;
            break;
        case DOWN:
            position -= worldUp * velocity;
            break;
    }


//    std::cout << "POS: " << position.x << " " << position.y << " " << position.z << std::endl;
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}





