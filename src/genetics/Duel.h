#ifndef DUEL_H
#define DUEL_H

#include <vector>
#include "Gladiator.h"


class Duel
{
    public:
        Duel(std::vector<Gladiator*> fighters);
        Duel(std::vector<Duel*> &previous_duels);
        Duel(Duel* prev_duel1,Duel *prev_duel2);
        Duel(Gladiator* fighter1,Gladiator* figher2);
        virtual ~Duel();
        std::vector<Gladiator*> getFighters() { return fighters; }
        void setFighters(std::vector<Gladiator*> val) { fighters = val; }
        Gladiator* getWinner() { return winner; }
        void setWinner(Gladiator* val);

        void setPreviousDuels(std::vector<Duel*> &previous_duels) { this->previous_duels.assign(previous_duels.begin(),previous_duels.end());}
        std::vector<Duel*> getPreviousDuels(void){return this->previous_duels;}

        unsigned int getID(void){ return this->id_count;}

        void prepare(void);


        Gladiator* start(void);

        friend std::ostream& operator<<(std::ostream & Str, Duel &d);


    protected:
    private:
        std::vector<Gladiator*> fighters;
        Gladiator* winner;
        std::vector<Duel*> previous_duels;


        void setID(void);
        unsigned int id_count;
        static unsigned int counter;
};

#endif // DUEL_H
