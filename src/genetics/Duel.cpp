#include "Duel.h"

#include <iostream>
using namespace std;

unsigned int Duel::counter = 0;

Duel::Duel(std::vector<Gladiator*> fighters)
{
    this->setID();
    if(fighters.size()==0 || fighters.size()>2) {std::exception e; throw e;}
    this->setFighters(fighters);
    this->setWinner(nullptr);
}

Duel::Duel(std::vector<Duel*> &previous_duels){
    this->setID();
    if(previous_duels.size()==0 || previous_duels.size()>2){std::exception e; throw e;}
    this->setPreviousDuels(previous_duels);
    this->setWinner(nullptr);
}

Duel::Duel(Duel* prev_duel1,Duel *prev_duel2){
    this->setID();
    if(prev_duel1==nullptr){std::exception e; throw e;}
    this->previous_duels.push_back(prev_duel1);
    if(prev_duel2!=nullptr){
        this->previous_duels.push_back(prev_duel2);
    }
    this->setWinner(nullptr);
}

Duel::Duel(Gladiator* fighter1,Gladiator* fighter2){
    this->setID();
    if(fighter1==nullptr){std::exception e; throw e;}
    else
        this->fighters.push_back(fighter1);
    if(fighter2!=nullptr)
        this->fighters.push_back(fighter2);
    this->setWinner(nullptr);
}

void Duel::setWinner(Gladiator* val){
    winner = val;
}


void Duel::setID(void){
    this->id_count=Duel::counter++;
}

void Duel::prepare(void){
    if(this->fighters.size()==0){
        if(this->previous_duels.size()!=0){
            this->fighters.push_back(this->previous_duels[0]->getWinner());
            if(this->previous_duels.size()==2){
                this->fighters.push_back(this->previous_duels[1]->getWinner());
            }
        }
    }
    for(int i=0;i<this->fighters.size();i++){
        if(this->fighters[i]==nullptr){std::exception e;throw e;}
    }
}

Gladiator* Duel::start(){
    this->prepare();
    if(this->fighters.size()==1){this->setWinner(this->fighters.front());} //no fight, only one competitor
    else {
        this->setWinner(this->fighters[0]->fight(this->fighters[1]));
    }
    if(this->getWinner()==nullptr){
        if(this->fighters[0]->getHealthLevel() > this->fighters[1]->getHealthLevel())
            this->setWinner(this->fighters[0]);
        else
            this->setWinner(this->fighters[1]);
    }
    return this->getWinner();
}


std::ostream& operator<<(std::ostream & Str, Duel & d) {
    char buff[512];
    sprintf(buff,"Duel %u",d.id_count);
    Str<<buff;
    return Str;
}



Duel::~Duel()
{
    //dtor
}
