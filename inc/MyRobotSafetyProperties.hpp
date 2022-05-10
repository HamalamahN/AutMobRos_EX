#ifndef MyRobotSAFETYPROPERTIES_HPP_
#define MyRobotSAFETYPROPERTIES_HPP_

#include <eeros/safety/SafetyProperties.hpp>
#include <eeros/hal/HAL.hpp>
#include "ControlSystem.hpp"

class MyRobotSafetyProperties : public eeros::safety::SafetyProperties
{
public:
    MyRobotSafetyProperties(ControlSystem &cs, double dt);

    // Define all possible events
    eeros::safety::SafetyEvent doSystemOff;
    eeros::safety::SafetyEvent doSystemOn;

    eeros::safety::SafetyEvent doRobotEndMov;
    eeros::safety::SafetyEvent doRobotStartMov;

    eeros::safety::SafetyEvent doGripperOpen;
    eeros::safety::SafetyEvent doGripperClosed;

    eeros::safety::SafetyEvent doGripperEndMov;
    eeros::safety::SafetyEvent doGripperStartMov;
    

    // Defina all possible levels
    eeros::safety::SafetyLevel slSystemOff;
    eeros::safety::SafetyLevel slSystemOn;

    eeros::safety::SafetyLevel slRobotIdle;
    eeros::safety::SafetyLevel slRobotMoving;

    eeros::safety::SafetyLevel slGripperOpen;
    eeros::safety::SafetyLevel slGripperClosed;

    eeros::safety::SafetyLevel slGripperMoving;
    eeros::safety::SafetyLevel slGripperIdle;



private:
    // Define all critical outputs
    // eeros::hal::Output<bool>* ...;

    // Define all critical inputs
    // eeros::hal::Input<bool>* ...;

    ControlSystem &cs;
};

#endif // MyRobotSAFETYPROPERTIES_HPP_
