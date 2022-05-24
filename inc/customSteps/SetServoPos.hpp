#ifndef SETSERVOPOS_HPP_
#define SETSERVOPOS_HPP_

#include <eeros/sequencer/Step.hpp>
#include "ControlSystem.hpp"
#include <eeros/sequencer/Condition.hpp>
#include <eeros/sequencer/Monitor.hpp>

class TiltCondition : public eeros::sequencer::Condition
{
public:
    ControlSystem &cs;

    TiltCondition(ControlSystem &cs) : cs(cs){ }                 // initialize any attributes necessary
    bool validate() {
      return mytest();
      }  // implement whatever your condition should check
    bool mytest() {
        return cs.q1.getOut().getSignal().getValue() >0.1 || cs.q1.getOut().getSignal().getValue() <-0.1;
    }
};

class SetServoPos : public eeros::sequencer::Step
{
public:
    SetServoPos(std::string name, eeros::sequencer::Sequence *caller, ControlSystem &cs)
        : eeros::sequencer::Step(name, caller),
        cs(cs)
    {
        log.info() << "Step created: " << name;
        
    }

    int action()
    {
        cs.myConstant.setValue(pos);
        return 0;
    }

    int operator() (double pos)
    {
        this->pos = pos;
        return start();
    }
private:
    double pos;
    ControlSystem &cs;
    // Define variables, conditions, monitors, exception sequences, ...
    
    

};

#endif // SETSERVOPOS_HPP_
