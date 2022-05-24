#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/Saturation.hpp>

using namespace eeros::control;

class ControlSystem
{
public:
    ControlSystem(double dt);

    // Define Blocks
    Constant<> myConstant;
    PeripheralInput<> q1;
    PeripheralOutput<> s1;
    Gain<> myGain;

    // Define Gains for Interfacing DC Motor and Encoder
    Gain<> k;
    Gain<> i;
    Gain<> kM;
    Gain<> R;
    // Define Encorder
    PeripheralInput<> e1;
    // Saturation
    Saturation<> sat;
    // Drive Motor
    PeripheralOutput<> M1;


    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP