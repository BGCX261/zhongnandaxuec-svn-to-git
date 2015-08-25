#include <stdafx.h>

#include "lib.h"

int __stdcall InitAgentCall()
{
	return 0;
}


int __stdcall RelsAgentCall()
{
	return 0;
}


int __stdcall SetFullWorkFlowsInfo(long lWorkFlowID, int iStatus, int Priority, unsigned short *sDetails, unsigned short *sFlowName, long lMaterialID, int iSubType, unsigned short *sCreator, unsigned short *sStartTime, unsigned short *sEndTime, int IsScheduleTask, unsigned short *sScheduleTime)
{
	printf("long lWorkFlowID=%ld, int iStatus=%d, int Priority=%d, unsigned short *sDetails=%d, unsigned short *sFlowName=%d, long lMaterialID=%ld, int iSubType=%d, unsigned short *sCreator=%d, unsigned short *sStartTime=%d, unsigned short *sEndTime=%d, int IsScheduleTask=%d, unsigned short *sScheduleTime=%d",
		lWorkFlowID, iStatus, Priority, sDetails, sFlowName, lMaterialID, iSubType, sCreator, sStartTime, sEndTime, IsScheduleTask, sScheduleTime);
	return 0;
}

int __stdcall SetFullModuleTasksInfo(long lTaskID, long lWorkFlowID, int iStatus, int Priority, unsigned short *sDetails, unsigned short *sModuleName, unsigned short *sTaskName, long lMaterialID, int iTaskType, unsigned short *sCreator, unsigned short *sStartTime, unsigned short *sEndTime, int IsScheduleTask, unsigned short *sScheduleTime)
{
	return 0;
}


int __stdcall SetFullTaskStepInfo(long lStepID, long lTaskID, int iProgress, int iStatus, int Priority, unsigned short *sErrorMessage, unsigned short *sDetails, unsigned short *sStepName, long lDependentStepID, unsigned short *sServerName, unsigned short *sServerIP, unsigned short *sStartTime, unsigned short *sEndTime)
{
	printf("%d", lTaskID);
	return 0;
}