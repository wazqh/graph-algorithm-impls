# K-Truss-Based Community Search

> Here, we only care about problems of simple graph.

### Definition

1. **$k$-truss**:

	 A $k$-truss is the largest subgraph $H$ of $G$ such that every edge is contained in at least $k-2$ triangles in $H$.

2. **triangle connectivity**

	  Given two triangles $\triangle_{1}$ and $\triangle_{2}$ in $G$ , $\triangle_{1}$ and $\triangle_{2}$ are said to be adjacent if they share a common edge. Then, for two edges $e_{1},e_{2} \in E$, $e_1$ and $e_2$ are triangle connected if  $\exist \space \triangle_1 , \triangle_2$  such that $e_1 \in \triangle_1$, $e_2 \in \triangle_2$ and $\triangle_1 = \triangle_2$  or $\triangle_1$ is triangle connected with $\triangle_2$.

3. **$k$-truss equivalence**

	  Given two edges $e_1,e_2\in E$ , $e_1$ and $e_2$ are k-truss equivalence if and only if   $\tau(e_1)=\tau(e_2)=k$   and      $e_1$ and $e_2$ are triangle-connected via a series of triangles in a $k$-truss

	

### Problem : TTC

- definition: Given an undirected simple graph $G(V,E)$ , a query vertex $q \in V$, and an integers $k \geq 2$ , return all subgraphs $H \sube G$ satisfies the following three properties:

	1. *Structure Cohesiveness*. $H$ contains the query vertex $q$ such that $\forall\space e\in E(H)$, $sup(e,H) \ge (k-2) $.
	2. *Triangle Connectivity*.  $\forall \space e_1 ,e_2 \in E(H)$, $e_1$ and $e_2$ are triangle connected.
	3. *Maximal Subgraph*. $H$ is the maximal subgraph if $G$ satisfying Properties 1 and 2(or a and b).

- **implements**:

	- *Online Search*:

		1. perform truss decomposition on the entire graph to compute the $trussness \space \tau(e)$ of each edge $e \in E$.

			> The $trussness$ of an edge is the largest $k$ such that the edge belongs to a $k$-truss.

		2. starts from the query vertex $q$ and checks a incident edge of $(q,v) \in E$ with trussness $\tau((q,v)) \geq k$ to search triangle-connected truss communities.

		3. For each such edge,  explore other edges that are connected to it , have trussness $\geq k$ and are reachable in BFS via other triangle-connected edges.

		4. repeat until all qualifying incident edges of $q$ have been processed.

	- *TCP-index based search algorithm*:

	  1. construct a TCP-index for each vertex in the given graph G

	  	> 1. construct the induced subgraph $G_x$ of  G by every set of x's neighbors as N(x) 
	  	> 2.  for each edge $(y,z) \in E((G_x))$, a weigh $w(y,z) = min\{\tau((x,y)),\tau((x,z)),\tau((y,z))\}$ is assigned to it , which indicates that $\triangle_{xyz}$ can appear only in k-truss communities where $k\leq w(y,z)$ . 
	  	> 3. let $T_x$ be the maximum spanning forest of $G_x$ , 
	
	  2.  assume that we want to query $\alpha$-truss communities containing a query vertex $q$ in $G$. The steps are followed:
	
	  	> 1. find an incident edge on $q$ , say $(q, x_1)$ where $\tau((q,x_1))=\alpha$
	  	> 2. retrieve the vertex belong to the same $\alpha$-truss community into a set 
	  	> 3. perform the reverse operations(search) on TCP-index for each vertex in the set and gets the complete community
	
	- *EquiTruss-index based search algorithm*:
	
		1. construct the EquiTruss-index for the given graph G
		
			> 1. compute the **truss number** $\tau(e)$ for every edge $e \in E(G)$ using truss decomposition
			> 2. **partition** all edges into **equivalence classes**, where edges $e_1$ and $e_2$ are in the same class if and only if:
			> 	- $\tau(e_1) = \tau(e_2) = k$
			> 	- $e_1$ and $e_2$ are **triangle-connected** via a series of triangles in the $k$-truss
			> 3. each equivalence class becomes a **super-node** $E_i$ in the EquiTruss index graph $G'$
			> 4. create a **super-edge** between $E_i$ and $E_j$ if there exists an edge in $E_i$ and another in $E_j$ that are **triangle-adjacent** (i.e., share a triangle in $G$)
			> 5. for each vertex $v$ in the original graph, maintain a **mapping** to all super-nodes that contain edges incident to $v$
		
		2. Assume we want to query an $\alpha$-truss community containing a query vertex $q$ in $G$. The steps are followed:
		
			> 1. identify all **super-nodes** in the EquiTruss index that contain edges incident to $q$ with $\tau \geq \alpha$
			> 2. for each such super-node, **perform a BFS traversal** over the EquiTruss index graph, expanding to neighboring super-nodes with truss number $\geq \alpha$
			> 3. aggregate all edges from the visited super-nodes and return them as **disjoint $\alpha$-truss communities** containing $q$

 
