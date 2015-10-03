#ifndef NordicArts_Game_Seeder_H
#define NordicArts_Game_Seeder_H

#include <Game/Includes.hpp>

namespace NordicArts {
    namespace Game {
        class Seeder {
        // Variables
        public:
        protected:
        private:
            int m_iSeed;

        // Methods
        public:
            Seeder();
            ~Seeder();

            int getSeed() const;
            int getSeedTime() const;

            void setSeed(std::string cSeed);
            void setSeed(int iSeed);

        protected:
        private:
            int getCommand(const char cChar);
            int getCharacter(const char cChar);

        };
    };
};

#endif
