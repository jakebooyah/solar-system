//
//  planet.h
//  solarSystemGRA
//
//  Created by Jake on 4/12/15.
//  Copyright (c) 2015 Jake. All rights reserved.
//

#ifndef __solarSystemGRA__planet__
#define __solarSystemGRA__planet__

#include <GLUT/glut.h>
#include <vector>

class Planet
{
    private:
    
    float distanceFromSun;
    float radius;
    float orbitTime;
    float rotationTime;
    
    int noOfMoons;
    
    bool isComet;
    
    GLuint planetTextureHandle;
    
    float position[3];
    
    float rotation;
    
    std::vector<Planet> moons;
    
    public:
    
    // Distance is in units of km and time is in days
    Planet(float distanceFromSun, float radius, float orbitTime, float rotationTime, int noOfMoons, GLuint planetTextureHandle, bool isComet);
    
    void calculatePosition(float time);
    
    void render(void);
    
    void drawOrbit(void);
    
    void getPosition(float* vec);
};

#endif /* defined(__solarSystemGRA__planet__) */
