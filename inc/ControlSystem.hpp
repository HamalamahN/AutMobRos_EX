#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/Saturation.hpp>
#include <eeros/control/D.hpp>
#include <eeros/control/Sum.hpp>


using namespace eeros::control;

class ControlSystem
{
public:
    ControlSystem(double dt);

    // Define Blocks
    PeripheralInput<> e1;
    PeripheralInput<> e4;
    Gain<> Kp;
    Gain<> Kd;
    D<> deriv;
    Gain<> M;
    Saturation<> Qmax;
    Gain<> i_;
    Gain<> kM_;
    Gain<> R;
    PeripheralOutput<> M1;

    Sum<> e;
    Sum<> qc_2;

    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP