#ifndef GENE_H
#define GENE_H

typedef int gene_t;

class Gene
{

    public:
        Gene(gene_t val=0);
        virtual ~Gene();
        gene_t getValue() const;
        void setValue(gene_t val);
        void setValue(double dbl_val);
    protected:
    private:
        gene_t _value;
};

#endif // GENE_H
