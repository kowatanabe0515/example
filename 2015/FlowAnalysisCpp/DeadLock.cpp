#include "Shapes.hpp"

#include <windows.h>


#define MAX_OBJECTS 100
#define STEP 20

CRITICAL_SECTION changePositionSection;

Circle ring(Point(0,0), 100);
Shape *participants[MAX_OBJECTS];
int participantsCount;
int exitGame;

DWORD WINAPI GameLogic_Thread(void*)
{
	// Implementation of function GameLogic_Thread()
	return 0;
}

DWORD WINAPI Controller_Thread(void*)
{
	// Implementation of function Controller_Thread()
	return 0;
}

void assertion(int condition, const char* message)
{
	if (!condition) {
		throw message;
	}
}

namespace Physics
{
	Point *velocityArray[MAX_OBJECTS];
	
	DWORD WINAPI Physics_Thread(void*)
	{
		while (!exitGame) {
			for(int i = 0; i < participantsCount; i++) {
				EnterCriticalSection(&changePositionSection);
				Point& position = participants[i]->getPosition();
				position.translate(*velocityArray[i]);
				assertion(ring.contains(position), "Participant is out of ring");
												// Deadlock: when assertion fails (throws exception)
												//     which cause game freeze
				LeaveCriticalSection(&changePositionSection);
			}
			Sleep(STEP);
		}
		return 0;
	}
}

namespace Render
{
	Point *currentCameraVelocity;
	
	void draw(const Shape *object)
	{
		// Implementation of function draw()
	}
	
	DWORD WINAPI Render_Thread(void*)
	{
		while (!exitGame) {
			EnterCriticalSection(&changePositionSection);
			ring.getPosition().translate(*currentCameraVelocity);
			LeaveCriticalSection(&changePositionSection);
			
			for(int i = 0; i < participantsCount; i++) {
				EnterCriticalSection(&changePositionSection);
				participants[i]->getPosition().translate(*currentCameraVelocity);
				LeaveCriticalSection(&changePositionSection);
				draw(participants[i]);
			}
			Sleep(STEP);
		}
		return 0;
	}
}

void runGameThreads()
{
	exitGame = 0;
	HANDLE handle1, handle2, handle3, handle4;
	DWORD id1, id2, id3, id4;
	handle1 = CreateThread (0, 0, &GameLogic_Thread, 0, CREATE_SUSPENDED, &id1);
	handle2 = CreateThread (0, 0, &Controller_Thread, 0, CREATE_SUSPENDED, &id2);
	handle3 = CreateThread (0, 0, &Physics::Physics_Thread, 0, CREATE_SUSPENDED, &id3);
	handle4 = CreateThread (0, 0, &Render::Render_Thread, 0, CREATE_SUSPENDED, &id4);
	
	WaitForSingleObject (handle1, INFINITE);
	WaitForSingleObject (handle2, INFINITE);
	WaitForSingleObject (handle3, INFINITE);
	WaitForSingleObject (handle4, INFINITE);
}
