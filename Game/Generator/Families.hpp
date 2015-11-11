#ifndef NordicArts_Game_Generators_Families_H
#define NordicArts_Game_Generators_Families_H

#include <Game/Includes.hpp>
#include <Game/Generator/Structs.hpp>

namespace NordicArts {
	namespace Game {
		namespace Generators {
			class Families {
			// Variables
			public:
			protected:
			private:
				int m_iSeed;

			// Methods
			public:
				Families(int iSeed);
				~Families();

				Family generate();

			protected:
			private:

			};
		};
	};
};

#endif
