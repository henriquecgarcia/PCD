import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

times_data = pd.read_csv('times.csv')

times_data['Eficiência'] = times_data['Speedup'] / times_data['Num. Threads'] * 100

plt.figure(figsize=(10, 5))
plt.plot(times_data['Num. Threads'], times_data['Speedup'], marker='o', label='Speedup')
plt.plot(times_data['Num. Threads'], times_data['Num. Threads'], linestyle='--', color='red', label='Linear')
plt.xlabel('Número de Threads')
plt.ylabel('Speedup')
plt.legend()
plt.grid()
plt.savefig('speedup.png')
plt.show()

plt.figure(figsize=(10, 5))
plt.plot(times_data['Num. Threads'], times_data['Eficiência'], marker='o', label='Eficiência')
plt.plot(times_data['Num. Threads'], np.ones(len(times_data['Num. Threads'])) * 100, linestyle='--', color='red', label='Ideal')
plt.xlabel('Número de Threads')
plt.ylabel('Eficiência (%)')
plt.legend()
plt.grid()
plt.savefig('eficiencia.png')
plt.show()


time_per_thread = 7.363605
time_overall = 7.861328
paralel_part = time_per_thread / time_overall

# Usando a fórmula de Amdahl
speedup = 1 / (1 - paralel_part + paralel_part / times_data['Num. Threads'])

print(speedup)
# Considerando a Lei de Amdhal, calcule e escreva abaixo qual o limite teórico de speedup para a sua implementação (para isso, medir a fração de tempo serial e depois usar a equação da lei de Amdhal para prever qual o speedup máximo).
print(f"Speedup máximo: {speedup.max()}")