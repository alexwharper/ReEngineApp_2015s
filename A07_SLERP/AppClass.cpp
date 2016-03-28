#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - YOUR USER NAME GOES HERE"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	float fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//------------------------------------------Student Code--------------------------------------------------
	//find orbit numbers
	int nEarthOrbits = floor(fRunTime / (fEarthHalfOrbTime * 2));
	int nEarthRevolutions = floor(fRunTime / (fEarthHalfRevTime * 2));
	int nMoonOrbits = floor(fRunTime / (fMoonHalfOrbTime * 2));
	
	//make matrices
	matrix4 sunMatrix = IDENTITY_M4;
	matrix4 earthMatrix = IDENTITY_M4;
	matrix4 moonMatrix = IDENTITY_M4;

	//orbit Earth
	glm::quat startRot = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat halfRot = glm::quat(vector3(0.0f, 180.0f, 0.0f));
	
	float rotPercent = MapValue(static_cast<float>(fRunTime), 0.0f, fEarthHalfOrbTime, 0.0f, 1.0f);
	glm::quat rotMat = glm::mix(startRot, halfRot, rotPercent);
	earthMatrix *= glm::mat4_cast(rotMat);
	earthMatrix *= glm::translate(11.0f, 0.0f, 0.0f);

	//rotate Earth
	rotPercent = MapValue(static_cast<float>(fRunTime), 0.0f, fEarthHalfRevTime, 0.0f, 1.0f);
	rotMat = glm::mix(startRot, halfRot, rotPercent);
	earthMatrix *= glm::mat4_cast(rotMat);

	//orbit Moon
	moonMatrix *= earthMatrix;
	rotPercent = MapValue(static_cast<float>(fRunTime), 0.0f, fMoonHalfOrbTime, 0.0f, 1.0f);
	rotMat = glm::mix(startRot, halfRot, rotPercent);
	moonMatrix *= glm::mat4_cast(rotMat);
	moonMatrix *= glm::translate(2.0f, 0.0f, 0.0f);

	//scale matrices
	sunMatrix *= glm::scale(5.936f, 5.936f, 5.936f);
	earthMatrix *= glm::scale(0.524f, 0.524f, 0.524f);
	moonMatrix *= glm::scale(0.524f, 0.524f, 0.524f);
	moonMatrix *= glm::scale(0.27f, 0.27f, 0.27f);
	//--------------------------------------------------------------------------------------------------------

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(sunMatrix, "Sun");
	m_pMeshMngr->SetModelMatrix(earthMatrix, "Earth");
	m_pMeshMngr->SetModelMatrix(moonMatrix, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}