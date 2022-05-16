#!/usr/bin/python3
import sys
import grafo, grafolib
from heapq import nlargest
CANCIONES = "canciones"
USUARIOS = "usuarios"
NO_RECORRIDO = "No se encontro recorrido"
NO_CANCIONES = "Tanto el origen como el destino deben ser canciones"
SIN_CICLO = "No se encontro recorrido"

def procesar_entrada(grafo_canciones, grafo_bipartito, playlists, set_usuarios, directorio_playlists):
  linea = sys.stdin.readline()

  rankings = {}
  while linea:
    if len(linea.split()) != 1:
      comando, parametros = linea.rstrip('\n').split(" ", 1)
    else:
      comando = "clustering"
      parametros = ""

    if comando == "camino":
      origen, destino = parametros.split(" >>>> ")
      if not (grafo_canciones.pertenece(origen) and grafo_canciones.pertenece(destino)):
        print(NO_CANCIONES)
        linea = sys.stdin.readline()
        continue
      camino_mas_corto(origen, destino, grafo_bipartito, directorio_playlists, set_usuarios, grafo_canciones)
    
    if comando == "mas_importantes":
      if len(rankings) == 0:
        rankings = calcular_rankings(grafo_bipartito, set_usuarios)
      
      cantidad = int(parametros)
      canciones_mas_importantes(cantidad, rankings)

    if comando == "recomendacion":
      vertice, cantidad, canciones = parametros.split(" ", 2)
      recomendacion(grafo_bipartito, vertice, int(cantidad), canciones, set_usuarios, grafo_canciones)

    if comando == "ciclo":
      n, cancion = parametros.split(" ", 1)
      if not grafo_canciones.pertenece(cancion): 
        print(SIN_CICLO)
        linea = sys.stdin.readline()
        continue
      ciclo_n_canciones(grafo_canciones, cancion, int(n))  

    if comando == "rango":
      k, cancion = parametros.split(" ", 1)
      todas_en_rango(grafo_canciones, int(k), cancion)

    if comando == "clustering":
      clusterings_canciones(parametros, grafo_canciones)

    linea = sys.stdin.readline()
    

def canciones_mas_importantes(cantidad, rankings):
  resultado = nlargest(cantidad, rankings, rankings.get)
  print("; ".join(resultado))
  

def recomendacion(grafo_bipartito, vertice, cantidad, canciones, set_usuarios, grafo_canciones):
  canciones = canciones.split(" >>>> ")
  ranks = grafolib.pagerank_personalizado(grafo_bipartito, canciones)
  for cancion in canciones:
    ranks.pop(cancion)
  if vertice == USUARIOS:
    for x in ranks.copy():
      if grafo_canciones.pertenece(x):
        ranks.pop(x)
  if vertice == CANCIONES:
    for x in ranks.copy():
      if x in set_usuarios:
        ranks.pop(x)
  resultado = nlargest(cantidad, ranks, ranks.get)
  
  print("; ".join(resultado))

def calcular_rankings(grafo_bipartito, set_usuarios):
	rankings = grafolib.pagerank(grafo_bipartito)

	for usuario in set_usuarios:
		rankings.pop(usuario)

	return rankings

  

def camino_mas_corto(origen, destino, grafo_bipartito, directorio_playlists, set_usuarios, grafo_canciones):
  camino = grafolib.camino_mas_corto(grafo_bipartito, origen, destino)
  if not camino:
    print(NO_RECORRIDO)
    return 
  
  #Aca imprimo el camino
  resultado : str = ""
  for i in range(len(camino)): 
    if i < len(camino) - 1:
      if camino[i] in set_usuarios:
        resultado += f"{camino[i]} --> tiene una playlist --> {directorio_playlists[grafo_bipartito.obtener_peso(camino[i], camino[i+1])]} --> donde aparece --> "

      if grafo_canciones.pertenece(camino[i]):
        resultado += f"{camino[i]} --> aparece en playlist --> {directorio_playlists[grafo_bipartito.obtener_peso(camino[i], camino[i+1])]} --> de --> "

    #Ultimo elemento del camino
    else:
      resultado += camino[i]

  print(resultado)


def ciclo_n_canciones(grafo_canciones, cancion, n):
  ciclo = grafolib.ciclo_n(grafo_canciones, cancion, n)
  if not ciclo:
    print(SIN_CICLO)
    return
  print(" --> ".join(ciclo))
  

def todas_en_rango(grafo_canciones, k, cancion):
  cantidad = grafolib.rango_k(grafo_canciones, cancion, k)
  print(cantidad)
  

def clusterings_canciones(cancion, grafo_canciones):
  if cancion == "":
    cancion = None
  resultado = grafolib.clustering(grafo_canciones, cancion)

  print(f"{resultado:.3f}")


def crear_grafo_canciones(grafo_canciones, playlists):
  for p in playlists:
    visitados = set()
    for cancion1 in playlists[p]:
      visitados.add(cancion1)
      for cancion2 in playlists[p]:
        if cancion2 in visitados: continue
        grafo_canciones.agregar_arista(cancion1, cancion2)

  return


def crear_estructuras(ruta_archivo):
  playlists = {} # {playlists: set[canciones] }
  grafo_bipartito = grafo.Grafo()
  grafo_canciones = grafo.Grafo()
  set_usuarios = set()
  directorio_playlists = {}
  with open(ruta_archivo, "r") as archivo:
    #Salteo header
    linea = archivo.readline()
    linea = archivo.readline()
    
    while linea:
      #Debo splitear con tab para funcionamiento correcto
      linea = linea.rstrip('\n').split("	")
      if len(linea) != 7:
        linea = archivo.readline()
        continue
      id, user_id, track_name, artist, playlist_id, playlist_name, genres = linea

      if playlist_name not in playlists:
        playlists[playlist_name] = set()

      playlists[playlist_name].add(f"{track_name} - {artist}")

      #Grafo Bipartito
      grafo_bipartito.agregar_vertice(f"{track_name} - {artist}")
      grafo_bipartito.agregar_vertice(user_id)
      grafo_bipartito.agregar_arista(f"{track_name} - {artist}", user_id, playlist_id)

      #Grafo canciones
      grafo_canciones.agregar_vertice(f"{track_name} - {artist}")

      #Set usuarios
      set_usuarios.add(user_id)

      #Directorio playlists
      if playlist_id not in directorio_playlists:
        directorio_playlists[playlist_id] = playlist_name

      linea = archivo.readline()

  crear_grafo_canciones(grafo_canciones, playlists)

  return grafo_canciones, grafo_bipartito, playlists, set_usuarios, directorio_playlists

def main():
  grafo_canciones, grafo_bipartito, playlists, set_usuarios, directorio_playlists = crear_estructuras(sys.argv[1])
  
  procesar_entrada(grafo_canciones, grafo_bipartito, playlists, set_usuarios, directorio_playlists)
  

main()