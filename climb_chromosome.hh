
#pragma once

#include "chromosome.hh"
#include "cities.hh"
#include <algorithm>


class ClimbChromosome : public Chromosome
{
  public:
  ClimbChromosome(const Cities* cities_ptr);

  void mutate() override;

  ClimbChromosome* clone() const override
  {
    return new ClimbChromosome(*this);
  }

  std::pair<ClimbChromosome*, ClimbChromosome*> recombine(const ClimbChromosome* other);

  private:
  virtual ClimbChromosome*
  create_crossover_child(const ClimbChromosome* parent1,
                         const ClimbChromosome* parent2,
                         unsigned begin,
                         unsigned end) const;
  //helper functions to make mutate() less clunky
  void swap_up(int p);
  void swap_down(int p);

};
