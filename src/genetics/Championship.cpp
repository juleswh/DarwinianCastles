#include "Championship.h"

#include <iostream>
using namespace std;

Championship::Championship(std::vector<Gladiator*> &competitors, ChampionshipInterface* interface)
{
    this->interface=interface;
    this->competitors.assign(competitors.begin(),competitors.end());
    this->duels.reserve(this->competitors.size()-1); //always at least n-1 duels
    for (unsigned int i=0;i<this->competitors.size();i++){
        if((i%2)==1){
            this->duels.push_back(new Duel(this->competitors[i-1],this->competitors[i]));
        }
    }
    if(this->competitors.size()%2!=0){
        this->duels.push_back(new Duel(this->competitors.back(),nullptr));
    }

    unsigned int pr_begin=0;
    unsigned int pr_end=this->duels.size(); //keep memory of the size at this moment
    while((pr_end-pr_begin)>1){
        cout << "previous size = " << pr_end-pr_begin << endl; //TODO maybe an issue here
        for(unsigned int i=pr_begin; i<pr_end;i++){
            if(((pr_begin-i)%2)==1){
                cout << "adding duel from duels "<< i-1 << " and " << i<<endl;
                this->duels.push_back(new Duel(this->duels[i-1],this->duels[i]));
            }
        }
        if((pr_end-pr_begin)%2!=0){
            cout << "adding duel from duel "<< pr_end-1 <<endl;
            this->duels.push_back(new Duel(this->duels[pr_end-1],nullptr));
        }
        pr_begin=pr_end;
        pr_end=this->duels.size();
    }
}

Gladiator* Championship::start(void)
{
    if(this->interface){
        ChampionshipEvent e;
        e.championship=this;
        e.type=BEGIN_CHAMPIONSHIP;
        interface->onChampionshipBegin(e);
    }
    for(std::vector<Duel*>::iterator it=this->duels.begin();it!=this->duels.end();++it){
        (*it)->prepare();
        if((*it)->getFighters().size()==2){
            cout << "fight #" << it - this->duels.begin()+1 <<" : "<< (*it)->getFighters()[0]->getName() << " vs " << (*it)->getFighters()[1]->getName() << endl;
        }else if ((*it)->getFighters().size()==1){
            cout << "fight #" << it - this->duels.begin()+1 <<" : "<< (*it)->getFighters()[0]->getName() << " alone" << endl;
        }
        if(this->interface){
            ChampionshipDuelEvent e;
            e.championship=this;
            e.type=BEGIN_CHAMPIONSHIP;
            e.duel=*it;
            interface->onDuelBegin(e);
        }

        (*it)->start();
        if((*it)->getWinner()==nullptr){std::exception e; throw e;}
        cout << "winner : " << (*it)->getWinner()->getName() <<endl;
        if(this->interface){
            ChampionshipDuelEvent e;
            e.championship=this;
            e.type=END_CHAMPIONSHIP;
            e.duel=*it;
            interface->onDuelEnd(e);
        }
    }
    this->setWinner(this->duels.back()->getWinner());

    if(this->interface){
        ChampionshipEvent e;
        e.championship=this;
        e.type=END_CHAMPIONSHIP;
        interface->onChampionshipEnd(e);
    }

    return this->getWinner();
}


Championship::~Championship()
{
    for(std::vector<Duel*>::iterator it=this->duels.begin();it!=this->duels.end();++it){
        delete *it;
    }
}
