
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

  private:
  //helper functions to make mutate() less clunky
  void swap_up(int p);
  void swap_down(int p);

};
