# -*- coding: utf-8 -*-
import fitness_values as fv
import wave_balancing_values as wbv
import tower_balancing_values as tbv
import tower_usage_values as tuv

import sys
import os


def readfile(file):
    fileDir = os.path.dirname(os.path.realpath('__file__'))
    print (fileDir + '\n')
    filename = os.path.join(fileDir, file)
    f = open(filename, "r")
    data = f.read()
    return data
    
def main():

    data = readfile('../pns-innov/runs/fitness/fitness_values_'
                    + sys.argv[1] + '.txt')
    #print(data)
    fitnessValues = fv.parser(data)
    for balance in fitnessValues:
        #fv.plot_all_fitnesses(balance)
        #fv.plot_best_fitnesses(balance)
        fv.plot_average_fitnesses(balance)
    
    
    data = readfile('../pns-innov/runs/wave_balancing/wave_balancing_values_'
                            + sys.argv[1] + '.txt')
    #print(data)
    waveBalancingValues = wbv.parser(data)
    wbv.plot_all_wave_balancing(waveBalancingValues)


    data = readfile('../pns-innov/runs/tower_balancing/tower_balancing_values_'
                            + sys.argv[1] + '.txt')
    #print(data) 
    towerBalancingValues = tbv.parser(data)
    tbv.plot_all_tower_balancing(towerBalancingValues)

    
    data = readfile('../pns-innov/runs/tower_usage/tower_usage_values_'
                            + sys.argv[1] + '.txt')
    #print(data)
    towerUsageValues = tuv.parser(data)
    tuv.plot_all_tower_usage(towerUsageValues)

if __name__ == "__main__":
    main()
