#include <iarduino_NeoPixel.h>                      //  Подключаем библиотеку iarduino_NeoPixel для работы со светодиодами NeoPixel
iarduino_NeoPixel led(6,30);                        //  Объявляем объект LED указывая (№ вывода Arduino к которому подключён модуль NeoPixel, количество используемых светодиодов)
void setup() {
  led.begin();                                    //  Инициируем работу с модулем NeoPixel
}
void loop() {
  led.setColor(NeoPixelAll, 250, 0, 0);           // делаем все красные
  led.write();                                    //  Записываем
  delay(2000);                                    //  Ждём 2 секунды
  //led.setColor(NeoPixelAll, 0, 0, 250);           // делаем все синие
  //led.write();                                    //  Записываем
  //delay(2000);                                    //  Ждём 2 секунды
  //led.setColor(NeoPixelAll, 250, 250, 250);       //  делаем все желтые
  //led.write();                                    //  Записываем
  //delay(2000);                                    //  Ждём 2 секунды
}
