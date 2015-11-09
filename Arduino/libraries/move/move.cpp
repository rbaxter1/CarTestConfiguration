#include <Arduino.h>
#include <move.h>

int MOVE::enA;
int MOVE::in1;
int MOVE::in2;
int MOVE::enB;
int MOVE::in3;
int MOVE::in4;

const int MOVE::minAnalogWrite = 0;
const int MOVE::maxAnalogWrite = 255;

int MOVE::validatePower(int power)
{
  if (power > MOVE::maxAnalogWrite)
  {
    return MOVE::maxAnalogWrite;
  }

  if (power < MOVE::minAnalogWrite)
  {
    return MOVE::minAnalogWrite;
  }

  return power;
}

void MOVE::off()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
	
void MOVE::onSetup(int eA, int a1, int a2, int eB, int b1, int b2)
{
	MOVE::enA = eA;
	MOVE::in1 = a1;
	MOVE::in1 = a2;
	MOVE::enB = eB;
	MOVE::in3 = b1;
	MOVE::in4 = b2;
	
	pinMode(MOVE::enA, OUTPUT);
  pinMode(MOVE::enB, OUTPUT);
  pinMode(MOVE::in1, OUTPUT);
  pinMode(MOVE::in2, OUTPUT);
  pinMode(MOVE::in3, OUTPUT);
  pinMode(MOVE::in4, OUTPUT);

	MOVE::off();
}

void MOVE::kill()
{
	MOVE::off();
}

void MOVE::setTurn(bool dir, int power)
{
	digitalWrite(in3, dir ? HIGH : LOW);
  digitalWrite(in4, dir ? LOW : HIGH);
  analogWrite(enB, validatePower(power));
}
	
void MOVE::setGear(bool dir, int power)
{
	digitalWrite(in1, dir ? HIGH : LOW);
  digitalWrite(in2, dir ? LOW : HIGH);
  analogWrite(enA, validatePower(power));
}

