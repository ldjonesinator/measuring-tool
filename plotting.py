import numpy as np
import matplotlib.pyplot as plt


def get_data(filename):
    distances = []
    times = []
    i = 0
    with open(filename, 'r') as data_file:
        for line in data_file:
            if i > 0:  # skips the first line
                values = line.strip().split(',')
                distances.append(int(values[0]))
                times.append(int(values[1]))
            i += 1

    return distances, times

def plot_characterisic(distances, times):
    plt.figure(figsize=(10,6))
    axes = plt.axes()
    axes.plot(distances, times)

    axes.set_title("Change in beep period due to distance")
    axes.set_xlabel("Distance (cm)")
    axes.set_ylabel("Time (ms)")

    xticks = range(0, 140, 10)
    axes.set_xlim(left=0)
    axes.set_xticks(xticks)
    axes.set_xticklabels(xticks)

    yticks = range(0, 3000, 250)
    axes.set_yticks(yticks)
    axes.set_yticklabels(yticks)

    axes.grid(True)
    plt.show()

distances, times = get_data("measurements.txt")
plot_characterisic(distances, times)