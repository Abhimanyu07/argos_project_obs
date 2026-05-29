#include "stop_and_go.h"
#include <algorithm>
CStopAndGo::CStopAndGo() : 
m_pcWheels(NULL),
m_pcProximity(NULL),
m_fTargetSpeed(10.0f){}

void CStopAndGo::Init(TConfigurationNode& t_node) {
    // Initialization code goes here
    m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
    m_pcProximity = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");

    myStopTime = 0;  
    isStopped = false; 
}

void CStopAndGo::ControlStep() {
    // This runs every single tick
    const CCI_FootBotProximitySensor::TReadings& proxReadings = m_pcProximity->GetReadings();
    UInt16 MAXSTOP = 10; 
    Real frontReading = std::max({proxReadings[23].Value, proxReadings[0].Value, proxReadings[1].Value}); // 30 degree front cone


    Real leftSpeed = m_fTargetSpeed; 
    Real rightSpeed = m_fTargetSpeed;

    if (isStopped) {
        myStopTime--;
        m_pcWheels->SetLinearVelocity(0.0f, 0.0f); // stop commands to the actuators 
        if (myStopTime == 0) {
            isStopped = false; 
            m_pcWheels->SetLinearVelocity(leftSpeed, -rightSpeed);
        }
    }
    
    if(!isStopped) {
        if (frontReading > 0.1f) {
            myStopTime = MAXSTOP;
            isStopped = true;
        }
        else{
            m_pcWheels->SetLinearVelocity(leftSpeed, rightSpeed); // go forward if no obstacle in front
        }
}

    
}

void CStopAndGo::Reset() {
    // Code to execute if you hit 'Reset' in the GUI
}

void CStopAndGo::Destroy() {
    // Cleanup memory here
}


REGISTER_CONTROLLER(CStopAndGo, "stop_and_go_controller")