#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : mygain(2.0),posVal(1.0), myquat("quat1"), myservo("servo1"), timedomain("Main time domain", dt, true)
{
    // Name all blocks
    myquat.setName("Quaternion X");
    // mygain.setName("My Gain");
    myservo.setName("Servo");
    // posVal.setName("ServoPosition");

    // Name all signals
    myquat.getOut().getSignal().setName("Quaternion Angle");
    // mygain.getOut().getSignal().setName("Quaternion multiplied with gain");
    // posVal.getOut().getSignal().setName("Servo Angle Position");

    // Connect signals
    // mygain.getIn().connect(myquat.getOut());
    // mygain.getIn().connect(posVal.getOut());
    myservo.getIn().connect(myquat.getOut());

    // Add blocks to timedomain
    // timedomain.addBlock(mygain);
    timedomain.addBlock(myquat);
    timedomain.addBlock(myservo);
    // timedomain.addBlock(posVal);
    
    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}