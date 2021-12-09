# hw-11


El: Override selection operator
===============================

## TournamenteDeme

### Constructor

The constructor just calls `Deme`'s constructor and seeds the random number generator.

### Destructor

This is basically the same as `Deme`; it goes through the population and frees up all of the memory used in it.

### select_parent()

This uses a logarithm to determine the maximum possible power of two that the method can run the tournament on. It then creates a vector and populates it with that many chromosomes (or climbchomosomes). Then, until there is only one chromosome left, it goes through the vector and compares each chromosome with the one after it and erases the one with the worse fitness from the vector. Once there's only one chromosome pointer left in the vector, it returns it as the selected chromosome.

## Other

Lots of bug fixes in the ClimbChromosome and Makefile, as well as the test_demetournament_test.cc file which I really wish I gave a shorter name.