import threading
import time

# Função que processa uma parte do array
def elevar_a_potencia(arr, inicio, fim, potencia):
	for i in range(inicio, fim):
		arr[i] = arr[i] ** potencia
	print(f"Thread processou de {inicio} a {fim}.")

start = time.time()

# Criação do array com 100 milhões de itens
array = [i for i in range(100_000_000)]

# Número de threads e cálculo do tamanho do "chunk" para cada thread
num_threads = 4
tamanho_chunk = len(array) // num_threads
threads = []

# Inicia as threads para processar o array em pedaços
for i in range(num_threads):
	inicio = i * tamanho_chunk
	fim = (i + 1) * tamanho_chunk if i < num_threads - 1 else len(array)
	thread = threading.Thread(target=elevar_a_potencia, args=(array, inicio, fim, 5))
	threads.append(thread)
	thread.start()

# Espera que todas as threads terminem
for thread in threads:
	thread.join()

end = time.time()
print(f"Tempo total: {end - start} segundos.")

print("Processamento completo.")
