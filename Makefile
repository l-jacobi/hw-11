CXX=g++
CXXFLAGS=-g -Wall -Wextra -pedantic -std=c++17 -O3
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  tsp

tsp: tsp.o chromosome.o deme.o cities.o tournament_deme.o climb_chromosome.o
	$(CXX) $(LDFLAGS) -o $@ $^

tsp_demetourney_test: tsp_demetourney_test.o chromosome.o deme.o tournament_deme.o cities.o chromosome.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o tsp tsp_demetourney_test
