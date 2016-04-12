#ifndef _CameraManager_
#define _CameraManager_

#include "RE\ReEng.h"

class CameraManager
{
	
	vector3 posVec, targVec, upVec;

private:
	//CameraManager(void);
	//CameraManager(CameraManager const& other);
	~CameraManager(void);

public:
	static CameraManager* instance;
	static CameraManager* GetInstance();
	static void ReleaseInstance();

	matrix4 GetView(void);
	matrix4 GetProjection(bool bOrthographic);

	//changing view matrix
	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);
	void SetUp(vector3 v3Up);

	//movement controls
	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);
	void ChangePitch(float fIncrement);
	void ChangeRoll(float fIncrement);
	void ChangeYaw(float fIncrement);
};
#endif //_CameraManager_
