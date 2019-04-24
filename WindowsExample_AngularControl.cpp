//General libraries
//#include "pch.h"
#include <string>
#include <iostream>

//JACO librabies
#include <Windows.h>
#include "CommunicationLayerWindows.h"
#include "CommandLayer.h"
#include <conio.h>
#include "KinovaTypes.h"


using namespace std;


//A handle to the API.
HINSTANCE commandLayer_handle;

//Function pointers to the functions we need
int(*MyInitAPI)();
int(*MyCloseAPI)();
int(*MySendBasicTrajectory)(TrajectoryPoint command);
int(*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
int(*MySetActiveDevice)(KinovaDevice device);
int(*MyMoveHome)();
int(*MyInitFingers)();
int(*MyGetCartesianCommand)(CartesianPosition &);




CartesianPosition currentCommand;

int programResult = 0;



bool camInitialised = 0;
//Function used for detecting an object of interest, and extracting distance and position of center pixel
int objectDetection()
{
	return 47;
}



int gripperValue = 1;
void manualMove(int buttonValue) {
	int(*MyGetCartesianCommand)(CartesianPosition &);
	MyGetCartesianCommand = (int(*)(CartesianPosition &)) GetProcAddress(commandLayer_handle, "GetCartesianCommand");
	TrajectoryPoint pointToSend;
	pointToSend.InitStruct();

	switch (buttonValue) {
	case 1: //Open/close gripper
		if (gripperValue == 0) {
			//We get the actual angular command of the robot.
			MyGetCartesianCommand(currentCommand);

			//Determine which direction the EE should move in cartesian space
			pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X;
			pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y;
			pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z;
			pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
			pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
			pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

			pointToSend.Position.Fingers.Finger1 = 6000;
			pointToSend.Position.Fingers.Finger2 = 6000;


			//Send this command to the JACO
			MySendBasicTrajectory(pointToSend);
			Sleep(500);
			

			//ControlFunctionalityTypeEnum::CF_CloseHandTwoFingers;
			//Sleep(500);
			gripperValue = 1;
			cout << "Close grip" << endl;
			break;
		}
		else {
			//We get the actual angular command of the robot.
			MyGetCartesianCommand(currentCommand);

			//Determine which direction the EE should move in cartesian space
			pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X;
			pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y;
			pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z;
			pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
			pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
			pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

			pointToSend.Position.Fingers.Finger1 = 1;
			pointToSend.Position.Fingers.Finger2 = 1;

			//Send this command to the JACO
			MySendBasicTrajectory(pointToSend);
			Sleep(500);
			

			//ControlFunctionalityTypeEnum::CF_OpenHandTwoFingers;
			//Sleep(500);
			gripperValue = 0;
			cout << "Open grip" << endl;
			break;
		}
		break;
	case 2: //Upward
		//We get the actual angular command of the robot.
		MyGetCartesianCommand(currentCommand);

		//Determine which direction the EE should move in cartesian space
		pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X;
		pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y;
		pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z + 0.1f;
		pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
		pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
		pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

		//Send this command to the JACO
		MySendBasicTrajectory(pointToSend);
		Sleep(100);
		break;
	case 3: //Downward
		//We get the actual angular command of the robot.
		MyGetCartesianCommand(currentCommand);

		//Determine which direction the EE should move in cartesian space
		pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X;
		pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y;
		pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z - 0.1f;
		pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
		pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
		pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

		//Send this command to the JACO
		MySendBasicTrajectory(pointToSend);
		Sleep(100);
		break;
	case 4: //Extend
		//We get the actual angular command of the robot.
		MyGetCartesianCommand(currentCommand);

		//Determine which direction the EE should move in cartesian space
		pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X + 0.1f;
		pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y;
		pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z;
		pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
		pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
		pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

		//Send this command to the JACO
		MySendBasicTrajectory(pointToSend);
		Sleep(100);
		break;
	case 5: //Retract
		//We get the actual angular command of the robot.
		MyGetCartesianCommand(currentCommand);

		//Determine which direction the EE should move in cartesian space
		pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X - 0.1f;
		pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y;
		pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z;
		pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
		pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
		pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

		//Send this command to the JACO
		MySendBasicTrajectory(pointToSend);
		Sleep(100);
		break;
	case 6: //rotateLeft
		//We get the actual angular command of the robot.
		MyGetCartesianCommand(currentCommand);

		//Determine which direction the EE should move in cartesian space
		pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X;
		pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y + 0.1f;
		pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z;
		pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
		pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
		pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

		//Send this command to the JACO
		MySendBasicTrajectory(pointToSend);
		Sleep(100);
		break;
	case 7: //rotateRight
		//We get the actual angular command of the robot.
		MyGetCartesianCommand(currentCommand);

		//Determine which direction the EE should move in cartesian space
		pointToSend.Position.CartesianPosition.X = currentCommand.Coordinates.X;
		pointToSend.Position.CartesianPosition.Y = currentCommand.Coordinates.Y - 0.1f;
		pointToSend.Position.CartesianPosition.Z = currentCommand.Coordinates.Z;
		pointToSend.Position.CartesianPosition.ThetaX = currentCommand.Coordinates.ThetaX;
		pointToSend.Position.CartesianPosition.ThetaY = currentCommand.Coordinates.ThetaY;
		pointToSend.Position.CartesianPosition.ThetaZ = currentCommand.Coordinates.ThetaZ;

		//Send this command to the JACO
		MySendBasicTrajectory(pointToSend);
		Sleep(100);
		break;
	}
}



void calculatePosition() {

}



void grapObject() {

}



//Function used for interpreting commands send from the Itongue
void userInput()
{
	int buttonValue;
	short keyPress = GetAsyncKeyState(0x41);

	// Test high bit - if set, key was down when GetAsyncKeyState was called.
	if ((1 << 15) & keyPress)
	{
		buttonValue = 1;
	}
	else {
		buttonValue = 0;
	}
	
	
	//**INSERT ITONGUE DETECTION OF KEYSTROKES**

	if (buttonValue != 0) {
		if (buttonValue <= 7) {
			manualMove(buttonValue);
		}
		else {
			calculatePosition();
		}
	}

	objectDetection();

}



int main(int argc, char* argv[])
{
	//We load the API.
	commandLayer_handle = LoadLibrary(L"CommandLayerWindows.dll");

	//We load the functions from the library (Under Windows, use GetProcAddress)
	MyInitAPI = (int(*)()) GetProcAddress(commandLayer_handle, "InitAPI");
	MyCloseAPI = (int(*)()) GetProcAddress(commandLayer_handle, "CloseAPI");
	MyMoveHome = (int(*)()) GetProcAddress(commandLayer_handle, "MoveHome");
	MyInitFingers = (int(*)()) GetProcAddress(commandLayer_handle, "InitFingers");
	MyGetDevices = (int(*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) GetProcAddress(commandLayer_handle, "GetDevices");
	MySetActiveDevice = (int(*)(KinovaDevice devices)) GetProcAddress(commandLayer_handle, "SetActiveDevice");
	MySendBasicTrajectory = (int(*)(TrajectoryPoint)) GetProcAddress(commandLayer_handle, "SendBasicTrajectory");
	MyGetCartesianCommand = (int(*)(CartesianPosition &)) GetProcAddress(commandLayer_handle, "GetCartesianCommand");

	//Verify that all functions has been loaded correctly
	if ((MyInitAPI == NULL) || (MyCloseAPI == NULL) || (MySendBasicTrajectory == NULL) ||
		(MyGetDevices == NULL) || (MySetActiveDevice == NULL) || (MyGetCartesianCommand == NULL) ||
		(MyMoveHome == NULL) || (MyInitFingers == NULL))

	{
		cout << "* * *  E R R O R   D U R I N G   I N I T I A L I Z A T I O N  * * *" << endl;
		return 0;
	}

	cout << "I N I T I A L I Z A T I O N   C O M P L E T E D" << endl << endl;

	int result = (*MyInitAPI)();

	cout << "Initialization's result :" << result << endl;

	KinovaDevice list[MAX_KINOVA_DEVICE];

	int devicesCount = MyGetDevices(list, result);

	for (int i = 0; i < devicesCount; i++)
	{
		cout << "Found a robot on the USB bus (" << list[i].SerialNumber << ")" << endl;

		//Setting the current device as the active device.
		MySetActiveDevice(list[i]);

		cout << "Send the robot to HOME position" << endl;
		MyMoveHome();

		cout << "Initializing the fingers" << endl;
		MyInitFingers();

		TrajectoryPoint pointToSend;
		pointToSend.InitStruct();

		//We specify that this point will be used an angular(joint by joint) velocity vector.
		pointToSend.Position.Type = CARTESIAN_POSITION;
	}


	for (;;)
	{
		objectDetection();
		userInput();

	}

	FreeLibrary(commandLayer_handle);

	cout << endl << "C L O S I N G   A P I" << endl;
	result = (*MyCloseAPI)();

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}