#ifndef SWARM_CONTROLLER_H
#define SWARM_CONTROLLER_H

#include <argos3/core/control_interface/ci_controller.h>

using namespace argos;

class CMyController : public CCI_Controller {
public:
    CMyController();
    virtual ~CMyController() {}

    virtual void Init(TConfigurationNode& t_node);
    virtual void ControlStep();
    virtual void Reset();
    virtual void Destroy();
};

#endif