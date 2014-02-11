#include "Specimen.h"

Specimen::Specimen(Genom* genom, Species * species)
{
    this->setGenom(genom);
    this->setSpecies(species);
    this->setSexuallyOpen(false);
    this->setAge(0);
    this->setHealthLevel(100);
    this->is_dead = false;
}

Specimen * Specimen::reproduct(Specimen* other)
{
    Specimen *child=NULL;
    if(this->getSpecies() == other->getSpecies() && (this->isAlive() && other->isAlive())){
        child=new Specimen(this->getGenom()->mix(other->getGenom()),this->getSpecies());
        this->setSexuallyOpen(false);
        other->setSexuallyOpen(false);
    }
    return child;
}

Specimen::~Specimen(){
    delete this->genom;
}

const Genom * Specimen::getGenom(void) const
{
    return this->genom;
}

void Specimen::alterateGenom(double probability, double std_dev)
{
    this->genom->alterate(probability,std_dev,this->getGeneratorProba(),this->getGeneratorAlteration());
}

std::default_random_engine * Specimen::getGeneratorProba()
{
    return this->species->getGeneratorProba();
}

std::default_random_engine * Specimen::getGeneratorAlteration()
{
    return this->species->getGeneratorAlteration();
}


Species * Specimen::getSpecies(void) const
{
    return this->species;
}

void Specimen::setHealthLevel(int health_lvl)
{
    this->health_lvl=health_lvl;
    if(health_lvl<=0) this->is_dead=true;
}

unsigned int Specimen::getHealthLevel(void)
{
    return this->health_lvl;
}

bool Specimen::isAlive(){
    return !this->is_dead;
}

bool Specimen::isSexuallyOpen() const
{
    return this->sexually_open;
}

void Specimen::setSexuallyOpen(bool open)
{
    this->sexually_open = open;
}


void Specimen::setAge(unsigned int age)
{
    this->age=age;
    if(this->age >= this->species->getSexualMajorityAge())
        this->setSexuallyOpen(true);
    else this->setSexuallyOpen(false);

    std::normal_distribution<double> life_distribution(this->getLifeEsperance(),this->getLifeEsperanceStdDev());
    double val=life_distribution(*this->getGeneratorProba());
    if((0<val) && (val<=this->getAge())){
        //die!
        this->is_dead=true;
    }
}

void Specimen::growOld(unsigned int time)
{
    this->setAge(this->age+time);
}

unsigned int Specimen::getLifeEsperance(void)
{
    return this->species->getLifeEsperance();
}

double Specimen::getLifeEsperanceStdDev(void)
{
    return this->species->getLifeEsperanceStdDev();
}

unsigned int Specimen::getAge(void)
{
    return this->age;
}

void Specimen::setGenom(Genom * genom)
{
    this->genom=genom;
}

void Specimen::setSpecies(Species * species)
{
    this->species=species;
}
char *Specimen::toString(void)
{
    return const_cast<char*>("specimen");
}


