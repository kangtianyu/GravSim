 /* author: Tianyu Kang
  * Class Physics
  * Final version - maybe :)
  */

#include "Physics.h"

//data conclude all planets' information
//position is in meters, speed is in meters per second
//mass is in kilograms
//interval is in seconds -- should be 1 for most accurate
Physics::Physics(){}

Physics::Physics(std::vector<SpaceObject> data,long interval){
        G = 6.6738480e-11;
        currentStep = data;
        nextStep = data;
        this->interval = interval;
    }

void Physics::step(){
    int n = currentStep.size();
    //calculate speed
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            calc(&currentStep[i],&currentStep[j],
                &nextStep[i],&nextStep[j]);
        //calculate position
    for(int i=0;i<n;i++){
        SpaceObject *cp = &currentStep[i];
        SpaceObject *p = &nextStep[i];
        p->_x += (p->_x_speed+cp->_x_speed)*interval/2;
        p->_y += (p->_y_speed+cp->_y_speed)*interval/2;
        p->_z += (p->_z_speed+cp->_z_speed)*interval/2;
    }
    currentStep = nextStep;
}

void Physics::calc(SpaceObject *p1,SpaceObject *p2,SpaceObject *np1,SpaceObject *np2){
    double distance = sqrt(pow(p1->_x-p2->_x,2)+pow(p1->_y-p2->_y,2)+pow(p1->_z-p2->_z,2));
    double radX = (p1->_x-p2->_x)/distance;
    double radY = (p1->_y-p2->_y)/distance;
    double radZ = (p1->_z-p2->_z)/distance;

    double g = G/pow(distance,2);
    double acc1 = g*p2->_mass;
    np1->_x_speed -= acc1*radX*interval;
    np1->_y_speed -= acc1*radY*interval;
    np1->_z_speed -= acc1*radZ*interval;
    double acc2 = g*p1->_mass;
    np2->_x_speed += acc2*radX*interval;
    np2->_y_speed += acc2*radY*interval;
    np2->_z_speed += acc2*radZ*interval;
}
