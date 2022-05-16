import random

class GrafoIterador:
	
	def __init__(self, grafo):
		self._vertices = grafo.obtener_vertices()
		self._indice = 0
		self._max_len = len(self._vertices)

	def __next__(self):
		if self._indice < self._max_len:
			_valor = self._vertices[self._indice]
			self._indice += 1
			return _valor
		else:
			raise StopIteration

class Grafo:
	
	def __init__(self, es_dirigido = False):
		self.vertices = {}
		self.es_dirigido = es_dirigido
		self.vertice_cantidad = 0


	def agregar_arista(self, vertice1, vertice2, peso = 1):
		"""
		Agrega una arista al grafo, si esta ya pertenece no hace nada
		Establece el pso de esta como 1 si no se indica
		"""
	
		if self.son_adyacentes(vertice1, vertice2):
				return
				
		self.vertices[vertice1][vertice2] = peso
		if not self.es_dirigido:
			self.vertices[vertice2][vertice1] = peso
		
		

	def eliminar_arista(self, vertice1, vertice2):
		""" 
		Elimina una arista si esta pertenece al grafo.
		"""
		if not self.son_adyacentes(vertice1, vertice2):
			return
		self.vertices[vertice1].pop(vertice2)
		if not self.es_dirigido:
			self.vertices[vertice2].pop(vertice1)  
		

	def agregar_vertice(self, vertice):
		"""
		Agrega un nuevo vertice al grafo
		Si ya pertenece, este no hace nada
		"""
		if self.pertenece(vertice):
			return
		self.vertices[vertice] = {}
		self.vertice_cantidad += 1

	def eliminar_vertice(self, vertice1):
		"""
		Elimina el vertice si este pertenece al grafo
		"""
		if not self.pertenece(vertice1):
			return
		if self.es_dirigido:
			for vertice2 in self.obtener_vertices():
				if self.son_adyacentes(vertice2, vertice1):
					self.eliminar_arista(vertice2, vertice1)
	 

		else:
			for vertice2 in self.adyacentes(vertice1):
				self.eliminar_arista(vertice1, vertice2)
		
		self.vertices.pop(vertice1)
		self.vertice_cantidad -= 1
		
	def obtener_vertices(self):
		"""
		Devuelve una lista con todos los vertices
		"""
		return list(self.vertices.keys())

	def obtener_aristas(self):
		"""
		Devuelve una lista con todas las aristas pertenecientes al grafo
		En caso de que el grafo no sea dirigido, este solo devuelve una vez cada arista
		"""
		aristas = []
		if self.es_dirigido:
			for v in self:
				for w in self.adyacentes(v):
					aristas.append((v, w))

		else:
			visitados = set()
			for v in self:
				for w in self.adyacentes(v):
					if (v, w) not in visitados:
						aristas.append((v, w))
						visitados.add((w, v))
						
		return aristas


	def esta_vacio(self):
		"""
		Devuelve true en caso de que no haya vertices y false en caso contrario
		"""
		return self.vertice_cantidad == 0

	def cantidad(self):
		"""
		Devuelve la cantidad de vertices del grafo
		"""
		return self.vertice_cantidad

	def adyacentes(self, vertice):
		"""
		Devuelve una lista con los adyacentes a ese vertice
		"""
		return self.vertices[vertice].keys()
		
	def pertenece(self, vertice):
		"""
		Devuelve true si el vertice pertenece al grafo y false en caso contrario
		"""
		return vertice in self.vertices
	
	def son_adyacentes(self, vertice1, vertice2):
		"""
		Devuelve true si el vertice1 esta conectado al vertice2, false en caso contrario. En caso de ser
		dirigido solo devolvera true en el caso en que el vertice1 este apuntando al vertice2
		"""
		if self.pertenece(vertice1):
			return vertice2 in self.vertices[vertice1]
		return False

	def obtener_peso(self, vertice1, vertice2):
		"""
		Devuelve el peso de una arista
		"""
		return self.vertices[vertice1][vertice2]

	def random_walk(self, tamanio, vertice_inicio = None):
		"""
		Devuelve una lista con un camino aleatorio
		Debe indicarse un tamanio del camino mayor a 0
		Opcionalmente puede incluirse un vertice de inicio donde comenzara el camino o 
		,en caso contrario, se eligira uno aleatoriamente
		"""
		if not vertice_inicio:
			indice = random.randrange(0,self.cantidad() - 1)
			vertice_inicio = self.obtener_vertices()[indice]

		camino = [vertice_inicio]
		actual = vertice_inicio
		for i in range(tamanio  - 1):
			adya = list(self.adyacentes(actual))
			if len(adya) == 0:
				continue
			elif len(adya) == 1:
				indice = 0
			else:
				indice = random.randrange(0,len(adya) - 1)
			actual = adya[indice]
			camino.append(actual)

		return camino

	def cantidad_adyacentes(self, vertice):
		return len(self.vertices[vertice])
	
	def __iter__(self):
		return GrafoIterador(self)
		
	