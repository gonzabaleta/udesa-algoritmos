from typing import Optional, Any, List
from collections import deque
import numpy as np
import math


class Graph:
    """
    Graph class
    """

    def __init__(self):
        self._graph = {}

    def add_vertex(self, vertex: str, data: Optional[Any] = None) -> None:
        """
        Adds a vertex to the graph
        :param vertex: the vertex name
        :param data: data associated with the vertex
        """
        if vertex not in self._graph:
            self._graph[vertex] = {"data": data, "neighbors": {}}

    def add_edge(self, vertex1: str, vertex2: str, data: Optional[Any] = None) -> None:
        """
        Adds an edge to the graph
        :param vertex1: vertex1 key
        :param vertex2: vertex2 key
        :param data: the data associated with the vertex
        """
        if not vertex1 in self._graph or not vertex2 in self._graph:
            raise ValueError("The vertexes do not exist")
        self._graph[vertex1]["neighbors"][vertex2] = data

    def get_neighbors(self, vertex) -> List[str]:
        """
        Get the list of vertex neighbors
        :param vertex: the vertex to query
        :return: the list of neighbor vertexes
        """
        if vertex in self._graph:
            return list(self._graph[vertex]["neighbors"].keys())
        else:
            return []

    def get_vertex_data(self, vertex: str) -> Optional[Any]:
        """
        Gets  vertex associated data
        :param vertex: the vertex name
        :return: the vertex data
        """
        if self.vertex_exists(vertex):
            return self._graph[vertex]["data"]
        else:
            return None

    def get_edge_data(self, vertex1: str, vertex2: str) -> Optional[Any]:
        """
        Gets the vertexes edge data
        :param vertex1: the vertex1 name
        :param vertex2: the vertex2 name
        :return: vertexes edge data
        """
        if self.edge_exists(vertex1, vertex2):
            return self._graph[vertex1]["neighbors"][vertex2]
        raise ValueError("The edge does not exist")

    def print_graph(self) -> None:
        """
        Prints the graph
        """
        for vertex, data in self._graph.items():
            print("Vertex:", vertex)
            print("Data:", data["data"])
            print("Neighbors:", data["neighbors"])
            print("")

    def vertex_exists(self, vertex: str) -> bool:
        """
        If contains a vertex
        :param vertex: the vertex name
        :return: boolean
        """
        return vertex in self._graph

    def edge_exists(self, vertex1: str, vertex2: str) -> bool:
        """
        If contains an edge
        :param vertex1: the vertex1 name
        :param vertex2: the vertex2 name
        :return: boolean
        """
        return vertex1 in self._graph and vertex2 in self._graph[vertex1]["neighbors"]

    def get_vertices(self):
        """
        Returns a list of all the vertices
        """
        return list(self._graph.keys())

    def get_undirected_graph(self) -> "Graph":
        """
        Returns an undirected version of the graph
        """
        undirected_graph = Graph()
        for vertex, data in self._graph.items():
            undirected_graph.add_vertex(vertex, data["data"])
            for neighbor, edge_data in data["neighbors"].items():
                undirected_graph.add_vertex(neighbor, self._graph[neighbor]["data"])
                undirected_graph.add_edge(vertex, neighbor, edge_data)
                undirected_graph.add_edge(neighbor, vertex, edge_data)

        return undirected_graph

    def bfs(self, vertex: str, func) -> int:
        """
        Performs a BFS on the graph starting from the desired vertex.
        Returns the number of nodes visited
        :param vertex: the name of the vertex from which to start the BFS
        :param func: the function to apply to each node
        :return: amount of nodes visited
        """
        queue = deque([vertex])
        visited = set()
        visited.add(vertex)

        while queue:
            v = queue.popleft()
            func(v)

            for u in self.get_neighbors(v):
                if u not in visited:
                    visited.add(u)
                    queue.append(u)
        return len(visited)

    def get_subgraph(self, n_vertices: int) -> "Graph":
        """
        Returns a subgraph with the first n vertices of the graph
        :param n_vertices: the number of vertices to include in the subgraph
        :return: a subgraph with the first n vertices of the graph
        """

        # Obtener los primeros n vértices del grafo
        vertices = self.get_vertices()[:n_vertices]

        # Crear un subgrafo con los primeros 5000 vértices
        subgraph = Graph()
        for vertex in vertices:
            subgraph.add_vertex(vertex, self.get_vertex_data(vertex))

        for vertex in vertices:
            for neighbor in self.get_neighbors(vertex):
                if neighbor in vertices:
                    subgraph.add_edge(
                        vertex, neighbor, self.get_edge_data(vertex, neighbor)
                    )
        return subgraph

    def get_all_shortest_paths_from(self, start_vertex: str) -> dict[str, int]:
        """
        Finds the shortest path from start_vertex to all other vertices
        :param start_vertex: the vertex from which to start the BFS
        :return: a dictionary with the shortest path to all other vertices
        """
        distances = {vertex: math.inf for vertex in self._graph}
        distances[start_vertex] = 0
        queue = deque([start_vertex])

        while queue:
            current_vertex = queue.popleft()

            for neighbor in self.get_neighbors(current_vertex):
                if distances[neighbor] == math.inf:
                    distances[neighbor] = distances[current_vertex] + 1
                    queue.append(neighbor)

        return distances

    def get_all_min_paths(self) -> dict[str, dict[str, int]]:
        """
        Computes the shortest path from every vertex to every other vertex
        :return: a dictionary with the lengths of all the shortest paths between any pair of nodes
        """
        all_paths = {}
        for vertex in self.get_vertices():
            all_paths[vertex] = self.get_all_shortest_paths_from(vertex)
        return all_paths

    def get_triangles_amount(self):
        """
        Calculates the number of triangles in the graph
        :return: the number of triangles in the graph
        """
        triangles = set()
        for i in self.get_vertices():
            for j in self.get_neighbors(i):
                for k in self.get_neighbors(j):
                    # Store the current potential triangle as a tuple with the vertices sorted
                    triangle = tuple(sorted((i, j, k)))
                    is_triangle = i in self.get_neighbors(k) and k != i

                    # If we haven't already counted this triangle, and it is a triangle indeed, add it to the set
                    if is_triangle and triangle not in triangles:
                        triangles.add(triangle)

        return len(triangles)

    def page_rank(self, n_walks: int, walk_length: int) -> dict:
        """
        Calculates the PageRank for all of the vertices in the graph
        :param num_walks: the number of walks to perform
        :param walk_length: the length of the walk
        :return: a dictionary with the first 10 vertices with the highest PageRank
        """
        num_visits = {}

        for _ in range(n_walks):
            current_vertex = np.random.choice(self.get_vertices())
            for _ in range(walk_length):
                if current_vertex not in num_visits:
                    num_visits[current_vertex] = 0
                num_visits[current_vertex] += 1
                neighbors = self.get_neighbors(current_vertex)
                if not neighbors:
                    break
                current_vertex = np.random.choice(neighbors)

        total_visits = sum(num_visits.values())
        ranks = {}
        if total_visits > 0:
            ranks = {
                vertex: visits / total_visits for vertex, visits in num_visits.items()
            }

        return sorted(ranks.items(), key=lambda x: x[1], reverse=True)[:10]

    def max_cycle_length_from(self, start_vertex: str) -> int:
        """
        Calculates the length of the longest cycle starting from a vertex by performing DFS
        :param start_vertex: the vertex from which to start the search
        :return: the length of the longest cycle starting from the vertex
        """

        # For each node, we store the current node, the parent node and the depth
        stack = [(start_vertex, None, 0)]
        visited = set()
        depth_dict = {}
        max_cycle_length = 0

        while stack:
            current, parent, depth = stack.pop()

            if current not in visited:
                visited.add(current)
                depth_dict[current] = depth

                for neighbor in self.get_neighbors(current):
                    if neighbor != parent:
                        if neighbor not in visited:
                            stack.append((neighbor, current, depth + 1))

                        # If we have already visited the neighbord, we found a cycle
                        else:
                            cycle_length = depth - depth_dict[neighbor] + 1
                            max_cycle_length = max(max_cycle_length, cycle_length)

        return max_cycle_length

    def find_longest_cycle(self, n_sample: int) -> int:
        """
        Finds the longest cycle in the graph
        :param n_sample: the number of vertices to sample
        :return: the length of the longest cycle in the graph
        """

        max_cycle_length = 0
        for vertex in self.get_subgraph(n_sample).get_vertices():
            max_cycle_length = max(max_cycle_length, self.max_cycle_length_from(vertex))

        return max_cycle_length

    def clustering_coefficient(self, vertex: str) -> float:
        """
        Calculates the clustering coefficient of a vertex using the formula 2E_i / k_i(k_i - 1) with:
        E_i = number of edges between the neighbors of the vertex
        k_i = number of neighbors of the vertex

        :param vertex: the vertex to calculate the clustering coefficient
        :return: the clustering coefficient of the vertex
        """
        neighbors = self.get_neighbors(vertex)
        k_i = len(neighbors)

        if k_i <= 1:
            return 0

        edge_count = 0
        for i in range(k_i):
            for j in range(i + 1, k_i):
                if self.edge_exists(neighbors[i], neighbors[j]):
                    edge_count += 1

        return (2 * edge_count) / (k_i * (k_i - 1))

    def average_clustering_coefficient(self) -> float:
        """
        Returns the average clustering coefficient of the graph
        """
        clustering_coefficients = []
        for vertex in self.get_vertices():
            clustering_coefficients.append(self.clustering_coefficient(vertex))

        return np.mean(clustering_coefficients)
