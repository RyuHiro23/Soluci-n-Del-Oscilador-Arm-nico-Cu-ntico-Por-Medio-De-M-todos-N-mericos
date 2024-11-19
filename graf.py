import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

if matplotlib.get_backend() == "agg":
    print("Advertencia: El backend actual es no interactivo ('Agg'). Guardando la gráfica en un archivo.")
    interactive = False
else:
    interactive = True


data = pd.read_csv("results.csv")

plt.plot(data["x"], data["psi"], label="ψ(x)" if "ψ" in data.columns else "ψ²(x)")
plt.title("Oscilador Armónico Cuántico")
plt.xlabel("x")
plt.ylabel("ψ(x) / ψ²(x)")
plt.grid()
plt.legend()

if interactive:
    plt.show()
else:
    output_file = "grafica.png"
    plt.savefig(output_file)
    print(f"Gráfica guardada como '{output_file}'.")
