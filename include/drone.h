#include <Arduino.h>
#include <AFMotor.h> // Подключаем библиотеку AFMotor
#include <SoftwareSerial.h>

AF_DCMotor motor(4); // Указываем какому порту подключен двигатель (1 - 4)

SoftwareSerial bluetooth(2, 13); // RX, TX   H06_RX -> PIN_12 Nano, H06_TX -> PIN_11 Nano

const int SIZE = 10; // количество элементов в массиве

struct Command
{
  String type;
  int value;
};

class Drone
{
public:
  // флаг выполнения команд
  // если false, то мы получаем команды через Serial порт
  // если true, то выполняем команды
  bool flag_com_execute = false;

  void Setup();
  void ReadBluetooth();
  void ExecuteCommands();
  int move(int val);
  int right(int val);
  int left(int val);
  int stop(int val);

private:
  char btByte; // хранит символ, полученный через Bluetooth порт

  char next_command = ';'; // отделяет команды
  char next_value = ' ';   // отделяет тип и значение
  char last_command = '#'; // ставится после последней команды

  Command commands[SIZE]; // массив команд

  int com_counter = 0;   // счетчик команд в массиве
  bool flag_type = true; // флаг для определения с чем работаем: тип или значение

  // временная переменная для хранения значения команды в виде строки
  // когда эта строку будет полностью сформирована, тогда конвертирем ее в число
  String temp = "";
};