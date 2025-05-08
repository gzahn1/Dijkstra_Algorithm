# Odd-Degree Node SSSP Finder using Dijkstra's Algorithm

## Project Overview

This project computes **Single Source Shortest Paths (SSSPs)** from all nodes with **odd degree** in a graph using **Dijkstra's algorithm**. It is designed to analyze connectivity from specific nodes of interest (odd-degree nodes), which are commonly used in problems such as the **Chinese Postman Problem** and **graph traversal optimizations**.

## Features

- Reads a graph from an adjacency matrix .
- Identifies all nodes with an odd degree.
- Runs Dijkstra's algorithm from each odd-degree node to compute the shortest paths to all other nodes.
- Outputs shortest path distances for each source.
