#include "testGladiators.h"

int test_gladiators(int argc, char ** argv);


using std::cout;
using std::endl;

inline unsigned long factorial(unsigned long x) {
  return (x <= 1 ? 1 : x * factorial(x - 1));
}

unsigned long numberOfSpecimen(unsigned long initialnumber,unsigned long generations){
    if(generations <= 0 ){
        return initialnumber;
    }else{
        return numberOfSpecimen((initialnumber + initialnumber*(initialnumber-1)/2),generations-1);
    }
}

int test_species(int argc, char ** argv){
    std::default_random_engine generator_alteration(time(NULL));
    std::default_random_engine generator_proba(time(NULL));

    Species hippocampe(std::string("hippocampe"),20,&generator_alteration,&generator_proba,2,0,0.05,3);
    hippocampe.setLifeEsperance(11);
    hippocampe.setLifeEsperanceStdDev(2);
    std::string str1("mmmmmmmmmmmmmmmmmmmm");
    std::string str2("AAAAAAAAAAAAAAAAAAAA");
    std::vector<Gene> genes1;
    std::vector<Gene> genes2;

    for(unsigned int i=0;i<str1.size();i++){
        genes1.push_back((gene_t)str1[i]);
        genes2.push_back((gene_t)str2[i]);
    }

    Specimen *sp1=new Specimen(new Genom(genes1),&hippocampe);
    Specimen *sp2=new Specimen(new Genom(genes2),&hippocampe);
    hippocampe.addSpecimen(sp1);
    hippocampe.addSpecimen(sp2);

    cout << "start love season"<<endl;

    int generations=15;
    for(int i=0; i<generations;i++){
        hippocampe.loveSeason();
        hippocampe.checkAlive();
        cout<<endl<<"---------------"<<endl<<"generation "<<i<<endl;
        cout << "specimens[] size = " << hippocampe.getSpecimens().size() << endl;
        for(unsigned int i=0;i<hippocampe.getSpecimens().size();i++){
            Specimen *sp=hippocampe.getSpecimens().at(i);
            cout << i << " : ";
            for(unsigned int j=0;j<hippocampe.getGenomSize();j++){
                cout << (char)(sp->getGenom()->getGenes()[j].getValue());
            }
            cout << " - age : " << sp->getAge() << endl;
        }
    }

    return 0;
}

int test_genom(int argc, char ** argv){

    std::default_random_engine generator_alteration(time(NULL));
    std::default_random_engine generator_proba(time(NULL));

    std::string str1("mmmmmm");
    std::string str2("MMMMMM");
    std::vector<Gene> genes1;
    std::vector<Gene> genes2;

    srand (time(NULL));

    for(unsigned int i=0;i<str1.size();i++){
        genes1.push_back((gene_t)str1[i]);
        genes2.push_back((gene_t)str2[i]);
    }


    Genom pere(genes1);
    Genom mere(genes2);

    pere.alterate(0.2,5,&generator_proba,&generator_alteration);
    mere.alterate(0.2,5,&generator_proba,&generator_alteration);
    cout << "pere alt = ";
    for(unsigned int i=0;i<str1.size();i++){
        cout << (char)(pere.getGenes()[i].getValue());
    }
    cout <<endl;
    cout << "mere alt = ";
    for(unsigned int i=0;i<str1.size();i++){
        cout << (char)(mere.getGenes()[i].getValue());
    }
    cout <<endl;

    Genom *fils=pere.mix(&mere);
    if(fils==NULL){
        cout << "erreur : mort né";
        exit(EXIT_FAILURE);
    }

    for(unsigned int i=0;i<str1.size();i++){
        cout << (char)(fils->getGenes()[i].getValue());
    }
    cout <<endl;

    delete fils;
    return 0;
}

int main(int argc, char ** argv){
    TestGladiators test;
    cout<< "run test"<<endl;
    return test.test_gladiators(argc,argv);
}
