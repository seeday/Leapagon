#include <Windows.h>
#include <iostream>
#include "./Leap.h"

const float HAND_ANGLE = .3f;

INPUT ld, lu, rd, ru;

int main() {
	ld.type = INPUT_MOUSE;
	ld.mi.mouseData = 0;
	ld.mi.time = 0;
	ld.mi.dwExtraInfo = 0;
	ld.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	ld.mi.dx = 0;
	ld.mi.dy = 0;
	//leftUp
	lu.type = INPUT_MOUSE;
	lu.mi.mouseData = 0;
	lu.mi.time = 0;
	lu.mi.dwExtraInfo = 0;
	lu.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	lu.mi.dx = 0;
	lu.mi.dy = 0;
	//rightDown
	rd.type = INPUT_MOUSE;
	rd.mi.mouseData = 0;
	rd.mi.time = 0;
	rd.mi.dwExtraInfo = 0;
	rd.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	rd.mi.dx = 0;
	rd.mi.dy = 0;
	//rightUp
	ru.type = INPUT_MOUSE;
	ru.mi.mouseData = 0;
	ru.mi.time = 0;
	ru.mi.dwExtraInfo = 0;
	ru.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	ru.mi.dx = 0;
	ru.mi.dy = 0;

	HWND hexagon = FindWindow(L"GLUT", L"Super Hexagon");
	if (hexagon == NULL) {
		std::cout << "Could not find super hexagon window." << std::endl;
		std::cin.get();
		return 1;
	}

	ShowWindow(hexagon, SW_MAXIMIZE);
	SetForegroundWindow(hexagon);

	Leap::Controller cont = Leap::Controller();
	std::cout << cont.devices()[0].isValid() << std::endl;
	while (!cont.isConnected()) {
		std::cout << "Controller not connected." << std::endl;
	}
	std::cout << "Controller connected." << std::endl;
	cont.setPolicyFlags(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	int_fast64_t lastFrameID = 0;
	Leap::Frame frame;
	Leap::Hand hand;

	while (cont.isConnected()) {
		frame = cont.frame();

		/*//Debugging info
		std::cout << "Frame id: " << frame.id()
		<< ", timestamp: " << frame.timestamp()
		<< ", hands: " << frame.hands().count()
		<< ", fingers: " << frame.fingers().count()
		<< ", tools: " << frame.tools().count() << std::endl;*/


		if (frame.id() == lastFrameID || !frame.isValid()) continue;
		lastFrameID = frame.id();

		hand = frame.hands()[0];
		if (!hand.isValid()) {
			std::cout << "No valid hands in view" << std::endl;
			continue;
		}

		float angle = hand.palmNormal().roll();

		if (angle > HAND_ANGLE) {
			SendInput(1, &ru, sizeof(INPUT));
			SendInput(1, &ld, sizeof(INPUT));
		} else if (angle < -HAND_ANGLE) {
			SendInput(1, &lu, sizeof(INPUT));
			SendInput(1, &rd, sizeof(INPUT));
		} else {
			SendInput(1, &lu, sizeof(INPUT));
			SendInput(1, &ru, sizeof(INPUT));
		}

		std::cout << "Hand angle: " << angle << std::endl;
	}
	std::cout << "Exited." << std::endl;
	std::cin.get();
	return 0;
}
