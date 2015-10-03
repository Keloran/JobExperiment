#include <Game/Seeder/Seeder.hpp>
#include <NordicEngine/Time/Time.hpp>

namespace NordicArts {
    namespace Game {
        Seeder::Seeder() {
        }

        Seeder::~Seeder() {
        }
    
        int Seeder::getCommand(const char cChar) {
            std::stringstream stringStream;
            std::string cResult;

            stringStream << cChar;
            stringStream >> cResult;

            // Characters
            std::string cSpace = " "; 
            std::string cDash = "-"; 
            std::string cUnder = "_"; 
            std::string cPlus = "+"; 
            std::string cEquals = "="; 
            std::string cStar = "*"; 
            std::string cBackSlash = "\\"; 
            std::string cForwardSlash = "/"; 
            std::string cExplination = "!"; 
            std::string cDollar = "$"; 
            std::string cPercentage = "%";
            std::string cHat = "^";
            std::string cLeftParenthesis = "(";
            std::string cRightParenthesis = ")";
            std::string cDot = ".";
            std::string cColon = ":";
            std::string cSemiColon = ";";
            std::string cCurlLeft = "{";
            std::string cCurlRight = "}";
            std::string cLeftBraket = "[";
            std::string cRightBraket = "]";
            std::string cHash = "#";
            std::string cAt = "@";
            std::string cPipe = "|";
            std::string cLeft = "<";
            std::string cRight = ">";
            std::string cQuestion = "?";
            std::string cComma = ",";

            // Matches Times
            if (cResult.compare(cSpace) == 0) { return 1; }
            if (cResult.compare(cStar) == 0) { return 1; }
            if (cResult.compare(cExplination) == 0) { return 1; }
            if (cResult.compare(cLeftParenthesis) == 0) { return 1; }
            if (cResult.compare(cSemiColon) == 0) { return 1; }
            if (cResult.compare(cRightBraket) == 0) { return 1; }
            if (cResult.compare(cLeft) == 0) { return 1; }

            // Matches Divide
            if (cResult.compare(cBackSlash) == 0) { return 2; }
            if (cResult.compare(cForwardSlash) == 0) { return 2; }
            if (cResult.compare(cDollar) == 0) { return 2; }
            if (cResult.compare(cRightParenthesis) == 0) { return 2; }
            if (cResult.compare(cCurlLeft) == 0) { return 2; }
            if (cResult.compare(cHash) == 0) { return 2; }
            if (cResult.compare(cRight) == 0) { return 2; }

            // Matches Minus
            if (cResult.compare(cDash) == 0) { return 3; }
            if (cResult.compare(cUnder) == 0) { return 3; }
            if (cResult.compare(cPercentage) == 0) { return 3; }
            if (cResult.compare(cDot) == 0) { return 3; }
            if (cResult.compare(cCurlRight) == 0) { return 3; }
            if (cResult.compare(cAt) == 0) { return 3; }
            if (cResult.compare(cQuestion) == 0) { return 3; }

            // Matches Plus
            if (cResult.compare(cPlus) == 0) { return 4; }
            if (cResult.compare(cEquals) == 0) { return 4; }
            if (cResult.compare(cHat) == 0) { return 4; }
            if (cResult.compare(cColon) == 0) { return 4; }
            if (cResult.compare(cLeftBraket) == 0) { return 4; }
            if (cResult.compare(cComma) == 0) { return 4; }
            if (cResult.compare(cPipe) == 0) { return 4; }

            // Not Matched
            return 0;
        }

        int Seeder::getCharacter(const char cChar) {
            std::stringstream stringStream;
            std::string cResult;
            
            stringStream << cChar;
            stringStream >> cResult;

            // LowerCase
            if (cResult.compare(std::string("a")) == 0) { return 1; }
            if (cResult.compare(std::string("b")) == 0) { return 2; }
            if (cResult.compare(std::string("c")) == 0) { return 3; }
            if (cResult.compare(std::string("d")) == 0) { return 4; }
            if (cResult.compare(std::string("e")) == 0) { return 5; }
            if (cResult.compare(std::string("f")) == 0) { return 6; }
            if (cResult.compare(std::string("g")) == 0) { return 7; }
            if (cResult.compare(std::string("h")) == 0) { return 8; }
            if (cResult.compare(std::string("i")) == 0) { return 9; }
            if (cResult.compare(std::string("j")) == 0) { return 10; }
            if (cResult.compare(std::string("k")) == 0) { return 11; }

            return 53;
        }

        void Seeder::setSeed(std::string cSeed) {
            int iSeed = 1;

            int iCommand;

            for (size_t i = 0; i != cSeed.length(); ++i) {
                iSeed += getCharacter(cSeed.at(i));

                iCommand = getCommand(cSeed.at(i));
                switch (iCommand) {
                    case 1: {
                        iSeed += (iSeed * 10);
                        break;
                    }
                    case 2: {
                        iSeed += (iSeed / 10);
                        break;
                    }
                    case 3: {
                        iSeed += (iSeed - 10);
                        break;
                    }
                    case 4: {
                        iSeed += (iSeed + 10);
                    }
                    default: {
                        break;
                    }
                }    
            }

            setSeed(iSeed);
        }

        void Seeder::setSeed(int iSeed) {
            m_iSeed = iSeed;
        }

        int Seeder::getSeed() const {
            return m_iSeed;
        }

        int Seeder::getSeedTime() const {
            int iSeedTime;

            NordicEngine::Time oTime;
            NordicEngine::Time *pTime = &oTime;

            iSeedTime =(int) pTime->sinceStartHigh();
            iSeedTime += m_iSeed;

            return iSeedTime;
        }
    };
};
