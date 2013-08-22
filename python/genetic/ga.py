### author: ccann
### Genetic Algorithm 

import random, sys

## parameters
target_fitness = int(sys.argv[3])
mut_theta = 10 ## higher => less likely to mutate

## counts
mutations = 0
generations = 0

## build the initial population of states: positive integer tuples of length state_size
def createpop(pop_size, state_size):
    population = []
    for i in range(pop_size):
        p = []
        for j in range(state_size):
            p.append(gen_state_elem())
        population.append(p)
    return population


def gen_state_elem():
    return random.randint(0,9)

## fittest states => even integers in increasing order
def fit(p):
    fitness = 0
    prev = 0
    for e in p:
        if (e%2) == 0: 
            fitness += 1
            if e > prev: 
                fitness += 1
        prev = e
    return fitness

## print the results
def results(p):
    print("Reached fitness target: "+ str(fit(p)) +
          "\ngenerations: "+ str(generations) + 
          "\nmutations: " + str(mutations) +
          "\nstate: " + str(p))
    
## returns true if fit enough to end GA search
def fitenough(pop):
    for p in pop:
        if fit(p) >= target_fitness:
            results(p)
            return True
    return False

## returns crossover of state x with state y
def reproduce(x, y):
    c = random.randint(0,len(x) - 1)
    left = x[0:c]
    right = y[c:len(y)]
    return left + right

## returns mutation of state x
def mutate(x):
    global mutations
    mutations += 1
    c = random.randint(0,len(x)-1)
    x[c] = gen_state_elem()
    return x

## runs until target_fitness is reached by 1 state in population
def ga(pop):
    global generations
    while(not fitenough(pop)):
        generations += 1
        npop = []
        for i in range(len(pop)):
            x = random.choice(pop)
            y = random.choice(pop)
            child = reproduce(x,y)
            if (random.randint(0,mut_theta) == 0):
                child = mutate(child)
            npop.append(child)
        pop = npop

ga(createpop(int(sys.argv[1]), int(sys.argv[2])))

#100, 20

        
