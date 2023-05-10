#include "../include/Cube.h"

namespace Geometry {

    namespace {
        const std::array<Vertex, VERTICES_PER_CUBE> DEFAULT_VERTICES = {
            // front
            Vertex(-1.0f,  1.0f, -1.0f, 0, 1),
            Vertex(-1.0f, -1.0f, -1.0f, 0, 1),
            Vertex( 1.0f,  1.0f, -1.0f, 0, 1),
            Vertex( 1.0f, -1.0f, -1.0f, 0, 1),

            // right side
            Vertex( 1.0f,  1.0f, -1.0f, 0, 1),
            Vertex( 1.0f, -1.0f, -1.0f, 0, 1),
            Vertex( 1.0f,  1.0f,  1.0f, 0, 1),
            Vertex( 1.0f, -1.0f,  1.0f, 0, 1),
            
            // back
            Vertex(-1.0f,  1.0f,  1.0f, 0, 1),
            Vertex(-1.0f, -1.0f,  1.0f, 0, 1),
            Vertex( 1.0f,  1.0f,  1.0f, 0, 1),
            Vertex( 1.0f, -1.0f,  1.0f, 0, 1),
            
            // left side
            Vertex(-1.0f,  1.0f, -1.0f, 0, 1),
            Vertex(-1.0f, -1.0f, -1.0f, 0, 1),
            Vertex(-1.0f,  1.0f,  1.0f, 0, 1),
            Vertex(-1.0f, -1.0f,  1.0f, 0, 1),
            
            // bottom
            Vertex(-1.0f, -1.0f,  1.0f, 0, 1),
            Vertex(-1.0f, -1.0f, -1.0f, 0, 1),
            Vertex( 1.0f, -1.0f,  1.0f, 0, 1),
            Vertex( 1.0f, -1.0f, -1.0f, 0, 1),
            
            // top
            Vertex(-1.0f,  1.0f,  1.0f, 0, 1),
            Vertex(-1.0f,  1.0f, -1.0f, 0, 1),
            Vertex( 1.0f,  1.0f,  1.0f, 0, 1),
            Vertex( 1.0f,  1.0f, -1.0f, 0, 1),
        };

        const std::array<Quad, QUADS_PER_CUBE> DEFAULT_QUADS = {
            Quad(DEFAULT_VERTICES.data() + VERTICES_PER_QUAD * 0),
            Quad(DEFAULT_VERTICES.data() + VERTICES_PER_QUAD * 1),
            Quad(DEFAULT_VERTICES.data() + VERTICES_PER_QUAD * 2),
            Quad(DEFAULT_VERTICES.data() + VERTICES_PER_QUAD * 3),
            Quad(DEFAULT_VERTICES.data() + VERTICES_PER_QUAD * 4),
            Quad(DEFAULT_VERTICES.data() + VERTICES_PER_QUAD * 5),
        };
    }

    Cube::Cube() {
        Reset();
    }

    Cube::Cube(float offsetX, float offsetY, float offsetZ) {

    }

    // resets the entire cube to default
    void Cube::Reset() {
        quads = DEFAULT_QUADS;
    }

    // resets the positions to defaults
    void Cube::ResetPosition() {
        for(size_t q = 0; q < QUADS_PER_CUBE; q++) {
            for(size_t v = 0; v < VERTICES_PER_QUAD; v++) {
                size_t currentVertex = (q * VERTICES_PER_QUAD) + v;
                
                glm::vec3 defaultPos = DEFAULT_VERTICES[currentVertex].getPosition();
                quads[q].vertices[v].setPosition(defaultPos);
            }
        }
    }

    // scales cube about the origin (center) of the cube
    void Cube::setScale(float scale) {
        glm::vec3 center = getCenter();

        for(auto& q : quads) {
            for(auto& v : q.vertices) {
                glm::vec3 pos = v.getPosition();
                pos -= center;
                pos *= scale;
                pos += center;
                v.setPosition(pos);
            }
        }
    }

    // returns the scale of the cube (default is 1.0). Since it is scaled
    // by a factor of a single number, we can simply return the distance
    // between any two adjacent points.
    float Cube::getScale() {
        glm::vec3 position1 = quads[0].vertices[0].getPosition();
        glm::vec3 position2 = quads[0].vertices[1].getPosition();

        return glm::distance(position1, position2) / 2.0f;
    }

    // adds X Y and Z to the position of the cube
    void Cube::addOffset(float X, float Y, float Z) {
        addOffset(glm::vec3(X, Y, Z));
    }

    void Cube::addOffset(const glm::vec3& offset) {
        for(auto& q : quads)
            for(auto& v : q.vertices)
                v.setPosition(v.getPosition() + offset);
    }

    // adds X Y and Z to the position of the cube, then scales
    void Cube::addOffsetAndScale(float X, float Y, float Z, float scale) {
        addOffsetAndScale(glm::vec4(X, Y, Z, scale));
    }

    void Cube::addOffsetAndScale(const glm::vec4& offsetAndScale) {
        addOffset(glm::vec3(offsetAndScale));
        setScale(offsetAndScale.w);
    }

    void Cube::setPosition(float X, float Y, float Z) {
        // get the scale
        float scale = getScale();
        
        // reset the cube, so that just adding an offset
        // will essentially be setting the position
        Reset();

        // add that offset, and re-scale it
        addOffsetAndScale(X, Y, Z, scale);
    }

    void Cube::setPosition(const glm::vec3& position) {
        // get the scale
        float scale = getScale();

        // reset the cube to the origin
        Reset();

        // add offset and scale to it
        addOffsetAndScale(glm::vec4(position, scale));
    }

    void Cube::setPositionAndScale(float X, float Y, float Z, float scale) {
        Reset();
        addOffset(X, Y, Z);
        setScale(scale);
    }

    void Cube::setPositionAndScale(const glm::vec4& positionAndScale) {
        Reset();
        addOffset(glm::vec3(positionAndScale));
        setScale(positionAndScale.w);
    }

    // returns the center point of the cube
    glm::vec3 Cube::getCenter() {
        glm::vec3 center = glm::vec3(0.0f);

        // adds up the position of all the vertices
        for(const auto& q : quads)
            for(const auto& v : q.vertices)
                center += v.getPosition();

        // then divides by the total number of vertices
        // to get the average position, aka cube center
        center /= (QUADS_PER_CUBE * VERTICES_PER_QUAD);

        return center;
    }

    std::array<float, FLOATS_PER_CUBE> Cube::getFloatArray() {
        
    }
}
