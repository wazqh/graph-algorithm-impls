# K-ECC-Based Community Search

## SMCS(Steiner Maximum-Connected Subgraph)

​	Given an undirected map $G(V,E)$ , a subset vertices $S \sube V$ and a positive  integers $k$,  the SMCS problem seek to find a subgraph $H(V_H,E_H)$,such that:

1. $S \in V_H$
2. $H$ is k-edge-connected (or k-vertex-connected, depending on the variant), meaning there are at least $k$ disjoint paths between any pair of vertices in $V_H$
3. $H$ contains the **maximum number of vertices** among all such subgraphs satisfying (1) and (2)

In simpler terms, SMCS asks for the largest possible subgraph of $G$ that contains all the Steiner vertices(the subset vertices $S$) and is $k$-connected.



## Maximum SMCS

- *definition*: Given an undirected graph $G(V,E)$ , and a set of query $Q \sube V$ , return a subgraph $H(V_h,E_H)$ of $G$, such that:
	1. $V_H$ contains $Q$
	2. $\lambda(H)$ is maximized
	3. There exists no other subgraph $H^{'}$ satisfying the above properties, such that $H \sub H^{'}$
- *Implements*:





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





 



​	