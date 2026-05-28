#include "swarm_controller.h"
#include <argos3/core/utility/math/vector2.h>
CMyController::CMyController() : 
m_pcWheels(NULL),
m_pcProximity(NULL),
m_fTargetSpeed(10.0f){}

void CMyController::Init(TConfigurationNode& t_node) {
    // Initialization code goes here
    m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
    m_pcProximity = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
}

void CMyController::ControlStep() {
    // This runs every single tick
    const CCI_FootBotProximitySensor::TReadings& proxReadings = m_pcProximity->GetReadings();
    CVector2 repulsionVector;
    for(size_t i = 0; i < proxReadings.size(); ++i) {
        repulsionVector += CVector2(proxReadings[i].Value, proxReadings[i].Angle);
    }

    // Averaging the repulsion vector
    if(proxReadings.size() > 0) {
        repulsionVector /= proxReadings.size();
    }

    Real leftSpeed = m_fTargetSpeed; 
    Real rightSpeed = m_fTargetSpeed;

    if(repulsionVector.Length() > 0.05){
        if(repulsionVector.Angle().GetValue() > 0.0){
            leftSpeed += m_fTargetSpeed; 
            rightSpeed -= m_fTargetSpeed;
        }
        else{
            leftSpeed -= m_fTargetSpeed; 
            rightSpeed += m_fTargetSpeed;   
        }

    }

    m_pcWheels->SetLinearVelocity(leftSpeed, rightSpeed); // sends the speed commands to the actuators 

}

void CMyController::Reset() {
    // Code to execute if you hit 'Reset' in the GUI
}

void CMyController::Destroy() {
    // Cleanup memory here
}


REGISTER_CONTROLLER(CMyController, "swarm_controller")