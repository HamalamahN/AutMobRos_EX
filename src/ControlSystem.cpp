#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : 
        e1("enc1"),
        e4("enc4"),
        e(),
        Kp(pow((1/(4.4*0.7*dt)),2.0)),
        deriv_e(),
        deriv_q(),
        Kd_(2.0/4.4/dt), 
        M(0.00007444),
        qc_2(),
        U(),
        Qmax(0.1),
        q_1max(21.2),
        i_(104.0/3441.0),
        i(3441.0/104.0), 
        kM_(1.0/0.00844), 
        kM(0.00844),    
        R(8.0),   
        M1("motor1"),
        timedomain("Main time domain", dt, true)
{
    // Name all blocks
    e1.setName("Encoder1");
    e4.setName("Encoder4");
    e.setName("Position Error");
    Kp.setName("Gain Kp");
    deriv_e.setName("Derivative of e");
    deriv_q.setName("Derivative of e1");
    Kd_.setName("Gain Kd");
    qc_2.setName("Second derivatice of qc");
    q_1max.setName("Motor Velocity Saturation");
    M.setName("Proportianal J");
    Qmax.setName("Motor Torque Saturation"); 
    i_.setName("Inverse Ratio");
    i.setName("Ratio");
    kM_.setName("Inverse Motor Torque Constant"); 
    kM.setName("Motor Torque Constant");
    U.setName("Motor 1 Voltage");
    R.setName("Resistance"); 
    M1.setName("Motor1");


    // Name all signals
    e1.getOut().getSignal().setName("Encoder 1 Signal");
    e4.getOut().getSignal().setName("Encoder 4 Signal");
    e.getOut().getSignal().setName("Error Signal");
    Kp.getOut().getSignal().setName("Kp Gain");
    deriv_e.getOut().getSignal().setName("e Derivative signal");
    
    Kd_.getOut().getSignal().setName("Kd Gain");
    qc_2.getOut().getSignal().setName("qc_2");
    M.getOut().getSignal().setName("M Gain");
    Qmax.getOut().getSignal().setName(" Qmax Saturation");
    q_1max.getOut().getSignal().setName("qdot max Saturation");
    
    i_.getOut().getSignal().setName("i inverse gain");
    i.getOut().getSignal().setName("i Gain");
    kM_.getOut().getSignal().setName("kM inverse Gain");
    kM.getOut().getSignal().setName("kM Gain");
    R.getOut().getSignal().setName("Resistance Gain");
    
    U.getOut().getSignal().setName("Voltage");
    deriv_q.getOut().getSignal().setName("q derivative Signal");
    
    // Connect signals
    e.getIn(0).connect(e4.getOut());
    e.getIn(1).connect(e1.getOut());
    e.negateInput(1);
    Kp.getIn().connect(e.getOut());
    deriv_e.getIn().connect(e.getOut());
    Kd_.getIn().connect(deriv_e.getOut());
    qc_2.getIn(0).connect(Kp.getOut());
    qc_2.getIn(1).connect(Kd_.getOut());
    M.getIn().connect(qc_2.getOut());
    Qmax.getIn().connect(M.getOut());
    i_.getIn().connect(Qmax.getOut());
    kM_.getIn().connect(i_.getOut());
    R.getIn().connect(kM_.getOut());

    deriv_q.getIn().connect(e1.getOut());
    q_1max.getIn().connect(deriv_q.getOut());
    i.getIn().connect(q_1max.getOut());
    kM.getIn().connect(i.getOut());
    U.getIn(0).connect(R.getOut());
    U.getIn(1).connect(kM.getOut());

    M1.getIn().connect(U.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(e1);
    timedomain.addBlock(e4);
    timedomain.addBlock(e);
    timedomain.addBlock(Kp);
    timedomain.addBlock(deriv_e);
    timedomain.addBlock(Kd_);
    timedomain.addBlock(qc_2);
    timedomain.addBlock(M);
    timedomain.addBlock(Qmax);
    timedomain.addBlock(i_);
    timedomain.addBlock(kM_);
    timedomain.addBlock(R);
    timedomain.addBlock(M1);
    timedomain.addBlock(kM);
    timedomain.addBlock(i);
    timedomain.addBlock(q_1max);
    timedomain.addBlock(deriv_q);
    timedomain.addBlock(U);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}