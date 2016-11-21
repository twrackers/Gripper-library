#include <Gripper.h>

Gripper::Gripper(
    const byte pin,
    const unsigned int closed,
    const unsigned int opened,
    const unsigned int timer
) : StateMachine(10, true),
    m_pin((int) pin),
    m_closed((int) closed), 
    m_opened((int) opened), 
    m_timer((int) timer),
    m_switchTime(millis()),
    m_state(eClosed),
    m_command(eOpen)    // force gripper to open immediately
{
}

void Gripper::open()
{
    m_command = eOpen;
}

void Gripper::close()
{
    m_command = eClose;
}

bool Gripper::isOpened() const
{
    return (m_state == eOpened) || (m_state == eClosing);
}

bool Gripper::isClosed() const
{
    return !isOpened();
}

bool Gripper::update()
{
    if (StateMachine::update()) {
        if (m_state == eOpened && m_command == eClose) {
            // Activate servo and command it to closed position.
            m_servo.attach(m_pin, m_closed, m_opened);
            m_servo.writeMicroseconds(m_closed);
            // Update state of this object.
            m_switchTime = millis();
            m_state = eClosing;
        } else if (m_state == eClosed && m_command == eOpen) {
            // Activate servo and command it to opened position.
            m_servo.attach(m_pin, m_closed, m_opened);
            m_servo.writeMicroseconds(m_opened);
            // Update state of this object.
            m_switchTime = millis();
            m_state = eOpening;
        } else if (m_state == eOpening || m_state == eClosing) {
            // If gripper is opening or closing, has time limit of motion
            // expired yet?
            if ((long) (millis() - (m_switchTime + m_timer)) >= 0) {
                // If so, kill the signal driving the servo to de-energize it.
                m_servo.detach();
                pinMode(m_pin, INPUT);
                // Update state of this object.
                m_state = (m_state == eClosing) ? eClosed : eOpened;
            }
        }
        return true;
    }
    return false;
}
