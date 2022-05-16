import grafo as g 

def pruebas_grafo_vacio():
	print("\nINICIO DE PRUEBAS GRAFO VACIO\n\n")
	grafo = g.Grafo()

	print(grafo.cantidad() == 0)
	print(grafo.esta_vacio())
	print(grafo.pertenece("vertice1") == False)


def pruebas_agregar_eliminar_vertices():
	print("\nINICIO DE PRUEBAS AGREGAR Y ELIMINAR VERTICES\n\n")
	grafo = g.Grafo()

	grafo.agregar_vertice( "vertice1")
	print(grafo.cantidad() == 1)
	print(grafo.esta_vacio() == False)
	print(grafo.pertenece( "vertice1"))

	grafo.agregar_vertice( "vertice2")
	print((grafo.cantidad() == 2))
	print(grafo.pertenece( "vertice2"))
	print(grafo.pertenece( "vertice3") == False)

	grafo.eliminar_vertice( "vertice1")
	print(grafo.cantidad() == 1)
	print(grafo.esta_vacio() == False)
	print(grafo.pertenece( "vertice1") == False)

	grafo.eliminar_vertice( "vertice2")
	print(grafo.cantidad() == 0)
	print(grafo.esta_vacio())
	print(grafo.pertenece( "vertice2") == False)

	grafo.eliminar_vertice( "vertice2")
	print(grafo.cantidad() == 0)


def pruebas_obtener_vertices():
	print("\nINICIO DE PRUEBAS OBTENER VERTICES\n\n")

	grafo = g.Grafo()

	vertices2 = grafo.obtener_vertices()
	print(len(vertices2) == 0)


	grafo2 = g.Grafo()
	lista_vertices = ["vertice1", "vertice2", "vertice3"]

	grafo.agregar_vertice( "vertice1")
	grafo.agregar_vertice( "vertice2")
	grafo.agregar_vertice("vertice3")

	vertices = grafo.obtener_vertices()
	print(len(vertices) == 3)
	flag = True

	for vertice in vertices:
		if vertice not in lista_vertices:
			print(False)
			flag = False
			break
	if flag:
		print(True)


def pruebas_aristas():
	print("\nINICIO DE PRUEBAS AGREGAR Y ELIMINAR ARISTAS\n\n")
	grafo = g.Grafo()

	grafo.agregar_vertice( "vertice1")
	grafo.agregar_vertice( "vertice2")
	grafo.agregar_vertice( "vertice3")
	grafo.agregar_arista( "vertice1", "vertice2")
	grafo.agregar_arista( "vertice2", "vertice3")

	print(grafo.son_adyacentes( "vertice1", "vertice2"))
	print(grafo.son_adyacentes( "vertice2", "vertice3"))
	print(grafo.son_adyacentes( "vertice1", "vertice3") == False)

	grafo.eliminar_arista("vertice1", "vertice2")
	print(grafo.son_adyacentes("vertice1", "vertice2") == False)
	grafo.eliminar_vertice("vertice2")
	print(grafo.son_adyacentes("vertice2", "vertice3") == False)
	
	

def pruebas_adyacentes():
	print("\nINICIO DE PRUEBAS ADYACENTES\n\n")
	grafo = g.Grafo()

	grafo.agregar_vertice("vertice1")
	grafo.agregar_vertice("vertice2")
	grafo.agregar_vertice("vertice3")
	grafo.agregar_vertice("vertice4")
	grafo.agregar_arista("vertice1", "vertice2")
	grafo.agregar_arista("vertice1", "vertice3")
	
	lista_adyacentes_1 = ["vertice2", "vertice3"]
	adyacentes_1 = grafo.adyacentes("vertice1")
	flag = True

	for adyacente in adyacentes_1:
		if adyacente not in lista_adyacentes_1:
			print(False)
			flag = False
			break

		if flag:
			print(True)
		
	adyacentes_2 = grafo.adyacentes("vertice2")
	if adyacentes_2[0] != "vertice1":
		print(False)
	else:
		print(True)

	adyacentes_4 = grafo.adyacentes("vertice4")
	print(len(adyacentes_4) == 0)
	

def pruebas_peso():
	print("\nINICIO DE PRUEBAS DE PESO\n\n")

	grafo = g.Grafo()

	grafo.agregar_vertice("a")
	grafo.agregar_vertice("b")
	grafo.agregar_vertice("c")
	grafo.agregar_vertice("d")
	grafo.agregar_vertice("e")

	grafo.agregar_arista("a", "b", 10)
	grafo.agregar_arista("b", "c", 20)
	grafo.agregar_arista("c", "d", 30)
	grafo.agregar_arista("d", "e", 40)
	grafo.agregar_arista("e", "a", 50)

	test = grafo.obtener_peso("a", "b") == 10 and grafo.obtener_peso("b", "c") == 20
	test = test and grafo.obtener_peso("c", "d") == 30 and grafo.obtener_peso("d", "e") == 40
	test = test and grafo.obtener_peso("e", "a") == 50

	print("Obtener peso funciona correctamente: ", test)

def pruebas_dirigido():
	print("\nINICIO PRUEBAS GRAFO DIRIGIDO\n\n")

	grafo = g.Grafo(True)

	grafo.agregar_vertice("vertice1")
	grafo.agregar_vertice("vertice2")
	grafo.agregar_vertice("vertice3")
	grafo.agregar_arista("vertice1", "vertice2")
	grafo.agregar_arista("vertice1", "vertice3")
	
	adyacentes = grafo.adyacentes("vertice1")
	adyacentes_1 = ["vertice2", "vertice3"]
	flag = True
	
	for adyacente in adyacentes:
		if adyacente not in adyacentes_1:
			flag = False
			print(False)
			break

	if flag:
		print(True)

	adyacentes_2 = grafo.adyacentes("vertice2")
	print(len(adyacentes_2) == 0)

	print(grafo.son_adyacentes("vertice1", "vertice2"))
	print(grafo.son_adyacentes("vertice2", "vertice3") == False)
	print(grafo.son_adyacentes("vertice2", "vertice1") == False)



def main():
	pruebas_grafo_vacio()
	pruebas_agregar_eliminar_vertices()
	pruebas_obtener_vertices()
	pruebas_aristas()
	pruebas_adyacentes()
	pruebas_peso()
	pruebas_dirigido()