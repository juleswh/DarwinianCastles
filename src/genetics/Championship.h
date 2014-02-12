#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include <vector>
#include "Gladiator.h"
#include "Duel.h"

class Championship;

enum EventType {END_DUEL,BEGIN_DUEL,END_CHAMPIONSHIP,BEGIN_CHAMPIONSHIP};

struct ChampionshipEvent{
    Championship* championship;
    EventType type;
};
struct ChampionshipDuelEvent:ChampionshipEvent{
    Duel* duel;
};

class ChampionshipInterface{

    public:
        virtual void onDuelEnd(ChampionshipDuelEvent &){};
        virtual void onDuelBegin(ChampionshipDuelEvent &){};
        virtual void onChampionshipBegin(ChampionshipEvent &){};
        virtual void onChampionshipEnd(ChampionshipEvent &){};
};

class Championship
{
    public:
        /** copies the pointers to local storage**/
        Championship(std::vector<Gladiator*> &competitors, ChampionshipInterface* interface=nullptr);
        virtual ~Championship();
        std::vector<Duel*> getDuels() { return duels; }
        void setDuels(std::vector<Duel*> val) { duels = val; }
        Gladiator* getWinner() { return winner; }
        void setWinner(Gladiator* val) { winner = val; }
        Gladiator* start(void);
    protected:
    private:
        std::vector<Gladiator*> competitors;
        std::vector<Duel*> duels;
        Gladiator* winner;

        ChampionshipInterface* interface;
};

#endif // CHAMPIONSHIP_H
