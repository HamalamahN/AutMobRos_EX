#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : myConstant(1.5), myGain(1.0), q1("quat1"), s1("servo1"),
      timedomain("Main time domain", dt, true)
{
    // Name all blocks
    myConstant.setName("My constant Position");
    myGain.setName("My gain");
    q1.setName("Quaternion X");
    s1.setName("Servo1");

    // Name all signals
    myConstant.getOut().getSignal().setName("My constant Position value");
    myGain.getOut().getSignal().setName("My Position value multiplied with my gain");
    q1.getOut().getSignal().setName("My Quaternion Angle/2");
    

    // Connect signals
    myGain.getIn().connect(myConstant.getOut());
    s1.getIn().connect(myGain.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(myConstant);
    timedomain.addBlock(myGain);
    timedomain.addBlock(q1);
    timedomain.addBlock(s1);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}