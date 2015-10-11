#include <Game/Game.hpp>

#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Utility/Seeder.hpp>
#include <NordicEngine/Time/Time.hpp>
#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/String/String.hpp>

#include <Game/Generator/Settlements.hpp>
#include <NordicEngine/NordicEngine/Utility/NameGen.hpp>

namespace NordicArts {
    namespace Game {
        void handleException(std::exception_ptr oException) {
            try {
                if (oException) {
                    std::rethrow_exception(oException);
                }
            } catch (const std::exception &oEx) {
                printIt(oEx.what());
            }
        }

        int Main(std::string cGameName) {
            try {
                NordicEngine::Logger oLogger(cGameName);
                NordicEngine::Logger *pLogger = &oLogger;

                NordicEngine::Time oTime;
                NordicEngine::Time *pTime = &oTime;

                try {
                    NordicEngine::Seeder oSeeder;
                    NordicEngine::Seeder *pSeeder = &oSeeder;

                    std::string cSeed = "bobs experiment";
                    pSeeder->setSeed(cSeed);
                    int iSeed = pSeeder->getSeed();

                    NordicEngine::NameGen oNameGen(iSeed);
                    oNameGen.generateLists();
                    int iRandLength = NordicEngine::getRandom(3, 6, iSeed);
                    printIt(iRandLength);
                    printIt(oNameGen.generateName(iRandLength));

                    Generators::Settlements oSettlements(3, iSeed);
                    oSettlements.generate();
                    
                    std::vector<Generators::Settlement> vSettlements = oSettlements.getSettlements();
                    int iSettlements, iPeople = 0;
                    iSettlements = vSettlements.size();

                    for (size_t i = 0; i != iSettlements; i++) {
                        iPeople += vSettlements.at(i).iPeople;
                    }
                    printIt(iSettlements);
                    printIt(iPeople);

                } catch (std::exception &oException) {
                    throw NordicEngine::Exception(oException.what());
                } catch (NordicEngine::Exception &oException) {
                    pLogger->log(oException.what());
                } catch ( ... ) {
                    handleException(std::current_exception());
                }
            } catch ( ... ) {
                handleException(std::current_exception());
            }

            return EXIT_SUCCESS;
        }
    };
};
