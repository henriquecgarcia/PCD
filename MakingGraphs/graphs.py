import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

times_data = pd.read_csv('times.csv')
time_1_thread = times_data[times_data['Num. Threads'] == 1]['Tempo(s)'].values[0]
times_data['Speedup'] = time_1_thread / times_data['Tempo(s)']

times_data['Eficiência'] = times_data['Speedup'] / times_data['Num. Threads'] * 100

times_data['Speedup'] = times_data['Speedup'].round(2)
times_data['Eficiência'] = times_data['Eficiência'].round(2)

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

# Gerando uma tabela com os dados de Speedup e Eficiência e salvando como imagem .png
# times_data.to_csv('speedup_eficiencia.csv', index=False)
plt.figure(figsize=(10, 5))
plt.axis('off')
plt.table(cellText=times_data.values, colLabels=times_data.columns, loc='center')
plt.savefig('speedup_eficiencia.png')
plt.show()
