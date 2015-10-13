#ifndef NordicArts_Game_Generators_People_H
#define NordicArts_Game_Generators_People_H

#include <Game/Includes.hpp>
#include <Game/Generator/Structs.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            class People {
            // Variables
            public:
            protected:
            private:
                Settlement m_sSettlement;

                int m_iSeed;
                int m_iPeople;
                int m_iHouses;

                std::vector<std::string> m_vNames;
                std::vector<Person> m_vPeople;

            // Methods
            public:
                People(Settlement sSettlement, int iSeed);
                ~People();

                Person getPerson(std::string cLastName, std::string cFirstName, bool bHomeless);
                
                std::vector<Person> getPeople();                

                void generate();

            protected:
            private:

            };
        };
    };
};

#endif
