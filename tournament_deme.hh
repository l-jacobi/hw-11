#pragma once

#include "climb_chromosome.hh"
#include "deme.hh"

class TournamentDeme: public Deme{
	public:
		//can it inherit the constructor?
		TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);

		virtual ~TournamentDeme();

	/*	* Select P parents at random, where P is some constant power of two that you choose (no bigger than the population size).
		* Take the first pair in the set of P parents and discard the parent with the lower fitness of the two.
		* Do the same for the next pair, and so forth. You should have P/2 parents in the resulting set.
		* Repeat the last two steps until you’re left with only one parent.
	*/	virtual void compute_next_generation();

	protected:
		// Randomly select a chromosome in the population and return a pointer to that chromosome.
		virtual Chromosome* select_parent();
};