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
    m_state(eInit)
{
}

void Gripper::open()
{
    m_servo.attach(m_pin, m_closed, m_opened);
    m_servo.writeMicroseconds(m_opened);
    m_switchTime = millis();
    m_state = eOpening;
}

void Gripper::close()
{
    m_servo.attach(m_pin, m_closed, m_opened);
    m_servo.writeMicroseconds(m_closed);
    m_switchTime = millis();
    m_state = eClosing;
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
        if (m_state == eInit) {
            // First time through, open the gripper.
            open();
        } else if (m_state == eOpening || m_state == eClosing) {
            // If gripper is opening or closing, has time limit of motion
            // expired yet?
            if (millis() >= (m_switchTime + m_timer)) {
                // If so, kill the signal driving the servo to de-energize it.
                m_servo.detach();
                pinMode(m_pin, INPUT);
                // Flip the current state.
                m_state = isOpened() ? eClosed : eOpened;
            }
        }
        return true;
    }
    return false;
}