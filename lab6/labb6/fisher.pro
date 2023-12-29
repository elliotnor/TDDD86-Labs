TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES = Event.cpp Fish.cpp Simulation.cpp main.cpp

HEADERS = $$files(*.h,true)
