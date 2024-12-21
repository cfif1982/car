#include <Arduino.h>

#include "drone.h"

Drone car;

void setup()
{
  Serial.begin(115200); // открываем порт для связи с ПК
  Serial.println("Start");

  car.Setup();
}

void loop()
{
  // выполняется, если сейчас режим чтения команд
  if (car.flag_com_execute == false)
  {
    car.ReadBluetooth();
  }
  // выполняется, если сейчас режим выполнение команд
  else
  {
    car.ExecuteCommands();
  }
}
