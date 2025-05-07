# Mathematical Art (Level 4)

Line sweep and Fenwick Tree solution to Meta Careers Page Coding Puzzle (33/33 Cases).

## Problem Description

You are creating a special painting on a canvas represented as a 2D Cartesian plane. You start with your brush at the origin (0,0) and make $N$ axis-aligned strokes without lifting the brush. For the $i$th stroke, you move your brush $L_i$ units from its current position in direction $D_i$, where $D_i \in \{\text{U, D, L, R}\}$. Each stroke leaves a line segment of paint between the starting and ending point. A “plus sign” is considered present at a point $P$ if and only if there is a painted line extending from $P$ in **all four** cardinal directions (up, down, left, and right).

# Mathematical Art (Level 4)

Solution to count the number of “plus signs” formed by axis‑aligned brush strokes on a 2D Cartesian plane.

## Problem Description

You are creating a special painting on a canvas represented as a 2D Cartesian plane. You start with your brush at the origin $(0,0)$ and make $N$ axis‑aligned strokes without lifting the brush. For the $i$th stroke, you move your brush $L_i$ units from its current position in direction $D_i$, where $D_i\in\{\texttt{U},\texttt{D},\texttt{L},\texttt{R}\}$. Each stroke leaves a line segment of paint between the starting and ending point.

A “plus sign” is considered present at a point $P$ if and only if there is painted line extending from $P$ in **all four** cardinal directions (up, down, left, and right). Strokes from multiple moves may together form a single plus, but each position counts at most one plus sign.

Determine how many positions in the final painting contain a plus sign.

## Function Header

```cpp
long long getPlusSignCount(int N, vector<int> L, string D);
```

## Usage/Input

* The first line contains an integer **N**, the number of strokes.
* The second line contains **N** space‑separated integers $L_1, L_2, \dots, L_N$.
* The third line contains a string **D** of length $N$, where the $i$th character is one of `U`, `D`, `L`, or `R` indicating the direction of the $i$th stroke.
