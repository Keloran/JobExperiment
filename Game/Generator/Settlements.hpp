#ifndef NordicArts_Game_Generators_Settlements_H
#define NordicArts_Game_Generators_Settlements_H

#include <Game/Includes.hpp>
#include <Game/Generator/Generator.hpp>
#include <Game/Generator/Jobs.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            struct Settlement {
                std::string cName;

                int iSize;
                int iHouses;
                int iShops;
                int iPeople;
                
                std::vector<Job> vJobs;
            };

            class Settlements : public Generator {
            // Variables
            public:
                std::vector<Settlement> m_vSettlements;

            protected:
            private:

            // Methods
            public:
                Settlements();
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
