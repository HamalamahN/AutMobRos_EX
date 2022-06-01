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
    Gain<> Kd_;
    D<> deriv_e;
    
    D<> deriv_q;
    Gain<> M;
    Saturation<> Qmax;
    Saturation<> q_1max;
    Gain<> i_;
    
    Gain<> i;
    Gain<> kM_;
    Gain<> kM;
    Gain<> R;
    PeripheralOutput<> M1;
    
    Sum<> e;
    Sum<> qc_2;
    Sum<> U;
    
    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP