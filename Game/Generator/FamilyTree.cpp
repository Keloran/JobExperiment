#include <Game/Generator/FamilyTree.hpp>
#include <Game/Generator/Families.hpp>

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
	namespace Game {
		namespace Generators {
			FamilyTree::FamilyTree(int iStartFamilies, int iGenerations, int iSeed) : m_iStartFamilies(iStartFamilies), m_iGenerations(iGenerations), m_iSeed(iSeed) {
			}

			FamilyTree::~FamilyTree() {
			}

			void FamilyTree::generate() {
				std::vector<NewFamily> vStartFamilies;

				for (int i = 0; i != m_iStartFamilies; i++) {
					Families oFamilies(m_iSeed);
					NewFamily sFamily = oFamilies.generate();

                    printIt(sFamily.cName);


					vStartFamilies.push_back(sFamily);
				}
			}
		};
	};
};
