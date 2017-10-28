//
//  system.h
//  solarSystemGRA
//
//  Created by Jake on 4/16/15.
//  Copyright (c) 2015 Jake. All rights reserved.
//

#ifndef __solarSystemGRA__system__
#define __solarSystemGRA__system__

#include <GLUT/glut.h>
#include <vector>
#include "planet.h"

class System
{
private:
    std::vector<Planet> planets;
    
public:
    System();
    
    // calculate the positions and logic of all planets
    void calculatePositions(float time);
    
    // Add a planet with the given data
    void addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, int noOfMoons, GLuint textureHandle, bool isComet);
        
    // render the planets with opengl
    void render();
    
    // render the drawing of the orbits
    void drawOrbits();
    
    void getPlanetPosition(int index, float* vec);
    
};

#endif /* defined(__solarSystemGRA__system__) */
