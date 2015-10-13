#include <Game/Generator/Settlements.hpp>
#include <Game/Generator/People.hpp>

#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace Game {
        namespace Generators {
            Settlements::Settlements(int iSize, int iSeed) : m_iSize(iSize), m_iSeed(iSeed) {
            }

            Settlements::~Settlements() {
            }

            void Settlements::generate() {
                std::cout << "S" << std::flush;

                for (int i = 0; i != m_iSize; i++) {
                    Settlement sSettlement = getSettlement();

                    People oPeople(sSettlement, m_iSeed);
                    sSettlement.vPeople = oPeople.getPeople();

                    m_vSettlements.push_back(sSettlement);
                }
            }

            std::vector<Settlement> Settlements::getSettlements() {
                return m_vSettlements;
            }

            Settlement Settlements::getDefault() {
                Settlement sSettlement;
                sSettlement.iSize       = 3;
                sSettlement.iHouses     = 10;
                sSettlement.iShops      = 6;
                sSettlement.iPeople     = 14;
                sSettlement.cName       = "Defaultious";

                People oPeople(sSettlement, m_iSeed);
                sSettlement.vPeople     = oPeople.getPeople();

                return sSettlement;
            }

            Settlement Settlements::getSettlement() {
                int iSize, iPeople;

                Settlement sSettlement;
                iSize = NordicEngine::getRandom(1, 37, m_iSeed);
                if (iSize == 1) { return getDefault(); }
                sSettlement.iSize = iSize;

                if (iSize > 3 && iSize < 10) {
                    iPeople = NordicEngine::getRandom(36, 80, m_iSeed);

                    sSettlement.iHouses = NordicEngine::getRandom((iPeople - iSize), (iPeople + iSize), m_iSeed);
                    sSettlement.iShops  = NordicEngine::getRandom((iPeople - (iSize - 5)), (iPeople + (iSize - 5)), m_iSeed);
                    sSettlement.cName   = ("town_" + NordicEngine::getString(iSize));
                } else if (iSize > 10) {
                    iPeople = NordicEngine::getRandom(65, 180, m_iSeed);

                    sSettlement.iHouses = NordicEngine::getRandom((iPeople - iSize), (iPeople + iSize), m_iSeed);
                    sSettlement.iShops  = NordicEngine::getRandom((iPeople - (iSize - 20)), (iPeople + (iSize - 20)), m_iSeed);
                    sSettlement.cName   = ("city_" + NordicEngine::getString(iSize));
                } else {
                    iPeople = NordicEngine::getRandom(1, 40, m_iSeed);

                    sSettlement.iHouses = NordicEngine::getRandom((iPeople - iSize), (iPeople + iSize), m_iSeed);
                    sSettlement.iShops  = NordicEngine::getRandom((iPeople - (iSize - 2)), (iPeople + (iSize - 2)), m_iSeed);
                    sSettlement.cName   = ("village_" + NordicEngine::getString(iSize));
                }

                sSettlement.iPeople = iPeople;

                return sSettlement;
            }
        };
    };
};
