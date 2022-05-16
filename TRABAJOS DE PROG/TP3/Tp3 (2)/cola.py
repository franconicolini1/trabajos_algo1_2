class _Nodo:
	def __init__(self, dato,  prox = None):
		self.dato = dato
		self.prox = prox

class Cola:
	def __init__(self):
		self.prim = None
		self.ult = None
		self.cantidad = 0

	def encolar(self, dato):
		if self.cantidad == 0:
			self.prim = _Nodo(dato)
			self.ult = self.prim

		else:
			self.ult.prox = _Nodo(dato)
			self.ult = self.ult.prox

		self.cantidad += 1

	def desencolar(self):
		if self.cantidad == 0:
			return None

		nodo = self.prim
		self.prim = self.prim.prox
		self.cantidad -= 1

		return nodo.dato

	def esta_vacia(self):
		return self.cantidad == 0


		

