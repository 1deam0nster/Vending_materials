/******************************************************************************
 * MicroOLED_Clock.ino
 * Часы со стрелками на библиотеке MicroOLED Breakout
 * Автор Джим Линдблом @ SparkFun Electronics
 * Дата создания оригинала: 27 октября 2014 г.
 *
 * Этот скетч использует библиотеку MicroOLED для рисования циферблата
 * и поворота стрелок как на часах.
 *
 * Особенности среды разработки:
 * Arduino 1.0.5
 * Arduino Pro 3.3V
 * Micro OLED Breakout v1.0
 *
 * Распространяется как есть; гарантия не предоставляется.
 ******************************************************************************/
 
    #include <Wire.h>                              // Подключаем библиотеку для работы с шиной I2C (если дисплей подключется по этой шине)
//  #include <SPI.h>                               // Подключаем библиотеку для работы с шиной SPI (если дисплей подключется по этой шине)
    #include <SFE_MicroOLED.h>                     // Подключаем библиотеку SFE_MicroOLED для работы с OLED дисплеем
                                                   //
//  #define PIN_RESET 9                            // Определяем номер вывода к которому подключён вывод RST дисплея при подключении по шине SPI
//  #define PIN_DC    8                            // Определяем номер вывода к которому подключён вывод DC  дисплея при подключении по шине SPI
//  #define PIN_CS    10                           // Определяем номер вывода к которому подключён вывод CS  дисплея при подключении по шине SPI
                                                   //
    #define PIN_RESET 255                          // Определяем номер вывода к которому подключён вывод RST дисплея при подключении по шине I2C (если у дисплея нет этого вывода, то присвиваем значение 255)
    #define DC_JUMPER 0                            // Определяем адрес дисплея на шине I2C: 0-0x3C / 1-0x3D
                                                   //
//  MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);     // Объявляем объект oled для работы с дисплеем по шине SPI, указывая ранее определённые выводы
    MicroOLED oled(PIN_RESET, DC_JUMPER);          // Объявляем объект oled для работы с дисплеем по шине I2C, указывая ранее определённые выводы и адрес дисплея
                                                   //
int           hours       = 11;                    // Определяем начальное время часов (часы)
int           minutes     = 50;                    // Определяем начальное время часов (минуты)
int           seconds     = 30;                    // Определяем начальное время часов (секунды)
const int     CLOCK_SPEED = 1000;                  // Определяем скорость часов        (время паузы между сменой положений секундной стрелки)
const int     MIDDLE_Y    = oled.getLCDHeight()/2; // Узнаём центр дисплея в пикселях по высоте
const int     MIDDLE_X    = oled.getLCDWidth() /2; // Узнаём центр дисплея в пикселях по ширине
unsigned long lastDraw    = 0;                     // Время последней прорисовки
int           CLOCK_RADIUS;                        // Радиус круга часов             (будет определён  после подключения шрифта)
int           POS_12_X, POS_12_Y;                  // Положение цифры 12 на часах    (будет определёно после подключения шрифта)
int           POS_3_X,  POS_3_Y;                   // Положение цифры 3  на часах    (будет определёно после подключения шрифта)
int           POS_6_X,  POS_6_Y;                   // Положение цифры 6  на часах    (будет определёно после подключения шрифта)
int           POS_9_X,  POS_9_Y;                   // Положение цифры 9  на часах    (будет определёно после подключения шрифта)
int           S_LENGTH;                            // Длина секундной стрелки часов  (будет определёна после подключения шрифта)
int           M_LENGTH;                            // Длина минутной  стрелки часов  (будет определёна после подключения шрифта)
int           H_LENGTH;                            // Длина часовой   стрелки часов  (будет определёна после подключения шрифта)
void          initClockVariables(void);            // Объявляем функцию определения значений объявленных переменных
void          updateTime(void);                    // Объявляем функцию обновления значений переменных времени
void          drawArms(int,int,int);               // Объявляем функцию прорисовки стрелок часов
void          drawFace(void);                      // Объявляем функцию прорисовки циферблата часов
                                                   //
void setup(){                                      //
     oled.begin();                                 // Инициируем работу с OLED дисплеем
     oled.clear(ALL);                              // Чистим графическую память дисплея
     oled.display();                               // Выводим данные из буфера библиотеки на дисплей
     delay(1000);                                  // Устанавливаем зажержку на 1 секунду
     oled.setFontType(0);                          // Устанавливаем шрифт номер 0 (0-5x7, 1-8x16, 2-семисегментный, 3-большие цифры, 4-31x48)
     initClockVariables();                         // Вызываем функцию определения значений объявленных переменных
     oled.clear(PAGE);                             // Чистим графический буфер библиотеки
     drawFace();                                   // Вызываем функцию прорисовки циферблата часов
     drawArms(hours, minutes, seconds);            // Вызываем функцию прорисовки стрелок часов
     oled.display();                               // Выводим данные из буфера библиотеки на дисплей
}                                                  //
                                                   //
void loop(){                                       //
     if(lastDraw + CLOCK_SPEED < millis()){        // Если разница между последней прорисовкой lastDraw и текущем временем millis() более CLOCK_SPEED миллисекунд, то ...
         lastDraw = millis();                      // Обновляем время последней прорисовки
         updateTime();                             // Вызываем функцию обновления значений переменных времени
         oled.clear(PAGE);                         // Чистим графический буфер библиотеки
         drawFace();                               // Вызываем функцию прорисовки циферблата часов
         drawArms(hours, minutes, seconds);        // Вызываем функцию прорисовки стрелок часов
         oled.display();                           // Выводим данные из буфера библиотеки на дисплей
     }                                             //
}                                                  //
                                                   //
/***************************************************/
                                                   //
//   Функция определения значений объявленных переменных:
void initClockVariables(){
     CLOCK_RADIUS = min(MIDDLE_X, MIDDLE_Y) - 1;
     POS_12_X     = MIDDLE_X - oled.getFontWidth();
     POS_12_Y     = MIDDLE_Y - CLOCK_RADIUS + 2;
     POS_3_X      = MIDDLE_X + CLOCK_RADIUS - oled.getFontWidth() - 1;
     POS_3_Y      = MIDDLE_Y - oled.getFontHeight()/2;
     POS_6_X      = MIDDLE_X - oled.getFontWidth()/2;
     POS_6_Y      = MIDDLE_Y + CLOCK_RADIUS - oled.getFontHeight() - 1;
     POS_9_X      = MIDDLE_X - CLOCK_RADIUS + oled.getFontWidth() - 2;
     POS_9_Y      = MIDDLE_Y - oled.getFontHeight()/2;
     S_LENGTH     = CLOCK_RADIUS - 2;
     M_LENGTH     = S_LENGTH * 0.7;
     H_LENGTH     = S_LENGTH * 0.5;
}

//   Функция обновления значений переменных времени:
void updateTime(){
     seconds++;
     if(seconds>=60){seconds = 0; minutes++;
     if(minutes>=60){minutes = 0; hours++;
     if(hours  >=12){hours   = 0;
     }}}
}

//   Функция прорисовки стрелок часов:
void drawArms(int h, int m, int s){
     double midHours;
     static int hx, hy, mx, my, sx, sy;
     h-=3;  if(h <=0){h += 12;}
     m-=15; if(m < 0){m += 60;}
     s-=15; if(s < 0){s += 60;}
     s = map(s, 0, 60, 0, 360); // Преобразуем секунды 0-60 в гражусы 0-360
     sx = S_LENGTH * cos(PI * ((float)s) / 180);
     sy = S_LENGTH * sin(PI * ((float)s) / 180);
     oled.line(MIDDLE_X, MIDDLE_Y, MIDDLE_X + sx, MIDDLE_Y + sy); // Прорисовка секундной срелки
     m = map(m, 0, 60, 0, 360); // Преобразуем миуты 0-60 в гражусы 0-360
     mx = M_LENGTH * cos(PI * ((float)m) / 180);
     my = M_LENGTH * sin(PI * ((float)m) / 180);
     oled.line(MIDDLE_X, MIDDLE_Y, MIDDLE_X + mx, MIDDLE_Y + my); // Прорисовка минутной срелки
     midHours = minutes/12;
     h *= 5; // Преобразуем часы от диапазона 0-12 к диапазону 0-60
     h += midHours; 
     h = map(h, 0, 60, 0, 360);  // Преобразуем часы 0-60 в гражусы 0-360
     hx = H_LENGTH * cos(PI * ((float)h) / 180);
     hy = H_LENGTH * sin(PI * ((float)h) / 180);
     oled.line(MIDDLE_X, MIDDLE_Y, MIDDLE_X + hx, MIDDLE_Y + hy); // Прорисовка часовой срелки
}

//   Функция прорисовки циферблата часов:
void drawFace(){
     oled.circle(MIDDLE_X, MIDDLE_Y, CLOCK_RADIUS); // Выводим круг (ободок циферблата)
     oled.setFontType(0); // Устанавливаем шрифт номер 0 (0-5x7, 1-8x16, 2-семисегментный, 3-большие цифры, 4-31x48)
     oled.setCursor(POS_12_X, POS_12_Y); oled.print(12); // Устанавливаем курсор в указанную позицию и выводим цифру 12
     oled.setCursor(POS_6_X,  POS_6_Y ); oled.print(6); // Устанавливаем курсор в указанную позицию и выводим цифру 6
     oled.setCursor(POS_9_X,  POS_9_Y ); oled.print(9); // Устанавливаем курсор в указанную позицию и выводим цифру 9
     oled.setCursor(POS_3_X,  POS_3_Y ); oled.print(3); // Устанавливаем курсор в указанную позицию и выводим цифру 3
}