#include "MyRobotSafetyProperties.hpp"

MyRobotSafetyProperties::MyRobotSafetyProperties(ControlSystem &cs, double dt)
    : cs(cs),
    
      slSystemOff("System is offline"),
      slSystemOn("System is online"),
      slRobotIdle("Robot is Idle"),
      slRobotMoving("Robot is Moving"),
      slGripperClosed("Gripper is Closed"),
      slGripperOpen("Gripper is Open"),
      slGripperIdle("Gripper is idle"),
      slGripperMoving("Gripper is Moving"),

      doSystemOn("Startup the system"),
      doSystemOff("Shutdown the system"),
      doRobotEndMov("Robot stopping Movement"),
      doRobotStartMov("Robot ist starting Movement"),
      doGripperClosed("Gripper is closing"),
      doGripperOpen("Gripper is opening"),
      doGripperEndMov("Gripper is stopping movement"),
      doGripperStartMov("Gripper is starting Movement")
{
    eeros::hal::HAL &hal = eeros::hal::HAL::instance();

    // Declare and add critical outputs
    // ... = hal.getLogicOutput("...");

    // criticalOutputs = { ... };

    // Declare and add critical inputs
    // ... = eeros::hal::HAL::instance().getLogicInput("...", ...);

    // criticalInputs = { ... };

    // Add all safety levels to the safety system
    addLevel(slSystemOff);
    addLevel(slSystemOn);
    addLevel(slRobotIdle);
    addLevel(slRobotMoving);
    addLevel(slGripperClosed);
    addLevel(slGripperOpen);
    addLevel(slGripperIdle);
    addLevel(slGripperMoving);

    // Add events to individual safety levels
    slSystemOff.addEvent(doSystemOn, slSystemOn, kPublicEvent);
    slSystemOn.addEvent(doSystemOff, slSystemOff, kPublicEvent);
    slRobotIdle.addEvent(doRobotStartMov, slRobotMoving, kPublicEvent);
    slRobotMoving.addEvent(doRobotEndMov, slRobotIdle, kPublicEvent);
    slGripperClosed.addEvent(doGripperOpen, slGripperOpen, kPublicEvent);
    slGripperOpen.addEvent(doGripperClosed, slGripperClosed, kPublicEvent);
    slGripperIdle.addEvent(doGripperStartMov, slGripperMoving, kPublicEvent);
    slGripperMoving.addEvent(doGripperEndMov, slGripperIdle, kPublicEvent);

    // Add events to multiple safety levels
    // addEventToAllLevelsBetween(lowerLevel, upperLevel, event, targetLevel, kPublicEvent/kPrivateEvent);

    // Define input actions for all levels
    // level.setInputActions({ ... });

    // Define output actions for all levels
    // level.setOutputActions({ ... });

    // Define and add level actions
    slSystemOff.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.stop();
        eeros::Executor::stop();
    });

    slSystemOn.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.start();
    });

    // Define entry level
    setEntryLevel(slSystemOff);

    // Define exit function
    exitFunction = ([&](SafetyContext *privateContext) {
        privateContext->triggerEvent(doSystemOff);
    });
}
