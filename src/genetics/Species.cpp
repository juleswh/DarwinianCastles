#include "Species.h"

using std::string;
using std::vector;

Species::Species(const std::string &name,unsigned int genom_size,
std::default_random_engine *generator_mutation_proba, std::default_random_engine *generator_mutation_alteration,
unsigned int sexual_majority,unsigned int minSexHealthLevel,
double mutation_probability,double mutation_stddev)
{
    this->setName(name);
    this->setGenomSize(genom_size);
    this->sexual_majority=sexual_majority;
    this->minSexHealthLevel=minSexHealthLevel;
    this->mutation_probability=mutation_probability;
    this->mutation_stddev=mutation_stddev;
    this->generator_mutation_alteration=generator_mutation_alteration;
    this->generator_mutation_proba=generator_mutation_proba;
    this->setLifeEsperance(0);
    this->setLifeEsperanceStdDev(0);
}

Species::~Species()
{
    for (unsigned int i=0;i<this->specimens.size();i++){
        delete this->specimens[i];
    }
}

void Species::setName(const std::string &name){
    this->name=name;
}

std::string Species::getName(void){
    return this->name;
}

void Species::setGenomSize(unsigned int genom_size)
{
    this->genom_size=genom_size;
}

unsigned int Species::getGenomSize(void)
{
    return this->genom_size;
}

unsigned int Species::getLifeEsperance(void) const
{
    return this->life_esperance;
}

double Species::getLifeEsperanceStdDev(void) const
{
    return this->life_esperance_std_dev;
}

void Species::setLifeEsperance(unsigned int esperance)
{
    this->life_esperance=esperance;
}

void Species::setLifeEsperanceStdDev(double std_dev)
{
    this->life_esperance_std_dev=std_dev;
}


unsigned int Species::addSpecimen(Specimen *new_specimen)
{
    if(new_specimen->getGenom()->getSize()!=this->getGenomSize()){
        return 1; //new specimen have a not the right genom size
    }else{
        this->specimens.push_back(new_specimen);
        return 0;
    }
}

std::vector<Specimen*> const & Species::getSpecimens(void) const{
    return this->specimens;
}

bool is_null(Specimen *sp){
    return sp==NULL;
}
unsigned int Species::checkAlive(void)
{
    for(unsigned int i=0; i<this->specimens.size();i++){
        if(!this->specimens[i]->isAlive()){
            delete this->specimens[i];
            this->specimens.erase(this->specimens.begin()+i);
            --i;
        }
    }
    //this->specimens.erase(std::remove_if(this->specimens.begin(),this->specimens.end(),is_null));
    return this->specimens.size();
}

std::default_random_engine *Species::getGeneratorProba()
{
    return this->generator_mutation_proba;
}

std::default_random_engine *Species::getGeneratorAlteration()
{
    return this->generator_mutation_alteration;
}

unsigned int Species::getSexualMajorityAge(void) const
{
    return this->sexual_majority;
}

bool Species::isSexuallyActive(Specimen* specimen)
{
    return (specimen->getHealthLevel()>=this->minSexHealthLevel) && (specimen->isSexuallyOpen());
}

bool Species::isSexuallyActive(unsigned int index)
{
    return this->isSexuallyActive(this->specimens[index]);
}

bool Species::canReproduct(unsigned int index1,unsigned int index2){
    if( this->isSexuallyActive(index1) && this->isSexuallyActive(index2)){
        if(1) return true; //TODO implement other tests here!
        else return false;
    }else return false;
}
unsigned int Species::loveSeason()
{
    unsigned int new_specimens=0;
    unsigned int initial_specimen_size=this->specimens.size();
    for(unsigned int a=0;a<initial_specimen_size;a++){
        for (unsigned int b=0;b<a;b++){
            if(canReproduct(a,b)){
                new_specimens+=this->reproduction(a,b);
            }
        }
    }
    for(unsigned int a=0;a<initial_specimen_size;a++){
        this->specimens.at(a)->growOld();
    }
    return new_specimens;
}

unsigned int Species::reproduction(unsigned int index1, unsigned int index2)
{
    this->addSpecimen(this->specimens.at(index1)->reproduct(this->specimens.at(index2)));
    this->specimens.at(this->specimens.size()-1)->alterateGenom(this->mutation_probability,
                    this->mutation_stddev);
    return 1;
}
