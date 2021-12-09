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

Rebecca: Override mutation operator
===============================
Changed `clone()` to return a new `ClimbChromosome*`, and changed `mutate()` to behave as follows:
- Create two new clones, `option_2` and `option_3`.
- Generate a random point p between 0 and N-1, with N being the size of the ordering permutation.
- Pass `option_2` and `option_3` to two helper functions, `swap_down` and `swap_up` respectively, which check the various conditions necessary and perform the corresponding swap.
- Find the fittest `ClimbChromosome` using `std::max_element`
- Set the ordering of the current `ClimbChromosome` to match that of the best one, and delete `option_2` and `option_3`.

The difficulty with testing this was that we could not figure out how to modify `deme.cc` to use a `ClimbChromosome` instead of a regular one, without overriding almost every single method of Chromosome, which ultimately proved impossible since there were various functions that could not be modified (such as `create_crossover_child`, which needs to take a `Chromosome*` as its parameter and so could not be overwritten). Ultimately, by just rewriting the original chromosome.cc to use the `ClimbChromosome` implementation, I was able to get it to work once and generated local.tsv, but then it broke again. I then had to set chromosome.cc back to its original form to make tournament.tsv.
