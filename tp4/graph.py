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

    def bfs(self, vertex: str, func):
        """
        Performs a BFS on the graph starting from the desired vertex.
        Returns the number of nodes visited
        :param vertex: the name of the vertex from which to start the BFS
        :param func: the function to apply to each node
        :return: integer
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

    def get_subgraph(self, n_vertices):
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

    def bfs_shortest_path(self, start_vertex: str) -> dict[str, int]:
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
                if distances[neighbor] == math.inf:  # if not visited
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
            all_paths[vertex] = self.bfs_shortest_path(vertex)
        return all_paths

    def get_triangles_amount(self):
        triangles = set()
        for i in self.get_vertices():
            for j in self.get_neighbors(i):
                for k in self.get_neighbors(j):
                    triangle = tuple(sorted((i, j, k)))
                    if i in self.get_neighbors(j) and triangle not in triangles:
                        triangles.add(triangle)
        return len(triangles)

    def page_rank(self, num_walks: int, walk_length: int) -> dict:
        """
        Calculates the PageRank of the vertices of the graph
        :param num_walks: the number of walks to perform
        :param walk_length: the length of the walk
        :return: the PageRank of the vertices
        """
        vertices = list(self._graph.keys())
        rank = {vertex: 0 for vertex in vertices}

        for _ in range(num_walks):
            current_vertex = np.random.choice(vertices)
            for _ in range(walk_length):
                rank[current_vertex] += 1
                neighbors = self.get_neighbors(current_vertex)
                if not neighbors:
                    break
                current_vertex = np.random.choice(neighbors)

        total_visits = sum(rank.values())
        if total_visits > 0:
            rank = {vertex: visits / total_visits for vertex, visits in rank.items()}

        return sorted(rank.items(), key=lambda x: x[1], reverse=True)[:10]
