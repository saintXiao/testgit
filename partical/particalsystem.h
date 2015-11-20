#ifndef PARTICALSYSTEM_H
#define PARTICALSYSTEM_H
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "particle.h"
#define PI 3.1415926

class ParticalSystem
{
public:
    ParticalSystem();
    ParticalSystem(int _count,float _gravity){ptlCount=_count;gravity=_gravity;};
            void init();
            void simulate(float dt,int x, int y);
            void aging(float dt ,int x, int y);
            void applyGravity();
            void kinematics(float dt);
            void checkBump(float x1,float x2,float y1,float y2);
            void render();
            virtual ~ParticalSystem();
protected:
private:
            int ptlCount;
                float gravity;
                GLUquadricObj *mySphere;
                vector<Particle> particles;
};

#endif // PARTICALSYSTEM_H
