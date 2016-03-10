#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	//--------------------------Student Code---------------------------------
	//add all stops
	stops.push_back(vector3(-4.0f, -2.0f, 5.0f));
	stops.push_back(vector3(1.0f, -2.0f, 5.0f));
	stops.push_back(vector3(-3.0f, -1.0f, 3.0f));
	stops.push_back(vector3(2.0f, -1.0f, 3.0f));
	stops.push_back(vector3(-2.0f, 0.0f, 0.0f));
	stops.push_back(vector3(3.0f, 0.0f, 0.0f));
	stops.push_back(vector3(-1.0f, 1.0f, -3.0f));
	stops.push_back(vector3(4.0f, 1.0f, -3.0f));
	stops.push_back(vector3(0.0f, 2.0f, -5.0f));
	stops.push_back(vector3(5.0f, 2.0f, -5.0f));
	stops.push_back(vector3(1.0f, 3.0f, -5.0f));
	//initialize sphere and m4_sphere
	sphere = new PrimitiveClass();
	m4_sphere = IDENTITY_M4;
	//initialize lastStop at 0
	lastStop = 0;
	//initialize m4_dude to the identity
	m4_dude = IDENTITY_M4;
	//initialize distanceTraveled to 0
	distanceTraveled = 0.0f;
	//-----------------------------------------------------------------------

	//set the first fDuration to be between the first two stops
	fDuration = glm::distance(stops[0], stops[1]);
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	m4_dude = glm::translate(stops[lastStop]); //set the dude to his most recent stop
	
	//increment distanceTraveled with the percent of fDuration that has passed
	//if it goes past 1, the point has been passed and it should be set to 1
	distanceTraveled += fTimeSpan / fDuration;
	if (distanceTraveled > 1)
	{
		distanceTraveled = 1;
	}

	//do some lerp
	vector3 travelVector;
	if (lastStop == stops.size() - 1)
	{
		travelVector = glm::lerp(stops[lastStop], stops[0], distanceTraveled);
	}
	else
	{
		travelVector = glm::lerp(stops[lastStop], stops[lastStop + 1], distanceTraveled);
	}

	//translate the dude
	m4_dude = glm::translate(travelVector);

	//if distanceTraveled is 1, reset it to 0, increment lastStop, and recalculate fDuration
	if (distanceTraveled == 1)
	{
		distanceTraveled = 0;
		if (lastStop == stops.size() - 1)
		{
			lastStop = 0;
		}
		else
		{
			lastStop++;
		}
		if (lastStop == stops.size() - 1)
		{
			fDuration = glm::distance(stops[lastStop], stops[0]);
		}
		else
		{
			fDuration = glm::distance(stops[lastStop], stops[lastStop + 1]);
		}
	}

	m_pMeshMngr->SetModelMatrix(m4_dude, "WallEye");
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
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

	//---------------------Student Code-------------------------
	//draw spheres at each stop
	sphere->GenerateSphere(0.1f, 5, RERED);
	for (int x = 0; x < stops.size(); x++)
	{
		m4_sphere = IDENTITY_M4;
		m4_sphere = glm::translate(stops[x]);
		sphere->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m4_sphere);
	}
	//----------------------------------------------------------

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	SafeDelete(sphere);
}