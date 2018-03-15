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

// digital pins
int wheelEnableRight = 10;
int wheelEnableLeft = 11;
int wheelDORRight = 12;
int wheelDORLeft = 13;
int led = 9;

bool hasLoad = false;
int numberLoad = 0;
int numberBoth = 0;

// analog pins
int ldrA = 0;
int sensor1 = 1;
int sensor2 = 2;
int sensor3 = 3;
int sensor4 = 4;

// used as a event. houd een doubele count tegen
bool trigger = false;
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
	// hier is het einde bereikt want allebij de lijnen zijn gedetecteerd

	if (hasLoad) {
		// als de robot de lading aan het lossen is moet hij voorruit
		if (getSensor1() && getSensor2()) {

			if (numberBoth % 2 == 0 && numberBoth != 0) {
				stop();
				dropLoad();
				hasLoad = false;
			}

			if(numberBoth % 2 == 1) {
				if (numberLoad % 2 == 1) {
					turnRight();
				}
				else {
					turnLeft();
				}
				numberLoad++;
			}
			if (!trigger) {
				numberBoth++;
				trigger = true;
			}
			// hier moet de logica voor het lossen
		}
		// hier moeten we naar rechts want de linker sensor heeft een lijn gedetecteerd.
		else if (getSensor1() && !getSensor2()) {
			right();
			trigger = false;
		}
		else if (!getSensor1() && getSensor2()) {
			left();
			trigger = false;
		}
		else if (!getSensor1() && !getSensor2()) {
			forward();
			trigger = false;
		}
	}
	else {

		if (getSensor3() && getSensor4()) {

			if (numberBoth % 2 == 0 && numberBoth != 0) {


				stop();

				setLed(true);
				// wachten totdat hij geen ldr meer heeft.
				while (getLdr()) {}

				hasLoad = true;
			}
			if(!trigger) {
				numberBoth++;
				trigger = true;
			}
			// hier moet de logica voor het lossen
		}
		// hier moeten we naar rechts want de linker sensor heeft een lijn gedetecteerd.
		else if (getSensor3() && !getSensor4()) {
			left();
			trigger = false;
		}
		else if (!getSensor3() && getSensor4()) {
			right();
			trigger = false;
		}
		else if (!getSensor3() && !getSensor4()) {
			backward();
			trigger = false;
		}
	}
	// als de robot de lading heeft gelost, dan moet hij achteruit rijden.
}



/*
* returns true if the sensor detects a white lite. else false
*/
bool statusSensor(int sensor) {
	return sensor > 400;
}

bool getSensor1()
{
	return statusSensor(sensor1);
}

bool getSensor2()
{
	return statusSensor(sensor2);
}

bool getSensor3()
{
	return statusSensor(sensor3);
}

bool getSensor4()
{
	return statusSensor(sensor4);
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
// returns between 0 - 1023
int getLdr() {
	return analogRead(ldrA);
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
void stop()
{
	setLeftWheel(false, speedOff);
	setRightWheel(false, speedOff);
}
void dropLoad()
{
	setLeftWheel(true, speedSlow);
	setRightWheel(true, speedSlow);
	delay(600);

	setLeftWheel(false, speedSlow);
	setRightWheel(false, speedSlow);
	delay(600);
	setLeftWheel(false, speedOff);
	setRightWheel(false, speedOff);
}

void turnRight() {
	right();
	delay(300);
	stop();
}
void turnLeft() 
{
	left();
	delay(300);
	stop();
}

