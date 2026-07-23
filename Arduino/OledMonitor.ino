#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int lineSpacing = 20;
unsigned long lastReceived = 0;

void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Not Connected");
  display.display();
}

void loop()
{
    if (Serial.available())
    {
        lastReceived = millis();

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

    // 5000 milliseconds = 5 seconds
    if (millis() - lastReceived >= 5000)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Not Connected");
        display.display();
    }
}