#ifndef DATA_HANDLE_H
#define DATA_HANDLE_H


#include <argos3/core/simulator/loop_functions.h>
#include <fstream>

using namespace argos;

class CDataHandle : public CLoopFunctions {
public:
    CDataHandle();
    virtual ~CDataHandle();  
    virtual void Init(TConfigurationNode& t_node);  
    virtual void PostStep();
    virtual void Destroy();
    
private:
    std::ofstream outputCSV;

};


#endif