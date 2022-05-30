#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : 
        e1("enc1"),
        e4("enc4"),
        e(),
        Kp(pow((1/(4.4*0.7*dt)),2.0)),
        deriv(),
        Kd_(2.0/4.4/dt), 
        M(0.00007444),
        qc_2(),
        Qmax(0.1),
        i_(104.0/3441.0), 
        kM_(1.0/0.00844),     
        R(8.0),   
        M1("motor1"),
        timedomain("Main time domain", dt, true)
{
    // Name all blocks
    e1.setName("Encoder1");
    e4.setName("Encoder4");
    e.setName("Position Error");
    Kp.setName("Gain Kp");
    deriv.setName("Derivative");
    Kd_.setName("Gain Kd");
    qc_2.setName("Second derivatice of qc");
    M.setName("Proportianal J");
    Qmax.setName("Motor Torque Saturation"); 
    i_.setName("Inverse Ratio");
    kM_.setName("Inverse Motor Torque Constant"); 
    R.setName("Resistance"); 
    M1.setName("Motor1");


    // Name all signals
    e1.getOut().getSignal().setName("Encoder 1 Signal");
    e4.getOut().getSignal().setName("Encoder 4 Signal");
    e.getOut().getSignal().setName("Error Signal");
    Kp.getOut().getSignal().setName("Kp Gain");
    deriv.getOut().getSignal().setName("Derivative signal");
    Kd_.getOut().getSignal().setName("Kd Gain");
    qc_2.getOut().getSignal().setName("qc_2");
    M.getOut().getSignal().setName("M Gain");
    Qmax.getOut().getSignal().setName(" Qmax Saturation");
    i_.getOut().getSignal().setName("i gain");
    kM_.getOut().getSignal().setName("kM Gain");
    R.getOut().getSignal().setName("Resistance Gain");

    
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
    timedomain.addBlock(e);
    timedomain.addBlock(Kp);
    timedomain.addBlock(deriv);
    timedomain.addBlock(Kd_);
    timedomain.addBlock(qc_2);
    timedomain.addBlock(M);
    timedomain.addBlock(Qmax);
    timedomain.addBlock(i_);
    timedomain.addBlock(kM_);
    timedomain.addBlock(R);
    timedomain.addBlock(M1);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}