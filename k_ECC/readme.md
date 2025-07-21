# K-ECC-Based Community Search

## Definition

1. **SMCS(Steiner Maximum-Connected Subgraph)**

	Given an undirected map $G(V,E)$ , a subset vertices $S \sube V$ and a positive  integers $k$,  the SMCS problem seek to find a subgraph $H(V_H,E_H)$,such that:

	1. $S \in V_H$
	2. $H$ is k-edge-connected (or k-vertex-connected, depending on the variant), meaning there are at least $k$ disjoint paths between any pair of vertices in $V_H$
	3. $H$ contains the maximum number of vertices among all such subgraphs satisfying (1) and (2)

	In simpler terms, SMCS asks for the largest possible subgraph of $G$ that contains all the Steiner vertices(the subset vertices $S$) and is $k$-connected.

2. **connectivity graph**

	A connectivity graph $G_c$ for a graph $G$ , is a graph which has the same sets of vertices and edges with $G$ , and for each edge $(u,v)\in G_c$, it is associated with a connectivity value denoting the edge-connectivity between vertices $u$ and $v$ in $G$.

 	



## Maximum SMCS

- *definition*: Given an undirected graph $G(V,E)$ , and a set of query $Q \sube V$ , return a subgraph $H(V_h,E_H)$ of $G$, such that:
	1. $V_H$ contains $Q$
	2. $\lambda(H)$ is maximized
	3. There exists no other subgraph $H^{'}$ satisfying the above properties, such that $H \sub H^{'}$
	
- *Implements*:

	- ***basic***: sequentially enumerate all the maximal $k$-ECCs by varying $k$ from $\vert V \vert$ to 1, and stops when the first $k$-ECC which contains $Q$ is found. And there are two efficient enumeration algorithms.

		1.  graph decomposition:

		2.  random contraction:

			> Not given either of the algorithms in the paper.

	- ***efficient***:

		1. computes $\lambda(H)$ by using the MST(the maximum spanning tree of $G_c$)
		2. find the maximum SMCS by collecting the subtree of MST, whose edges have connectivity values being at least $\lambda(H)$

## Minimum and Minimal SMCS

1. **Minimum SMCS**

  Given an undirected simple graph $G(V,E)$ , and a set of query vertices $Q \sube V$, return a subgraph $H(V_H,E_H)$ of  $G$, such that

  1.  $V_H$ contains $Q$
  2. $\lambda(H)$ is maximized
  3. $\vert H_V\vert$ is minimized

2. **Minimal SMCS**

  Given an undirected simple graph $G(V,E)$ , and a set of query $Q \sube V$, return a subgraph $H(V_H,E_H)$ of $G$, such that

  1. $V_H$ contains $Q$
  2. $\lambda(H)$ is maximized
  3. There exists no other subgraph $H^{'} \sub H$ satisfying the above properties

  > Obviously, a minimum SMCS is also a minimal SMCS,and both of them are much smaller than the maximum SMCS.

3. **Implements**

	- naive solution: adopt the solution in a specific paper to compute the maximum SMCS $G^{'}$ to ensure its minimality.

	- ***Expand-Refine***:

		1. compute the Steiner-connectivity of the query vertex set $Q$ (i.e.., the maximum $\lambda(H)$)
		2. obtain a subgraph $H^{'}$ of  $G$ with connectivity being $\lambda(H)$ through local expansion of vertices starting from vertices in $Q$
		3.  in this step, an algorithm is proposed to remove vertices based on the dependence of vertices on their minimal SMCS's.

		> Not given either of the algorithms in the paper.

		





 



​	