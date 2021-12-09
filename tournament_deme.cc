#include "tournament_deme.hh"
#include <chrono>
#include <cmath>

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
 : Deme(cities_ptr, pop_size, mut_rate)
{	//seeds the generator
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	generator_ = generator;
}

TournamentDeme::~TournamentDeme(){}

/*	* Select P parents at random, where P is some constant power of two that you choose (no bigger than the population size).
* Take the first pair in the set of P parents and discard the parent with the lower fitness of the two.
* Do the same for the next pair, and so forth. You should have P/2 parents in the resulting set.
* Repeat the last two steps until you’re left with only one parent.*/
Chromosome* TournamentDeme::select_parent(){
	std::uniform_int_distribution<> log_max_tourney_size(1, std::log2(pop_.size()));
	int tourney_size = std::pow(2, log_max_tourney_size(generator_));

	std::vector<Chromosome*> tournament(tourney_size);
	std::uniform_int_distribution<> random_chrom(0, pop_.size() - 1);
	//fill with random chromosomes
	for(int i = 0; i < tourney_size; ++i){
		tournament[i] = pop_[random_chrom(generator_)];
	}
	//get the best
	while(tournament.size() != 1){
		/*
		for(auto it = tournament.begin(); it != tournament.end(); ){
			if((*it)->get_fitness() > (*(it + 1))->get_fitness()){
				tournament.erase(it);
			}else{
				tournament.erase(it + 1);
			}
		}*/
		for(long unsigned i = 0; i < tournament.size(); ++i){
			if(tournament[i]->get_fitness() > tournament[i+1]->get_fitness()){
				tournament.erase(tournament.begin() + i);
			}else{
				tournament.erase(tournament.begin() + i + 1);
			}
		}
	}
	
	return tournament[0];
}