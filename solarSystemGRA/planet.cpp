//
//  planet.cpp
//  solarSystemGRA
//
//  Created by Jake on 4/12/15.
//  Copyright (c) 2015 Jake. All rights reserved.
//

#include "planet.h"
#include "tga.h"
#include <cmath>

Planet::Planet(float distanceFromSun, float radius, float orbitTime, float rotationTime, int noOfMoons, GLuint planetTextureHandle, bool isComet)
{
    this->distanceFromSun = distanceFromSun;
    this->radius = radius;
    this->orbitTime = orbitTime;
    this->rotationTime = rotationTime;
    this->noOfMoons = noOfMoons;
    this->planetTextureHandle = planetTextureHandle;
    this->isComet = isComet;
    
    for (int i = 0; i < noOfMoons; i++)
    {
        TGA* moon = new TGA("Images/moon.tga");
        moons.push_back(Planet(2 * radius, radius * 0.3, 10, 10, 0, moon->getTextureHandle(), false));
    }
}

void Planet::calculatePosition(float time)
{
    // find the angle of orientation of the orbit around the sun
    float angle = time * 3.1419f / orbitTime;
    
    // use trig to find the position in space
    position[0] = sin(angle) * distanceFromSun;
    position[1] = cos(angle) * distanceFromSun;
    position[2] = 0;
    
    if (isComet)
    {
        position[0] = distanceFromSun*10 - angle;
        position[1] = distanceFromSun*10 - angle;
    }
    
    // find the rotation of the planet around its axis
    rotation = time * 360 / rotationTime;
    
    // calculate positions of moons
    for (int i = 0; i < moons.size(); i++)
    {
        moons[i].calculatePosition(time);
    }
}

void Planet::render(void)
{
    glPushMatrix();
    
    // translate to the right positon
    glTranslatef(position[0], position[1], position[2]);
    
    // Draw the moons
    for (int i = 0; i < moons.size(); i++)
    {
        moons[i].render();
    }
    
    /// rotate for the planet's spin
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    
    // bind the planets texture
    glBindTexture(GL_TEXTURE_2D, planetTextureHandle);
    
    // render as a GLU sphere quadric object
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, true);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    // if this is the sun, disable lighting
    if (distanceFromSun == 0)
    {
        glDisable(GL_LIGHTING);
        gluSphere(quadric, radius, 30, 30);
        glEnable(GL_LIGHTING);
    }
    else
    {
        gluSphere(quadric, radius, 30, 30);
    }
    
    glPopMatrix();
}

void Planet::drawOrbit(void)
{
    if (!isComet)
    {
        // draw a line strip
        glBegin(GL_LINE_STRIP);
        
        // loop round from 0 to 2*PI and draw around the radius of the orbit using trigonometry
        for (float angle = 0.0f; angle < 6.283185307f; angle += 0.05f)
        {
            glVertex3f(sin(angle) * distanceFromSun, cos(angle) * distanceFromSun, 0.0f);
        }
        glVertex3f(0.0f, distanceFromSun, 0.0f);
        
        glEnd();
        
        // render the moons' orbit
        glPushMatrix();
        
        // translate to the center of this planet to draw the moon orbit around it
        glTranslatef(position[0], position[1], position[2]);
        
        // draw all moon orbits
        for (int i = 0; i < moons.size(); i++)
        {
            moons[i].drawOrbit();
        }
        
        glPopMatrix();
    }
}

void Planet::getPosition(float* vec)
{
    vec[0] = position[0];
    vec[1] = position[1];
    vec[2] = position[2];
}