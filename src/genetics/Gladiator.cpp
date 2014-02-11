#include "Gladiator.h"

Gladiator::Gladiator(Genom* genom, Species * species, const char* name) : Specimen(genom,species)
{
    this->initialize(this->getGenom()->getGenes());
    this->setName(name);
}

Gladiator::Gladiator(Genom* genom, Species * species, std::string &name) : Specimen(genom,species)
{
    this->initialize(this->getGenom()->getGenes());
    this->setName(name);
}

void Gladiator::initialize(std::vector<Gene> const &genes)
{
    std::vector<gene_t> a;
    for (std::vector<Gene>::const_iterator it=genes.begin();it!=genes.end();++it){
        a.push_back((it->getValue()>=100 ? 100 : it->getValue())); //saturates values at 100
    }
    int def=    -0.2*a[0]   +0.1*a[1]   +0.3*a[2]   +0.3*a[4]   +0.3*a[6];
    int att=    0.2*a[0]   -0.2*a[1]   +0.4*a[2]   +0.2*a[5]   +0.3*a[6];
    int health= (0.5*a[3]   +0.5*a[7]   -0.2*a[4])/2;
    int charism=0.2*a[0]   +0.5*a[2]   +0.3*a[3]   -0.3*a[4];
    int obstination=1.0*a[7]   -0.2*a[5];
    int lifeEsperance=0.5*a[3] +0.2*a[5]   +0.3*a[7]   -0.3*a[4];

    def=(def<0 ? 0 : def);
    att=(att<0 ? 0 : att);
    health=(health<0 ? 50 : health+50);
    charism=(charism<0 ? 0 : charism);
    obstination=(obstination<0 ? 0 : obstination);
    lifeEsperance=(lifeEsperance<0 ? 0 : lifeEsperance);

    this->setDefense(def);
    this->setAttack(att);
    this->setHealthLevel(health);
    this->setCharism(charism);
    this->setObstination(obstination);
    this->setLifeEsperance(lifeEsperance);
}

bool Gladiator::continueFighting(void)
{
    return (this->getHealthLevel()>100-this->getObstination()) && this->isAlive();
}

int Gladiator::attacks(Gladiator* other,bool simulation)
{
    int damage=this->getAttack() - other->getDefense();
    damage=(damage<=0 ? 0 : damage);
    if(!simulation){
        other->setHealthLevel(other->getHealthLevel()-damage);
    }
    return damage;
}

Gladiator* Gladiator::fight(Gladiator* other)
{
    Gladiator* winner;
    if(this==other){
        //no fight vs itself
        winner =nullptr;
    }else if(this->attacks(other,true)==0 && other->attacks(this,true)== 0 ){
        //no winner
        winner=nullptr;
    }else{
    //fight
        while(this->continueFighting() && other->continueFighting())
        {
            std::cout << " -"<<this->attacks(other);
            std::cout << " || -"<<other->attacks(this)<<std::endl;
        }
        //victory => +10 charism
        //loss => death
        //give up => -10 charism

        if(this->continueFighting()) {
            this->setCharism(this->getCharism()+10);
            other->setCharism(other->getCharism()-10);
            winner=this;
        }else{
            this->setCharism(this->getCharism()-10);
            other->setCharism(other->getCharism()+10);
            winner=other;
        }
    }

    return winner;

}

std::ostream& operator<<(std::ostream & Str, Gladiator & g) {
    char buff[512];
    sprintf(buff,"Gladiator %s, %s, age:%u\nHP: %u\tCHM: %u\nATT: %u\tOBS: %u\nDEF: %u\tESP: %u\n%s\n",
        g.getName().c_str(),
        (g.isAlive() ? "alive":"dead"),
        g.getAge(),g.getHealthLevel(),g.getCharism(),g.getAttack(),g.getObstination(),g.getDefense(),g.getLifeEsperance(),
        (g.continueFighting() ? "ready for fight!" : "taking some rest..."));
    Str<<buff;
    return Str;
}


/*char *Gladiator::toString(void){
    char str[512];
    //std::string s;
    sprintf(str,"Gladiator %s, %s, age:%u\nHP: %u\tCHM: %u\nATT: %u\tOBS: %u\nDEF: %u\tESP: %u\n%s\n",
        this->getName().c_str(),
        (this->isAlive() ? "alive":"dead"),
        this->getAge(),this->getHealthLevel(),this->getCharism(),this->getAttack(),this->getObstination(),this->getDefense(),this->getLifeEsperance(),
        (this->continueFighting() ? "ready for fight!" : "taking some rest..."));
    return str;
}*/

Gladiator::~Gladiator()
{
    //dtor
}
