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
int speedSlow = 70;
int speedUltraSlow = 40;
int speedOff = 0;

// digital pins
int wheelEnableRight = 10;
int wheelEnableLeft = 11;
int wheelDORRight = 12;
int wheelDORLeft = 13;
int led = 9;
int button = 8;

bool hasLoad = true;
int numberLoad = 0;
int numberBoth = 0;

// analog pins
int ldrA = 0;
int sensor1 = 1;
int sensor2 = 2;
int sensor3 = 3;
int sensor4 = 4;

// check if sensor has black or white underground.
// lower than given value is white,
// higher tha given value is black;
int whiteOrBlackSwitch = 400;
// these timers are used to correct the sensors, we weren't sure if the infrared singals were lost or not. so we used a 100MS delay to compare both statuses
bool previousStatus1 = false;
long previousMillis1 = 0;        // will store last time Sensor1 was updated

bool previousStatus2 = false;
long previousMillis2 = 0;        // will store last time Sensor2 was updated

bool previousStatus3 = false;
long previousMillis3 = 0;        // will store last time Sensor3 was updated

bool previousStatus4 = false;
long previousMillis4 = 0;        // will store last time Sensor4 was updated

long interval = 100;            // interval at which to blink ( miliseconds )



// reset button
bool start = false;

// used as a event. houd een doubele count tegen
bool trigger = false;




// can only be called inside the setup function.
void setupPins() {

	for (int i = 9; i < 13; i++) {
		pinMode(i, OUTPUT);
	}

	pinMode(button, INPUT);


	for (int i = 0; i < 4; i++) {
		pinMode('A' + i, INPUT);
	}


}


void setup() {
	Serial.begin(9600);
	setupPins();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// hier is het einde bereikt want allebij de lijnen zijn gedetecteerd


	// als de knop is ingedrukt en losgelaten
	if (digitalRead(button) == HIGH) {

		delay(500);

		start = !start;

	}

	if (start) {
		// als we lading hebben gaan we vooruit.
		//if (hasLoad) {
			// als de robot de lading aan het lossen is moet hij voorruit
		if (getSensor1() && getSensor2()) {

			Serial.print("Stop");
			stop();

			//if (numberBoth % 2 == 0 && numberBoth != 0) {
			//	dropLoad();
			//	hasLoad = false;
			//}

			//if (numberBoth % 2 == 1) {
			//	if (numberLoad % 2 == 1) {
			//		turnRight();
			//	}
			//	else {
			//		turnLeft();
			//	}
			//	numberLoad++;
			//}
			//if (!trigger) {
			//	numberBoth++;
			//	trigger = true;
			//}
		}
		// hier moeten we naar rechts want de linker sensor heeft een lijn gedetecteerd.
		else if (getSensor1() && !getSensor2()) {
			right();
			Serial.print("Right");
			trigger = false;
		}
		else if (!getSensor1() && getSensor2()) {
			left();
			Serial.print("Left");
			trigger = false;
		}
		else if (!getSensor1() && !getSensor2()) {
			forward();
			Serial.print("Forward");
			trigger = false;
		}
	}
	// als we geen lading hebben gaan we achteruit.
//	else {

//		if (getSensor3() && getSensor4()) {

//			if (numberBoth % 2 == 0 && numberBoth != 0) {


//				stop();

//				setLed(true);
//				// wachten totdat hij geen ldr meer heeft.
//				while (getLdr() > 800) {}
//				setLed(false);
//				hasLoad = true;
//			}
//			if (!trigger) {
//				numberBoth++;
//				trigger = true;
//			}
//		}
//		// hier moeten we naar rechts want de linker sensor heeft een lijn gedetecteerd.
//		else if (getSensor3() && !getSensor4()) {
//			setLeftWheel(false, speedSlow);
//			setRightWheel(false, speedRegular);
//			trigger = false;
//		}
//		else if (!getSensor3() && getSensor4()) {
//			setLeftWheel(false, speedRegular);
//			setRightWheel(false, speedSlow);
//			trigger = false;
//		}
//		else if (!getSensor3() && !getSensor4()) {
//			backward();
//			trigger = false;
//		}
//	}
//}
	else {
		stop();
	}
	// als de robot de lading heeft gelost, dan moet hij achteruit rijden.


}



bool getSensor1()
{
	unsigned long currentMillis = millis();
	bool currentStatus = (sensor1 > whiteOrBlackSwitch);
	/**
	* if the current millis minus the previous millis is higher than the setten interval.
	*
	* else if previous millis en status not equals null.
	*
	*/
	if (currentMillis - previousMillis1 > interval) {
		/**
		* check if the current state is the same as the previous one.
		* if it is the same the return that status.
		*
		* else return the previous status
		*/
		bool returnstatus = false;
		if (currentStatus == previousStatus1) {
			returnstatus = currentStatus;
		}
		else {
			returnstatus = previousStatus1;
		}
		previousMillis1 = currentMillis;
		previousStatus1 = currentStatus;
		return returnstatus;
	}
	else if (previousMillis1 == NULL || previousStatus1 == NULL) {
		previousMillis1 = currentMillis;
		previousStatus1 = currentStatus;
	}
	return previousStatus1;
}

bool getSensor2()
{
	unsigned long currentMillis = millis();
	bool currentStatus = (sensor2 > whiteOrBlackSwitch);
	/**
	* if the current millis minus the previous millis is higher than the setten interval.
	*
	* else if previous millis en status not equals null.
	*
	*/
	if (currentMillis - previousMillis2 > interval) {
		/**
		* check if the current state is the same as the previous one.
		* if it is the same the return that status.
		*
		* else return the previous status
		*/
		bool returnstatus = false;
		if (currentStatus == previousStatus2) {
			returnstatus = currentStatus;
		}
		else {
			returnstatus = previousStatus2;
		}
		previousMillis2 = currentMillis;
		previousStatus2 = currentStatus;
		return returnstatus;
	}
	else if (previousMillis2 == NULL || previousStatus2 == NULL) {
		previousMillis2 = currentMillis;
		previousStatus2 = currentStatus;
	}
	return previousStatus2;
}

bool getSensor3()
{
	unsigned long currentMillis = millis();
	bool currentStatus = (sensor3 > whiteOrBlackSwitch);
	/**
	* if the current millis minus the previous millis is higher than the setten interval.
	*
	* else if previous millis en status not equals null.
	*
	*/
	if (currentMillis - previousMillis3 > interval) {
		/**
		* check if the current state is the same as the previous one.
		* if it is the same the return that status.
		*
		* else return the previous status
		*/
		bool returnstatus = false;
		if (currentStatus == previousStatus3) {
			returnstatus = currentStatus;
		}
		else {
			returnstatus = previousStatus3;
		}
		previousMillis3 = currentMillis;
		previousStatus3 = currentStatus;
		return returnstatus;
	}
	else if (previousMillis3 == NULL || previousStatus3 == NULL) {
		previousMillis3 = currentMillis;
		previousStatus3 = currentStatus;
	}
	return previousStatus3;
}

bool getSensor4()
{
	unsigned long currentMillis = millis();
	bool currentStatus = (sensor4 > whiteOrBlackSwitch);
	/**
	* if the current millis minus the previous millis is higher than the setten interval.
	*
	* else if previous millis en status not equals null.
	*
	*/
	if (currentMillis - previousMillis4 > interval) {
		/**
		* check if the current state is the same as the previous one.
		* if it is the same the return that status.
		*
		* else return the previous status
		*/
		bool returnstatus = false;
		if (currentStatus == previousStatus4) {
			returnstatus = currentStatus;
		}
		else {
			returnstatus = previousStatus4;
		}
		previousMillis4 = currentMillis;
		previousStatus4 = currentStatus;
		return returnstatus;
	}
	else if (previousMillis4 == NULL || previousStatus4 == NULL) {
		previousMillis4 = currentMillis;
		previousStatus4 = currentStatus;
	}
	return previousStatus4;
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
	return analogRead('A' + ldrA);
}



void forward() {
	setLeftWheel(true, speedSlow);
	setRightWheel(true, speedSlow);
}

void right() {
	setRightWheel(true, speedSlow);
	setLeftWheel(true, speedUltraSlow);
}

void left() {
	setLeftWheel(true, speedSlow);
	setRightWheel(true, speedUltraSlow);
}
void backward() {
	setLeftWheel(false, speedSlow);
	setRightWheel(false, speedSlow);
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

