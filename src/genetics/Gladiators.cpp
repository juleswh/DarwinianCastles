#include "Gladiators.h"

Gladiators::Gladiators(const std::string &name,unsigned int genom_size,
            std::default_random_engine *generator_mutation_proba, std::default_random_engine *generator_mutation_alteration,
            unsigned int sexual_majority,unsigned int minSexHealthLevel,
            double mutation_probability,double mutation_stddev)
    :Species(name,genom_size,generator_mutation_proba,generator_mutation_alteration,sexual_majority,minSexHealthLevel,mutation_probability,mutation_stddev)
{
}

Gladiators::~Gladiators()
{
}

unsigned int Gladiators::addSpecimen(Gladiator *new_specimen)
{
    if(new_specimen->getGenom()->getSize()!=this->getGenomSize()){
        return 1; //new specimen have a not the right genom size
    }else{
        this->specimens.push_back(new_specimen);
        return 0;
    }
}

std::vector<Gladiator*> const & Gladiators::getSpecimens(void) const{
    return this->specimens;
}

void Gladiators::tournament(void)
{
    std::vector<Gladiator*> competitors;
    unsigned int previous_competitors_size=0;
    do{
        previous_competitors_size=competitors.size();
        competitors.clear();

        for(std::vector<Gladiator*>::iterator it=this->specimens.begin();it!=this->specimens.end();++it){
            if((*it)->continueFighting()){
                competitors.push_back(*it);
            }
        }

        std::cout << std::endl << competitors.size() << " competitors (over "<<this->specimens.size()<<" gladiators)" <<std::endl;

        for(std::vector<Gladiator*>::iterator it=competitors.end()-1;it>competitors.begin();it=it-2){
            std::cout << "  " << it-1-competitors.begin() << "  vs  " << it-competitors.begin() <<std::endl;
            std::cout << (*(it-1))->getName() << " - " << (*it)->getName() <<std::endl;
            (*it)->fight(*(it-1));
            if((*it)->continueFighting()){
                if((*(it-1))->continueFighting()){
                    std::cout << "match null"<<std::endl;
                }else{
                    std::cout << it-competitors.begin() << " winner"<<std::endl;
                }
            }else{
                std::cout << it-1-competitors.begin() << " winner"<<std::endl;
            }
        }
    }while(competitors.size()!=previous_competitors_size);


}

unsigned int Gladiators::loveSeason(void)
{
    return 0;
}

