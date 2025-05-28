import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results.csv", names=["size", "threads", "time"])

for thread in sorted(data["threads"].unique()):
    subset = data[data["threads"] == thread]
    plt.plot(subset["size"], subset["time"], label=f"{thread} потоков")

plt.xlabel("Размер матрицы (N)")
plt.ylabel("Время выполнения (мс)")
plt.title("Зависимость времени выполнения от размера матрицы и количества потоков")
plt.legend()
plt.grid(True)
plt.savefig("result_plot.png")
plt.show()