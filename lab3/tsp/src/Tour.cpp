/*This class uses two different heuristic approches to
 * solve the famous "Traveling Salesman Problem"*/

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

//Create an empty tour
Tour::Tour(){
    firstNode = nullptr;
}

Tour::Tour(Point p1, Point p2, Point p3, Point p4){
    firstNode = new Node(p1);
    firstNode->next = new Node(p2, new Node(p3, new Node(p4,firstNode)));
}

//Free all memory used by nodes
Tour::~Tour(){
    if(firstNode != nullptr){
        Node* current = firstNode->next;
        Node* next;
        while(current != firstNode){
            next = current->next;
            delete current;
            current = next;
        }
        delete firstNode;
    }
}

//Print the tour to the terminal
void Tour::show() const{
    if(firstNode != nullptr){
        cout << firstNode->point << endl;
        Node* current = firstNode->next;
        while(current != firstNode){
            cout << current->point << endl;
            current = current->next;
        }
    }
}

//This function draws the tour on the screen
void Tour::draw(QGraphicsScene *scene) const{
    if(firstNode != nullptr){
        Node* current = firstNode;
        Node* next = current->next;
        current->point.drawTo(next->point,scene);
        current = next;
        while(current != firstNode){
            next = current->next;
            current->point.drawTo(next->point, scene);
            current = next;
        }
    }
}

//Determines the amount of points on a tour
int Tour::size() const{
    int size = 0;
    if(firstNode != nullptr){
        size++;
        Node* current = firstNode->next;
        while(current != firstNode){
            current = current->next;
            size++;
        }
    }
    return size;
}

//This function returns the total distance of a tour
double Tour::distance() const{
    double distance = 0;
    if(firstNode != nullptr){
        Node* current = firstNode->next;
        Node* next;
        distance += firstNode->point.distanceTo(current->point);
        while(current != firstNode){
            next = current ->next;
            distance += current->point.distanceTo(next->point);
            current = next;
        }
    }
    return distance;
}

/*Heuristic approach no. 1
 * Inserts the point thats closest the current node*/
void Tour::insertNearest(Point p) {
    double distance = 0;
    if(firstNode != nullptr){
        Node* nearestNode = firstNode;
        double nearestDistance = nearestNode->point.distanceTo(p);
        Node* current = firstNode->next;
        while(current != firstNode){
            distance = current->point.distanceTo(p);
            if(distance < nearestDistance){
                nearestDistance = distance;
                nearestNode = current;
            }
            current = current->next;
        }
        Node* next = nearestNode->next;
        nearestNode->next = new Node(p, next);
    }
    else{
        firstNode = new Node(p);
        firstNode->next = firstNode;
    }

}

/*Heuristic approach no.2
 * Inserts the point that results in the smallest increment in total tour length*/
void Tour::insertSmallest(Point p){
    double change = 0;
    double smallestChange;

    if(firstNode != nullptr){
        Node* current = firstNode;
        Node* next = current->next;
        smallestChange = current->point.distanceTo(p) + p.distanceTo(next->point) - current->point.distanceTo(next->point);
        Node* nodes [2] = {current, next};
        current = next;
        while(current != firstNode){
            next = current->next;
            change = current->point.distanceTo(p) + p.distanceTo(next->point) - current->point.distanceTo(next->point);
            if(change < smallestChange){
                nodes[0] = current;
                nodes[1] = next;
                smallestChange = change;
            }
            current = next;
        }
        nodes[0]->next = new Node(p, nodes[1]);
    }
    else{
        firstNode = new Node(p);
        firstNode->next = firstNode;
    }
}
