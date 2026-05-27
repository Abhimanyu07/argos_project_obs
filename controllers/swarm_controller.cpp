#include "swarm_controller.h"

CMyController::CMyController() {}

void CMyController::Init(TConfigurationNode& t_node) {
    // Initialization code goes here
}

void CMyController::ControlStep() {
    // This runs every single tick
}

void CMyController::Reset() {
    // Code to execute if you hit 'Reset' in the GUI
}

void CMyController::Destroy() {
    // Cleanup memory here
}

/* 
 * This statement is CRITICAL. It registers the class so ARGoS can 
 * find it via the XML configuration file. The string "my_controller" 
 * is what you will use in your .argos file.
 */
REGISTER_CONTROLLER(CMyController, "swarm_controller")