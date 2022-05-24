#ifndef MAINSEQUENCE_HPP_
#define MAINSEQUENCE_HPP_

#include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>
#include <eeros/safety/SafetySystem.hpp>
#include "AutMobRoSSafetyProperties.hpp"
#include "ControlSystem.hpp"
#include <eeros/sequencer/Wait.hpp>
#include "customSteps/SetServoPos.hpp"
#include "customSequences/TiltException.hpp"


class MainSequence : public eeros::sequencer::Sequence
{
public:
    MainSequence(std::string name, eeros::sequencer::Sequencer &seq,
                 eeros::safety::SafetySystem &ss,
                 AutMobRoSSafetyProperties &sp, ControlSystem &cs)
        : eeros::sequencer::Sequence(name, seq),
            ss(ss),
            sp(sp),
            cs(cs),

            sleep("Sleep", this),
            ServPos("ServPos", this, cs),
            myTiltCondition(cs),
            myTiltException("TiltExep", this, cs),
            TiltMonitor("TiltMon", this, myTiltCondition, eeros::sequencer::SequenceProp::resume, &myTiltException)
          
    {
        log.info() << "Sequence created: " << name;
        addMonitor(&TiltMonitor);
        
    }

    int action()
    {
        while (eeros::sequencer::Sequencer::running)
        {
            sleep(1.0);
            log.info() << cs.q1.getOut().getSignal();
            ServPos(1.5);
            // log.info() << cs.myConstant.getOut().getSignal();
            sleep(1.0);
            ServPos(-1.5);
            // log.info() << cs.myConstant.getOut().getSignal();

        }
        return 0;
    }


private:
    eeros::safety::SafetySystem &ss;
    ControlSystem &cs;
    AutMobRoSSafetyProperties &sp;

    eeros::sequencer::Wait sleep;
    SetServoPos ServPos;

    eeros::sequencer::Monitor TiltMonitor;
    TiltCondition myTiltCondition;
    TiltException myTiltException;
};

#endif // MAINSEQUENCE_HPP_