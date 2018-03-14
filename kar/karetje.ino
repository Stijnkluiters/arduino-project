/*
 Name:		karetje.ino
 Created:	3/14/2018 9:53:40 AM
 Author:	stijn
*/

// the setup function runs once when you press reset or power the board

// wielen worden gedefineerd vannuit achteraanzicht ( waar het wieletje zit )
// #directionOfRotation == DOR
int wheelEnableRight = 13;
int wheelDORRight = 12;
int wheelEnableLeft = 11;
int wheelDORLeft = 10;
int led = 9;




void setup() {
	setupPins();

}

// the loop function runs over and over again until power down or reset
void loop() {
	
}
// can only be called inside the setup function.
void setupPins() {
	for (int i = 9; i < 13; i++) {
		pinMode(i, OUTPUT);
	}
}
