import heapq
from cola import Cola
import grafo as g
AMORTIGUADOR = 0.85
MAX_ITERACIONES_PERSONALIZADO = 100
MAX_ITERACIONES = 13
LARGO_CAMINO = 100

def bfs(grafo, vertice):
	"""
	Algoritmo de recorrido de grafo que devuelve todas las distancias de los vertices sin considerar los pesos desde un vertice pasado por parametro junto con un diccionario que establece quien es el antecesor de cada vertice 
	en el camino minimo.
	"""
	q = Cola()

	distancia = {}
	padres = {}
	distancia[vertice] = 0
	padres[vertice] = None

	q.encolar(vertice)

	while not q.esta_vacia():
		v = q.desencolar()
		for w in grafo.adyacentes(v):
			if w not in distancia:
				distancia[w] = distancia[v] + 1
				padres[w] = v
				q.encolar(w)

	return distancia, padres
				

def camino_minimo_dijkstra(grafo, origen):
	distancia = {}
	padre = {}
	for v in grafo:
		distancia[v] = 1000000000000000000000
		
	distancia[origen] = 0
	padre[origen] = None
	heap = heapq()
	heap.heappush(origen, 0)

	while not heap.esta_vacio():
		v = heap.heappop()
		for w in grafo.adyacentes(v):
			if distancia[v] + grafo.obtener_peso(v, w) < distancia[w]:
				distancia[w] = distancia[v] + grafo.obtener_peso(v, w)
				padre[w] = v
				heap.heappush(w, distancia[w])

	return padre, distancia 



def orden_topologico(grafo):
	"""
	Realiza un orden topologico de el grafo pasado
	Unicamente funciona si el grafo es dirigido
	"""
	grent = {}

	for v in grafo:
		grent[v] = 0
	for v in grafo:
		for w in grafo.adyacentes(v):
			grent[w] += 1

	q = Cola()

	for v in grafo:
		if grent[v] == 0:
			q.encolar(v)

	salida = []

	while not q.esta_vacia():
		v = q.desencolar()

		salida.append(v)

		for w in grafo.adyacentes(v):
			grent[w] -= 1
			if grent[w] == 0:
				q.encolar(w)

	return salida

def pagerank(grafo, iteraciones = MAX_ITERACIONES):
	"""
	Algoritmo de pagerank, el cual le da un ranking a cada vertice del grafo.
	Este funciona de manera iterativa.
	Solo funciona en NO dirigidos. Devuelve un diccionario con:
	clave -> vertice
	valor -> rank
	Addicionalmente se puede indicar el numero de iteraciones que se desee
	"""
	ranks = {}
	cant_vertices = grafo.cantidad()
	for v in grafo:
		ranks[v] = 1 / cant_vertices

	for i in range(iteraciones):
		new_ranks = {}
		for v in grafo:
			sumatoria = 0
			for w in grafo.adyacentes(v):
				sumatoria += ranks[w] / grafo.cantidad_adyacentes(w)


			new_ranks[v] = (1 - AMORTIGUADOR) / cant_vertices + sumatoria  * AMORTIGUADOR

		ranks = new_ranks

	return ranks


def pagerank_personalizado(grafo , vertices_iniciales, iteraciones = MAX_ITERACIONES_PERSONALIZADO):
	"""
	Algortimo de pagerank personalizado que utiliza un random walk para encontrar los vertices mas similares a los pasados.
	Los vertices iniciales deben pasarse dentro de un iterable
	Se puede opcionalmente aclarar la cantidad de repeticiones deseadas o , en caso de no aclarar, se repetira tantas veces como establezca la variable global MAX_ITERACIONES
	Adicionalmente el largo de los caminos del random walk es determinado por la variable global LARGO_CAMINO
	"""

	ranks = {}
	for i in range(iteraciones):
		for vertice in vertices_iniciales:
			camino = grafo.random_walk(LARGO_CAMINO, vertice)

			valor_actual = 1
			for v in camino:
				valor_actual = valor_actual / len(grafo.adyacentes(v))
				ranks[v] = ranks.get(v, 0) + valor_actual

	return ranks


def camino_mas_corto(grafo, origen, destino):
	"""
	Devuelve None en el caso que no haya camino. En caso que funcione devuelve una lista ordenada.
	"""

	orden = {}
	padres = {}
	orden[origen] = 0
	padres[origen] = None
	q = Cola()
	q.encolar(origen)
	resultado = []
 
	while not q.esta_vacia():
		v = q.desencolar()
		for w in grafo.adyacentes(v):
			if w == destino:
				resultado.append(w)
				padres[w] = v
				while True:
					if not padres[resultado[-1]]:
						resultado.reverse()
						return resultado
					resultado.append(padres[resultado[-1]])


			if w not in padres:
				padres[w] = v
				orden[w] = orden[v] + 1
				q.encolar(w)

	return None


def _ciclo_n(grafo, v, origen, n, visitados, camino):
	visitados.add(v)
	if len(camino) == n:
		if grafo.son_adyacentes(v, origen): return camino
		return 

	for w in grafo.adyacentes(v):
		if w in visitados: continue
		resultado = _ciclo_n(grafo, w, origen, n, visitados, camino + [w])
		if resultado:
			return resultado
	visitados.remove(v)
	return 

def ciclo_n(grafo, vertice, n):
	resultado = _ciclo_n(grafo, vertice, vertice, n, set(), [vertice])
	if resultado: resultado += [vertice]
	return resultado
			

def clustering(grafo, vertice = None):
	"""
	Devuelve el indice de clustering para un vertice indicado o en caso de que no se pase ninguno devuelve el indice de clustering promedio del grafo
	Solo funciona en grafos no dirigidos
	"""

	if vertice:
		grado_salida = grafo.cantidad_adyacentes(vertice)
		k = 0
		
		if grado_salida < 2:
			return 0
		visitados1 = set()
		for v in grafo.adyacentes(vertice): #L veces
			visitados1.add(v)
			for w in grafo.adyacentes(v):   #L veces
				if w in visitados1: continue
				if grafo.son_adyacentes(vertice, w):
					k += 2

		return k / (grado_salida * (grado_salida - 1))
	
	#Caso que no se especifica vertice

	clusterings = {}
	visitados2 = set()
	for v in grafo:
		mini_visitados = set()
		if v in visitados2: continue
		for w in grafo.adyacentes(v):
			if w in visitados2: continue

			for x in grafo.adyacentes(w):
				if x in visitados2 or x in mini_visitados: continue
				if grafo.son_adyacentes(v, x):
					clusterings[v] = clusterings.get(v, 0) +2
					clusterings[w] = clusterings.get(w, 0) +2
					clusterings[x] = clusterings.get(x, 0) +2
			mini_visitados.add(w)
		visitados2.add(v)

	total = 0
	for vertice in grafo: #O(V)
		k = grafo.cantidad_adyacentes(vertice)
		if k > 1:
			clusterings[vertice] = clusterings.get(vertice, 0) / (k*k - k)
			total += clusterings[vertice]
		else:
			clusterings[vertice] = 0

	return total / grafo.cantidad()

			
def rango_k(grafo, origen,  k):
	"""
	Permite obtener la cantidad de vertices que se encuenten a exactamente n saltos desde el vertice pasado por parámetro.
	"""
	visitados = set()
	orden = {}
	contador = 0
	orden[origen] = 0
	visitados.add(origen)
	q = Cola()
	q.encolar(origen)
 
	while not q.esta_vacia():
		v = q.desencolar()
		for w in grafo.adyacentes(v):
			if w not in visitados and orden[v] < k:
				orden[w] = orden[v] + 1
				visitados.add(w)
				q.encolar(w)

				if orden[w] == k:
					contador += 1

	return contador
