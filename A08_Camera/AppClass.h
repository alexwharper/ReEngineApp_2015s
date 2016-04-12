/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyPrimitive.h"
#include "CameraManager.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	MyPrimitive* m_pPrimitive = nullptr;
	CameraManager* camMngr = nullptr;
public:
	typedef ReEngAppClass super;
	/*
	USAGE: Constructor
	ARGUMENTS:
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: ---
	*/
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void) { Release(); }
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS: String a_sWindowName -> Name of the window
	OUTPUT: ---
	*/
	virtual void InitWindow(String a_sWindowName) final;
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void) final;
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void) final;
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Display(void) final;
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void) final;
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void) final;
	/*
	USAGE: Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Release(void) final;

	virtual void AppClass::CameraRotate(float a_fSpeed = 0.005f) final
	{
		UINT	MouseX, MouseY;		// Coordinates for the mouse
		UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

									//Initialize the position of the pointer to the middle of the screen
		CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
		CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

		//Calculate the position of the mouse and store it
		POINT pt;
		GetCursorPos(&pt);
		MouseX = pt.x;
		MouseY = pt.y;

		//Calculate the difference in view with the angle
		float fAngleX = 0.0f;
		float fAngleY = 0.0f;
		float fDeltaMouse = 0.0f;
		if (MouseX < CenterX)
		{
			fDeltaMouse = static_cast<float>(CenterX - MouseX);
			fAngleY += fDeltaMouse * a_fSpeed;
		}
		else if (MouseX > CenterX)
		{
			fDeltaMouse = static_cast<float>(MouseX - CenterX);
			fAngleY -= fDeltaMouse * a_fSpeed;
		}

		if (MouseY < CenterY)
		{
			fDeltaMouse = static_cast<float>(CenterY - MouseY);
			fAngleX -= fDeltaMouse * a_fSpeed;
		}
		else if (MouseY > CenterY)
		{
			fDeltaMouse = static_cast<float>(MouseY - CenterY);
			fAngleX += fDeltaMouse * a_fSpeed;
		}
		//Change the Yaw and the Pitch of the camera
		camMngr->ChangeYaw(fAngleY * 3.0f);
		camMngr->ChangePitch(-fAngleX * 3.0f);
		SetCursorPos(CenterX, CenterY);//Position the mouse in the center
	}
};

#endif //__APPLICATION_H_
