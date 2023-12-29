#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    Tour(); //Create an empty tour
    Tour(Point a, Point b, Point c, Point d);
    ~Tour(); //Free all memory used by nodes
    void show() const; //Show the nodes in the terminal
    void draw(QGraphicsScene* scene) const; //Draw the nodes
    int size() const; //Return the amount of nodes in a tour
    double distance() const; //Return the total distance between all of the nodes in a tour
    void insertNearest(Point p); //Heuristic No.1. Insert the node next node that's closest to the current node
    void insertSmallest(Point p); //Heuristic No.2. Insert the node that results in the smallest increase in total tour distance

private:
    Node* firstNode; //A pointer to the first node in a tour. If the tour is empty => firstNode = Nullptr.


};

#endif // TOUR_H
