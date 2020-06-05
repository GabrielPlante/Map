# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
#from bokeh.plotting import figure, output_file, show

def parser(data):
    parsed_data = []
    for bal in data.split("\n")[:-1]:
        balance = []
        for gen in bal.split(";")[:-1]:
            generation = []
            for value in gen.split(" ")[:-1]:
                generation.append(int(value))
            balance.append(generation)
        parsed_data.append(balance)
    return parsed_data    

def plot_all_fitnesses(balance):
    bots = [i+1 for i in range(len(balance[0]))]
    for line in balance:
        plt.plot(bots, line, marker = '.', label = str(balance.index(line) + 1))
    plt.xticks(bots)
    plt.xlabel("bot")
    plt.ylabel("fitness")
    plt.title("bot fitnesses for each generation")
    plt.legend(title = "generations", loc = 'lower right')
    #plt.savefig('all_bots.png', dpi = 200)
    plt.show()

def plot_best_fitnesses(balance):
    generations = []
    best_bots_values = []
    for gen in balance:
        generations.append(balance.index(gen) + 1)
        best_bots_values.append(max(gen))
    plt.plot(generations, best_bots_values)
    plt.xticks(generations)
    plt.xlabel("generation")
    plt.ylabel("fitness")
    plt.title("best fitness for each generation")
    #plt.savefig('best_fitnesses.png', dpi = 200)
    plt.show()

def plot_average_fitnesses(balance):
    generations = []
    average_fitnesses = []
    for gen in balance:
        generations.append(balance.index(gen) + 1)
        average_fitnesses.append(sum(gen)/len(gen))
    plt.plot(generations, average_fitnesses)
    plt.xticks(generations)
    plt.xlabel("generation")
    plt.ylabel("fitness")
    plt.title("average fitnesses for each generation")
    #plt.savefig('average_fitnesses.png', dpi = 200)
    plt.show()