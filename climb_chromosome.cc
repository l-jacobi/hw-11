#include "climb_chromosome.hh"
#include <random>
#include <algorithm>
#include <cassert>
#include <vector>

bool my_compare(ClimbChromosome* a, ClimbChromosome* b)
{
    return (a->get_fitness() > b->get_fitness());
}

void
ClimbChromosome::mutate() //override?
{
  ClimbChromosome* option_2 = clone();
  ClimbChromosome* option_3 = clone();

  std::uniform_int_distribution<int> distr(0, order_.size() - 1);
  int p = distr(generator_);

  //calling respective helper functions on the two new options,
  //note that the same p is passed to both, it can't be generated locally
  swap_down(option_2, p);
  swap_up(option_3, p);

  std::vector<ClimbChromosome*> options({this, option_2, option_3});

  ClimbChromosome* best = std::max_element(options.begin(), options.end(), my_compare);

  //if the original is best, compiler will basically ignore this line
  //otherwise it should update our permutation to match the best one
  order_ = best->get_ordering();

  if(option_2){ delete option_2; }
  if(option_3){ delete option_3; }
}

void swap_down(ClimbChromosome* chromo, int p)
{
  //reference, to make sure the original Chromosome is modified
  Cities::permutation_t& order = chromo->get_ordering();
  auto N = order.size();
  int pos_2;
  (p == 0) ? (pos_2 = N-1) : (pos_2 = p-1);
  std::swap(order[p], order[pos_2]);
}

void swap_up(ClimbChromosome* chromo, int p)
{
  Cities::permutation_t& order = chromo->get_ordering();
  auto N = order.size();
  int pos_2;
  (p == N-1) ? (pos_2 = 0) : (pos_2 = p+1);
  std::swap(order[p], order[pos_2]);
}
