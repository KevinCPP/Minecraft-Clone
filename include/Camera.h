#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    void updateCameraVectors();

    glm::vec3 position;     // position of the camera
    glm::vec3 worldUp;      // direction that is considered to be "up" in the world coordinate system (+Y axis)
    glm::vec3 front;        // direction that is considered to be "front" in the world coordinate system (-Z axis)
    glm::vec3 right;        // direction that is considered to be "right" in the world coordinate system (+X axis)
    glm::vec3 up;           // direction that is "up" relative to the camera (pitch +90 degrees, cross product of right/front)

    float movementSpeed;    // speed for the camera to move
    float sensitivity;      // sensitivity for changing angle of camera
    float pitch;            // what angle up/down it's looking (ranges from -90° (down) to 90°(up))
    float zoom;             // how zoomed in the camera is, basically the FOV
    float yaw;              // what angle horizontally it's looking at (0° - 360°). At 0° it's looking at "front". At 90° "right"

    // Default values
    static const float DEFAULT_SENSITIVITY;
    static const float DEFAULT_SPEED;
    static const float DEFAULT_PITCH;
    static const float DEFAULT_ZOOM;
    static const float DEFAULT_YAW;
public:

    enum Direction {
        FRONT = 0, RIGHT, BACK, LEFT, UP, DOWN
    };

    Camera();

    // setters
    void setPosition(const glm::vec3& position);
    void setSensitivity(float sensitivity);
    void setMovementSpeed(float speed);
    void setPitch(float pitch);
    void setZoom(float zoom);
    void setYaw(float yaw);

    // getters
    glm::vec3 getPosition() const;
    float getMovementSpeed() const;
    float getSensitivity() const;
    float getPitch() const;
    float getZoom() const;
    float getYaw() const;

    // camera movement
    void processKeyboardInput(Direction direction, float deltaTime);

    // mouse movement
    void processMouseMovement(float xOffset, float yOffset);

    // Calculate View Matrix
    glm::mat4 getViewMatrix() const;
};

#endif
