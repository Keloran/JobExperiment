#ifndef NordicArts_Game_Generators_People_H
#define NordicArts_Game_Generators_People_H

#include <Game/Includes.hpp>
#include <Jobs.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            struct Person {
                // Person Details
                int iAge;
                int iMaxAge;

                // Linkers
                int iBornSettlement;
                int iParent;


                // Male or Female
                bool bMale;
                
                // Name
                std::string cFirstName;
                std::string cLastName;

                Job sJob;
            };

            class People {
            // Variables
            public:
            protected:
            private:
                int m_iSeed;
                int m_iPeople;
                int m_iHouses;

                std::vector<std::string> m_vNames;
                std::vector<Person> m_vPeople;

            // Methods
            public:
                People(int iPeople, int iHouses, int iSeed);
                ~People();

                Person getPerson(std::string cLastName, std::string cFirstName);
                
                std::vector<Person> getPeople();                

                void generate();

            protected:
            private:

            };
        };
    };
};

#endif
