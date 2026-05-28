#include "wall_follower.h"
#include <algorithm>
#include <argos3/core/utility/math/vector2.h>
CWallFollower::CWallFollower() : 
m_pcWheels(NULL),
m_pcProximity(NULL),
m_fTargetSpeed(10.0f){}


void CWallFollower::Init(TConfigurationNode& t_node) {
    m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
    m_pcProximity = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
}

void CWallFollower::ControlStep(){
    const CCI_FootBotProximitySensor::TReadings& proxReadings = m_pcProximity->GetReadings(); 
    Real frontReading = std::max({proxReadings[23].Value, proxReadings[0].Value, proxReadings[1].Value}); // 30 degree front cone
    Real leftReading = std::max({proxReadings[5].Value, proxReadings[6].Value, proxReadings[7].Value}); // 30 degree left cone

    if (frontReading > 0.1f) {
        m_pcWheels->SetLinearVelocity(m_fTargetSpeed, -m_fTargetSpeed); // turn right
    }
    else if(leftReading > 0.0f){
        if(leftReading > 0.6f){
            m_pcWheels->SetLinearVelocity(m_fTargetSpeed, m_fTargetSpeed*0.5f); // move forward but slighty towards right
        }
        else if(leftReading < 0.4f){
            m_pcWheels->SetLinearVelocity(m_fTargetSpeed*0.5f, m_fTargetSpeed); // move forward but slighty towards left
        }
        else{
            m_pcWheels->SetLinearVelocity(m_fTargetSpeed, m_fTargetSpeed); // just forward 
        }
    }
    else {
        m_pcWheels->SetLinearVelocity(m_fTargetSpeed, m_fTargetSpeed); // no wall in sight just forward 
        }
} 

void CWallFollower::Reset() {
    // Code to execute if you hit 'Reset' in the GUI
}
void CWallFollower::Destroy() {
    // Cleanup memory here
}   

REGISTER_CONTROLLER(CWallFollower, "wall_follower_controller")