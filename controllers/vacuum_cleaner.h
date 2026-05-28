#ifndef VACUUM_CLEANER_H
#define VACUUM_CLEANER_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

using namespace argos;

class CVacuumCleaner : public CCI_Controller {
public:
    CVacuumCleaner();
    virtual ~CVacuumCleaner() {}

    virtual void Init(TConfigurationNode& t_node);
    virtual void ControlStep();
    virtual void Reset();
    virtual void Destroy();

private:
    CCI_DifferentialSteeringActuator* m_pcWheels;
    CCI_FootBotProximitySensor* m_pcProximity;

    Real m_fTargetSpeed;
};

#endif