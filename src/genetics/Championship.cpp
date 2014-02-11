#include "Championship.h"

Championship::Championship(std::vector<Gladiator*> &competitors)
{
    this->competitors.assign(competitors.begin(),competitors.end());
    this->duels.reserve(this->competitors.size()-1); //always at least n-1 duels
    for (unsigned int i=0;i<this->competitors.size();i++){
        if((i%2)==1){
            this->duels.push_back(Duel(this->competitors[i-1],this->competitors[i]));
        }
    }
    if(this->competitors.size()%2!=0){
        this->duels.push_back(Duel(this->competitors.back(),nullptr));
    }

    unsigned int pr_begin=0;
    unsigned int pr_end=this->duels.size(); //keep memory of the size at this moment
    while((pr_end-pr_begin)>1){
        for(unsigned int i=pr_begin; i<pr_end;i++){
            if((i%2)==1){
                this->duels.push_back(Duel(&(this->duels[i-1]),&(this->duels[i])));
            }
        }
        if((this->duels.size()-pr_end)%2!=0){
            this->duels.push_back(Duel(&(this->duels[pr_end-1]),nullptr));
        }
        pr_begin=pr_end;
        pr_end=this->duels.size();
    }
}

Gladiator* Championship::start(void)
{
    for(std::vector<Duel>::iterator it=this->duels.begin();it!=this->duels.end();++it){
        it->start();
    }
    this->setWinner(this->duels.back().getWinner());
    return this->getWinner();
}


Championship::~Championship()
{
    //dtor
}
