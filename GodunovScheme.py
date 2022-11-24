# Графики выводятся для при каждом N для всех r сразу, чтобы посмотреть для следующего N, нужно закрыть предыдущие
# Для изменения количества одновременно выводимых графиков можно переносить табуляциями последнюю строку *plt.show()*

import matplotlib.pyplot as plt
from matplotlib.animation import ArtistAnimation

counts = [10, 100]
courants = [0.25, 0.5, 1, 1.25]
T = 1
a = 5
begin, end = -10, 10


def v(x):
    if x <= 0:
        return 3
    else:
        return 1


def GodunovScheme(r, uj, ujprev):
    return uj * (1 - r) + r * ujprev


for N in counts:
    animations = []
    for r in courants:
        grafics = []
        shelfs = []
        fig = plt.figure()
        ax = plt.axes()
        plt.xlim([begin, end])
        plt.ylim([-5, 5])
        ax.spines['left'].set_position('center')
        ax.spines['bottom'].set_position('center')
        ax.spines['top'].set_visible(False)
        ax.spines['right'].set_visible(False)

        h = (end - begin) / N
        xs = [begin + i * h for i in range(N)]
        layers = [[v(x) for x in xs]]
        line, = ax.plot(xs, layers[0])
        grafics.append([line])
        shelfs.append([line])
        tay = r * h / a
        time = tay
        while time <= T:
            layer = [v(begin)]
            layer.extend([GodunovScheme(r, layers[-1][i], layers[-1][i - 1])
                          for i in range(1, N)])
            layers.append(layer)
            line, = ax.plot(xs, layer)
            grafics.append([line])
            line, = ax.plot(xs, [v(x - a * time) for x in xs])
            shelfs.append([line])
            time += tay
        if time < T + tay:
            rfin = a * (T + tay - time) / h
            layer = [v(begin)]
            layer.extend([GodunovScheme(rfin, layers[-1][i], layers[-1][i - 1])
                          for i in range(1, N)])
            line, = ax.plot(xs, layer)
            grafics.append([line])
            line, = ax.plot(xs, [v(x - a * T) for x in xs])
            shelfs.append([line])

        plt.title(f"N = {N}, r = {r}")
        animations.append(ArtistAnimation(fig, grafics, interval=1000, repeat=False))
        animations.append(ArtistAnimation(fig, shelfs, interval=1000, repeat=False))
    plt.show()