# -*- coding: utf-8 -*-

import os
import matplotlib.pyplot as plt

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
    bots = [i for i in range(len(fitnessValues[0]))]
    for line in fitnessValues:
        plt.plot(bots, line)
    plt.show()

def plot_best_bots(fitnessValues):
    generations = []
    best_bots_values = []
    for gen in fitnessValues:
        generations.append(fitnessValues.index(gen))
        best_bots_values.append(max(gen))
    plt.plot(generations, best_bots_values)
    plt.show()


def main():
    fileDir = os.path.dirname(os.path.realpath('__file__'))
    print (fileDir + '\n')

    filename = os.path.join(fileDir, '../Ianagd/fitnessValues.txt')

    f = open(filename, "r")
    stats = f.read()
    
    fitnessValues = parser(stats)
    print(fitnessValues)
    
    plot_all_bots(fitnessValues)
    plot_best_bots(fitnessValues)

if __name__ == "__main__":
    main()