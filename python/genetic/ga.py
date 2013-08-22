import random

target = 32
size = 20
rt = 10
mutations = 0
generations = 0


def createpop(popsize):
    population = []
    for i in range(popsize):
        p = []
        for j in range(size):
            p.append(random.randint(0,9))
        population.append(p)
    return population

def even(e):
    return (e % 2) == 0

def fit(p):
    fitness = 0
    prev = 0
    for e in p:
        if even(e):
            fitness += 1
            if e > prev:
                fitness += 1
        prev = e
    return fitness

def results(p):
    print("Reached fitness target!  "+ str(fit(p)))
    print(p)
    print("in "+ str(generations) + " generations")
    print(str(mutations) + " mutations")
    
def fitenough(pop):
    for p in pop:
        if fit(p) >= target:
            results(p)
            return True
    return False

def reproduce(x, y):
    c = random.randint(0,size - 1)
    left = x[0:c]
    right = y[c:size]
    return left + right

def mutate(x):
    global mutations
    mutations += 1
    c = random.randint(0,size-1)
    x[c] = random.randint(0,9)
    return x

def ga(pop):
    global generations
    while(not fitenough(pop)):
        generations += 1
        npop = []
        for i in range(len(pop)):
            x = random.choice(pop)
            y = random.choice(pop)
            child = reproduce(x,y)
            if (random.randint(0,rt) == 0):
                child = mutate(child)
            npop.append(child)
        pop = npop

ga(createpop(100))

        
