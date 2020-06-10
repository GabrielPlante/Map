# -*- coding: utf-8 -*-

import fitness_values as fv
import wave_balancing_values as wbv
import tower_balancing_values as tbv
import tower_usage_values as tuv
import statistics_main as sm

import unittest
import sys

class FitnessImprovment(unittest.TestCase):
    """
    test genetic algorithm efficiency and improvment of the fitness
    between different generations of bots
    """
    file_id = ''
    
    def test_average_fitness(self):
        fitnessValues = fv.parser(sm.readfile(
        '../pns-innov/runs/fitness/fitness_values_' + self.file_id + '.txt'))
        for balance in fitnessValues[:-1]:
            average1 = sum(balance[0])/len(balance[0])
            average2 = sum(balance[1])/len(balance[1])
            self.assertGreater(average2, average1)
    
    def test_best_fitness(self):
        fitnessValues = fv.parser(sm.readfile(
        '../pns-innov/runs/fitness/fitness_values_' + self.file_id + '.txt'))
        for balance in fitnessValues[:1]:
            best1 = max(balance[0])
            best2 = max(balance[1])
            self.assertGreaterEqual(best2, best1)


if __name__ == "__main__":
    
    FitnessImprovment.file_id = sys.argv[1]
    unittest.main(argv=['first-arg-is-ignored'], exit=False)