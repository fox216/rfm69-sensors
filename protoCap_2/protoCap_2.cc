// protoCap_2


byte analogPin = 5;
int val = 0;

void setup() {

	Serial.begin(115200);
	pinMode(11, OUTPUT);
}


void loop() {
	analogWrite(11, 127);

	val = analogRead(analogPin);

	Serial.println(val);

	delay(200);
}