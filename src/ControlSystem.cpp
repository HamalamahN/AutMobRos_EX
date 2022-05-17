#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : mygain(2), myquat("quat1"), myservo("servo1"), timedomain("Main time domain", dt, true)
{
    // Name all blocks
    myquat.setName("Quaternion X");
    mygain.setName("My Gain");
    myservo.setName("Servo");

    // Name all signals
    myquat.getOut().getSignal().setName("Quaternion Angle");
    mygain.getOut().getSignal().setName("Quaternion multiplied with gain");
    

    // Connect signals
    mygain.getIn().connect(myquat.getOut());
    myservo.getIn().connect(mygain.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(mygain);
    timedomain.addBlock(myquat);
    timedomain.addBlock(myservo);
    
    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}