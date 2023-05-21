#ifndef BLOCKATTRIBUTEFACTORY_H
#define BLOCKATTRIBUTEFACTORY_H

#include "BlockAttributes.h"

namespace Blocks {

    class BlockAttributeFactory {
    public:
        
        static BlockAttributeFactory& getInstance() {
            static BlockAttributeFactory instance;
            return instance;
        }

        BlockAttributes* getAttributes(const Material& mat);

    private:
         
        BlockAttributeFactory();
        ~BlockAttributeFactory();
        BlockAttributeFactory(const BlockAttributeFactory&) = delete;
        BlockAttributeFactory& operator=(const BlockAttributeFactory&) = delete;

        BlockAttributes attributes[NUM_MATERIALS];
    };

}

#endif
