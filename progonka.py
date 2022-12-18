N = 101 #размерность матрицы или число интервалов + 1
y0 = 6
yN = 4
begin = 0
end = 10
h = (end - begin) / (N - 1)


def fillSystem():
    f = [y0]
    f.extend([2 * h * h for i in range(1, N - 1)])
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
x = [begin + i * h for i in range(N)]
ax = plt.axes()
ax.spines['left'].set_position('center')
ax.spines['bottom'].set_position('center')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
xlim = max(abs(begin), abs(end))
plt.xlim([-xlim, xlim])
ylim = max(abs(min(solve)), abs(max(solve))) + 5
plt.ylim([-ylim, ylim])
plt.plot(x, solve)
plt.show()

