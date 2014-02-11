#ifndef SPECIES_H
#define SPECIES_H

#include <string>
#include <vector>
#include <algorithm>

#include "Specimen.h"
class Specimen;



class Species
{
    public:
        Species(const std::string &name,unsigned int genom_size,
        std::default_random_engine *generator_mutation_proba, std::default_random_engine *generator_mutation_alteration,
        unsigned int sexual_majority=0,unsigned int minSexHealthLevel=0,
        double mutation_probability=0,double mutation_stddev=0);

        virtual ~Species();

        void setName(const std::string &name);
        std::string getName(void);

        void setGenomSize(unsigned int genom_size);
        unsigned int getGenomSize(void);

        std::default_random_engine *getGeneratorProba();
        std::default_random_engine *getGeneratorAlteration();

        unsigned int getLifeEsperance(void) const ;
        double getLifeEsperanceStdDev(void) const ;
        void setLifeEsperanceStdDev(double std_dev);
        void setLifeEsperance(unsigned int esperance);

        //specimen list acccessor/modifier
        unsigned int addSpecimen(Specimen *new_specimen);
        std::vector<Specimen*> const & getSpecimens(void) const;

        unsigned int checkAlive(void);

        //reproduction
        unsigned int getSexualMajorityAge(void) const;
        bool isSexuallyActive(Specimen *specimen);
        bool isSexuallyActive(unsigned int index);
        bool canReproduct(unsigned int index1,unsigned int index2);

        /**
         *  find possible couples and make them reproduct.
         *  @see reproduction()
         *  also increment age of all specimens (excpet new born)
         */
        unsigned int loveSeason();
        /**
         *  take two specimens and add their new child to the specimens list.
         *  @param index1 index of the first parent in the specimens list
         *  @param index2 index of the second parent in the specimens list
         *  @see Specimen::reproduct()
        **/
        unsigned int reproduction(unsigned int index1,unsigned int index2);

    protected:
        std::vector<Specimen*> specimens;

    private:

        std::string name;
        unsigned int genom_size;
        unsigned int sexual_majority;
        unsigned int minSexHealthLevel;
        unsigned int life_esperance;
        double life_esperance_std_dev;

        double mutation_probability;
        double mutation_stddev;
        std::default_random_engine *generator_mutation_proba;
        std::default_random_engine *generator_mutation_alteration;


};

#endif // SPECIES_H
