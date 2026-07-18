#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int lineSpacing = 20;

void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("READY");
  display.display();
}

void loop()
{
    if (Serial.available())
    {
        String text = Serial.readStringUntil('\n');

        display.clearDisplay();

        int start = 0;
        int y = 0;

        while (true)
        {
            int separator = text.indexOf("|", start);

            if (separator == -1)
            {
                display.setCursor(0, y);
                display.println(text.substring(start));
                break;
            }

            display.setCursor(0, y);
            display.println(text.substring(start, separator));

            y += lineSpacing;
            start = separator + 1;
        }

        display.display();
    }
}