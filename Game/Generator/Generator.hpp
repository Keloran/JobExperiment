#ifndef NordicArts_Game_Generators_Generator_H
#define NordicArts_Game_Generators_Generator_H

#include <Game/Includes.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            class Generator {
            // Variables
            public:
            protected:
                int m_iSeed;
                int m_iSize;

            private:
            
            // Methods
            public:
                void setSeed(int iSeed) { m_iSeed = iSeed; }
                void setSize(int iSize) { m_iSize = iSize; }
                
                virtual void generate() = 0;

            protected:
            private:

            };
        };
    };
};

#endif
