#include "climb_chromosome.hh"
#include <random>
#include <algorithm>
#include <cassert>
#include <vector>
#include <utility>

ClimbChromosome::ClimbChromosome(const Cities* cities_ptr)
 : Chromosome(cities_ptr)
{}

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
  option_2->swap_down(p);
  option_3->swap_up(p);

  std::vector<ClimbChromosome*> options({this, option_2, option_3});

  ClimbChromosome* best = *std::max_element(options.begin(), options.end(), my_compare);

  //if the original is best, compiler will basically ignore this line
  //otherwise it should update our permutation to match the best one
  order_ = best->get_ordering();

  if(option_2){ delete option_2; }
  if(option_3){ delete option_3; }
}

void ClimbChromosome::swap_down(int p)
{
  //reference, to make sure the original Chromosome is modified
  //Cities::permutation_t& order = chromo->get_ordering();
  auto N = order_.size();
  int pos_2;
  (p == 0) ? (pos_2 = N-1) : (pos_2 = p-1);
  std::swap(order_[p], order_[pos_2]);
}

std::pair<ClimbChromosome*, ClimbChromosome*>
ClimbChromosome::recombine(const ClimbChromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  // need to include size() because create_crossover_child takes [b, e):
  std::uniform_int_distribution<int> dist(0, order_.size());

  // Pick two random indices such that b <= e:
  auto r1 = dist(generator_);
  auto r2 = dist(generator_);
  auto [b, e] = std::minmax(r1, r2);

  // Make children:
  auto child1 = create_crossover_child(this, other, b, e);
  auto child2 = create_crossover_child(other, this, b, e);

  return std::make_pair(child1, child2);
}

ClimbChromosome*
ClimbChromosome::create_crossover_child(const ClimbChromosome* p1, const ClimbChromosome* p2,
                                   unsigned b, unsigned e) const
{
  const unsigned len = p1->order_.size();
  assert(len == p2->order_.size());
  ClimbChromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < len && j < len; ++i) {
    if (i >= b && i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < len);
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

void ClimbChromosome::swap_up(int p)
{
  //Cities::permutation_t& order = chromo->get_ordering();
  auto N = order_.size();
  int pos_2;
  (p == N-1) ? (pos_2 = 0) : (pos_2 = p+1);
  std::swap(order_[p], order_[pos_2]);
}
