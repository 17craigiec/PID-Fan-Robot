#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//=============================================================
//RUDDER CLASS
//=============================================================

class Rudder
{
public:
	int pinNumber;
	int currentPos;

	void moveTo(int givenPos)
	{
		int offsetConstant = 0;
		int writtenValue = 150+givenPos+offsetConstant;

		if(writtenValue > 200)
		{
			analogWrite(this->pinNumber, 200);
			this->currentPos = 200;
		}
		if(writtenValue < 100)
		{
			analogWrite(this->pinNumber, 100);
			this->currentPos = 100;
		}
		else
		{
			analogWrite(this->pinNumber, writtenValue);
			this->currentPos = writtenValue;
		}
	}

	void moveAbsolute(int givenAbsValue)
	{
		int writtenValue = currentPos + givenAbsValue;

		if(writtenValue > 200)
		{
			analogWrite(this->pinNumber, 200);
			this->currentPos = 200;
		}
		if(writtenValue < 100)
		{
			analogWrite(this->pinNumber, 100);
			this->currentPos = 100;
		}
		else
		{
			analogWrite(this->pinNumber, writtenValue);
			this->currentPos = writtenValue;
		}
	}
};


//RudderPin
int rudderPin = 3;

//RudderObjectCreation
Rudder bikeRudder;

//====================END CLASS================================
//=============================================================







//=============================================================
//STATUS LIGHT CLASS
//=============================================================

class StatusLight{
public:

	int pinNumber;
	char color;

	void pinSetup()
	{
		pinMode(this->pinNumber, OUTPUT);
	}

	void on()
	{
		digitalWrite(this->pinNumber, HIGH);
	}

	void off()
	{
		digitalWrite(this->pinNumber, LOW);
	}

};


//Status light pins
int redLight = 10;
int yellowLight = 11;
int greenLight = 12;

//LightObjectCreation
StatusLight Red;
StatusLight Yellow;
StatusLight Green;


//====================END CLASS================================
//=============================================================







//=============================================================
//STATUS DRIVE CLASS
//=============================================================

class Drive{
public:

	int pinNumber;

	//rawWrittenValue should accept an integer >0 && <255
	void driveBlind(int rawWrittenValue)
	{
		if(rawWrittenValue < 0)
		{
			analogWrite(this->pinNumber, 0);
		}
		if(rawWrittenValue > 255)
		{
			analogWrite(this->pinNumber, 255);
		}
		else
		{
			analogWrite(this->pinNumber, rawWrittenValue);
		}
	}
};


//Drive wheel PWM pin
int driveWheelPin = 6;

//Drive object creation
Drive driveWheel;


//====================END CLASS================================
//=============================================================







//=============================================================
//STATUS PROPELLER CLASS
//=============================================================

class Propeller{
public:

	int pinNumber;

	//rawWrittenValue should accept an integer >0 && <255
	void driveBlind(int rawWrittenValue)
	{
		if(rawWrittenValue < 0)
		{
			analogWrite(this->pinNumber, 0);
		}
		if(rawWrittenValue > 255)
		{
			analogWrite(this->pinNumber, 255);
		}
		else
		{
			analogWrite(this->pinNumber, rawWrittenValue);
		}
	}
};


//Propeller PWM pin
int propellerPin = 5;

//Propeller object creation
Propeller propeller;


//====================END CLASS================================
//=============================================================







//=============================================================
//TEXT CLASS
//=============================================================

class Text{
public:

	//ERROR function prints an error
	void error(char error[])
	{
		Serial.print("[ERROR]: ");
		Serial.println(error);
	}

	//WARNING function prints an warning
	void warning(char warn[])
	{
		Serial.print("[WARNING]: ");
		Serial.println(warn);
	}

	//NOTE function prints an note
	void note(char note[])
	{
		Serial.print("[NOTE]: ");
		Serial.println(note);
	}
};

//Text object creation
Text txt;


//====================END CLASS================================
//=============================================================







//=============================================================
//ADAFRUIT BNO055 IMU
//=============================================================

Adafruit_BNO055 IMU = Adafruit_BNO055(55);


//=============================================================
//MAIN ArduinoSetupAndLoop
//=============================================================

void setup() {

	Serial.begin(115200);
	txt.note("Serial Initialized");

	//Testing the status of the IMU
	if(!IMU.begin())
	{
		txt.error("IMU failed to initialize");
		txt.note("Terminating program");
		//Safety exit of the program
		while(1);
	}
	else
	{
		delay(1000);
		IMU.setExtCrystalUse(true);
		txt.note("IMU properly initialized");
	}

	//Instantiation of rudder object
	bikeRudder.pinNumber = rudderPin;
	//Initializing rudder pin
	pinMode(rudderPin, OUTPUT);


	//Instantiating status light object
	//RED
	Red.pinNumber = redLight;
	Red.color = "Red";
	//YELLOW
	Yellow.pinNumber = yellowLight;
	Yellow.color = "Yellow";
	//GREEN
	Green.pinNumber = greenLight;
	Green.color = "Green";


	//Initializing light pins
	Red.pinSetup();
	Yellow.pinSetup();
	Green.pinSetup();


	//Instantiating drive object
	driveWheel.pinNumber = driveWheelPin;


	//Instantiating propeller object
	propeller.pinNumber = propellerPin;

}

void loop() {


	Red.on();
	//analogWrite(rudderPin, 150);
	delay(100);
	Red.off();

	Yellow.on();
	//analogWrite(rudderPin, 150);
	delay(100);
	Yellow.off();

	Green.on();
	//analogWrite(rudderPin, 150);
	delay(100);
	Green.off();


	sensors_event_t event;
	//if getEvent is not recognized
	//Go to project -> C/C++ Index -> Rebuild
	IMU.getEvent(&event);

	/* Display the floating point data */
	Serial.print("X: ");
	Serial.print(event.orientation.x, 4);
	Serial.print("\tY: ");
	Serial.print(event.orientation.y, 4);
	Serial.print("\tZ: ");
	Serial.print(event.orientation.z, 4);
	Serial.println("");
	//test change for git


}





