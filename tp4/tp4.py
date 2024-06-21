from graph import Graph
from time import time
import numpy as np

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

VERTICES_AMOUNT = len(page_graph.get_vertices())


def calculate_execution_time(func):
    """
    Calculates the execution time of a function
    :func: function to calculate the execution time
    :return: tuple with the execution time and the result of the function
    """
    start_time = time()
    result = func()
    return (result, time() - start_time)


def print_punto_title(n):
    """
    Prints the title of a section
    """
    print(f"\n----- PUNTO {n} -----")


def punto1():
    """
    ¿Cuál es el tamaño de la componente conexa más grande? ¿Cuántas componentes conexas hay?
    """
    print_punto_title(1)
    undirected_graph = page_graph.get_undirected_graph()

    visited = set()
    component_lengths = []

    for node in undirected_graph.get_vertices():
        if node in visited:
            continue
        component_lengths.append(undirected_graph.bfs(node, visited.add))

    print(f"Cantidad de componentes conexas: {len(component_lengths)}")
    print(f"Tamaño de la componente más grande: {max(component_lengths)}")


def punto2():
    """
    Calcular el camino mínimo de todos con todos. ¿En cuanto tiempo lo puede hacer? ¿Qué orden tiene
    el algoritmo? En caso de no alcanzarle el tiempo, estime cuanto tiempo le llevaría.
    """
    print_punto_title(2)

    # Since the running time is cubic, we calculate the paths for the first 10000 vertices
    min_paths, time_min_paths = calculate_execution_time(
        page_graph.get_subgraph(10000).get_all_min_paths
    )

    print(
        f"Tiempo de ejecución de los caminos mínimos para 10000 vértices: {time_min_paths} segundos"
    )

    # For estimating the time for all vertices, we calculate the time it takes for N single vertices, take the average, and then multiply by the total amount of vertices
    times = []
    samples = 100
    for _ in range(samples):
        vertex = np.random.choice(page_graph.get_vertices())
        _, time_min_paths = calculate_execution_time(
            lambda: page_graph.get_all_shortest_paths_from(vertex)
        )
        times.append(time_min_paths)

    estimated_time = np.mean(times) * VERTICES_AMOUNT

    print(
        f"Tiempo estimado para {VERTICES_AMOUNT} vértices: {estimated_time / 60 / 60} horas"
    )

    return min_paths


def punto3():
    """
    ¿Cuántos triángulos tiene el grafo?
    """
    print(f"Cantidad de triangulos: {page_graph.get_triangles_amount()}")


def punto4(all_paths):
    """
    Utilice el punto 2 para calcular el diámetro del grafo.
    """
    print_punto_title(4)
    print(f"Diámetro del grafo: {max(all_paths)}")


def punto5():
    """
    Calcule el PageRank de los vértices del grafo.
    """
    print_punto_title(5)
    page_rank, time_page_rank = calculate_execution_time(
        lambda: page_graph.page_rank(1000, 100)
    )
    print(f"Tiempo de ejecución de PageRank: {time_page_rank} segundos")
    print("PageRank de los 10 vértices más altos: ", page_rank)


def punto6():
    """
    La circunferencia del grafo es el largo del ciclo más largo.
    ¿Cuál es la circunferencia del grafo?
    """
    print_punto_title(6)
    circunference, time_circunference = calculate_execution_time(
        lambda: page_graph.find_longest_cycle(50)
    )
    print("Circunferencia del grafo: ", circunference)
    print("Tiempo de ejecución de la circunferencia: ", time_circunference)


def punto_extra2():
    """
    Calcule el coeficiente de clustering del grafo
    """
    print_punto_title("EXTRA 2")
    print(f"Coeficiente de clustering: {page_graph.average_clustering_coefficient()}")


# punto1()
paths = punto2()
# punto3()
# punto4(paths)
# punto5()
# punto6()
# punto_extra2()
