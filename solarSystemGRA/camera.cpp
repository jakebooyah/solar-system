//
//  camera.cpp
//  solarSystemGRA
//
//  Created by Jake on 4/17/15.
//  Copyright (c) 2015 Jake. All rights reserved.
//

#include <GLUT/glut.h>
#include "camera.h"
#include "vectorMath.h"

Camera::Camera(void)
{
	cameraSpeed = 0.005f;
	cameraTurnSpeed = 0.01f;

    vectorSet(position, 0.764331460f, -1.66760659f, 0.642456770);
    vectorSet(forwardVec,-0.398769796f, 0.763009906f, -0.508720219f);
	vectorSet(rightVec, 0.886262059f, 0.463184059f, 0.000000000f);
    vectorSet(upVec, -0.235630989f, 0.450859368f, 0.860931039f);
}

// transform the opengl view matrix for the camera
void Camera::transformOrientation(void)
{
	// look in the direction of the orientation vectors
	gluLookAt(0, 0, 0, forwardVec[0], forwardVec[1], forwardVec[2], upVec[0], upVec[1], upVec[2]);
}

// transform the opoengl view matrix for the translation
void Camera::transformTranslation(void)
{
	// translate to emulate camera position
	glTranslatef(-position[0], -position[1], -position[2]);
}

// points the camera at the given point in 3d space
void Camera::pointAt(float* targetVec)
{
	float tempVec[3];
	float up[3] = { 0.0f, 0.0f, 1.0f };

	// first work out the new forward vector by subtracting the target position from the camera position
	forwardVec[0] = targetVec[0] - position[0];
	forwardVec[1] = targetVec[1] - position[1];
	forwardVec[2] = targetVec[2] - position[2];
	// then normalise it to 1 length
	normaliseVec(forwardVec);

	// now to find the right vector we rotate the forward vector -pi/2 around the z axis
	rotateAroundVec(forwardVec, up, -1.57079632679f, tempVec);
	// and remove the y component to make it flat
	tempVec[2] = 0;
	// then normalise it
	normaliseVec(tempVec);
	// and assign it to rightVec
	vectorCopy(rightVec, tempVec);

	// now work out the upvector by rotating the forward vector pi/2 around the rightvector
	rotateAroundVec(forwardVec, rightVec, 1.57079632679f, tempVec);
	vectorCopy(upVec, tempVec);
}

// move the camera forward
void Camera::forward(void)
{
	// make a movement vector the right speed facing the forward direction
	float vec[3];
	vectorCopy(vec, forwardVec);
	vectorMul(vec, cameraSpeed);

	// add the movement vec to the position vec
	vectorAdd(position, vec);
}

// move the camera backward
void Camera::backward(void)
{
	// make a movement vector the right speed facing the backward direction
	float vec[3];
	vectorCopy(vec, forwardVec);
	vectorMul(vec, -cameraSpeed); // -cameraSpeed for backwards

	// add the movement vec to the position vec
	vectorAdd(position, vec);
}

// strafe left
void Camera::left(void)
{
	// make a movement vector the right speed facing the left direction
	float vec[3];
	vectorCopy(vec, rightVec);
	vectorMul(vec, -cameraSpeed); // -cameraSpeed for left

	// add the movement vec to the position vec
	vectorAdd(position, vec);
}

// strafe right
void Camera::right(void)
{
	// make a movement vector the right speed facing the right direction
	float vec[3];
	vectorCopy(vec, rightVec);
	vectorMul(vec, cameraSpeed);

	// add the movement vec to the position vec
	vectorAdd(position, vec);
}

// roll the camera to the right
void Camera::rollRight(void)
{
	float tempVec[3];
	// rotate the up and right vectors around the forward vector axis for roll
	rotateAroundVec(upVec, forwardVec, cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
	
	rotateAroundVec(rightVec, forwardVec, cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// roll the camera to the left
void Camera::rollLeft(void)
{
	float tempVec[3];
	// rotate the up and right vectors around the forward vector axis for roll
	rotateAroundVec(upVec, forwardVec, -cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
	
	rotateAroundVec(rightVec, forwardVec, -cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// pitch the camera up
void Camera::pitchUp(void)
{
	float tempVec[3];
	// rotate the forward and up vectors around the right vector axis for pitch
	rotateAroundVec(forwardVec, rightVec, cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);
	
	rotateAroundVec(upVec, rightVec, cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
}

// pitch the camera down
void Camera::pitchDown(void)
{
	float tempVec[3];
	// rotate the forward and up vectors around the right vector axis for pitch
	rotateAroundVec(forwardVec, rightVec, -cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);
	
	rotateAroundVec(upVec, rightVec, -cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
}

// yaw left
void Camera::yawLeft(void)
{
	float tempVec[3];
	// rotate the forward and right vectors around the up vector axis for yaw
	rotateAroundVec(forwardVec, upVec, cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);
	
	rotateAroundVec(rightVec, upVec, cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// yaw right
void Camera::yawRight(void)
{
	float tempVec[3];
	// rotate the forward and right vectors around the up vector axis for yaw
	rotateAroundVec(forwardVec, upVec, -cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);
	
	rotateAroundVec(rightVec, upVec, -cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}