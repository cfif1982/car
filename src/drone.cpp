#include "drone.h"

void Drone::Setup()
{
  bluetooth.begin(9600);
  bluetooth.setTimeout(50);

  motor.setSpeed(200); // Начальная скорость вращения
  motor.run(RELEASE);  // Останавливаем двигатель
}

int ReadBluetooth()
{
  if (bluetooth.available() > 0)
  {
    // btByte = bluetooth.read();
    btByte = bluetooth.read();
    Serial.println(btByte);
  }

  // Если есть какие нибудь данные на приеме Serial порта
  if (Serial.available() > 0)
  {
    // считываем байт данных
    curByte = Serial.read();

    bluetooth.println(curByte);

    // если текущий символ == ";" то это означает
    // что мы начинаем работать со следующей командой
    // а текущая команда закончилась
    if (curByte == next_command)
    {
      // переводим строку в число и сохраняем его в массив команд
      commands[com_counter].value = atoi(temp.c_str());

      temp = "";        // обнуляем строку для числа
      flag_type = true; // устанавливаем флаг типа. Это означает что будет записываться тип команды

      com_counter++; // переходим к записи в следующий элемент массива команд
    }
    // если текущий символ == " "
    else if (curByte == next_value)
    {
      // снимаем флаг работы с типом команды
      // это значит, что мы закончили работать с типом комнады
      // и начинаем рабоать со значением команды
      flag_type = false;
    }
    // если текущий символ == #
    else if (curByte == last_command)
    {
      flag_com_execute = true; // меняем режим работы дрона. режим - выполнение команд
      Serial.println("mode: execute command");
    }
    // если это любой другой символ
    else
    {
      // если мы сейчас работаем с типом команды
      if (flag_type == true)
      {
        // добавляем текущий символ к полю тип команды
        commands[com_counter].type += curByte;
      }
      // иначе означает, что мы сейчас рабоатем со значением команды
      else
      {
        // добавляем текущий символ к переменной в которой хранится значение команды
        // чтобы в дальнейшем перевести эту строку в число
        temp += curByte;
      }
    }
  }
}

int ExecuteCommands()
{
  for (int i = 0; i < SIZE; i++)
  {
    Serial.println(commands[i].type);

    // если тип команды - move
    if (commands[i].type == "move")
    {
      motor.run(FORWARD);              // запускаем двигатель
      delay(commands[i].value * 1000); // задержка в текущем режиме
    }
    // если тип команды - stop
    else if (commands[i].type == "stop")
    {
      motor.run(RELEASE);              // останавливааем двигатель
      delay(commands[i].value * 1000); // задержка в текущем режиме
    }
  }
  flag_com_execute = false; // меняем режим работы дрона. режим - чтения команд
}

int move(int val)
{
}
int right(int val)
{
}
int left(int val)
{
}
int stop(int val)
{
}