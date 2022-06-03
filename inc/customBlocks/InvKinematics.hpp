#ifndef INVKINEMATICS_HPP_
#define INVKINEMATICS_HPP_

#include <eeros/control/Block.hpp>
// Include header files for the inputs, outputs and subblocks

using namespace eeros::control;

template <typename T = double>
class InvKinematics : public Block
{
public:
    InvKinematics() 
    {
        // Connect subblocks, initialize variables, ...
    }
    
    // Implement getter functions for the inputs and outputs

    virtual void run()
    {
        // Calculate output values, set timestamps and 
        // call the run method of the subblocks
    }

protected:
    // Define inputs, outputs, intermediate variables and subblocks
};

#endif //INVKINEMATICS_HPP_