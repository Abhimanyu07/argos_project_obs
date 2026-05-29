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
    Camera = GetSensor<CCI_ColoredBlobOmnidirectionalCameraSensor>("colored_blob_omnidirectional_camera");
    LEDs = GetActuator<CCI_LEDsActuator>("leds");
    myStopTime = 0;  
    isStopped = false; 
    Camera->Enable();
}

void CStopAndGo::ControlStep() {
    // This runs every single tick
    const CCI_FootBotProximitySensor::TReadings& proxReadings = m_pcProximity->GetReadings();
    UInt16 MAXSTOP = 10; 
    Real frontReading = std::max({proxReadings[23].Value, proxReadings[0].Value, proxReadings[1].Value}); // 30 degree front cone
    Real leftReading = std::max({proxReadings[5].Value, proxReadings[6].Value, proxReadings[7].Value}); // 30 degree left cone
    Real rightReading = std::max({proxReadings[17].Value, proxReadings[18].Value, proxReadings[19].Value}); // 30 degree right cone
    Real leftSpeed = m_fTargetSpeed; 
    Real rightSpeed = m_fTargetSpeed;

    if (isStopped) {
        LEDs->SetAllColors(CColor::RED);
        myStopTime--;
        m_pcWheels->SetLinearVelocity(0.0f, 0.0f); // stop commands to the actuators 
        if (myStopTime == 0) {
            isStopped = false; 
            m_pcWheels->SetLinearVelocity(leftSpeed, -rightSpeed);
        }
    }

    else{
        LEDs->SetAllColors(CColor::GREEN);
        if (frontReading > 0.05f) {
            myStopTime = MAXSTOP;
            isStopped = true;
        }
        else if (leftReading > 0.1f) {
            m_pcWheels->SetLinearVelocity(leftSpeed*1.5f, 0.0f); // turn right if obstacle is too close on the left
        }
        else if (rightReading > 0.1f) {
            m_pcWheels->SetLinearVelocity(0.0f, rightSpeed*1.5f); // turn left if obstacle is too close on the right
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