#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_GFX.h>

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

boolean RecordOn = false;

#define FRAME_X 10//this is for button1
#define FRAME_Y 60
#define FRAME_W 100
#define FRAME_H 50


#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W/2)
#define REDBUTTON_H FRAME_H


#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W/2)
#define GREENBUTTON_H FRAME_H


#define FRAME_X1 130//this is for button2
#define FRAME_Y1 60
#define FRAME_W1 100
#define FRAME_H1 50


#define REDBUTTON_X1 FRAME_X1
#define REDBUTTON_Y1 FRAME_Y1
#define REDBUTTON_W1 (FRAME_W1/2)
#define REDBUTTON_H1 FRAME_H1


#define GREENBUTTON_X1 (REDBUTTON_X1 + REDBUTTON_W1)
#define GREENBUTTON_Y1 FRAME_Y1
#define GREENBUTTON_W1 (FRAME_W1/2)
#define GREENBUTTON_H1 FRAME_H1

#define FRAME_X2 215//this is for button3
#define FRAME_Y2 175
#define FRAME_W2 100
#define FRAME_H2 50


#define REDBUTTON_X2 FRAME_X2
#define REDBUTTON_Y2 FRAME_Y2
#define REDBUTTON_W2 (FRAME_W2/2)
#define REDBUTTON_H2 FRAME_H2


#define GREENBUTTON_X2 (REDBUTTON_X2 + REDBUTTON_W2)
#define GREENBUTTON_Y2 FRAME_Y2
#define GREENBUTTON_W2 (FRAME_W2/2)
#define GREENBUTTON_H2 FRAME_H2


#define Frame_X 25 //this is for the fader slider
#define Frame_Y 175
#define Frame_W 150
#define Frame_H 50

#define CIRCLE_X 275
#define CIRCLE_Y 75
#define CIRCLE_R 20

#define SQUARE_X 270
#define SQUARE_Y 96
#define SQUARE_W 12
#define SQUARE_H 12
#define SQUARE_R 2

#define LINE_X 267
#define LINE_Y 87
#define LINE_L 17



int currentX = Frame_X;
int currentY = Frame_Y;
bool touchLock = false;

int counter = 100;

unsigned long timerecord = 0;

void SQUARE()
{
  tft.drawRoundRect(SQUARE_X, SQUARE_Y, SQUARE_W, SQUARE_H, SQUARE_R, ILI9341_BLACK);
  tft.fillRoundRect(SQUARE_X, SQUARE_Y, SQUARE_W, SQUARE_H, SQUARE_R, ILI9341_BLACK);
}
void LINE()
{
  tft.drawFastHLine(LINE_X, LINE_Y, LINE_L, ILI9341_BLACK);
}

void drawFrame()
{
  tft.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, ILI9341_CYAN);

}

void Circle()
{
  tft.drawCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_R, ILI9341_YELLOW);
  tft.fillCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_R, ILI9341_YELLOW);
}

void redBtn()
{
  tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_GREEN);
  tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_BLACK);
  drawFrame();
  tft.setCursor(GREENBUTTON_X + 6 , GREENBUTTON_Y + (GREENBUTTON_H / 2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("ON");
  RecordOn = false;
}


void greenBtn()
{
  tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_RED);
  tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLACK);
  drawFrame();
  tft.setCursor(REDBUTTON_X + 6 , REDBUTTON_Y + (REDBUTTON_H / 2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("OFF");
  RecordOn = true;
}
void redBtn1()//this is for button2
{
  tft.fillRect(REDBUTTON_X1, REDBUTTON_Y1, REDBUTTON_W1, REDBUTTON_H1, ILI9341_GREEN);/////////////////////this is for button2
  tft.fillRect(GREENBUTTON_X1, GREENBUTTON_Y1, GREENBUTTON_W1, GREENBUTTON_H1, ILI9341_BLACK);
  drawFrame();
  tft.setCursor(GREENBUTTON_X1 + 6 , GREENBUTTON_Y1 + (GREENBUTTON_H1 / 2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("ON");
  RecordOn = false;
}



void greenBtn1()//this is for button2
{
  tft.fillRect(GREENBUTTON_X1, GREENBUTTON_Y1, GREENBUTTON_W1, GREENBUTTON_H1, ILI9341_RED);/////////////////this is for button2
  tft.fillRect(REDBUTTON_X1, REDBUTTON_Y1, REDBUTTON_W1, REDBUTTON_H1, ILI9341_BLACK);
  drawFrame();
  tft.setCursor(REDBUTTON_X1 + 6 , REDBUTTON_Y1 + (REDBUTTON_H1 / 2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("OFF");
  RecordOn = true;
}

void redBtn2()//this is for button3
{
  tft.fillRect(REDBUTTON_X2, REDBUTTON_Y2, REDBUTTON_W2, REDBUTTON_H2, ILI9341_GREEN);/////////////////////this is for button2
  tft.fillRect(GREENBUTTON_X2, GREENBUTTON_Y2, GREENBUTTON_W2, GREENBUTTON_H2, ILI9341_BLACK);
  drawFrame();
  tft.setCursor(GREENBUTTON_X2 + 6 , GREENBUTTON_Y2 + (GREENBUTTON_H2 / 2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("ON");
  RecordOn = false;
}



void greenBtn2()//this is for button3
{
  tft.fillRect(GREENBUTTON_X2, GREENBUTTON_Y2, GREENBUTTON_W2, GREENBUTTON_H2, ILI9341_RED);/////////////////this is for button2
  tft.fillRect(REDBUTTON_X2, REDBUTTON_Y2, REDBUTTON_W2, REDBUTTON_H2, ILI9341_BLACK);
  drawFrame();
  tft.setCursor(REDBUTTON_X2 + 6 , REDBUTTON_Y2 + (REDBUTTON_H2 / 2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("OFF");
  RecordOn = true;
}  


void DrawFrame (int x, int y, int w, int h, uint16_t color)
{
  tft.drawRect(x, y, w, h, color);
}

void DrawBox (int x, int y, int w, int h, uint16_t fill)
{
  tft.fillRect(x, y, w, h, fill);
}

void Btn()
{
  tft.setCursor(5 , 20);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tft.begin();
  if (!ts.begin())
  {
    Serial.println("Unable to start touchscreen");
  }
  else
  {
    Serial.println("Touchscreen Started");
  }

  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  tft.fillScreen(ILI9341_CYAN);//this is to change the background
  tft.setRotation(1);
  greenBtn();//this is to set the beginning state of button1
  greenBtn1();//this is to set the beginning state of button2
  greenBtn2();//this is to set the beginning state of button 3
  DrawBox (Frame_X, Frame_Y, Frame_W, Frame_H, ILI9341_BLACK);
  DrawBox(currentX, currentY, 50, 50, ILI9341_GREEN); //set the slider color
  Circle();
  SQUARE();

  tft.drawLine(264, 80, 270, 90, ILI9341_BLACK);////diagonal lines for birghtness lightbulb filliment
  tft.drawLine(286, 80, 281, 90, ILI9341_BLACK);

  tft.drawLine(271, 106, 281, 105, ILI9341_WHITE);///diagonal lines for screw base
  tft.drawLine(271, 103, 281, 102, ILI9341_WHITE);
  tft.drawLine(271, 100, 281, 99, ILI9341_WHITE);

  tft.drawCircle(195, 164, 2, ILI9341_BLACK);/////this is for the music note symbol
  tft.fillCircle(195, 164, 2, ILI9341_BLACK);
  tft.drawCircle(210, 164, 2, ILI9341_BLACK);
  tft.fillCircle(210, 164, 2, ILI9341_BLACK);
  tft.drawLine(197, 164, 201, 149, ILI9341_BLACK);
  tft.drawLine(212, 164, 216, 149, ILI9341_BLACK);
  tft.drawFastHLine(201, 149, 15, ILI9341_BLACK);
  tft.drawFastHLine(201, 150, 15, ILI9341_BLACK);
  tft.drawFastHLine(201, 151, 15, ILI9341_BLACK);
  tft.drawFastHLine(201, 155, 14, ILI9341_BLACK);

 
  tft.setCursor(8 , 200);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("0%");

  tft.setCursor(180 , 200);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("100%");

  tft.setCursor(40 , 155);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("Interior Cabin Lights");

  tft.setCursor(80 , 25);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("STEVEN AND ELIZABETH LAHR");

  tft.setCursor(25 , 5);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("TEARDROP TRAILER V.1.2");

  tft.setCursor(20 , 120);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("DRV SIDE LIGHT");

  tft.setCursor(130 , 120);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("PASS SIDE LIGHT");


  tft.setCursor(257 , 120);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("Screen");

  tft.setCursor(247 , 130);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("Brightness");

  tft.setCursor(225 , 155);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("Bluetooth Audio");
  
  tft.setCursor(264 ,74);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println("oooo");
}

int ReadXPoint ()
{
  TS_Point p = ts.getPoint();
  p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
  return p.y;
}
int ReadYPoint()
{
  TS_Point p = ts.getPoint();
  p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
  return (tft.height() - p.x);
}

void loop() {
  int touchx = 0;
  int touchy = 0;
  // put your main code here, to run repeatedly:
  if (ts.touched())
  {
    timerecord = millis();
    analogWrite(3, map(counter, 0, 100, 10, 255));
    
    if (!ts.bufferEmpty())  // SLIDER CODE
    {
      touchx = ReadXPoint();
      touchy = ReadYPoint();
    }

    if ((touchy > Frame_Y) && (touchy < (Frame_Y + Frame_H))) {
      if ((touchx > (Frame_X)) && (touchx < (Frame_X + Frame_W)))
      {
        currentX = ReadXPoint()-25;
        DrawBox (Frame_X, Frame_Y, Frame_W, Frame_H, ILI9341_BLACK);
        if (currentX > (Frame_X + Frame_W - 50))
        {
          currentX = (Frame_X + Frame_W - 50);
          DrawBox((Frame_X + Frame_W - 50), currentY, 50, 50, ILI9341_GREEN);
        }
        else if (currentX < (Frame_X))
        {
          currentX = Frame_X;
          DrawBox(Frame_X, Frame_Y, 50, 50, ILI9341_GREEN);
        }
        else
        {
          DrawBox(currentX, currentY, 50, 50, ILI9341_GREEN);
        }
        analogWrite(5, map(currentX, 25, 125, 0, 255)); /////this is for PWM of the led's
        
        Serial.println(currentX);
        Serial.println(currentY);
      }
    }


    // See if there's any  touch data for us
    if (!ts.bufferEmpty())
    {

      // Retrieve a point
      TS_Point p = ts.getPoint();
      // Scale using the calibration #'s
      // and rotate coordinate system
      p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
      p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
      int y = tft.height() - p.x;
      int x = p.y;

      if (RecordOn)///this is for button 1
      {
        if ((x > REDBUTTON_X) && (x < (REDBUTTON_X + REDBUTTON_W))) {
          if ((y > REDBUTTON_Y) && (y <= (REDBUTTON_Y + REDBUTTON_H))) {
            Serial.println("Red btn hit");
            redBtn();
            digitalWrite(7, HIGH);
            
            
          }
        }
      }
      else //Record is off (RecordOn == false)
      {
        if ((x > GREENBUTTON_X) && (x < (GREENBUTTON_X + GREENBUTTON_W))) {
          if ((y > GREENBUTTON_Y) && (y <= (GREENBUTTON_Y + GREENBUTTON_H))) {
            Serial.println("Green btn hit");
            greenBtn();
            digitalWrite(7, LOW);
          }
        }
      }

      Serial.println(RecordOn);//////this is for button 2
      if (RecordOn)
      {
        if ((x > REDBUTTON_X1) && (x < (REDBUTTON_X1 + REDBUTTON_W1))) {
          if ((y > REDBUTTON_Y1) && (y <= (REDBUTTON_Y1 + REDBUTTON_H1))) {
            Serial.println("Red btn hit");
            redBtn1();
            digitalWrite(2, HIGH);
          }
        }
      }
      else //Record is off (RecordOn == false)
      {
        if ((x > GREENBUTTON_X1) && (x < (GREENBUTTON_X1 + GREENBUTTON_W1))) {
          if ((y > GREENBUTTON_Y1) && (y <= (GREENBUTTON_Y1 + GREENBUTTON_H1))) {
            Serial.println("Green btn hit");
            greenBtn1();
            digitalWrite(2, LOW);
          }
        }
      }
       Serial.println(RecordOn);//////this is for button 3
      if (RecordOn)
      {
        if ((x > REDBUTTON_X2) && (x < (REDBUTTON_X2 + REDBUTTON_W2))) {
          if ((y > REDBUTTON_Y2) && (y <= (REDBUTTON_Y2 + REDBUTTON_H2))) {
            Serial.println("Red btn hit");
            redBtn2();
            digitalWrite(6, HIGH);
          }
        }
      }
      else //Record is off (RecordOn == false)
      {
        if ((x > GREENBUTTON_X2) && (x < (GREENBUTTON_X2 + GREENBUTTON_W2))) {
          if ((y > GREENBUTTON_Y2) && (y <= (GREENBUTTON_Y2 + GREENBUTTON_H2))) {
            Serial.println("Green btn hit");
            greenBtn2();
            digitalWrite(6, LOW);
          }
        }
      }

      Serial.println(RecordOn);

      if ((x > (CIRCLE_X - CIRCLE_R) && (x < (CIRCLE_X + CIRCLE_R))))
      {
        if (y > (CIRCLE_Y - CIRCLE_R) && (y < (CIRCLE_Y + CIRCLE_R)))
        {
          if (touchLock != true)
          {
            if (counter == 100)
            {
              counter = 0;
            }
            else
            {
              counter += 25;
            }
            analogWrite(3, map(counter, 0, 100, 10, 255));
            touchLock = true;
            delay(50);
          }
        }
      }
    }
  }
  else
  {
    touchLock = false;
        if ((millis()-timerecord) >= 30000)
    {
      analogWrite(3, map(0, 0, 100, 10, 255));
    }
  }

}





