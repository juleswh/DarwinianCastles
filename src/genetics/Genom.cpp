#include "Genom.h"

//Genom::Genom(const std::vector<Gene> &genes,std::default_random_engine *generator_proba,std::default_random_engine *generator_alteration){
Genom::Genom(const std::vector<Gene> &genes){
//    this->setRandomGenerators(generator_proba,generator_alteration);
    this->size=0;
    this->setGenes(genes);
}

//Genom::Genom(std::default_random_engine *generator_proba,std::default_random_engine *generator_alteration){
Genom::Genom(void){
//    this->setRandomGenerators(generator_proba,generator_alteration);
    this->size=0;
}

/*void Genom::setRandomGenerators(std::default_random_engine *generator_proba,std::default_random_engine *generator_alteration){
    this->generator_alteration=generator_alteration;
    this->generator_proba=generator_proba;
}*/

int Genom::setGenes(const std::vector<Gene> &genes){
    if(this->getSize()==0){
        this->genes.assign(genes.begin(),genes.end());
        this->size=this->genes.size();
        return 0;
    }else{
        return 1;
    }
}

int Genom::getSize() const{
    return this->size;
}

Genom* Genom::mix(const Genom *other) const{
    Genom* child=NULL;
    if(this->getSize()==other->getSize()){
        child=new Genom(this->genes);
        //for each gene, take randomly from A or B and put in C (the generated child)
        for (int i=0;i<this->getSize();i++){
            if((rand()%2)>=1){
                child->genes[i]=other->genes[i];
            }
        }
    }else{
    //error, genoms have different size, returns nullptr
    }
    return child;
}

//void Genom::alterate(double probability, double std_dev)
void Genom::alterate(double probability, double std_dev,std::default_random_engine &generator_proba,std::default_random_engine &generator_alteration)
{
    std::normal_distribution<double> alteration(0,std_dev);
    std::uniform_real_distribution<double> proba(0.0,1.0);

    for (int i=0;i<this->getSize();i++){
        if(proba(generator_proba)<probability){
            //this gene is selected to be modified
            this->genes[i].setValue(genes[i].getValue()+alteration(generator_alteration));
        }
    }

}

std::vector<Gene> const & Genom::getGenes(void) const{
    return this->genes;
}

