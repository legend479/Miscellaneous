#!/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import math as mth

#Exact Time Plot
for i in range(0,7):
    # Read data from .dat file
    data = np.loadtxt("time_complexity_"+str(i)+".dat")
    # pow = 1
    # Extract x and y values from the data
    x = data[:, 0]#N
    y = data[:, 1]#time
    # z = [n for n in x]
    # Plot the data as a line graph
    plt.plot(x, y, linewidth=0.5)
    # plt.plot(x, z)

    

# Display the graphs
# Set the title and axis labels
plt.title("Time Curve for various sorting technique")
plt.xlabel("N")
plt.ylabel("Time Taken for Program to run")
plt.legend(["QuickSort", "BubbleSort", "InsertionSort", "MergeSort", "ShellSort", "SelectionSort", "SystemSort"])
plt.savefig("Time_Curve_for_various_sorting_technique.png",dpi=1000)
plt.show()

#Logarithmic Time Plot
for i in range(0,7):
    # Read data from .dat file
    data = np.loadtxt("time_complexity_"+str(i)+".dat")
    # pow = 1
    # Extract x and y values from the data
    x = data[:, 0]#N
    y = data[:, 1]#time
    y = [mth.log(time) for time in y]
    # z = [n for n in x]
    # Plot the data as a line graph
    plt.plot(x, y, linewidth=0.5)
    # plt.plot(x, z)

    

# Display the graphs
# Set the title and axis labels
plt.title("Logarithm Time Curve for various sorting technique")
plt.xlabel("N")
plt.ylabel("Log(Time Taken)")
plt.legend(["QuickSort", "BubbleSort", "InsertionSort", "MergeSort", "ShellSort", "SelectionSort", "SystemSort"])
plt.savefig("Logarithmic_Time_Curve_for_various_sorting_technique.png",dpi=1000)
plt.show()

