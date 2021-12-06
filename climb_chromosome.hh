
#pragma once

#include "chromosome.hh"
#include "cities.hh"
#include <algorithm>


class ClimbChromosome : public Chromosome
{

  void mutate() override;

  ClimbChromosome* clone() const override
  {
    return new ClimbChromosome(*this);
  }

  //helper functions to make mutate() less clunky
  friend void swap_up(ClimbChromosome* chromo);
  friend void swap_down(ClimbChromosome* chromo);

};
