import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# Leer CSV (lo lee de la carpeta principal donde lo creó tiempos_AR.cpp)
df = pd.read_csv('resultados_AR.csv')

# Calcular variables auxiliares
df['n'] = df['Longitud']

# ¡AQUÍ ESTÁ LA MAGIA! Tu complejidad es N^2 * log(N)
df['n2logn'] = (df['Longitud']**2) * np.log(df['Longitud'])

# --- primero generar las figuras sin la regresión ---
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso con escala logarítmica')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/puntos_peor_log_AR.pdf')

# idem pero sin log
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/puntos_peor_AR.pdf')


# --- REGRESIÓN PARA PEOR CASO: T(n) vs n^2 log n ---
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['n2logn'], df['PeorCaso'])

# Resultados por terminal
print(f"  Regresión lineal PeorCaso ~ n^2 log n")
print(f"  Pendiente: {slope_peor:.8f}")
print(f"  R²: {r_peor**2:.4f}")
print(f"  MSE: {np.mean((df['PeorCaso'] - (slope_peor * df['n2logn'] + intercept_peor))**2):.4f}")
print(f"  p-valor: {p_peor:.4e}")

# --- Ajuste peor caso ~ Θ(n^2 log n) con logaritmo ---
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n2logn'] + intercept_peor, label=r'Ajuste $\Theta(n^2 \log n)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso $\sim \Theta(n^2\log n)$')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/ajuste_peor_log_AR.pdf')

# idem pero sin log
plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['n2logn'] + intercept_peor, label=r'Ajuste $\Theta(n^2 \log n)$')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Peor caso $\sim \Theta(n^2\log n)$')
plt.legend()
plt.grid(True)
plt.savefig('figurasAR/ajuste_peor_AR.pdf')