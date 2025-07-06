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
		1.  assumes that there is only one query vertex $q\space (i.e.,Q=\{q\})$.
		
		2.  firstly, expand the search space from q
		
		3.  selects the vertex that is local optimal and adds it into the candidate set $C$.
		
			> One typical criterion to choose a vertex is to selects the vertex that leads to the largest increment of goodness function, another one is select the vertex which has the largest number of connections to vertices of candidate set.
		
		4.  repeat step iii until the set $C$ theoretically guarantees that is containing a community satisfying the constraints of Problem 1. Actually, it generates a candidate vertex set $C$  in the search space.
		
		5.  eventually, find the community from $C$.
		
	- *index-based*
	
		1. it starts from the $l$-$\text{th}$ level where $l$ is the maximum core number of vertices in $Q$ and checks its upper levels based on $ShellStruct$ until there is a connected component containing all the query vertices 

	
## undirected graphs
### Problem 2: community search on directed graph(CSD)

- **Definition**: Given  a directed graph $G(V,E)$ ,two positive integers k and l, and a query vertex q, return a connected subgraph $G_q \subseteq G$,such that it contains q and $\forall\space v \in G_q\space,\delta_{in}(G_q) \geq k\space$,and $\delta_{out}(G_q) \geq l$.

	> Here, the core is defined as follow:
	>
	> ​	Given a directed graph $G(V,E)$ and two non-negative integers k and l, the ( k, l )-core is the maximum subgraph C of G such that $\delta_{in}(C) \geq k$ and $\delta_{out}(G_q) \geq l$.

- **Implements**:

	- *simple method*:  peel vertices iteratively until each remaining vertex satisfies all the demand.
	-  *second method* : we notice that for any *k, l* *≥* 0, we have both (*k*+1, *l*)-core $\subseteq$ ( *k*, *l*)-core and (*k*, *l*+1)-core $\subseteq$ (*k*, *l*)-core. After keeping (*k*,l*+1)-core and (*k+1, *l*)-core, for (*k*, *l*)-core, if$ |V_{k+1,l}| ≥|V_{k,l+1}|$, we only keep $V_{k,l} \setminus V_{k+1,l}$; otherwise, we keep $V_{k,l} \setminus V_{k,l+1}$.
