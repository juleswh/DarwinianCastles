#ifndef SPECIMEN_H
#define SPECIMEN_H

#include "Genom.h"
#include "Species.h"
class Species;

class Specimen{

	public:

        Specimen(Genom *genom, Species * species);
        virtual ~Specimen();

        /** side effect : set sexually open to false for both specimens**/
        Specimen *reproduct(Specimen *other);

        const Genom * getGenom(void) const;
        void alterateGenom(double probability, double std_dev);

        std::default_random_engine *getGeneratorProba();
        std::default_random_engine * getGeneratorAlteration();

        Species * getSpecies(void) const;

        /** side effect : reset sexually open to true if sexually major according to species->getSexualMajorityAge()**/
        void setAge(unsigned int age);
        unsigned int getAge(void);
        /** side effect : reset sexually open to true if sexually major according to species->getSexualMajorityAge()
         *  @param time the increment of age
        **/
        void growOld(unsigned int time=1);

        unsigned int getLifeEsperance(void);
        unsigned int getLifeEsperanceStdDev(void);

        void setHealthLevel(int health_lvl);
        int getHealthLevel(void);

        bool isAlive(void);

        bool isSexuallyOpen() const;
        void setSexuallyOpen(bool open);

    protected:
        /** set the genom.
        *   @param genom the genom to set (makes a copy)
        **/
        void setGenom(Genom *genom);
        /** set the species this specimen belongs to.
        *   this method do not update the species specimen list
        *   @param species the species this specimen should belong to
        **/
        void setSpecies(Species *species);

	private:
        Genom *genom;
        Species *species;
        unsigned int age;
        int health_lvl;
        bool is_dead;
        bool sexually_open;
        std::default_random_engine *generator_proba;
        std::default_random_engine *generator_alteration;


};
#endif // SPECIMEN_H
