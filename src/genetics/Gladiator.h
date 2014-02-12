#ifndef GLADIATOR_H
#define GLADIATOR_H

#include "Specimen.h"
#include <iostream>


class Gladiator : public Specimen
{
    public:
        Gladiator(Genom* genom, Species * species,const char* name="");
        Gladiator(Genom* genom, Species * species,std::string &name);

        void initialize(std::vector<Gene> genes);
        virtual ~Gladiator();

        Gladiator* fight(Gladiator *other);

        /** attack an other gladiator.
         *  @param other pointer to the other gladiator
         *  @param simulation if true, the other will not take damage
         *  @return the damage taken by the other, or it would have taken
         **/
        int attacks(Gladiator *other,bool simulation=false);
        bool continueFighting(void);

        unsigned int getDefense() { return defense; }
        void setDefense(unsigned int val) { defense = val; }
        unsigned int getAttack() { return attack; }
        void setAttack(unsigned int val) { attack = val; }
        unsigned int getCharism() { return charism; }
        void setCharism(unsigned int val) { charism = val; }
        unsigned int getObstination() { return obstination; }
        void setObstination(unsigned int val){ obstination=val; }

        void resetDefense(void);
        void resetAttack(void);
        void resetCharism(void);
        void resetObstination(void);
        void resetHealthLevel(void);
        void resetLifeEsperance(void);

        void reset(void);

        void setName(std::string &name){this->name.assign(name);};
        void setName(const char* name){this->name.assign(name);};
        std::string const & getName(void){return this->name;}
        /** override **/
        unsigned int getLifeEsperance(void){ return lifeEsperance; }
        void setLifeEsperance(unsigned int val){ lifeEsperance=val; }

        friend std::ostream& operator<<(std::ostream & Str, Gladiator &g);
        //char* toString(void);

    protected:
    private:
        unsigned int defense;
        unsigned int attack;
        unsigned int charism;
        unsigned int obstination;
        unsigned int lifeEsperance;
        std::string name;
};

#endif // GLADIATOR_H
