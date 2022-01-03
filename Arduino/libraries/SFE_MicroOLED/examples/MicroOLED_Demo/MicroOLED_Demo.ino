/******************************************************************************
 * MicroOLED_Demo.ino
 * Демонстрация примеров работы с OLED дисплеем на библиотеке MicroOLED Breakout
 * Автор Джим Линдблом @ SparkFun Electronics
 * Дата создания оригинала: 27 октября 2014 г.
 *
 * Этот скетч использует библиотеку MicroOLED для демонстрации
 * примеров работы с OLED дисплеем.
 *
 * Особенности среды разработки:
 * Arduino 1.0.5
 * Arduino Pro 3.3V
 * Micro OLED Breakout v1.0
 *
 * Распространяется как есть; гарантия не предоставляется.
 ******************************************************************************/
 
     #include <Wire.h>                             // Подключаем библиотеку для работы с шиной I2C (если дисплей подключется по этой шине)
//   #include <SPI.h>                              // Подключаем библиотеку для работы с шиной SPI (если дисплей подключется по этой шине)
     #include <SFE_MicroOLED.h>                    // Подключаем библиотеку SFE_MicroOLED для работы с OLED дисплеем
                                                   //
//   #define PIN_RESET 9                           // Определяем номер вывода к которому подключён вывод RST дисплея при подключении по шине SPI
//   #define PIN_DC    8                           // Определяем номер вывода к которому подключён вывод DC  дисплея при подключении по шине SPI
//   #define PIN_CS    10                          // Определяем номер вывода к которому подключён вывод CS  дисплея при подключении по шине SPI
                                                   //
     #define PIN_RESET 255                         // Определяем номер вывода к которому подключён вывод RST дисплея при подключении по шине I2C (если у дисплея нет этого вывода, то присвиваем значение 255)
     #define DC_JUMPER 0                           // Определяем адрес дисплея на шине I2C: 0-0x3C / 1-0x3D
                                                   //
//   MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);    // Объявляем объект oled для работы с дисплеем по шине SPI, указывая ранее определённые выводы
     MicroOLED oled(PIN_RESET, DC_JUMPER);         // Объявляем объект oled для работы с дисплеем по шине I2C, указывая ранее определённые выводы и адрес дисплея
                                                   //
int  SCREEN_WIDTH  = oled.getLCDWidth();           // Узнаём ширину дисплея в пикселях
int  SCREEN_HEIGHT = oled.getLCDHeight();          // Узнаём высоту дисплея в пикселях
void pixelExample(void);                           // Объявляем функцию примера прорисовки точек
void lineExample(void);                            // Объявляем функцию примера прорисовки линий
void shapeExample(void);                           // Объявляем функцию примера прорисовки и выполнения примера игры
void textExamples(void);                           // Объявляем функцию примера вывода текста различными шрифтами
void printTitle(String, int);                      // Объявляем функцию вывода текста перед демонстрацией примера
                                                   //
void setup(){                                      //
     oled.begin();                                 // Инициируем работу с OLED дисплеем
     oled.clear(ALL);                              // Чистим графическую память дисплея (избавляемся от артефактов которые могли появиться при подаче питания)
     oled.display();                               // Выводим данные из буфера библиотеки на дисплей
     delay(1000);                                  // Устанавливаем зажержку на 1 секунду
     oled.clear(PAGE);                             // Чистим графический буфер библиотеки
     randomSeed(analogRead(A0));                   // Выбираем случайное начальное положение в последовательности чисел для последующих вызовов фунции random()
}                                                  //
                                                   //
void loop(){                                       //
     pixelExample();                               // Вызываем функцию примера прорисовки точек
     lineExample();                                // Вызываем функцию примера прорисовки линий
     shapeExample();                               // Вызываем функцию примера прорисовки и выполнения примера игры
     textExamples();                               // Вызываем функцию примера вывода текста различными шрифтами
}                                                  //
                                                   //
/***************************************************/
                                                   //
//   Функция примера прорисовки точек:
void pixelExample(){
     printTitle("Pixels", 1);
     for(int i=0; i<100; i++){
        oled.pixel(random(SCREEN_WIDTH), random(SCREEN_HEIGHT));
        oled.display(); delay(10);
     }
}

//   Функция примера прорисовки линий:
void lineExample(){
     int middleX = SCREEN_WIDTH  / 2;
     int middleY = SCREEN_HEIGHT / 2;
     int xEnd, yEnd;
     int lineWidth = min(middleX, middleY);
     printTitle("Lines!", 1);
     for(int i=0; i<3; i++){ // Прорисовываем 3 раза
         for(int deg=0; deg<360; deg+=15){ // Прорисовка белых линий
             xEnd = lineWidth * cos(deg * PI / 180.0);
             yEnd = lineWidth * sin(deg * PI / 180.0);
             oled.line(middleX, middleY, middleX + xEnd, middleY + yEnd);
             oled.display();
             delay(10);
         }
         for(int deg=0; deg<360; deg+=15){ // Прорисовка тёмных линий (стирание)
             xEnd = lineWidth * cos(deg * PI / 180.0);
             yEnd = lineWidth * sin(deg * PI / 180.0);
             oled.line(middleX, middleY, middleX + xEnd, middleY + yEnd, BLACK, NORM);
             oled.display();
             delay(10);
         }
     }
}

//   Функция примера прорисовки и выполнения примера игры
void shapeExample(){
     printTitle("Shapes!", 0);
     int paddleW = 3;  // Paddle width
     int paddleH = 15;  // Paddle height
     int paddle0_Y = (SCREEN_HEIGHT / 2) - (paddleH / 2);
     int paddle0_X = 2;
     int paddle1_Y = (SCREEN_HEIGHT / 2) - (paddleH / 2);
     int paddle1_X = SCREEN_WIDTH - 3 - paddleW;
     int ball_rad = 2;
     int ball_X = paddle0_X + paddleW + ball_rad;
     int ball_Y = random(1 + ball_rad, SCREEN_HEIGHT - ball_rad);//paddle0_Y + ball_rad;
     int ballVelocityX = 1;
     int ballVelocityY = 1;
     int paddle0Velocity = -1;
     int paddle1Velocity = 1;
     while( (ball_X - ball_rad > 1) && (ball_X + ball_rad < SCREEN_WIDTH - 2) ){
         ball_X+=ballVelocityX;
         ball_Y+=ballVelocityY;
         if(ball_X - ball_rad < paddle0_X + paddleW){ if((ball_Y > paddle0_Y) && (ball_Y < paddle0_Y + paddleH)){ball_X++; ballVelocityX = -ballVelocityX;}}
         if(ball_X + ball_rad > paddle1_X){           if((ball_Y > paddle1_Y) && (ball_Y < paddle1_Y + paddleH)){ball_X--; ballVelocityX = -ballVelocityX;}}
         if((ball_Y <= ball_rad) || (ball_Y >= (SCREEN_HEIGHT - ball_rad - 1)))                                 {ballVelocityY = -ballVelocityY;} paddle0_Y += paddle0Velocity; paddle1_Y += paddle1Velocity;
         if((paddle0_Y <= 1) || (paddle0_Y > SCREEN_HEIGHT - 2 - paddleH))                                      {paddle0Velocity = -paddle0Velocity;}
         if((paddle1_Y <= 1) || (paddle1_Y > SCREEN_HEIGHT - 2 - paddleH))                                      {paddle1Velocity = -paddle1Velocity;}
         oled.clear(PAGE);
         oled.rect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT);
         oled.rectFill(SCREEN_WIDTH/2 - 1, 0, 2, SCREEN_HEIGHT);
         oled.rectFill(paddle0_X, paddle0_Y, paddleW, paddleH);
         oled.rectFill(paddle1_X, paddle1_Y, paddleW, paddleH);
         oled.circle(ball_X, ball_Y, ball_rad);
         oled.display();
         delay(25);
     }   delay(1000);
}

//   Функция примера вывода текста различными шрифтами
void textExamples(){
     printTitle("Text!", 1);
     // Вывод всех символов (от 0 до 255) для шрифта с номером 0 (0-5x7, 1-8x16, 2-семисегментный, 3-большие цифры, 4-31x48)
     oled.clear(PAGE);
     oled.setFontType(0);
     oled.setCursor(0, 0);
     for(int i=0; i<=255; i++){ // проходим по 256 символам
         oled.write(i);
         oled.display();
         delay(10);
         if((i%60 == 0) && (i != 0)){delay(500); oled.clear(PAGE); oled.setCursor(0, 0);} // далее выводим на новой странице
     }
     delay(500);
     // Вывод некоторых символов для шрифта с номером 1 (0-5x7, 1-8x16, 2-семисегментный, 3-большие цифры, 4-31x48)
     oled.setFontType(1);
     oled.clear(PAGE); oled.setCursor(0, 0); oled.print(" !\"#$%&'()*+,-./01234"); oled.display(); delay(1000);
     oled.clear(PAGE); oled.setCursor(0, 0); oled.print("56789:;<=>?@ABCDEFGHI" ); oled.display(); delay(1000);
     oled.clear(PAGE); oled.setCursor(0, 0); oled.print("JKLMNOPQRSTUVWXYZ[\\]^"); oled.display(); delay(1000);
     oled.clear(PAGE); oled.setCursor(0, 0); oled.print("_`abcdefghijklmnopqrs" ); oled.display(); delay(1000);
     oled.clear(PAGE); oled.setCursor(0, 0); oled.print("tuvwxyz{|}~"           ); oled.display(); delay(1000);
     // Вывод показаний с аналогового входа A0 шрифтом с номером 2 (0-5x7, 1-8x16, 2-семисегментный, 3-большие цифры, 4-31x48)
     for(int i=0; i<25; i++){ // выводим 25 показаний
         oled.clear(PAGE);
         oled.setCursor(0, 0);
         oled.setFontType(0);
         oled.print("A0: ");
         oled.setFontType(2);
         oled.print(analogRead(A0));
         oled.setCursor(0, 16);
         oled.display();
         delay(100);
     }
     // Вывод подобия секундомера шрифтом с номером 3 (0-5x7, 1-8x16, 2-семисегментный, 3-большие цифры, 4-31x48)
     oled.setFontType(3);
     int ms = 0, s = 0;
     while (s <= 5){
         oled.clear(PAGE);
         oled.setCursor(0, 0);
         oled.print("00");
         oled.print(s);
         oled.print(":");
         oled.print(ms);
         oled.display();
         ms++; if(ms >= 10){ms = 0; s++;}
         delay(10);
     }
     // Вывод текста OLED шрифтом с номером 4 (0-5x7, 1-8x16, 2-семисегментный, 3-большие цифры, 4-31x48)
     oled.setFontType(4);
     oled.clear(PAGE); oled.setCursor(0, 0); oled.print("OL"); oled.display(); delay(1000);
     oled.clear(PAGE); oled.setCursor(0, 0); oled.print("ED"); oled.display(); delay(1000);
}

//   Функция вывода текста перед демонстрацией примера
void printTitle(String title, int font){
     int middleX = SCREEN_WIDTH  / 2;
     int middleY = SCREEN_HEIGHT / 2;
     oled.clear(PAGE);
     oled.setFontType(font);
     oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)), middleY - (oled.getFontHeight() / 2));
     oled.print(title);
     oled.display();
     delay(1500);
     oled.clear(PAGE);
}