#ifndef MOVE_h
#define MOVE_h

class MOVE {
	public:
	  static void onSetup(int eA, int a1, int a2, int eB, int b1, int b2);
	  static void setTurn(bool dir, int power);
	  static void setGear(bool dir, int power);
	  static void kill();
	  
	  static int enA;
	  static int in1;
	  static int in2;
	  static int enB;
	  static int in3;
	  static int in4;
	  
	  static const int maxAnalogWrite;
		static const int minAnalogWrite;
		
	private:
		static void off();
		static int validatePower(int power);
};

#endif