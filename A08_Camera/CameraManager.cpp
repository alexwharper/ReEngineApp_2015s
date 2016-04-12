#include "CameraManager.h"

vector3 posVec = vector3(0.0f, 0.0f, 20.0f);
vector3 targVec = vector3(0.0f, 0.0f, 0.0f);
vector3 upVec = vector3(0.0f, 1.0f, 0.0f);

CameraManager::~CameraManager(void)
{
	ReleaseInstance();
}

CameraManager* CameraManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CameraManager();
	}
	return instance;
}

void CameraManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//Get the view matrix
matrix4 CameraManager::GetView(void)
{
	return glm::lookAt(posVec, targVec, upVec);
}

//Get the projection matrix
matrix4 CameraManager::GetProjection(bool bOrthographic)
{
	if (bOrthographic)
	{
		return glm::ortho(0.0f, 100.0f, 100.0f, 0.0f);
	}
	else
	{
		return glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	}
}

//set the position of the camera
void CameraManager::SetPosition(vector3 v3Position)
{
	posVec = v3Position;
}

//set the target of the camera
void CameraManager::SetTarget(vector3 v3Target)
{
	targVec = v3Target;
}

//set the up vector of the camera
void CameraManager::SetUp(vector3 v3Up)
{
	upVec = v3Up;
}

//"zoom" the camera
void CameraManager::MoveForward(float fIncrement)
{
	posVec += vector3(0.0f, 0.0f, fIncrement);
}

//move the camera from side to side
void CameraManager::MoveSideways(float fIncrement)
{
	posVec += vector3(fIncrement, 0.0f, 0.0f);
}

//move the camera up and down
void CameraManager::MoveVertical(float fIncrement)
{
	posVec += vector3(0.0f, fIncrement, 0.0f);
}

//"look" up and down
void CameraManager::ChangePitch(float fIncrement)
{
	//glm::quat rotQuat = glm::quat(vector3(fIncrement, 0.0f, 0.0f));
	//upVec = upVec * glm::mat4_cast(rotQuat);
	//targVec += vector3(0.0f, sin(fIncrement), 0.0f);
}
//rotate the camera
void CameraManager::ChangeRoll(float fIncrement)
{
	//glm::quat rotQuat = glm::quat(vector3(0.0f, 0.0f, fIncrement));
	//upVec = upVec * glm::mat4_cast(rotQuat);
}

//"look" left and right
void CameraManager::ChangeYaw(float fIncrement)
{
	//glm::quat rotQuat = glm::quat(vector3(0.0f, fIncrement, 0.0f));
	//upVec = upVec * glm::mat4_cast(rotQuat);
	//targVec += vector3(sin(fIncrement), 0.0f, 0.0f);
}
