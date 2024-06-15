from graph import Graph

page_graph = Graph()

with open("web-Google.txt", "r") as file:
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

undirected_graph = page_graph.get_undirected_graph()

visited = set()
component_lengths = []

for node in undirected_graph.get_vertices():
    if node in visited:
        continue
    component_lengths.append(undirected_graph.bfs(node, visited.add))

print(f"Cantidad de componentes conexas: {len(component_lengths)}")
print(f"Tamaño de la componente más grande: {max(component_lengths)}")

triangles = set()
for i in page_graph.get_vertices():
    for j in page_graph.get_neighbors(i):
        for k in page_graph.get_neighbors(j):
            triangle = tuple(sorted((i, j, k)))
            if i in page_graph.get_neighbors(j) and triangle not in triangles:
                triangles.add(triangle)

print(f"Cantidad de triangulos: {len(triangles)}")
