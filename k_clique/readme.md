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

5. **k-clique percolation community** (KCPC)

	  A set of k-cliques such that each pair is connected via a chain of k-cliques where each consecutive pair shares $k-1$ nodes.

## K-Clique-Based Community Search

### Problem 1: (($\alpha, \gamma$)-OCS)

- **Definition**: 

	Given an undirected simple graph $G(V,E)$, a query vertex $q \in V$, and an integer k , an integer $\alpha \leq k - 1$, and a real value $\gamma$ with $0 \leq \gamma \leq 1$, find all [$\gamma$-quasi-$k$-clique](## K-Clique and Its Variants) components containing query vertex $q$.

- **Implements**:

	- **exact**:
	
		1. enumerate all the [$\gamma$-quasi-$k$-clique](## K-Clique and Its Variants)  containing the query vertex $q$
		2. compute the [$\gamma$-quasi-$k$-clique](## K-Clique and Its Variants) components based on the $\alpha$-adjacency.
		3. let $G^{'}$ be the connected component containing in step ii which containing $q$, then  $G^{'}$ is what we want.
	
	- **approximate**:
	
		1. only enumerates an unvisited clique which contains at least one new vertex not contained by any existing community
	
		2. Besides, a heuristic is proposed to choose a vertex sequence such that the resulting clique sequence is short,leading to a good approximation solution.
	
			```plaintext
			Input: Graph G, query vertex q, parameters α, γ, k
			
			1. Initialize community set S ← ∅, visited ← ∅
			2. While there are unvisited vertices:
			    a. Choose a vertex v not in any existing community.
			    b. Enumerate γ-quasi-k-cliques containing v.
			    c. Add clique C if valid, merge with α-adjacent cliques in S.
			    d. Mark vertices in C as visited.
			3. Return component containing q.
			```
	
			

### Problem 2: Densest Clique Percolation Community Search

- **Definition**:

	Given an undirected simple graph $G(V,E)$ and a set of query vertex $Q \subseteq V$, the problem of the densest  Clique Percolation Community(DCPC) search is to find the k-clique component with the maximum $k$ value that contains all the vertices in $Q$.

- **Implements**:

	- **baseline**:
	
		1. Start with a maximum possible k value (e.g., based on the graph’s maximal clique size), let's denote it as $k_{max}$
		2. Then, do iterative search from high to low. For $k=k_{max},k_{max}-1,\dots,2$, repeat step iii to step v until a valid value $q$ is found.
		3.  generate all k-clique in the graph
		4. construct the k-clique percolation graph whose nodes are k-clique and edges exist between k-cliques that share $k-1$ vertices.
		5. Find connected components in this clique graph and Check if any connected component contains a k-clique that includes the query vertex $q$. If yes, return this component as the DCPC.
		
  - **DCPC-Index**:
  
  	Particularly, based on the observation that a *k*-clique component can be treated as a union of *maximal* cliques, they take maximal cliques as building blocks of *k*-clique components and propose a tree-structure named *clique adjacency tree* which can efficiently identify the *k*-clique components for a given *k* value. The authors further developed a new tree structure named *ordered adjacency tree* such that only the subtrees related to the query vertices will be explored. Together with maximal cliques and their in verted indexes, a compact index structure named DCPC. Index is proposed to support efficient DCPC queries.
  
  













​	

​	 

​	

