# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
#from bokeh.plotting import figure, output_file, show

def parser(data):
    parsed_data = []
    for b in data.split(";")[:-1]:
        bal = []
        total = 0
        for value in b.split(" ")[:-1]:
            bal.append(float(value))
            total += float(value)
        for i in range(len(bal)):
            bal[i] = (bal[i]/total)*100
        parsed_data.append(bal)
    return parsed_data    


def plot_all_tower_usage(towerUsageValues):
    towers = [[] for i in range(len(towerUsageValues[0]))]
    nbrOfBalancing = [i+1 for i in range(len(towerUsageValues))]
    print(nbrOfBalancing)
    for i in range(len(towerUsageValues)):
        for j in range(len(towerUsageValues[i])):
            towers[j].append(towerUsageValues[i][j])

    for t in towers:
        plt.plot(nbrOfBalancing, t, label = str(towers.index(t)))
    plt.xlabel("number of balancing")
    plt.ylabel("usage in percentage")
    plt.title("tower usage")
    plt.legend(title = "tower", loc = 'lower right')
    plt.show()



