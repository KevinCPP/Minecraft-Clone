#include "../include/Cube.h"

namespace Geometry {

    namespace {
        const Vertex DEFAULT_VERTICES[VERTICES_PER_CUBE] = {
            // front
            Vertex(-0.5f,  0.5f, -0.5f, 1, 1, 0), 
            Vertex( 0.5f,  0.5f, -0.5f, 0, 1, 0),
            Vertex( 0.5f, -0.5f, -0.5f, 0, 0, 0),
            Vertex(-0.5f, -0.5f, -0.5f, 1, 0, 0),

            // right side
            Vertex( 0.5f, -0.5f, -0.5f, 1, 0, 0), // bottom left
            Vertex( 0.5f,  0.5f, -0.5f, 1, 1, 0), // bottom right
            Vertex( 0.5f,  0.5f,  0.5f, 0, 1, 0), // top right
            Vertex( 0.5f, -0.5f,  0.5f, 0, 0, 0), // top left
             
            // back
            Vertex(-0.5f, -0.5f,  0.5f, 0, 0, 0),
            Vertex( 0.5f, -0.5f,  0.5f, 1, 0, 0),
            Vertex( 0.5f,  0.5f,  0.5f, 1, 1, 0),
            Vertex(-0.5f,  0.5f,  0.5f, 0, 1, 0),
            
            // left side
            Vertex(-0.5f, -0.5f,  0.5f, 1, 0, 0),
            Vertex(-0.5f,  0.5f,  0.5f, 1, 1, 0),
            Vertex(-0.5f,  0.5f, -0.5f, 0, 1, 0),
            Vertex(-0.5f, -0.5f, -0.5f, 0, 0, 0),
            
            // bottom
            Vertex(-0.5f, -0.5f, -0.5f, 0, 0, 0),
            Vertex( 0.5f, -0.5f, -0.5f, 1, 0, 0),
            Vertex( 0.5f, -0.5f,  0.5f, 1, 1, 0),
            Vertex(-0.5f, -0.5f,  0.5f, 0, 1, 0),
            
            // top
            Vertex(-0.5f,  0.5f,  0.5f, 0, 1, 0),
            Vertex( 0.5f,  0.5f,  0.5f, 1, 1, 0),
            Vertex( 0.5f,  0.5f, -0.5f, 1, 0, 0),
            Vertex(-0.5f,  0.5f, -0.5f, 0, 0, 0),
        };

        const Quad DEFAULT_QUADS[QUADS_PER_CUBE] = {
            Quad(DEFAULT_VERTICES + VERTICES_PER_QUAD * 0),
            Quad(DEFAULT_VERTICES + VERTICES_PER_QUAD * 1),
            Quad(DEFAULT_VERTICES + VERTICES_PER_QUAD * 2),
            Quad(DEFAULT_VERTICES + VERTICES_PER_QUAD * 3),
            Quad(DEFAULT_VERTICES + VERTICES_PER_QUAD * 4),
            Quad(DEFAULT_VERTICES + VERTICES_PER_QUAD * 5),
        };
    }

    Cube::Cube() {
        reset();
    }

    Cube::Cube(const Cube& other) {
        memcpy(quads, other.quads, sizeof(Quad) * QUADS_PER_CUBE);
    }   

    Cube& Cube::operator=(const Cube& other) {
        if(this != &other) {
            memcpy(quads, other.quads, sizeof(Quad) * QUADS_PER_CUBE);
        }

        return *this;
    }

    Cube::Cube(float X, float Y, float Z) {
        setPosition(X, Y, Z); 
    }

    Cube::Cube(const glm::vec3& position) {
        setPosition(position);
    }

    Cube::Cube(std::array<Quad, 6> quadArr) {
        assert(QUADS_PER_CUBE == 6 && "QUADS_PER_CUBE != 6");
        memcpy(quads, quadArr.data(), QUADS_PER_CUBE * sizeof(Quad));
    }

    bool Cube::operator==(const Cube& other) const {
        for(size_t i = 0; i < QUADS_PER_CUBE; i++) {
            if(quads[i] != other.quads[i]) return false;
        }
        return true;
    }
    

    bool Cube::operator!=(const Cube& other) const {
        for(size_t i = 0; i < QUADS_PER_CUBE; i++) {
            if(quads[i] == other.quads[i]) return false;
        }
        return true;
    }
    
    // resets the entire cube to default
    void Cube::reset() {
        assert((sizeof(DEFAULT_QUADS) == sizeof(quads)) && "DEFAULT_QUADS size doesn't match quads size!");
        memcpy(quads, DEFAULT_QUADS, QUADS_PER_CUBE * sizeof(Quad));
    }

    // resets the positions to defaults
    void Cube::resetPosition() {
        for(size_t q = 0; q < QUADS_PER_CUBE; q++) {
            for(size_t v = 0; v < VERTICES_PER_QUAD; v++) {
                size_t currentVertex = (q * VERTICES_PER_QUAD) + v;
                
                glm::vec3 defaultPos = DEFAULT_VERTICES[currentVertex].getPosition();
                quads[q].vertices[v].setPosition(defaultPos);
            }
        }
    }

    // scales cube about the origin (center) of the cube
    void Cube::setScale(const glm::vec3& scale) {
        glm::vec3 currentScale = getScale();
        glm::vec3 scaleRatio = scale / currentScale;

        for(auto& q : quads) {
            for(auto& v : q.vertices) {
                v.setPosition(v.getPosition() * scaleRatio);
            }
        }
    }

    // returns the scale of the cube (default is 1.0). Since it is scaled
    // by a factor of a single number, we can simply return the distance
    // between any two adjacent points.
    glm::vec3 Cube::getScale() {
        // quad 0 is the front quad, vertex 0 is the bottom left and vertex 1
        // is the bottom right, so the distance will be the scale on the x-axis
        glm::vec3 position1 = quads[0].vertices[0].getPosition();
        glm::vec3 position2 = quads[0].vertices[1].getPosition();
        float xScale = glm::distance(position1, position2);
        
        // quad 1 is the right side, so it will get the z-scale
        position1 = quads[1].vertices[0].getPosition();
        position2 = quads[1].vertices[1].getPosition();
        float zScale = glm::distance(position1, position2);
        
        // for the y scale, we can just use vertex 0 again, but this time,
        // use 0 for the bottom right and 3 for the top right vertex to get height
        position1 = quads[0].vertices[0].getPosition();
        position2 = quads[0].vertices[3].getPosition();
        float yScale = glm::distance(position1, position2);
        
        // finally, return the scale.
        return glm::vec3(xScale, yScale, zScale);
    }

    float Cube::getHeight() {
        glm::vec3 scale = getScale();
        return scale.y / scale.x;
    }

    void Cube::setHeight(float height) {
        Quad* back = getQuad(Geometry::BACK); 
        Quad* left = getQuad(Geometry::LEFT);
        Quad* front = getQuad(Geometry::FRONT);
        Quad* right = getQuad(Geometry::RIGHT);
        
          
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

    void Cube::setPosition(float X, float Y, float Z) {
        // get the scale
        glm::vec3 scale = getScale();
        
        // reset the cube, so that just adding an offset
        // will essentially be setting the position
        resetPosition();

        // add that offset, and re-scale it
        addOffset(X, Y, Z);
        setScale(scale);
    }

    void Cube::setPosition(const glm::vec3& position) {
        setPosition(position.x, position.y, position.z);
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

    // sets the texture coordinates for every cube face
    void Cube::setAllTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        setSidesTextureCoords(a, x, y, width, height);
        setTopBottomTextureCoords(a, x, y, width, height);
    }
    
    // sets the texture coordinates for individual faces
    void Cube::setTopTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        quads[5].setTextureCoordsFromAtlas(a, x, y, width, height); 
    }

    void Cube::setBackTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        quads[2].setTextureCoordsFromAtlas(a, x, y, width, height); 
    }

    void Cube::setLeftTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        quads[3].setTextureCoordsFromAtlas(a, x, y, width, height); 
    }

    void Cube::setRightTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        quads[1].setTextureCoordsFromAtlas(a, x, y, width, height); 
    }

    void Cube::setFrontTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        quads[0].setTextureCoordsFromAtlas(a, x, y, width, height); 
    }

    void Cube::setBottomTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        quads[4].setTextureCoordsFromAtlas(a, x, y, width, height); 
    }
    
    // sets the texture coords for all the side faces
    void Cube::setSidesTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        setBackTextureCoords(a, x, y, width, height);
        setLeftTextureCoords(a, x, y, width, height);
        setRightTextureCoords(a, x, y, width, height);
        setFrontTextureCoords(a, x, y, width, height);
    }
    
    // sets the texture coords for both the top and bottom
    void Cube::setTopBottomTextureCoords(TextureAtlas* a, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        setTopTextureCoords(a, x, y, width, height);
        setBottomTextureCoords(a, x, y, width, height);
    }

    void Cube::setTopTextureArrayIndex(float index) { quads[5].setTextureArrayIndex(index); }
    void Cube::setBackTextureArrayIndex(float index) { quads[2].setTextureArrayIndex(index); }
    void Cube::setLeftTextureArrayIndex(float index) { quads[3].setTextureArrayIndex(index); }
    void Cube::setRightTextureArrayIndex(float index) {quads[1].setTextureArrayIndex(index); }
    void Cube::setFrontTextureArrayIndex(float index) { quads[0].setTextureArrayIndex(index); }
    void Cube::setBottomTextureArrayIndex(float index) { quads[4].setTextureArrayIndex(index); }

    void Cube::setAllTextureArrayIndex(float index) {
        setSidesTextureArrayIndex(index);
        setTopBottomTextureArrayIndex(index);
    }

    void Cube::setSidesTextureArrayIndex(float index) {
        setLeftTextureArrayIndex(index);
        setBackTextureArrayIndex(index);
        setRightTextureArrayIndex(index);
        setFrontTextureArrayIndex(index);
    }

    void Cube::setTopBottomTextureArrayIndex(float index) {
        setTopTextureArrayIndex(index);
        setBottomTextureArrayIndex(index);
    }
    
    Quad* Cube::getQuad(Geometry::Direction dir) {
        switch(dir) {
            case TOP:
                return quads + 5;
            case LEFT:
                return quads + 3;
            case BACK:
                return quads + 2;    
            case RIGHT:
                return quads + 1;
            case FRONT:
                return quads + 0;
            case BOTTOM:
                return quads + 4;
        }
    }

    Quad Cube::copyQuad(Geometry::Direction dir) const {
        switch(dir) {
            case TOP:
                return quads[5];
            case LEFT:
                return quads[3];
            case BACK:
                return quads[2];    
            case RIGHT:
                return quads[1];
            case FRONT:
                return quads[0];
            case BOTTOM:
                return quads[4];
        }
    }
}
