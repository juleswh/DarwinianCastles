#ifndef GENOM_CODEC_H
#define GENOM_CODEC_H

#include "Object.h"

virtual class GenomCodec
{

	typedef Genom std::vector<gene_t>;

	typedef struct Gene
	{
		std::Vector<point> points;
		float density;
		float friction;
		point position;
	}gene_t;

	public:
		/**
		 * creates an object from a gene.
		 **/
		Object GeneDecode(gene_t gene);
		std::vector<Object> GenomDecode(Genom& genom);

		Genom CreateRandomGenom(int size);

}




#endif //GENOM_CODEC_H
