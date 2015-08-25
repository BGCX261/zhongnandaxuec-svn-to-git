#ifndef __AGENT_CALL_H__
#define __AGENT_CALL_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif 
	
#ifdef AGENT_DLLEXPORT_API
#define AGENT_API  __declspec(dllexport) 
#else
#define AGENT_API  __declspec(dllimport)
#endif

// #define AGENT_API
// #define AGEENT_DLLEXPORT_API extern "C"__declspec(dllexport)
	
	
AGENT_API int __stdcall InitAgentCall();
	
	
AGENT_API int __stdcall RelsAgentCall();
	
	
AGENT_API int __stdcall SetFullWorkFlowsInfo(long lWorkFlowID, int iStatus=0, int Priority=0, unsigned short *sDetails=NULL, unsigned short *sFlowName=NULL, long lMaterialID=0, int iSubType=0, unsigned short *sCreator=NULL, unsigned short *sStartTime=NULL, unsigned short *sEndTime=NULL, int IsScheduleTask=0, unsigned short *sScheduleTime=NULL);
	
	
AGENT_API int __stdcall SetFullModuleTasksInfo(long lTaskID, long lWorkFlowID, int iStatus=0, int Priority=0, unsigned short *sDetails=NULL, unsigned short *sModuleName=NULL, unsigned short *sTaskName=NULL, long lMaterialID=0, int iTaskType=0, unsigned short *sCreator=NULL, unsigned short *sStartTime=NULL, unsigned short *sEndTime=NULL, int IsScheduleTask=0, unsigned short *sScheduleTime=NULL);
	
	
AGENT_API int __stdcall SetFullTaskStepInfo(long lStepID, long lTaskID, int iProgress=0, int iStatus=0, int Priority=0, unsigned short *sErrorMessage=NULL, unsigned short *sDetails=NULL, unsigned short *sStepName=NULL, long lDependentStepID=0, unsigned short *sServerName=NULL, unsigned short *sServerIP=NULL, unsigned short *sStartTime=NULL, unsigned short *sEndTime=NULL);
	
	
#ifdef __cplusplus
}
#endif

#endif