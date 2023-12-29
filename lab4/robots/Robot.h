/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool crashed = false;

public:
    /*
     * Creates a new Robot object
     */
    Robot();
    /*
     * Creates a new Robot object given a point
     * Used by Junk
     */
    Robot(const Point& p);

    /*
     * did not crash yet
     */
    virtual bool canMove() const;

    /*
     * Crashes and remembers it
     */
    virtual void doCrash();

    /*
     * Return whether the robot crashed
     */
   virtual bool justCrashed() const;


    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const;

       //Generates a clone of the robot object
    virtual Robot* clone();
};

#endif // ROBOT_H
