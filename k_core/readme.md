# K-Core-Based Community Search


## undirected graphs

### Problem 1: size-unbounded community search

- **Definition**: Given an undirected simple graph $G(V,E)$, a set of query vertices $Q \in V$, and a goodness function f, return a subgraph $H(V_H,E_H)$ of G, such that

	1. $V_H$ contains Q

	2. $H$ is connected 

	3. $f(H)$ is maximized among all feasible choices for H.

		> Here, f is defined based on the minimum degree: $f(H)=min_{\forall v \in H}\space deg_H(v)$

- **Implements**:

	- *Global*:
		1.  let $G_0 = G$ and $G_t$ be the graphs in $t-th$ iterations($1\leq t \leq n$)
		2. remove the vertex which has the minimum degree in $G_{t-1}$ and obtain an updated graph $G_t$
		3. repeat step ii until at least one of the query vertices $Q$ has minimum in the graph $G_{T-1}$ or the query vertices $Q$ are no longer connected.
		4. let $G_{t}^{'}$ be the connected component containing $Q$ in $G_t$. Then the subgraph $G_{O}= arg\space max\{f(G^{'}_t)\}$
	- *local*:
		1. 1
		2. 1
		3. 1
		4. 1
		5. 1
		6. 11
	- *index-based*
	
	
	
	
	
	 
