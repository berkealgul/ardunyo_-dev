/*
	- upper left (ul)
	- upper right (ur)
	- lower left (ll)
	- lower right (lr)
	- digital pin for direction (dp)
	- analog pin for speed (ap)
*/

// these digital inputs are for h bridge
// 2 pins for each motor. i_dp and i_dp_1 for motor i
int ul_dp = 2;
int ur_dp = 4;
int ll_dp = 7;
int lr_dp = 8;

int ul_dp_1 = 13;
int ur_dp_1 = 12;
int ll_dp_1 = 11;
int lr_dp_1 = 10;

int ul_ap = 3;
int ur_ap = 5;
int ll_ap = 6;
int lr_ap = 9;


void setup()
{
	Serial.begin(9600);	

	pinMode(ul_dp, OUTPUT);
	pinMode(ul_ap, OUTPUT);
	pinMode(ur_dp, OUTPUT);
	pinMode(ur_ap, OUTPUT);
	pinMode(ll_dp, OUTPUT);
	pinMode(ll_ap, OUTPUT);
	pinMode(lr_dp, OUTPUT);
	pinMode(lr_ap, OUTPUT);
	pinMode(ul_dp_1, OUTPUT);
	pinMode(ur_dp_1, OUTPUT);
	pinMode(ll_dp_1, OUTPUT);
	pinMode(lr_dp_1, OUTPUT);
}


void loop()
{
	String msg = "s";	

	/*
		motors assinged to indices as ascending order
		- upper left (ul)
		- upper right (ur)
		- lower left (ll)
		- lower right (lr)
	*/

	int motorDirs[4];
	int motorSpeeds[4];

	for(int i = 0; i < 4; i++)
	{
		int dir = random(2);
		int speed = random(256);

		motorDirs[i] = dir;
		motorSpeeds[i] = speed;

		msg += String(dir); 
		msg += adjust_str(String(speed));
	}

	msg += "f";

	Serial.println(msg);


	/*
		adjust pins depend on motor values
		mi diredction of motor i
		msi speed of motor 1

	*/
	int m1, m2, m3, m4;
	int ms1, ms2, ms3, ms4;
	
	m1 = motorDirs[0];
	m2 = motorDirs[1];
	m3 = motorDirs[2];
	m4 = motorDirs[3];

	ms1 = motorSpeeds[0];
	ms2 = motorSpeeds[1];
	ms3 = motorSpeeds[2];
	ms4 = motorSpeeds[3];

	driveMotor(m1, ms1, ul_dp, ul_dp_1, ul_ap);
	driveMotor(m2, ms2, ur_dp, ur_dp_1, ur_ap);
	driveMotor(m3, ms3, ll_dp, ll_dp_1, ll_ap);
	driveMotor(m4, ms4, lr_dp, lr_dp_1, lr_ap);

	delay(1000);
}

String adjust_str(String val)
{
	String str = "000";

	for(int i = sizeof(val)-1; i >= 0; i--)
	{
		str[i] = val[i];
	}

	return str;
}

void driveMotor(int dir, int speed, int in1, int in2, int enab)
{
	if(dir == 0)
	{
		digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
	}
	else
	{
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
	}
	
	analogWrite(enab, speed);
}