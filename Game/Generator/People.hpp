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
                int m_iMinAge = 0;

                bool m_bHomeless = false;

                std::vector<Person> m_vPeople;
                std::vector<Family> m_vFamilies;

            // Methods
            public:
                People(Settlement sSettlement, int iSeed);
                ~People();

                Person getPerson(std::string cLastName);
                Person getPerson(std::string cLastName, bool bMale);
                
                std::vector<Person> getPeople();                

                void generate();

            protected:
            private:
                void personInfo(Person sPerson);
                void setMinAge(int iMinAge);
                void setHomeless(bool bHomeless);

                Family makeFamily(std::string cLastName, std::vector<Person> vPeople);

            };
        };
    };
};

#endif
