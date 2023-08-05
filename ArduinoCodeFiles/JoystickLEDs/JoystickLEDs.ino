const byte x = A0;
const byte y = A1;

const int redLight = 11;
const int greenLight = 10;
const int blueLight = 9;

const int leftLight = 5;
const int rightLight = 6;

const int joystickButton = 2;

bool flag = false;
int idx = 0;

int r = 255;
int b = 0;
int g = 0;

void setup() {
  Serial.begin(9600);
  int lights[] = {redLight, greenLight, blueLight, leftLight, rightLight};
  for (int i = 0; i < 5; i++) {
    pinMode(lights[i], OUTPUT); 
  }
  pinMode(joystickButton, INPUT_PULLUP);
}

void loop(){
  int xVal = (analogRead(x) / 2);
  int yVal = 255 - (analogRead(y) / 4);
  changeColor(yVal);
  leftRightPWM(xVal);
}

bool turnOff(int brightness) {
  if (brightness < 10) {
    analogWrite(redLight, 0);
    analogWrite(greenLight, 0);
    analogWrite(blueLight, 0);
    return false;
  }
  return true;
}

void changeColor(int brightness) {
  int status = digitalRead(joystickButton);
  if (status == 0 && flag == false) {
    if (idx < 6)
      idx += 1;
    else
      idx = 0;
    flag = true;
    delay(300);
  }
  else if (status == 0 && flag == true)
    setToRGB(brightness);
  else
    flag = false;
  nextColor(brightness, idx);
}

void nextColor(int brightness, int idx) {
  switch(idx) {
    case 0:
      setToWhite(brightness);
      break;
    case 1:
      setToRed(brightness);
      break;
    case 2:
      setToGreen(brightness);
      break;
    case 3:
      setToBlue(brightness);
      break;
    case 4:
      setToMagenta(brightness);
      break;
    case 5:
      setToCyan(brightness);
      break;
    case 6:
      setToYellow(brightness);
      break;
  }
}

void setToWhite(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    analogWrite(redLight, brightness);
    analogWrite(greenLight, brightness);
    analogWrite(blueLight, brightness);
  }
}

void setToRed(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    analogWrite(redLight, brightness);
    analogWrite(greenLight, 0);
    analogWrite(blueLight, 0);
  }
}

void setToGreen(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    analogWrite(redLight, 0);
    analogWrite(greenLight, brightness);
    analogWrite(blueLight, 0);
  }
}

void setToBlue(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    analogWrite(redLight, 0);
    analogWrite(greenLight, 0);
    analogWrite(blueLight, brightness);
  }
}

void setToMagenta(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    analogWrite(redLight, brightness);
    analogWrite(greenLight, 0);
    analogWrite(blueLight, brightness);
  }
}

void setToCyan(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    analogWrite(redLight, 0);
    analogWrite(greenLight, brightness);
    analogWrite(blueLight, brightness);
  }
}

void setToYellow(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    analogWrite(redLight, brightness);
    analogWrite(greenLight, brightness);
    analogWrite(blueLight, 0);
  }
}

void setToRGB(int brightness) {
  bool isOn = turnOff(brightness);
  if (isOn) {
    for (/* no initialization */; r >= 0, b < 255; b++, r--) {
      analogWrite(redLight, r);
      analogWrite(blueLight, b);
      delay(5);
    }

    for (/* no initialization */; b >= 0, g < 255; g++, b--) {
      analogWrite(blueLight, b);
      analogWrite(greenLight, g);
      delay(5);
    }

    for (/* no initialization */; g >= 0, r<255; r++, g--) {
      analogWrite(redLight, r);
      analogWrite(greenLight, g);
      delay(5);
    }
  }
}

void leftRightPWM(int brightness) {
  if (brightness <= 200) {
    if (brightness <= 10) {
      analogWrite(leftLight, 255);
      analogWrite(rightLight, 0);
    }
    else {
      analogWrite(leftLight, 256 - brightness);
      analogWrite(rightLight, brightness);
    }
  }
  else if (brightness >= 306) {
    int val = 256 - (brightness / 2);
    if (val <= 10) {
      analogWrite(rightLight, 255);
      analogWrite(leftLight, 0);
    }
    else {
      analogWrite(leftLight, 256 - (brightness / 2));
      analogWrite(rightLight, brightness / 2);
    }
  }
  else {
    analogWrite(leftLight, 128);
    analogWrite(rightLight, 128);
  }
}
