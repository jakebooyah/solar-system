//
//  system.cpp
//  solarSystemGRA
//
//  Created by Jake on 4/16/15.
//  Copyright (c) 2015 Jake. All rights reserved.
//

#include "system.h"

System::System()
{
    
}

// calculate the positions and logic of all planets
void System::calculatePositions(float time)
{
    for (int i = 0; i < planets.size(); i++)
    {
        planets[i].calculatePosition(time);
    }
}

// Add a planet with the given data
void System::addPlanet(float distanceFromSun, float radius, float orbitTime, float rotationTime, int noOfMoons, GLuint textureHandle, bool isComet)
{
    planets.push_back(Planet(distanceFromSun, radius, orbitTime, rotationTime, noOfMoons, textureHandle, isComet));
}

void System::render()
{
    for (int i = 0; i < planets.size(); i++)
    {
        planets[i].render();
    }
}

// render the drawing of the orbits
void System::drawOrbits()
{
    for (int i = 0; i < planets.size(); i++)
    {
        planets[i].drawOrbit();
    }
}

void System::getPlanetPosition(int index, float* vec)
{
    planets[index].getPosition(vec);
}