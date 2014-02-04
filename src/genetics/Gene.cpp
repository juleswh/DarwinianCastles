#include "Gene.h"

Gene::Gene(gene_t val)
{
    this->_value=val;
}

Gene::~Gene()
{
    //dtor
}



gene_t Gene::getValue() const{
    return this->_value;
}

void Gene::setValue(gene_t val){
    this->_value=val;
}
void Gene::setValue(double dbl_val){
    this->setValue(static_cast<gene_t>(dbl_val));
}
