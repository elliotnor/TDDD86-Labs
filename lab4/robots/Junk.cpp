/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Junk.h"
#include "constants.h"


Junk::Junk(const Point& p) : Robot(p){}


void Junk::draw(QGraphicsScene *scene) const{
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

void Junk::moveTowards(const Unit& u) {
}

/*
 * did not crash yet
 */
bool Junk::canMove() const{
    return false;
}

/*
 * Crashes and remembers it
 */
void Junk::doCrash(){

}

/*
 * Return whether the robot crashed
 */
bool Junk::justCrashed() const{
    return false;
}

Robot* Junk::clone(){
    return new Junk(*this);
}
