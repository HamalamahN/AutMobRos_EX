#ifndef TILTEXCEPTION_HPP_
#define TILTEXCEPTION_HPP_

#include <eeros/sequencer/Sequence.hpp>
#include "ControlSystem.hpp"
#include <eeros/sequencer/Wait.hpp>

class TiltException : public eeros::sequencer::Sequence
{
public:
    TiltException(std::string name, eeros::sequencer::Sequence *caller, ControlSystem &cs)
        : eeros::sequencer::Sequence(name, caller, true),
        cs(cs),
        sleep("Sleep", this)
    {
        
    }

    int action()
    {
        sleep(1.0);
        log.info() << "Robot X-Axis Tilt is too high, return to level surface: " << name;
        return 0;
    }

    bool checkPreCondition() {
        return cs.q1.getOut().getSignal().getValue() >0.1 || cs.q1.getOut().getSignal().getValue() <-0.1;
    }

    bool checkExitCondition() {
        return cs.q1.getOut().getSignal().getValue()<0.1 || cs.q1.getOut().getSignal().getValue()>-0.1;
    }

private:
    // Define steps, sub-sequences, variables, conditions, monitors, exception sequences, ...
    ControlSystem &cs;
    eeros::sequencer::Wait sleep;

};

#endif // TILTEXCEPTION_HPP_
