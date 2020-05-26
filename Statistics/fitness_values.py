# -*- coding: utf-8 -*-

import sys
import os
import matplotlib.pyplot as plt
#from bokeh.plotting import figure, output_file, show

def parser(data):
    parsed_data = []
    gen = []
    value = ""
    for c in data:
        if ((c != " ") and (c != ";")):
            value += c
        if (c == " "):
            gen.append(int(value))
            value = ""
        if (c == ";"):
            parsed_data.append(gen)
            gen = []
            value = ""
    return parsed_data


def plot_all_bots(fitnessValues):
    bots = [i+1 for i in range(len(fitnessValues[0]))]
    for line in fitnessValues:
        plt.plot(bots, line, marker = '.',
                 label = str(fitnessValues.index(line) + 1))
    plt.xticks(bots)
    plt.xlabel("bot")
    plt.ylabel("fitness")
    plt.title("bot fitnesses for each generation")
    plt.legend(title = "generations", loc = 'lower right')
    #plt.savefig('all_bots.png', dpi = 200)
    plt.show()

def plot_best_bots(fitnessValues):
    generations = []
    best_bots_values = []
    for gen in fitnessValues:
        generations.append(fitnessValues.index(gen) + 1)
        best_bots_values.append(max(gen))
    plt.plot(generations, best_bots_values)
    plt.xticks(generations)
    plt.xlabel("generation")
    plt.ylabel("fitness")
    plt.title("best fitness for each generation")
    plt.show()

def plot_average_fitnesses(fitnessValues):
    generations = []
    average_fitnesses = []
    for gen in fitnessValues:
        generations.append(fitnessValues.index(gen) + 1)
        average_fitnesses.append(sum(gen)/len(gen))
    plt.plot(generations, average_fitnesses)
    plt.xticks(generations)
    plt.xlabel("generation")
    plt.ylabel("fitness")
    plt.title("average fitnesses for each generation")
    plt.show()


def main():
    fileDir = os.path.dirname(os.path.realpath('__file__'))
    print (fileDir + '\n')

    filename = os.path.join(fileDir, '../pns-innov/runs/fitness/' + sys.argv[1])

    f = open(filename, "r")
    stats = f.read()
    
    fitnessValues = parser(stats)
    print(fitnessValues)
    
    #plt.figure(dpi = 200)
    plot_all_bots(fitnessValues)
    plot_best_bots(fitnessValues)
    plot_average_fitnesses(fitnessValues)

if __name__ == "__main__":
    main()