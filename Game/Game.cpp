#include <Game/Game.hpp>

#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Utility/Seeder.hpp>
#include <NordicEngine/Time/Time.hpp>

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

                    printIt(pSeeder->getSeed() + (int)pTime->sinceStart());
                    for (int i = 0; i < 99999; i++) { }
                    printIt(pSeeder->getSeed() + (int)pTime->sinceStart());
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
