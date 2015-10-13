#ifndef NordicArts_Game_Generators_Settlements_H
#define NordicArts_Game_Generators_Settlements_H

#include <Game/Includes.hpp>
#include <Game/Generator/Structs.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            class Settlements {
            // Variables
            public:
                std::vector<Settlement> m_vSettlements;

            protected:
            private:
                int m_iSeed;
                int m_iSize;

            // Methods
            public:
                Settlements(int iSize, int iSeed);
                ~Settlements();

                Settlement getSettlement();
                Settlement getDefault();

                std::vector<Settlement> getSettlements();

                void generate();
        
            protected:
            private:
            };
        };
    };
};

#endif
