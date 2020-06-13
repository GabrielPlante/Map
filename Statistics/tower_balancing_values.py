# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
#from bokeh.plotting import figure, output_file, show

def parser(data):
    parsed_data = []
    for b in data.split(";")[:-1]:
        bal = []
        for value in b.split(" ")[:-1]:
            bal.append(int(value))
        parsed_data.append(bal)
    return parsed_data    


def plot_all_tower_balancing(towerBalancingValues):
    towers = [[] for i in range(len(towerBalancingValues[0]))]
    nbrOfBalancing = [i+1 for i in range(len(towerBalancingValues))]
    for i in range(len(towerBalancingValues)):
        for j in range(len(towerBalancingValues[i])):
            towers[j].append(towerBalancingValues[i][j])
    for t in towers:
        plt.plot(nbrOfBalancing, t, label = str(towers.index(t)))
    plt.xticks(nbrOfBalancing)
    plt.xlabel("number of balancing")
    plt.ylabel("buffing or nerfing")
    plt.title("tower balancing")
    plt.legend(title = "tower", loc = 'lower right')
    plt.show()



