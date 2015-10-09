#ifndef NordicArts_Game_Generators_People_H
#define NordicArts_Game_Generators_People_H

#include <Game/Includes.hpp>

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
                int iJob;

                // Male or Female
                bool bMale;
                
                // Name
                std::string cFirstName;
                std::string cLastName;                
            };

            class People {
            // Variables
            public:
            protected:
            private:
                int m_iSeed;
                int m_iPeople;

                std::vector<std::string> m_vNames;

            // Methods
            public:
                People(int iPeople, int iSeed);
                ~People();

                Person getPerson();
                
                std::vector<Person> getPeople();                

                void generate();

            protected:
            private:

            };
        };
    };
};

#endif
