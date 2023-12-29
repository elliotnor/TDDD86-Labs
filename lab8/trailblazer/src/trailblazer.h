/*
 * TDDD86 Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Slight modifications by Tommy Farnqvist
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include <vector>
#include "BasicGraph.h"

//Search algorithm based on the DFS method
vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);

//Search algorithm based on the BFS method
vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);

//Search algorithm based on Dijikstras algorithm
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);

//Search algorithm based on the A* method
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);

//Recursive step of the DFS algorithm
bool recursiveDFS(BasicGraph& graph, Node* start, Node* end);

#endif
