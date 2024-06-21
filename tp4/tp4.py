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


# Punto 1: ¿Cuál es el tamaño de la componente conexa más grande? ¿Cuántas componentes conexas hay?
undirected_graph = page_graph.get_undirected_graph()

visited = set()
component_lengths = []

for node in undirected_graph.get_vertices():
    if node in visited:
        continue
    component_lengths.append(undirected_graph.bfs(node, visited.add))

print(f"1. a. Cantidad de componentes conexas: {len(component_lengths)}")
print(f"1. b. Tamaño de la componente más grande: {max(component_lengths)}")


# Punto 2: Calcular el camino mínimo de todos con todos. ¿En cuanto tiempo lo puede hacer? ¿Qué orden tiene el algoritmo? En caso de no alcanzarle el tiempo, estime cuanto tiempo le llevaría.
graph20000 = page_graph.get_subgraph(20000)
graph10000 = page_graph.get_subgraph(10000)
graph5000 = graph10000.get_subgraph(5000)
graph1000 = graph5000.get_subgraph(1000)
graph100 = graph1000.get_subgraph(100)


def calculate_execution_time(func):
    start_time = time.time()
    func()
    end_time = time.time()
    return end_time - start_time


# Medimos el tiempo de ejecucion para cada tamaño
print(
    f"Tiempo de ejecución con 100 vértices: {calculate_execution_time(graph100.get_all_min_paths)}"
)

print(
    f"Tiempo de ejecución con 1000 vértices: {calculate_execution_time(graph1000.get_all_min_paths)}"
)
print(
    f"Tiempo de ejecución con 5.000 vértices: {calculate_execution_time(graph5000.get_all_min_paths)}"
)
print(
    f"Tiempo de ejecución con 10.000 vértices: {calculate_execution_time(graph10000.get_all_min_paths)}"
)

# print(f"Tiempo de ejecución con 20.000 vértices: {calculate_execution_time(graph20000.get_all_min_paths)}")

# Tiempo de ejecución con 100 vértices: 0.0033490657806396484
# Tiempo de ejecución con 1000 vértices: 0.07987689971923828
# Tiempo de ejecución con 5.000 vértices: 1.3014400005340576
# Tiempo de ejecución con 10.000 vértices: 5.524548053741455
# Tiempo de ejecución con 20.000 vértices: 80.74490022659302

# Punto 3
# print(f"3. Cantidad de triangulos: {page_graph.get_triangles_amount()}")

# Punto 4
print(f"Diámetro del grafo: {max(graph5000.get_all_min_paths())}")

# Punto 5
print("PAGE RANK!")
print(page_graph.page_rank(1000, 100)[:20])
