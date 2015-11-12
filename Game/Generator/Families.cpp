#include <Game/Generator/Families.hpp>
#include <Game/Generator/People.hpp>

#include <NordicEngine/Utility/Maths.hpp>

namespace NordicArts {
	namespace Game {
		namespace Generators {
			Families::Families(int iSeed) : m_iSeed(iSeed) {
			}

			Families::~Families() {
			}

            NewFamily Families::generate() {
                return generate(1, 1);
            }
            NewFamily Families::generate(int iMales, int iFemales) {
                return generate(iMales, iFemales, nullptr, nullptr);
            }
			NewFamily Families::generate(int iMales, int iFemales, NewPerson *sDad, NewPerson *sMum) {
                int iChildren = NordicEngine::getRandom(1, 8, m_iSeed);

				NewFamily sFamily("Bob", iMales, iFemales, iChildren);
                sFamily.sDad = sDad;
                sFamily.sMum = sMum;

				return sFamily;
			}
		};
	};
};
