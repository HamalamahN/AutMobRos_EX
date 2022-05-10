#ifndef CONTROLLERSUB_HPP_
#define CONTROLLERSUB_HPP_

#include <eeros/control/Block.hpp>
#include <eeros/control/InputSub.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Sum.hpp>
#include <eeros/control/Gain.hpp>
// Include header files for the inputs, outputs and subblocks

using namespace eeros::control;

template <typename T = double>
class Controller : public Block  // Set number of inputs and outputs
{
public:
    ControllerSub() : phi(this), phi_S{0.0}, kp{2.0}
    {
        // Connect subblocks, initialize variables, ...
        sum.getIn(0).connect(phi_S.getOut());
        sum.negateInput(1);
        sum.getIn(1).connect(phi);
        kp.getIn().connect(sum.getOut());
    }
    
    // Implement getter functions for the inputs and outputs
    void setSetpoint(double phi) { phi_S.setValue(phi); }

    Input<T> &getIn() { return phi;}

    Output<T> &getOut() { return kp.getOut; }


    virtual void run()
    {
        phi_S.run();
        sum.run();
        kp.run();
    }

protected:
    // Define inputs, outputs, intermediate variables and subblocks
    InputSub<T> phi;
    Constant<T> phi_S;
    Sum<2,T> sum;
    Gain<T> kp;
};

#endif //CONTROLLERSUB_HPP_