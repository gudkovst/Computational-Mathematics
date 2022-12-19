N = 5 #размерность матрицы или число интервалов + 1
a = 2
y0 = 6
yN = 4
begin = 0
end = 10
h = (end - begin) / (N - 1)

#константы интегрирования для точного решения
C = (y0 - yN - a/2 * (begin*begin - end*end)) / (begin - end)
D = y0 - a/2 * begin*begin - C * begin


def fillSystem():
    f = [y0]
    f.extend([a * h * h for i in range(1, N - 1)])
    f.append(yN)

    A = [[0 for i in range(N)] for i in range(N)]
    A[0][0] = 1
    for i in range(1, N - 1):
        A[i][i - 1] = 1
        A[i][i] = -2
        A[i][i + 1] = 1
    A[-1][-1] = 1

    return A, f


def forward(A, f):
    alpha = [-A[0][1] / A[0][0]]
    beta = [f[0] / A[0][0]]
    for i in range(1, N - 1):
        alpha.append(-A[i][i + 1] / (A[i][i] + alpha[i - 1] * A[i][i - 1]))
        beta.append((f[i] - beta[i - 1] * A[i][i - 1]) / (A[i][i] + alpha[i - 1] * A[i][i - 1]))
    alpha.append(0)
    beta.append((f[-1] - beta[-1] * A[-1][-2]) / A[-1][-1] + alpha[-2] * A[-1][-2])
    return alpha, beta


def backward(alpha, beta):
    x = [0 for i in range(N - 1)]
    x.append(beta[-1])
    for i in range(N - 2, -1, -1):
        x[i] = alpha[i] * x[i + 1] + beta[i]
    return x


A, f = fillSystem()
alpha, beta = forward(A, f)
solve = backward(alpha, beta)

print(solve)
import matplotlib.pyplot as plt
xs = [begin + i * h for i in range(N)]
xe = [begin + i * (end - begin) / 1000 for i in range(1000)]
ys = [a/2 * x*x + C * x + D for x in xe]
ax = plt.axes()
ax.spines['left'].set_position('center')
ax.spines['bottom'].set_position('center')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
xlim = max(abs(begin), abs(end)) + 5
plt.xlim([-xlim, xlim])
ylim = max(abs(min(solve)), abs(max(solve)), abs(max(ys)), abs(min(ys))) + 5
plt.ylim([-ylim, ylim])
plt.plot(xe, ys, 'b', label='exact solution')
plt.plot(xs, solve, 'bo', label='numerical solution')
plt.legend()
plt.show()

