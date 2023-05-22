# The source code for "Representing polynomial of ST-Connectivity"
This repository contains the source code accompanying the paper https://arxiv.org/abs/2106.15018.

ub.cpp contains the code constructing the matrices needed for the upper bound. Similarly, lb.cpp contains the code constructing the matrices needed for the lower bound. Both use the power iteration method defined in util.hpp to compute the maximum eigenvalue.

## The lower bound
We construct the matrix $S_i$ explicitly by first constructing all the possible strips (stored in valid_inputs). Then we compute the adjacency matrix and compute a vector close to its principal eigenvector. Then we lower bound the largest eigenvalue by the Collatz-Wielandt formula: $$\rho(A) = \min_{x:x_j\geq 0}{\max_{j:x_j\neq 0}{\frac{[Ax]_j}{x_j}}}.$$

## The upper bound
We will write matrix $S_i'$ as a sum of four matrices $A_{00}^{(i)}, A_{01}^{(i)}, A_{10}^{(i)}, A_{11}^{(i)}$ where $A_{xy}^{(i)}$ counts only the strips with bottom edges defined by $x$ and $y$. Then the following recursive expression relates $A_{xy}^{(i)}$:
If 
```math
A^{(i)}=\begin{pmatrix}A_{00}&A_{01}\\A_{10}&A_{11}\end{pmatrix}
```
then 
```math
A^{(i+1)} =\left(\begin{array}{cc|cc}A_{00}+A_{11}&A_{10}+A_{11}&0&A_{00}+A_{10}+2A_{11}\\A_{01}+A_{11}& A_{00}+A_{01}+A_{10}+A_{11}&0&A_{00}+2A_{01}+A_{10}+2A_{11}\\ \hline 0&0&0&0\\A_{00}+A_{01}+2A_{11}& A_{00}+A_{01}+2A_{10}+2A_{11}&0&2A_{00}+2A_{01}+2A_{10}+4A_{11}\end{array}\right).
```
Thus we construct the matrix $S_i'$ iteratively. Then we compute compute a vector close to $S_i'$ 's principal eigenvector. Then we upper bound the largest eigenvalue by the Collatz-Wielandt formula: $\rho(A) = \max_{x:x_j> 0}{\min_{j}{\frac{[Ax]_j}{x_j}}}$.

