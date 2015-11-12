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

				NewFamily generate();
                NewFamily generate(int iMales, int iFemales);
                NewFamily generate(int iMales, int iFemales, NewPerson *sDad, NewPerson *sMum);

			protected:
			private:

			};
		};
	};
};

#endif
