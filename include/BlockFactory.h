#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

namespace Blocks {
    
    class BlockFactory {
    public:
        
        static BlockFactory& getInstance() {
            static BlockFactory instance;
            return instance;
        }

        Block* getBlock(const Material& mat);
        Block makeBlock(const Material& mat);
        

    private:
        
        CubeFactory();
        ~CubeFactory();
        CubeFactory(const Material&) = delete;
        CubeFactory& operator=(const Material&) = delete;
        
        Block[NUM_MATERIALS] blocks; 
    }

}

#endif
