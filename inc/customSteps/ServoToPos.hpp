#ifndef SERVOTOPOS_HPP_
#define SERVOTOPOS_HPP_

#include <eeros/sequencer/Step.hpp>
#include "ControlSystem.hpp"

class ServoToPos : public eeros::sequencer::Step
{
public:
    ServoToPos(std::string name, eeros::sequencer::Sequence *caller, ControlSystem &cs)
        : eeros::sequencer::Step(name, caller),
        cs(cs)
    {
        log.info() << "Step created: " << name;
    }

    int action()
    {
        cs.posVal.setValue(this->pos);
        return 0;
    }

    int operator() (double pos) {
        this->pos = pos;
        return start();
    }

private:
    // Define variables, conditions, monitors, exception sequences, ...
    double pos;
    ControlSystem &cs;
};

#endif // SERVOTOPOS_HPP_
