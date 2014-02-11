#include "Duel.h"

Duel::Duel(std::vector<Gladiator*> fighters)
{
    if(fighters.size()==0 || fighters.size()>2) {std::exception e; throw e;}
    this->setFighters(fighters);
    this->setWinner(nullptr);
}

Duel::Duel(std::vector<Duel*> const &previous_duels){
    if(previous_duels.size()==0 || previous_duels.size()>2){std::exception e; throw e;}
    this->setPreviousDuels(previous_duels);
}
Duel::Duel(Duel* prev_duel1,Duel *prev_duel2){
    if(prev_duel1==nullptr){std::exception e; throw e;}
    this->previous_duels.push_back(prev_duel1);
    if(prev_duel2!=nullptr){
        this->previous_duels.push_back(prev_duel2);
    }
}

Duel::Duel(Gladiator* fighter1,Gladiator* fighter2){
    if(fighter1==nullptr){std::exception e; throw e;}
    else
        this->fighters.push_back(fighter1);
    if(fighter2!=nullptr)
        this->fighters.push_back(fighter2);
}


Gladiator* Duel::start(){
    if(this->fighters.size()==0){
        this->fighters.push_back(this->previous_duels[1]->getWinner());
        if(this->previous_duels.size()==2)
            this->fighters.push_back(this->previous_duels[2]->getWinner());
    }
    if(this->fighters.size()==1){this->setWinner(this->fighters.front());} //no fight, only one competitor
    else this->setWinner(this->fighters[0]->fight(this->fighters[1]));
    return this->getWinner();
}




Duel::~Duel()
{
    //dtor
}
