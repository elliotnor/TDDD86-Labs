/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    /*
     * Creates a Junk object given a point
     */
    Junk(const Point& p);

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;

     void moveTowards(const Unit&) override;

     /*
      * did not crash yet
      */
     virtual bool canMove() const override;

     /*
      * Crashes and remembers it
      */
     void doCrash() override;

     /*
      * Return whether the robot crashed
      */
     bool justCrashed() const override;

     //Clone the robot
     Robot* clone() override;
};

#endif // JUNK_H
