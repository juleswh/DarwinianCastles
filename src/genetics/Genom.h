#ifndef _GENOM_CLASS_H_
#define _GENOM_CLASS_H_
#include <stdlib.h>
#include <vector>
#include <random>
#include "Gene.h"

class Genom{
	public:
		//Genom(const std::vector<Gene> &genes,std::default_random_engine *generator_proba,std::default_random_engine *generator_alteration);
		Genom(const std::vector<Gene> &genes);
		//Genom(std::default_random_engine *generator_proba,std::default_random_engine *generator_alteration);
		Genom(void);

        //void setRandomGenerators(std::default_random_engine *generator_proba,std::default_random_engine *generator_alteration);
		Genom* mix(const Genom *other) const;

		int setGenes(const std::vector<Gene> &genes);

		/** returns the size of the genom*/
		unsigned int getSize() const;

		std::vector<Gene> const & getGenes(void) const;

		/** randommly change genes.
		 * @param probability the probability for each gene to be changed
		 * @param std_dev the standard deviation (sqrt(variance)) of the change to be applied
		 * The genom is randomly modified. Is gene has a probability given by the parameter
		 * to be modified. If the gene is modified, a random number is generated thanks to
		 * a Normal Distribution of mean 0 and standard deviation given by the 2nd parameter
		**/
		void alterate(double probability, double std_dev,std::default_random_engine *generator_proba,std::default_random_engine *generator_alteration);
		//void alterate(double probability, double std_dev);


	private:
		std::vector<Gene> genes;
		int size;
		//std::default_random_engine * generator_proba;
		//std::default_random_engine * generator_alteration;

};
#endif // _GENOM_CLASS_H_
