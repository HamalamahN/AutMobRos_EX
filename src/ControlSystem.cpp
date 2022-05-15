#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : mygain(1.5), myquat("quat1"), myservo("servo1"), timedomain("Main time domain", dt, true)
{
    // Name all blocks
    myquat.setName("Quaternion X");
    //mygain.setName("My Gain");

    // Name all signals
    myquat.getOut().getSignal().setName("Quaternion Angle");
    //mygain.getOut().getSignal().setName("Quaternion multiplied with gain");
    

    // Connect signals
    // mygain.getIn().connect(myquat.getOut());
    myservo.getIn().connect(myquat.getOut());

    // Add blocks to timedomain
    // timedomain.addBlock(mygain);
    timedomain.addBlock(myquat);
    timedomain.addBlock(myservo);
    
    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}