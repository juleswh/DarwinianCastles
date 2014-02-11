#ifndef GLADIATORS_H
#define GLADIATORS_H

#include "Species.h"
#include "Gladiator.h"
#include <iostream>


class Gladiators : public Species
{
    public:
        Gladiators(const std::string &name,unsigned int genom_size,
            std::default_random_engine *generator_mutation_proba, std::default_random_engine *generator_mutation_alteration,
            unsigned int sexual_majority=0,unsigned int minSexHealthLevel=0,
            double mutation_probability=0,double mutation_stddev=0);

        virtual ~Gladiators();

        //specimen list acccessor/modifier
        unsigned int addSpecimen(Gladiator *new_specimen);
        std::vector<Gladiator*> const & getSpecimens(void) const;

        void tournament(void);
        unsigned int loveSeason(void);

    protected:
        std::vector<Gladiator*> specimens;

    private:
};

#endif // GLADIATORS_H
