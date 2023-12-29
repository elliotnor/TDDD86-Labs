//Contains 4 search-algorithms

#include "costs.h"
#include "trailblazer.h"
#include <set>
#include <queue>
#include <pqueue.h>
using namespace std;


vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    if(start != end){
        recursiveDFS(graph, start, end);
    }
    Vertex* temp = end;
    while(temp != start){
        path.insert(path.begin(), temp);
        temp = temp->previous;
    }
    path.insert(path.begin(), start);
    return path;
}


bool recursiveDFS(BasicGraph& graph, Vertex* start, Vertex* end){
    start->setColor(GREEN);
    start->visited = true;
    if(start == end){
        return true;
    }
    for(Vertex* next : graph.getNeighbors(start)){
            if(!next->visited){
                next->previous = start;
                next->setColor(YELLOW);
                if(recursiveDFS(graph, next, end)){
                    return true;
                }
            }
        }
    start->setColor(GRAY);
    return false;
    }

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    queue<Vertex*> queue;
    Vertex* current;

    queue.push(start);
    while(!queue.empty()){
        current = queue.front();
        queue.pop();
        current->setColor(GREEN);
        if(current == end){
            break;
        }
        else{
            for(Vertex* next : graph.getNeighbors(current)){
                if(!next->visited){
                    next->setColor(YELLOW);
                    next->visited = true;
                    next->previous = current;
                    queue.push(next);
                }
            }
        }
    }
    path.insert(path.begin(), current);
    while(start != current){
        current  = current->previous;
        path.insert(path.begin(), current);
    }
    return path;
}


vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end){
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> priorityQueue;
    double cost = 0.0;
    double oldCost = 0.0;
    start->cost = cost;
    priorityQueue.enqueue(start, cost);
    Vertex* current;
    Edge* currentEdge;

    while(priorityQueue.size() != 0){
        current = priorityQueue.dequeue();
        current->setColor(GREEN);

        if(current == end){
            break;
        }
        else{
            for(Vertex* next : graph.getNeighbors(current)){
                currentEdge = graph.getEdge(current, next);
                oldCost = next->cost;
                cost = current->cost + currentEdge->cost;
                if(!next->visited){
                    next->visited = true;

                    next->cost = cost;
                    next->previous = current;
                    priorityQueue.enqueue(next, next->cost);
                    next->setColor(YELLOW);
                }
                if(cost < oldCost){
                    next->cost = cost;
                    next->previous = current;
                    priorityQueue.changePriority(next, next->cost);
                }

            }
        }
    }
    path.insert(path.begin(), current);
    while(start != current){
        current  = current->previous;
        path.insert(path.begin(), current);
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> priorityQueue;
    double cost = 0.0;
    double oldCost = 0.0;
    double prio = start->heuristic(end);
    start->cost = cost;
    priorityQueue.enqueue(start, cost + prio);
    Vertex* current;
    Edge* currentEdge;

    while(priorityQueue.size() != 0){
        current = priorityQueue.dequeue();
        current->setColor(GREEN);

        if(current == end){
            break;
        }
        else{
            for(Vertex* next : graph.getNeighbors(current)){
                currentEdge = graph.getEdge(current, next);
                oldCost = next->cost;
                cost = current->cost + currentEdge->cost;

                if(!next->visited){
                    next->visited = true;

                    next->cost = current->cost + currentEdge->cost;
                    next->previous = current;
                    prio = next->cost + next->heuristic(end);

                    priorityQueue.enqueue(next, prio);
                    next->setColor(YELLOW);

                }
                else{
                    if(cost < oldCost){
                        next->previous = current;
                        next->cost = cost;
                        prio = next->cost + next->heuristic(end);
                        priorityQueue.changePriority(next, prio);
                    }
                }

            }
        }
    }
    path.insert(path.begin(), current);
    while(start != current){
        current  = current->previous;
        path.insert(path.begin(), current);
    }

    return path;
}
