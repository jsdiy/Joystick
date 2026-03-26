#include <Arduino.h>
#include "Joystick.hpp"
using Key = Joystick::KeyCode;

Joystick	jstk;

static	constexpr	gpio_num_t
	PinX = GPIO_NUM_1, PinY = GPIO_NUM_0, PinSwP = GPIO_NUM_3,
	PinSwA = GPIO_NUM_8, PinSwB = GPIO_NUM_9, PinSwC = GPIO_NUM_NC;


void	AsyncKeyAction(Joystick::KeyCode keys)
{
	Serial.printf("KeyCode %d Press", keys);
}

void	setup(void)
{
	Serial.begin(115200);
	delay(1000);
	jstk.Initialize(PinX, PinY, true, true, 3, 8, PinSwP, PinSwA, PinSwB, PinSwC);
	jstk.OnPressCb().Add(Key::P, AsyncKeyAction(Key::P));
}

void	loop(void)
{
	bool isUpdated = jstk.CheckKeyState();
	if (!isUpdated) { return; }

	if (jstk.OnKeyPress(Key::A)) { Serial.println("Key::A - Press"); }
	if (jstk.OnKeyHolding(Key::Up | Key::Left)) { Serial.println("Key::Up+Left - Holding"); }
}
