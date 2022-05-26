#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : myConstant(1.5), myGain(1.0), q1("quat1"), s1("servo1"), e1("enc1"),
      timedomain("Main time domain", dt, true),
      k(0.0047746), i(104.0/3441.0), kM(1/0.00844), sat(0.03), M1("motor4"), R(8.0)
{
    // Name all blocks
    myConstant.setName("My constant Position");
    myGain.setName("My gain");
    q1.setName("Quaternion X");
    s1.setName("Servo1");


    e1.setName("Encoder1");
    k.setName("Gain K");
    i.setName("Ratio");
    kM.setName("Motor Torque Constant");
    sat.setName("Motor Velocity Saturation");
    M1.setName("Motor4");
    R.setName("Resistance");


    // Name all signals
    myConstant.getOut().getSignal().setName("My constant Position value");
    myGain.getOut().getSignal().setName("My Position value multiplied with my gain");
    q1.getOut().getSignal().setName("My Quaternion Angle/2");


    e1.getOut().getSignal().setName(" Encoder Signal Right Motor");
    k.getOut().getSignal().setName("qd1");
    sat.getOut().getSignal().setName("qd1sat");
    i.getOut().getSignal().setName("omega1");
    kM.getOut().getSignal().setName("U1");
    R.getOut().getSignal().setName("ResistanceSignal");

    

    // Connect signals
    myGain.getIn().connect(myConstant.getOut());
    s1.getIn().connect(myGain.getOut());

    k.getIn().connect(e1.getOut());
    sat.getIn().connect(k.getOut());
    i.getIn().connect(sat.getOut());
    kM.getIn().connect(i.getOut());
    R.getIn().connect(kM.getOut());
    M1.getIn().connect(R.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(myConstant);
    timedomain.addBlock(myGain);
    timedomain.addBlock(q1);
    timedomain.addBlock(s1);
    timedomain.addBlock(e1);

    timedomain.addBlock(k);
    timedomain.addBlock(sat);
    timedomain.addBlock(i);
    timedomain.addBlock(kM);
    timedomain.addBlock(R);
    timedomain.addBlock(M1);
    

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}