#ifndef DUEL_H
#define DUEL_H

#include <vector>
#include "Gladiator.h"


class Duel
{
    public:
        Duel(std::vector<Gladiator*> fighters);
        Duel(std::vector<Duel*> const &previous_duels);
        Duel(Duel* prev_duel1,Duel *prev_duel2);
        Duel(Gladiator* fighter1,Gladiator* figher2);
        virtual ~Duel();
        std::vector<Gladiator*> getFighters() { return fighters; }
        void setFighters(std::vector<Gladiator*> val) { fighters = val; }
        Gladiator* getWinner() { return winner; }
        void setWinner(Gladiator* val) { winner = val; }

        void setPreviousDuels(std::vector<Duel*> const &previous_duels) { this->previous_duels.assign(previous_duels.begin(),previous_duels.end());}
        std::vector<Duel*> getPreviousDuels(void){return this->previous_duels;}
        Gladiator* start(void);

    protected:
    private:
        std::vector<Gladiator*> fighters;
        Gladiator* winner;
        std::vector<Duel*> previous_duels;
};

#endif // DUEL_H
