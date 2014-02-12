#include "Genom.h"
#include "Gene.h"
#include "Species.h"
#include "Specimen.h"
#include "Championship.h"

#include <iostream>
#include <string>
#include <cstdio>

class TestGladiators : public ChampionshipInterface{

    public:
        TestGladiators(void);
        ~TestGladiators(void);
        int test_gladiators(int argc, char ** argv);

        void onDuelEnd(ChampionshipDuelEvent &e);
    private:
        static const char* names[];

};
