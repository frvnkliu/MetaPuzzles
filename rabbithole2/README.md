# Rabbit Hole (Chapter 2)

Modified Tarjan's Algorithm solution to Meta Careers Page Coding Puzzle (22/22 Cases).

## Problem Description

You're having a grand old time clicking through the rabbit hole that is your favorite online encyclopedia.

The encyclopedia consists of **N** different web pages, numbered from **1** to **N**. There are **M** links present across the pages, the *i*-th of which is present on page **Aᵢ** and links to a different page **Bᵢ**. A page may include multiple links, including multiple leading to the same other page.

A session spent on this website involves beginning on one of the **N** pages, and then navigating around using the links until you decide to stop. That is, while on page *i*, you may either move to any of the pages linked to from it, or stop your browsing session.

Assuming you can choose which page you begin the session on, what’s the maximum number of different pages you can visit in a single session? Note that a page only counts once even if visited multiple times during the session.

## Function Header
```cpp
int getMaxVisitableWebpages(int N, int M, vector<int> A, vector<int> B);
```

## Usage/Input
The first line contains an integer **N**

The second line contains an integer **M**

The third and fourth line contain **M** integers each; corresponding to **Aᵢ** and **Bᵢ** 