import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results.csv")

plt.plot(data["x"], data["psi"], label="ψ(x)" if "ψ" in data.columns else "ψ²(x)")
plt.title("Oscilador Armónico Cuántico")
plt.xlabel("x")
plt.ylabel("ψ(x) / ψ²(x)")
plt.grid()
plt.legend()
plt.show()
