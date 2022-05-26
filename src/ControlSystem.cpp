#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : timedomain("Main time domain", dt, true),
        e1("enc1"),
        e4("enc4"),
        Kp(pow((dt/(4.4*0.7)),2.0)),
        Kd_(dt*2.0/4.4), 
        i_(104.0/3441.0), 
        kM_(1.0/0.00844), 
        Qmax(0.1),  
        R(8.0),
        M(0.00007444),
        M1("motor1")
{
    // Name all blocks
    e1.setName("Encoder1");
    e4.setName("Encoder4");
    Kp.setName("Gain Kp");
    Kd_.setName("Gain Kd");
    M.setName("Proportianal J");
    i_.setName("Inverse Ratio");
    kM_.setName("Inverse Motor Torque Constant");
    Qmax.setName("Motor Torque Saturation");  
    R.setName("Resistance");
    e.setName("Position Error");
    qc_2.setName("Second derivatice of qc");
    deriv.setName("Derivative");
    M1.setName("Motor1");


    // Name all signals
    e1.getOut().getSignal().setName("Encoder 1 Signal");
    e4.getOut().getSignal().setName("Encoder 4 Signal");
    Kp.getOut().getSignal().setName("Kp Gain");
    Kd_.getOut().getSignal().setName("Kd Gain");
    M.getOut().getSignal().setName("M Gain");
    i_.getOut().getSignal().setName("i gain");
    kM_.getOut().getSignal().setName("kM Gain");
    Qmax.getOut().getSignal().setName(" Qmax Saturation");
    R.getOut().getSignal().setName("Resistance Gain");
    e.getOut().getSignal().setName("Error Signal");
    qc_2.getOut().getSignal().setName("qc_2");
    deriv.getOut().getSignal().setName("Derivative signal");
    // Connect signals
    e.getIn(0).connect(e4.getOut());
    e.getIn(1).connect(e1.getOut());
    e.negateInput(1);
    Kp.getIn().connect(e.getOut());
    deriv.getIn().connect(e.getOut());
    Kd_.getIn().connect(deriv.getOut());
    qc_2.getIn(0).connect(Kp.getOut());
    qc_2.getIn(1).connect(Kd_.getOut());
    M.getIn().connect(qc_2.getOut());
    Qmax.getIn().connect(M.getOut());
    i_.getIn().connect(Qmax.getOut());
    kM_.getIn().connect(i_.getOut());
    R.getIn().connect(kM_.getOut());
    M1.getIn().connect(R.getOut());
    // Add blocks to timedomain
    timedomain.addBlock(e1);
    timedomain.addBlock(e4);
    timedomain.addBlock(Kd_);
    timedomain.addBlock(Kp);
    timedomain.addBlock(M);
    timedomain.addBlock(Qmax);
    timedomain.addBlock(i_);
    timedomain.addBlock(kM_);
    timedomain.addBlock(R);
    timedomain.addBlock(e);
    timedomain.addBlock(qc_2);
    timedomain.addBlock(deriv);
    timedomain.addBlock(M1);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}