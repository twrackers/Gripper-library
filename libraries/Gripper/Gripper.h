#ifndef _GRIPPER__H_
#define _GRIPPER__H_

#include <Servo.h>
#include <StateMachine.h>

class Gripper : public StateMachine
{
    private:
        enum E_STATE {
            eClosed, eOpening, eOpened, eClosing
        };
        enum E_COMMAND {
            eClose, eOpen
        };
        
        Servo m_servo;              // servo object
        const int m_pin;            // GPIO pin connected to servo
        const int m_closed;         // closed position (microseconds)
        const int m_opened;         // opened position (microseconds)
        const int m_timer;          // attached time limit
        unsigned long m_switchTime; // time of last open/close (milliseconds)
        E_STATE m_state;            // current state
        E_COMMAND m_command;        // commanded state
        
    public:
        /**
         * Constructor
         *
         * @param pin    servo pin
         * @param closed calibrated closed position (microseconds)
         * @param opened calibrated opened position (microseconds)
         * @param timer  maximum attached time (0 = indefinite)
         */
         Gripper(
            const byte pin,
            const unsigned int closed,
            const unsigned int opened,
            const unsigned int timer
         );
         
         /**
          * Command the gripper to open.
          */
         void open();
         
         /**
          * Command the gripper to close.
          */
         void close();
         
         /**
          * Is gripper opened (or closing)?
          */
         bool isOpened() const;
         
         /**
          * Is gripper closed (or opening)?
          */
         bool isClosed() const;
         
         /**
          * Update the state machine.
          */
         virtual bool update();
};

#endif
