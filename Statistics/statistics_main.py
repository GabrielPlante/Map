# -*- coding: utf-8 -*-
import fitness_values as fv
import wave_balancing_values as wbv
import tower_balancing_values as tbv
import tower_usage_values as tuv

import sys
import os


def readfile(file):
    try:
        fileDir = os.path.dirname(os.path.realpath('__file__'))
        filename = os.path.join(fileDir, file)
        f = open(filename, "r")
    except:
        print("file not found: ")
        data = []
    else:
        data = f.read()
        f.close()
    return data

def process(arg):
    if arg == "af":
        data = readfile('../pns-innov/runs/fitness/fitness_values_'
                    + sys.argv[1] + '.txt')
        if not data:
            print("fitness values")
        else:
            fitnessValues = fv.parser(data)
            for balance in fitnessValues:
                fv.plot_average_fitnesses(balance)
    elif arg == "bf":
        data = readfile('../pns-innov/runs/fitness/fitness_values_'
                    + sys.argv[1] + '.txt')
        if not data:
            print("fitness values")
        else:
            fitnessValues = fv.parser(data)
            for balance in fitnessValues:
                fv.plot_best_fitnesses(balance)
    elif arg == "wb":
        data = readfile('../pns-innov/runs/wave_balancing/wave_balancing_values_'
                            + sys.argv[1] + '.txt')
        if not data:
            print("wave balancing values")
        else:
            waveBalancingValues = wbv.parser(data)
            wbv.plot_all_wave_balancing(waveBalancingValues)
    elif arg == "tb":
        data = readfile('../pns-innov/runs/tower_balancing/tower_balancing_values_'
                            + sys.argv[1] + '.txt')
        if not data:
            print("tower balancing values")
        else:
            towerBalancingValues = tbv.parser(data)
            tbv.plot_all_tower_balancing(towerBalancingValues)
    elif arg == "tu":
        data = readfile('../pns-innov/runs/tower_usage/tower_usage_values_'
                            + sys.argv[1] + '.txt')
        if not data:
            print("tower usage values")
        else:
            towerUsageValues = tuv.parser(data)
            tuv.plot_all_tower_usage(towerUsageValues)
    else:
        print("Error: " + arg + " is not a valid argument")
        
    
def main():
    print("""Pass a file id as first argument, then pass at least one of these arguments:\n
af: plot average fitness values for each generation of each balancing\n
bf: plot best fitness values for each generation of each balancing\n
wb: plot wave balancing values\n
tb: plot tower balancing values\n
tu: plot tower usage values\n""")
    if (len(sys.argv) == 1):
        print("Error: no argument was given")
        return 0
    elif (len(sys.argv) == 2):
        print("Error: must specify at least one optional argument after file id")
    else:
        for arg in sys.argv[2:]:
            process(arg)

if __name__ == "__main__":
    main()
