#ifndef _VERTICES_H_
#define _VERTICES_H_

#include <memory>
#include <iostream>
#include <vector>
#include "edge.h"
#include "observer.h"
#include "subject.h"

class Vertices : public Observer, public Subject {
    int location;  // location on the board
    // truth value of whether a residence can build at the location
    bool canBuildResidence;
    int whichBuilder;  // the owner of the residence
    // vector list of shared pointer of edges that are neighbours of vertice
    std::vector<std::shared_ptr<Edge>> connectedEdges;

   public:
    Vertices(int _location, bool _canBuildResidence = true,
             int _whichBuilder = -1);  // initially -1 represent no residence
    void addResidence(int builder);  // build a residence (basement) at the location
    // update the availability of building residence at the location
    void updateAvailableResidence();
    // notify all neighbour to update the availability of building residences
    void notifyObservers();
    // update the availability of building residence for neighbour vertices
    void update();

    void addEdgeNeighbour(const std::shared_ptr<Edge> &edge);
};

#endif