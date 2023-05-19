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
        Reset();
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

    Cube::Cube(float X, float Y, float Z, float scale) {
        setPositionAndScale(X, Y, Z, scale);
    }

    Cube::Cube(const glm::vec3& position) {
        setPosition(position);
    }

    Cube::Cube(const glm::vec4& positionAndScale) {
        setPositionAndScale(positionAndScale);
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
    void Cube::Reset() {
        assert((sizeof(DEFAULT_QUADS) == sizeof(quads)) && "DEFAULT_QUADS size doesn't match quads size!");
        memcpy(quads, DEFAULT_QUADS, QUADS_PER_CUBE * sizeof(Quad));
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

        return glm::distance(position1, position2);
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
        ResetPosition();

        // add that offset, and re-scale it
        addOffsetAndScale(X, Y, Z, scale);
    }

    void Cube::setPosition(const glm::vec3& position) {
        // get the scale
        float scale = getScale();

        // reset the cube to the origin
        ResetPosition();

        // add offset and scale to it
        addOffsetAndScale(glm::vec4(position, scale));
    }

    void Cube::setPositionAndScale(float X, float Y, float Z, float scale) {
        ResetPosition();
        addOffset(X, Y, Z);
        setScale(scale);
    }

    void Cube::setPositionAndScale(const glm::vec4& positionAndScale) {
        ResetPosition();
        addOffset(glm::vec3(positionAndScale));
        setScale(positionAndScale.w);
    }

    void Cube::setNormalizedDeviceCoordinates(float maxDist) {
        float newScale = getScale() / (2.0f * maxDist);
        glm::vec3 newPos = getCenter() / maxDist;
        setPositionAndScale(glm::vec4(newPos, newScale));
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

    std::tuple<float*, size_t> Cube::floats() {
        return std::make_tuple((float*)quads, FLOATS_PER_CUBE);
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

    void Cube::setTopTextureArrayIndex(float index) {
        quads[5].setTextureArrayIndex(index);
    }
    
    void Cube::setBackTextureArrayIndex(float index) {
        quads[2].setTextureArrayIndex(index);
    }
   
    void Cube::setLeftTextureArrayIndex(float index) {
        quads[3].setTextureArrayIndex(index);
    }

    void Cube::setRightTextureArrayIndex(float index) {
        quads[1].setTextureArrayIndex(index);
    }

    void Cube::setFrontTextureArrayIndex(float index) {
        quads[0].setTextureArrayIndex(index);
    }

    void Cube::setBottomTextureArrayIndex(float index) {
        quads[4].setTextureArrayIndex(index);
    }

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
