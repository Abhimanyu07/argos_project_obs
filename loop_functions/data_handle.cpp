#include "data_handle.h"
#include "../controllers/stop_and_go.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>    



CDataHandle::CDataHandle(){} 
CDataHandle::~CDataHandle(){}


void CDataHandle::Init(TConfigurationNode& t_node) {
    outputCSV.open("stop_and_go_data.csv", std::ios_base::trunc); 
    outputCSV << "Tick,StoppedRobots,AvgDistance\n"; 
}

void CDataHandle::PostStep(){
    UInt32 unTick = GetSpace().GetSimulationClock();
    UInt32 unStoppedCounts = 0;
    std::vector<CVector3> positions;   

    CSpace::TMapPerType& footBots = GetSpace().GetEntitiesByType("foot-bot");
    for (auto i = footBots.begin(); i!=footBots.end(); ++i){
        CFootBotEntity* footBot = any_cast<CFootBotEntity*>(i->second);
        CStopAndGo& controller = dynamic_cast<CStopAndGo&>(footBot->GetControllableEntity().GetController());
        if(controller.isRobotStopped()){
            unStoppedCounts++;
        }
        CVector3 pos = footBot->GetEmbodiedEntity().GetOriginAnchor().Position;
        positions.push_back(pos);
    }

    Real fAvgDistance = 0.0;
    Real fTotalDistance = 0.0;
    UInt32 unPairs = 0;

    for (size_t i = 0; i<positions.size(); ++i){
        for(size_t j = i+1; j<positions.size(); ++j){
            fTotalDistance += Distance(positions[i], positions[j]);
            unPairs++;
        }
    }
    if (unPairs > 0){
        fAvgDistance = fTotalDistance / unPairs; 
    }

    outputCSV << unTick << "," << unStoppedCounts << "," << fAvgDistance << "\n";
}




void CDataHandle::Destroy(){
    outputCSV.close();  
}



REGISTER_LOOP_FUNCTIONS(CDataHandle, "data_handle_loop_function")