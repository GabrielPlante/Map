# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
#from bokeh.plotting import figure, output_file, show

def parser(data):
    parsed_data = []
    for w in data.split(";")[:-1]:
        wave = []
        for value in w.split(" ")[:-1]:
            wave.append(int(value))
        parsed_data.append(wave)
    return parsed_data    


def plot_all_wave_balancing(waveBalancingValues):
    waveCounter = 1
    for wave in waveBalancingValues:
        balancing = [i+1 for i in range(len(wave))]
        plt.plot(balancing, wave, linestyle='dashed',
                 label = str(waveCounter))
        waveCounter += 1
    plt.xlabel("number of balancing")
    plt.ylabel("buffing or nerfing")
    plt.title("balancing for each wave")
    plt.legend(title = "waves", loc = 'lower right')
    plt.show()

