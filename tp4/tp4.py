from graph import Graph
import time

page_graph = Graph()

SOURCE_BIG = "web-Google.txt"
SOURCE_LITE = "web-Google-lite.txt"

with open(SOURCE_BIG, "r") as file:
    for l in file:
        if "# FromNodeId	ToNodeId" in l:
            break
    for l in file:
        if not l:
            break
        edge = tuple(int(v.replace("\n", "").replace("\t", "")) for v in l.split("\t"))
        for v in edge:
            if not page_graph.vertex_exists(v):
                page_graph.add_vertex(str(v))
        page_graph.add_edge(str(edge[0]), str(edge[1]))


# Punto 1
undirected_graph = page_graph.get_undirected_graph()

visited = set()
component_lengths = []

print("CANT VERTICES:", len(page_graph.get_vertices()))

for node in undirected_graph.get_vertices():
    if node in visited:
        continue
    component_lengths.append(undirected_graph.bfs(node, visited.add))

print(f"1. a. Cantidad de componentes conexas: {len(component_lengths)}")
print(f"1. b. Tamaño de la componente más grande: {max(component_lengths)}")


# Punto 2

# Obtener los primeros 5000 vértices del grafo
vertices = page_graph.get_vertices()[:1000]

# Crear un subgrafo con los primeros 5000 vértices
subgraph = Graph()
for vertex in vertices:
    subgraph.add_vertex(vertex, page_graph.get_vertex_data(vertex))

for vertex in vertices:
    for neighbor in page_graph.get_neighbors(vertex):
        if neighbor in vertices:
            subgraph.add_edge(
                vertex, neighbor, page_graph.get_edge_data(vertex, neighbor)
            )

# Medir el tiempo de ejecución de la función floyd_warshall
start_time = time.time()
result = subgraph.floyd_warshall()
end_time = time.time()

# Imprimir el resultado de floyd_warshall
print(result)

# Calcular e imprimir el tiempo de ejecución
execution_time = end_time - start_time
print(f"El tiempo de ejecución de floyd_warshall es: {execution_time} segundos")

# Imprimir el resultado de floyd_warshall
print(result)

# Calcular e imprimir el tiempo de ejecución
execution_time = end_time - start_time
print(f"El tiempo de ejecución de floyd_warshall es: {execution_time} segundos")


# Punto 3
triangles = set()
for i in page_graph.get_vertices():
    for j in page_graph.get_neighbors(i):
        for k in page_graph.get_neighbors(j):
            triangle = tuple(sorted((i, j, k)))
            if i in page_graph.get_neighbors(j) and triangle not in triangles:
                triangles.add(triangle)

print(f"3. Cantidad de triangulos: {len(triangles)}")
