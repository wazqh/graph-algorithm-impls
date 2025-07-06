# K-Clique-Based Community Search

## K-Clique and Its Variants

1. **$\gamma$-quasi-$k$-clique**

	  A $\gamma$-quasi-$k$-clique is a graph with $k$ vertices at least $\lfloor \gamma\frac{k(k-1)}{2} \rfloor$ edges where $0 \leq \gamma\leq1$. Where $\gamma = 1$, the corresponding  $\gamma$-quasi-$k$-clique is a k-clique. We can tune desired cohesiveness of the k vertices by varying $\gamma$ value.

2. **k-plex**

	A graph $G(V,E)$ is a k-plex, if for each vertex $v \in V$,  $v$ has at least $\vert V \vert - k$ neighbors in $G$, where $1 \leq k \leq \vert V \vert$When $k=1$ , the k-plex is exactly a k-clique. Clearly, by setting a smaller value of k, we can obtain a more cohesive k-plex. The problem of finding a k-plex from a given graph for an integers $k$ is NP-hard. Another way to relax the constraint of k-clique is to consider the connection of two vertices.

3. **$kr$-clique**

	Given a graph $G$ and two integers k and r, a $kr$-clique $S$ is an induced subgraph of $G$ such that:

	(1) the number of vertices in $S$ is at least $k$

	(2) any two vertices in $S$ can reach each other within r hops.

4. **$k$-clique component**

	Let $C$ denote a connected component in the k-clique graph, then a k-clique component is the union of all k-cliques represented by vertices in $C$.

## K-Clique-Based Community Search

### Problem 1: (($\alpha, \gamma$)-OCS)

- **Definition**: 

	Given an undirected simple graph $G(V,E)$, a query vertex $q \in V$, and an integer k , an integer $\alpha \leq k - 1$, and a real value $\gamma$ with $0 \leq \gamma \leq 1$, find all [$\gamma$-quasi-$k$-clique](## K-Clique and Its Variants) components containing query vertex $q$.

- **Implements**:

	TBA

### Problem 2: Densest Clique Percolation Community Search

- **Definition**:

	Given an undirected simple graph $G(V,E)$ and a set of query vertex $Q \subseteq V$, the problem of the densest  Clique Percolation Community(DCPC) search is to find the k-clique component with the maximum $k$ value that contains all the vertices in $Q$.

- **Implements**:

	TBA













​	

​	 

​	

