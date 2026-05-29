#ifndef STOP_AND_GO_H
#define STOP_AND_GO_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/generic/control_interface/ci_colored_blob_omnidirectional_camera_sensor.h>
using namespace argos;

class CStopAndGo : public CCI_Controller {
public:
    CStopAndGo();
    virtual ~CStopAndGo() {}

    virtual void Init(TConfigurationNode& t_node);
    virtual void ControlStep();
    virtual void Reset();
    virtual void Destroy();

private:
    CCI_DifferentialSteeringActuator* m_pcWheels;
    CCI_FootBotProximitySensor* m_pcProximity;
    bool IsRobotAhead();
    Real m_fTargetSpeed;
    UInt16 myStopTime;  
    bool isStopped; 
    CCI_LEDsActuator* LEDs;
    CCI_ColoredBlobOmnidirectionalCameraSensor* Camera;
};

#endif