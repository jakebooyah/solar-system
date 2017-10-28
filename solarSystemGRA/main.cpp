//
//  main.cpp
//  solarSystemGRA
//
//  Created by Jake on 4/12/15.
//  Copyright (c) 2015 Jake. All rights reserved.
//

#include <GLUT/glut.h>
#include "tga.h"
#include "system.h"
#include "camera.h"

int screenWidth;
int screenHeight;

double timeLocal;
double timeSpeed;

System solarSystem;
Camera camera;

int planetSelected = 1;

bool forward;
bool backward;
bool left;
bool right;
bool yawLeft;
bool yawRight;
bool pitchUp;
bool pitchDown;
bool rollLeft;
bool rollRight;

TGA* stars;
TGA* help;

bool helpDialogue = true;

void timer(int)
{
    glutPostRedisplay(); // post for display func
    glutTimerFunc(10, timer, 0); // limit frame drawing to 100fps
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    
    // set up lighting
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat matShininess[] = { 20.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);
    
    GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
    stars = new TGA("Images/stars.tga");
    help = new TGA("Images/help.tga");

    TGA* sun = new TGA("Images/sun.tga");
    TGA* mercury = new TGA("Images/mercury.tga");
    TGA* venus = new TGA("Images/venus.tga");
    TGA* earth = new TGA("Images/earth.tga");
    TGA* mars = new TGA("Images/mars.tga");
    TGA* jupiter = new TGA("Images/jupiter.tga");
    TGA* saturn = new TGA("Images/saturn.tga");
    TGA* uranus = new TGA("Images/uranus.tga");
    TGA* neptune = new TGA("Images/neptune.tga");
    TGA* pluto = new TGA("Images/pluto.tga");
    TGA* moon = new TGA("Images/moon.tga");
    
    solarSystem.addPlanet(0, 0.5, 1, 500, 0, sun->getTextureHandle(), false); // sun
    solarSystem.addPlanet(1, 0.05, 88, 58.6, 0, mercury->getTextureHandle(), false); // mercury
    solarSystem.addPlanet(1.5, 0.055, 224.65, 243, 0, venus->getTextureHandle(), false); // venus
    solarSystem.addPlanet(2, 0.06, 365, 1, 1, earth->getTextureHandle(), false); // earth
    solarSystem.addPlanet(2.5, 0.05, 686, 1.03f, 0, mars->getTextureHandle(), false); // mars
    solarSystem.addPlanet(5, 0.3, 4332, 0.4139, 0, jupiter->getTextureHandle(), false); // jupiter
    solarSystem.addPlanet(7.5, 0.3, 10759, 0.44375, 0, saturn->getTextureHandle(), false); // saturn
    solarSystem.addPlanet(12.5, 0.1, 30685, 0.718056, 0, uranus->getTextureHandle(), false); // uranus
    solarSystem.addPlanet(15, 0.09, 60188, 0.6713, 0, neptune->getTextureHandle(), false); // neptune
    solarSystem.addPlanet(1, 0.03, 50, 58.6, 0, moon->getTextureHandle(), true); // comet

    // set up time
    timeLocal = 0;
    timeSpeed = 0.1f;
    
    timer(0);
}

void drawCube(void)
{
    glBegin(GL_QUADS);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    
    glEnd();
}

void display(void)
{
    // update the logic and simulation
    timeLocal += timeSpeed;
    solarSystem.calculatePositions(timeLocal);
        
    if (forward) camera.forward();
    if (backward) camera.backward();
    if (left) camera.left();
    if (right) camera.right();
    if (yawLeft) camera.yawLeft();
    if (yawRight) camera.yawRight();
    if (rollLeft) camera.rollLeft();
    if (rollRight) camera.rollRight();
    if (pitchUp) camera.pitchUp();
    if (pitchDown) camera.pitchDown();
    
    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    
    // set up the perspective matrix for rendering the 3d world
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    // perform the camera orientation transform
    camera.transformOrientation();
    
    // draw the skybox
    glBindTexture(GL_TEXTURE_2D, stars->getTextureHandle());
    drawCube();
    
    // perform the camera translation transform
    camera.transformTranslation();
    
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // render the solar system
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    solarSystem.render();
    glDisable(GL_LIGHTING);
    
    solarSystem.drawOrbits();
    
    glDisable(GL_DEPTH_TEST);
    
    // set up ortho matrix for showing the UI (help dialogue)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) screenWidth, (GLdouble) screenHeight, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // draw the help dialogue
    if (helpDialogue)
    {
        glBindTexture(GL_TEXTURE_2D, help->getTextureHandle());
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);	glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);	glVertex2f(512.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);	glVertex2f(512.0f, 512.0f);
        glTexCoord2f(0.0f, 1.0f);	glVertex2f(0.0f, 512.0f);
        glEnd();
    }
    
//    glFlush();
    glutSwapBuffers();
    
    if (planetSelected > 0 && planetSelected <= 9)
    {
        float vec[3];
        solarSystem.getPlanetPosition(planetSelected, vec);
        camera.pointAt(vec);
    }
}

void reshape(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyDown(unsigned char key, int x, int y)
{
    // check for numerical keys
    if (key > '0' && key <= '9')
    {
        if (planetSelected == key - '0')
        {
            planetSelected = 0;
        }
        else
        {
            planetSelected = key - '0';
        }
    }
    
    switch (key)
    {
        case 'h':
            helpDialogue = !helpDialogue; // toggle the dialogue
            break;
        case 'w':
            forward = true;
            break;
        case 's':
            backward = true;
            break;
        case 'a':
            left = true;
            break;
        case 'd':
            right = true;
            break;
        case 'l':
            rollRight = true;
            break;
        case 'j':
            rollLeft = true;
            break;
        case 'i':
            pitchDown = true;
            break;
        case 'k':
            pitchUp = true;
            break;
        case 'q':
            yawLeft = true;
            break;
        case 'e':
            yawRight = true;
            break;
    }
    
}

void keyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            forward = false;
            break;
        case 's':
            backward = false;
            break;
        case 'a':
            left = false;
            break;
        case 'd':
            right = false;
            break;
        case 'l':
            rollRight = false;
            break;
        case 'j':
            rollLeft = false;
            break;
        case 'i':
            pitchDown = false;
            break;
        case 'k':
            pitchUp = false;
            break;
        case 'q':
            yawLeft = false;
            break;
        case 'e':
            yawRight = false;
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
    return 0;
}

