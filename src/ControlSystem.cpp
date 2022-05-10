#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : encoder("enc1"),
      motor("motor1"),
      timedomain("Main time domain", dt, true)
{
    // Name all blocks
    // myConstant.setName("My constant");
    // myGain.setName("My gain");

    encoder.setName("Encoder");
    controller.setName("Controller");
    motor.setName("Motor");

    // Name all signals
    // myConstant.getOut().getSignal().setName("My constant value");
    // myGain.getOut().getSignal().setName("My constant value multiplied with my gain");

    encoder.getOut().getSignal().setName("phi [rad]");
    controller.getOut().getSignal().setName("U [V]");

    // Connect signals
    // myGain.getIn().connect(myConstant.getOut());

    controller.getIn().connect(encoder.getOut());
    motor.getIn().connect(controller.getOut());

    // Add blocks to timedomain
    // timedomain.addBlock(myConstant);
    // timedomain.addBlock(myGain);
    timedomain.addBlock(encoder);
    timedomain.addBlock(controller);
    timedomain.addBlock(motor);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}