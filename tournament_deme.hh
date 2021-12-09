#pragma once

#include "climb_chromosome.hh"
#include "deme.hh"

class TournamentDeme: public Deme{
	public:
		//can it inherit the constructor?
		TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);

		virtual ~TournamentDeme();

	protected:
		// Randomly select a chromosome in the population and return a pointer to that chromosome.
		virtual ClimbChromosome* select_parent();
};