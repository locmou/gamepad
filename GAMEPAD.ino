/*
  Téléchargeable uniquement depuis le PC (impossible depuis raspbian) sur une pro-micro.
  
  Toutes les bibliothèques HID, USB, keyboard, Joystick sont à effacer 
  
... elles interagissent avec la bibliothèque utilisé dans ce programme, à savoir
ArduinoJoystickLibrary-master, téléchargée sur le site internet suivant:
https://github.com/MHeironimus/ArduinoJoystickLibrary

Pour fonctionner, bien choisir comme board : 
"sparkfun pro micro"
*/

#include <Joystick.h>

const uint8_t buttonCount = 9;
Joystick_ controller(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, buttonCount,
                     0, true, true, false,
                     false, false, false,
                     false, false, false,
                     false, false);

int const BTN_A_PIN = 10;
int const BTN_B_PIN = 14;
int const BTN_C_PIN = 15;
int const BTN_D_PIN = 16;
int const BTN_E_PIN = 9;
int const BTN_F_PIN = 8;
int const BTN_K_PIN = 7;
int const BTN_J_PIN = 6;
int const BTN_Z_PIN = 5;
int const AXIS_X_PIN = A0;
int const AXIS_Y_PIN = A1;
int const ledpin = 4;       // Mouse control LED

int const buttonPins[buttonCount] = {
  BTN_A_PIN,
  BTN_B_PIN,
  BTN_C_PIN,
  BTN_D_PIN,
  BTN_E_PIN,
  BTN_F_PIN,
  BTN_K_PIN,
  BTN_J_PIN,
  BTN_Z_PIN

};
int lastButtonValue[buttonCount];
int lastXAxisValue = -1;
int lastYAxisValue = -1;

void setup()
{
  controller.setYAxisRange(0, 1023);
  controller.setYAxisRange(1023, 0);
  controller.begin(false);

  for (int i = 0; i < buttonCount; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonValue[i] = -1;
  }

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledpin, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(ledpin, LOW);
}

void loop()
{
  if (digitalRead(5)==true )
  {
  digitalWrite(ledpin, HIGH);
  }  
  else digitalWrite(ledpin, LOW);
  
  bool sendUpdate = false;
  for (int i = 0; i < buttonCount; i++)
  {
    const int buttonValue = digitalRead(buttonPins[i]);
    
    if (buttonValue != lastButtonValue[i])
    {
      controller.setButton(i, !buttonValue);
      lastButtonValue[i] = buttonValue;
      sendUpdate = true;
    }
  }

  const int currentXAxisValue = analogRead(AXIS_X_PIN);
  if (currentXAxisValue != lastXAxisValue)
  {
    controller.setXAxis(currentXAxisValue);
    lastXAxisValue = currentXAxisValue;
    sendUpdate = true;
  }

  const int currentYAxisValue = analogRead(AXIS_Y_PIN);
  if (currentYAxisValue != lastYAxisValue)
  {
    controller.setYAxis(currentYAxisValue);
    lastYAxisValue = currentYAxisValue;
    sendUpdate = true;
  }

  if (sendUpdate)
  {
    controller.sendState();
  }
  delay(50);
}
