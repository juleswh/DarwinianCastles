#include "Gladiator.h"
#include "Gladiators.h"
#include "Species.h"
#include <iostream>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

const char* names[]={"Jean","Jacques","Edouard","Francis","Etienne","Paul","Titouan","Eric","Henry","Victor","Georges","Quentin","Neuville"};

int test_gladiators(int argc, char ** argv){
    std::default_random_engine generator_alteration(time(NULL));
    std::default_random_engine generator_proba(time(NULL));

    Gladiators gladiators(std::string("gladiators"),8,&generator_alteration,&generator_proba,2,49,0.05,3);
    gladiators.setLifeEsperance(40);
    gladiators.setLifeEsperanceStdDev(7);

    for (unsigned int i=0;i<10;i++){
        std::vector<Gene> genes;
        std::normal_distribution<double> distr(50,30); //normal distribution esperance 50, std_dev 30
        for(unsigned int j=0;j<8;j++){
            double value = distr(generator_proba);
            value=(value<0 ? 0 : value);
            value=(value>100 ? 100:value);
            genes.push_back(static_cast<gene_t>(value));
        }
        if(gladiators.addSpecimen(new Gladiator(new Genom(genes),&gladiators,names[i]))){cout<<"error adding specimen"<<endl;}
        else{
        Gladiator *new_g=dynamic_cast<Gladiator*>(gladiators.getSpecimens()[i]);
        cout << "added a gladiator"<<endl;
        cout<< *new_g <<endl;
        }
    }
    cout<<"total added"<<gladiators.getSpecimens().size()<<endl;
    gladiators.tournament();
    cout<<"\n\nend of tournament!"<<endl;
    for(std::vector<Gladiator*>::const_iterator it=gladiators.getSpecimens().begin();it!=gladiators.getSpecimens().end();++it){
        cout<< **it <<endl;
    }

    int generations=0;
    for(int i=0; i<generations;i++){
        gladiators.loveSeason();
        gladiators.checkAlive();
        cout<<endl<<"---------------"<<endl<<"generation "<<i<<endl;
        cout << "specimens[] size = " << gladiators.getSpecimens().size() << endl;

    }

    return 0;
}
