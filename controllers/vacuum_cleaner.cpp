#include "vacuum_cleaner.h"
#include <algorithm>
#include <ctime>

#include <argos3/core/utility/math/vector2.h>
CVacuumCleaner::CVacuumCleaner() : 
m_pcWheels(NULL),
m_pcProximity(NULL),
m_fTargetSpeed(20.0f){}


void CVacuumCleaner::Init(TConfigurationNode& t_node) {
    m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
    m_pcProximity = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
}

void CVacuumCleaner::ControlStep(){
    srand(time(0)); // seed for random number generation
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

    int randomTurn = rand() % 24; 
    if(repulsionVector.Length() > 0.05){
        if(repulsionVector.Angle().GetValue() > 0.0){
        leftSpeed += m_fTargetSpeed*randomTurn/8.0f; 
        rightSpeed -= m_fTargetSpeed;
        }
        else{
        leftSpeed -= m_fTargetSpeed; 
        rightSpeed += m_fTargetSpeed*(randomTurn-8)/8.0f;     
        }

    }
    m_pcWheels->SetLinearVelocity(leftSpeed, rightSpeed); // sends the speed commands to the actuators 
} 

void CVacuumCleaner::Reset() {
    // Code to execute if you hit 'Reset' in the GUI
}
void CVacuumCleaner::Destroy() {
    // Cleanup memory here
}   

REGISTER_CONTROLLER(CVacuumCleaner, "vacuum_cleaner_controller")