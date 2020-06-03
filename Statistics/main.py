# -*- coding: utf-8 -*-
import fitness_values as fv
import wave_balancing_values as wbv

import sys
import os

def main():
    fileDir = os.path.dirname(os.path.realpath('__file__'))
    print (fileDir + '\n')

    filename = os.path.join(fileDir, '../pns-innov/runs/fitness/fitness_values_'
                            + sys.argv[1] + '.txt')

    f = open(filename, "r")
    data = f.read()
    #print(data)

    fitnessValues = fv.parser(data)
    
    for balance in fitnessValues:
        #fv.plot_all_fitnesses(balance)
        #fv.plot_best_fitnesses(balance)
        fv.plot_average_fitnesses(balance)
        
        
    fileDir = os.path.dirname(os.path.realpath('__file__'))
    print (fileDir + '\n')

    filename = os.path.join(fileDir, '../pns-innov/runs/wave_balancing/wave_balancing_values_'
                            + sys.argv[1] + '.txt')
    f = open(filename, "r")
    data = f.read()
    print(data)
    
    waveBalancingValues = wbv.parser(data)
    print(waveBalancingValues)
    
    wbv.plot_all_wave_balancing(waveBalancingValues)


if __name__ == "__main__":
    main()
