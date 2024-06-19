from typing import Optional, Any, List
from collections import deque
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

    def floyd_warshall(self) -> dict[tuple[str, str], float]:
        """
        Implementation of the Floyd-Warshall algorithm
        :return: A dictionary with the shortest path distances between all pairs of vertices
        """
        vertices = self.get_vertices()
        dist = {(i, j): math.inf for i in vertices for j in vertices}

        for v in vertices:
            dist[(v, v)] = 0

        for v in vertices:
            for neighbor, weight in self._graph[v]["neighbors"].items():
                dist[(v, neighbor)] = (
                    weight if weight is not None else 1
                )  # assuming default weight of 1 if none

        for k in vertices:
            for i in vertices:
                for j in vertices:
                    if dist[(i, j)] > dist[(i, k)] + dist[(k, j)]:
                        dist[(i, j)] = dist[(i, k)] + dist[(k, j)]

        return dist
