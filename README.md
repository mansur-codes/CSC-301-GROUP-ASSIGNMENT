# CSC-301-GROUP-ASSIGNMENT

U22CS1090
MANSUR OHINE MUHAMMAD


SIMPLEX GROUP ASSIGNMENT
Overview
This program is designed to solve Linear Programming Problems (LPP) using the Simplex Method. It takes user input for constraints, variables, and an objective function, then applies an iterative approach to find the optimal solution.

Features
Solves maximization and minimization problems.
Uses the Simplex Algorithm to efficiently determine the best solution.
Identifies cases of unbounded solutions.
Provides a step-by-step solution approach.
How It Works
Input the Problem:

Define the number of constraints and variables.
Enter the constraint coefficients and right-hand side values.
Provide the objective function coefficients.
Processing:

The program sets up a Simplex Tableau.
It checks for optimality and iterates until an optimal solution is found.
If necessary, it identifies cases like unbounded solutions or no feasible solution.
Output:

Displays the values of the decision variables.
Prints the optimal value of the objective function.
Example
Problem Statement:
Maximize Z = 3x₁ + 5x₂
Subject to:

x₁ + x₂ ≤ 6
2x₁ + x₂ ≤ 8
x₁, x₂ ≥ 0
Expected Output:
Optimal values: x₁ = 2, x₂ = 4
Maximum Z value: 26
Notes
Works for standard form linear programming problems.
Assumes non-negative constraints on variables.
If multiple solutions exist, only one is returned.

Made By Group 9
