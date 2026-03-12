import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# Leer CSV
df = pd.read_csv('resultados.csv')

# Calcular variables auxiliares según nuestro análisis teórico
df['n'] = df['Longitud']
df['logn'] = np.log2(df['Longitud']) # Usamos logaritmo en base 2 por las divisiones por la mitad

# --- REGRESIÓN PARA MEJOR CASO: T(n) vs log n ---
slope_mejor, intercept_mejor, r_mejor, p_mejor, _ = stats.linregress(df['logn'], df['MejorCaso'])

# --- REGRESIÓN PARA PEOR CASO: T(n) vs n ---
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['n'], df['PeorCaso'])

# Resultados por consola
print("--- Regresión lineal MejorCaso ~ log n ---")
print(f"  Pendiente: {slope_mejor:.6f}")
print(f"  R²: {r_mejor**2:.4f}")
print(f"  MSE: {np.mean((df['MejorCaso'] - (slope_mejor * df['logn'] + intercept_mejor))**2):.4f}")
print(f"  p-valor: {p_mejor:.4e}\n")

print("--- Regresión lineal PeorCaso ~ n ---")
print(f"  Pendiente: {slope_peor:.6f}")
print(f"  R²: {r_peor**2:.4f}")
print(f"  MSE: {np.mean((df['PeorCaso'] - (slope_peor * df['n'] + intercept_peor))**2):.4f}")
print(f"  p-valor: {p_peor:.4e}\n")

# Gráficos

# 1. Gráfico de dispersión sin ajuste
plt.figure()
plt.scatter(df['Longitud'], df['MejorCaso'], label='MejorCaso', marker='o')
plt.scatter(df['Longitud'], df['PeorCaso'], label='PeorCaso', marker='x')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot_log.pdf')

# 2. Ajuste mejor caso ~ Θ(log n)
plt.figure()
plt.plot(df['Longitud'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['Longitud'], slope_mejor * df['logn'] + intercept_mejor, label=r'Ajuste $\Theta(\log n)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Mejor caso $\sim \Theta(\log n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_mejor_log.pdf')

# 3. Ajuste peor caso ~ Θ(n)
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n'] + intercept_peor, label=r'Ajuste $\Theta(n)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_peor_log.pdf')

# 4. Gráfico de dispersión sin escala logarítmica

# 1. Gráfico de dispersión sin ajuste
plt.figure()
plt.scatter(df['Longitud'], df['MejorCaso'], label='MejorCaso', marker='o')
plt.scatter(df['Longitud'], df['PeorCaso'], label='PeorCaso', marker='x')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot.pdf')

# 2. Ajuste mejor caso ~ Θ(log n)
plt.figure()
plt.plot(df['Longitud'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['Longitud'], slope_mejor * df['logn'] + intercept_mejor, label=r'Ajuste $\Theta(\log n)$')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Mejor caso $\sim \Theta(\log n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_mejor.pdf')

# 3. Ajuste peor caso ~ Θ(n)
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n'] + intercept_peor, label=r'Ajuste $\Theta(n)$')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuster_peor.pdf')