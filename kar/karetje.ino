/*
 Name:		karetje.ino
 Created:	3/14/2018 9:53:40 AM
 Author:	stijn
*/

// the setup function runs once when you press reset or power the board

// wielen worden gedefineerd vannuit achteraanzicht ( waar het wieletje zit )
// #directionOfRotation == DOR
// een variable van Stijn, dus niet van Leon.
int speedSanic = 254;

int speedFast = 220;
int speedRegular = 150;
int speedSlow = 50;
int speedUltraSlow = 15;
int speedOff = 0;


int wheelEnableRight = 10;
int wheelEnableLeft = 11;
int wheelDORRight = 12;
int wheelDORLeft = 13;
int led = 9;

// can only be called inside the setup function.
void setupPins() {
	for (int i = 9; i < 13; i++) {
		pinMode(i, OUTPUT);
	}

	for (int i = 0; i < 4; i++) {
		pinMode('A' + i, OUTPUT);
	}
}


void setup() {
	setupPins();
}

// the loop function runs over and over again until power down or reset
void loop() {

}


void forward() {
	setLeftWheel(true, speedRegular);
	setRightWheel(true, speedRegular);
}

void right() {
	setRightWheel(true, speedFast);
	setLeftWheel(false, speedOff);
}

void left() {
	setLeftWheel(true, speedFast);
	setRightWheel(false, speedOff);
}
void backward() {
	setLeftWheel(false, speedRegular);
	setRightWheel(false, speedRegular);
}
// status moet de voorruit of achtertuit voorstellen
void setLeftWheel(boolean status, int speed = 0) {
	if (status) {
		analogWrite(wheelEnableLeft, speed);
		digitalWrite(wheelDORLeft, HIGH);
	}
	else {
		analogWrite(wheelEnableLeft, speed);
		digitalWrite(wheelDORLeft, LOW);
	}
}
// status moet de voorruit of achtertuit voorstellen
void setRightWheel(boolean status, int speed) {
	if (status) {
		analogWrite(wheelEnableRight, speed);
		digitalWrite(wheelDORRight, HIGH);
	}
	else {
		analogWrite(wheelEnableRight, speed);
		digitalWrite(wheelDORRight, LOW);
	}
}
void setLed(boolean enabled) {
	if (enabled)
	{
		digitalWrite(led, HIGH);
	}
	else {
		digitalWrite(led, LOW);
	}
}





