#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include <vector>
#include "Gladiator.h"
#include "Duel.h"

class Championship
{
    public:
        /** copies the pointers to local storage**/
        Championship(std::vector<Gladiator*> &competitors);
        virtual ~Championship();
        std::vector<Duel> getDuels() { return duels; }
        void setDuels(std::vector<Duel> val) { duels = val; }
        Gladiator* getWinner() { return winner; }
        void setWinner(Gladiator* val) { winner = val; }
        Gladiator* start(void);
    protected:
    private:
        std::vector<Gladiator*> competitors;
        std::vector<Duel> duels;
        Gladiator* winner;
};

#endif // CHAMPIONSHIP_H
