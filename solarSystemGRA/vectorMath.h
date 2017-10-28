//
//  vectorMath.h
//  solarSystemGRA
//
//  Created by Jake on 4/16/15.
//  Copyright (c) 2015 Jake. All rights reserved.
//

#ifndef __solarSystemGRA__vectorMath__
#define __solarSystemGRA__vectorMath__

#include <cmath>

void vectorSet(float* vec, float x, float y, float z)
{
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

// adds v2 to v1
void vectorAdd(float* v1, float* v2)
{
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
}

// copies v2 into v1
void vectorCopy(float* v1, float* v2)
{
    v1[0] = v2[0];
    v1[1] = v2[1];
    v1[2] = v2[2];
}

// multiplies vec by the scalar
void vectorMul(float* vec, float scalar)
{
    vec[0] *= scalar;
    vec[1] *= scalar;
    vec[2] *= scalar;
}

// finds the magnitude of a vec using pythag
float lengthOfVec(float* vec)
{
    return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

// normalises a vector to magnitude 1
void normaliseVec(float* vec)
{
    vectorMul(vec, 1 / lengthOfVec(vec));
}

// makes a 3x3 rotation matrix from the given angle and axis and pointer to a 3x3 matrix
void rotationMatrix(float* matrix, float* axis, float angle)
{
    float cos1 = cos(angle);
    float cos2 = 1 - cos1;
    float sin1 = sin(angle);
    
    matrix[0] = cos1 + axis[0]*axis[0]*cos2;
    matrix[1] = axis[0] * axis[1] * cos2 - axis[2]*sin1;
    matrix[2] = axis[0] * axis[2] * cos2 + axis[1]*sin1;
    
    matrix[3] = axis[1] * axis[0] * cos2 + axis[2]*sin1;
    matrix[4] = cos1 + axis[1] * axis[1] * cos2;
    matrix[5] = axis[1] * axis[2] * cos2 - axis[0] * sin1;
    
    matrix[6] = axis[2] * axis[0] * cos2 - axis[1] * sin1;
    matrix[7] = axis[2] * axis[1] * cos2 + axis[0] * sin1;
    matrix[8] = cos1 + axis[2] * axis[2] * cos2;
}

// multiplies a vector v1 by a matrix and puts the results into vector v2
void mulVecBy(float* v1, float* matrix, float* v2)
{
    v2[0] = v1[0] * matrix[0] + v1[1] * matrix[1] + v1[2] * matrix[2];
    v2[1] = v1[0] * matrix[3] + v1[1] * matrix[4] + v1[2] * matrix[5];
    v2[2] = v1[0] * matrix[6] + v1[1] * matrix[7] + v1[2] * matrix[8];
}

// rotate a vector v1 around the axis v2 by angle and put the result into v3
void rotateAroundVec(float* v1, float* v2, float angle, float* v3)
{
    //. make a rotation matrix for it
    float matrix[16];
    rotationMatrix(matrix, v2, angle);
    
    // multiply by the matrix
    mulVecBy(v1, matrix, v3);
}

#endif /* defined(__solarSystemGRA__vectorMath__) */
