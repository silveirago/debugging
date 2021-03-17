
//#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display

//////////////////////
// Scales
#include "scaleNames.h"
#include "scales.h"
#include "notes.h"

Adafruit_SSD1306 display(128, 64);  // Create display

//#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
//#include <Fonts/FreeMono9pt7b.h>  // Add a custom font

/////////////////////////////////////////////
// MIDI CHANNEL
byte MIDI_CH = 2; //* MIDI channel to be used
byte BUTTON_MIDI_CH = 0; //* MIDI channel to be used
byte NOTE = 36; //* Lowest NOTE to be used - if not using custom NOTE NUMBER
byte CC = 1; //* Lowest MIDI CC to be used - if not using custom CC NUMBER

/////////////////////////////////////////////
// SCALES
byte scaleIndex = 8;
byte octaveIndex = 0;
int octave[5] = {-24, -12, 0, 12, 24};

byte display_text_size = 2;

void setup() {

  /////////////////////////////////////////////
  // DISPLAY
  delay(100);  // This delay is needed to let the display to initialize
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
  //display.begin(SSD1306_SWITCHCAPVCC, 0x7A);  // Initialize display with the I2C address of 0x3C
  display.clearDisplay();  // Clear the buffer
  display.setTextColor(WHITE);  // Set color of the text
  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3
  display.setTextWrap(true);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
  // To override this behavior (so text will run off the right side of the display - useful for
  // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
  // with setTextWrap(true).
  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)

  display.setTextSize(display_text_size);
  //  display.setFont(&FreeMonoBold12pt7b);  // Set a custom font
  //display.setFont(&FreeMono9pt7b);  // Set a custom font
  //display.setFont(&FreeSansBoldOblique9pt7b);  // Set a custom font
  // Print variable with left alignment:
  //  display.setCursor(display_pos_x, display_pos_y);  // posição onde vai começar a ser mostrado na tela (x,y)
  //  //display.println(Variable1);  // Text or value to print
  //  display.print(MIDI_CH);  // Text or value to print
  //  display.display();  // Print everything we set previously

  printDisplay(scaleNames[scaleIndex], octave[octaveIndex], MIDI_CH);


}

void loop() {
  // put your main code here, to run repeatedly:

}


/////////////////////////////////////////////
// prints the MIDI channel in the display
void printDisplay(char* scaleName, int octave, byte channel) {

  //  display.setCursor(display_pos_x, display_pos_y);  // posição onde vai começar a ser mostrado na tela (x,y)
  display.clearDisplay();  // Clear the display so we can refresh

  display.setCursor(0, 0);
  display.print("Scl: ");  // Imprime no display
  display.println(scaleName);

  display.setCursor(0, 32);
  display.print("Oct: ");  // Imprime no display
  display.println(octave);

  display.print("Ch: ");  // Imprime no display
  display.println(channel);


  display.print(octave);  // Imprime no display

  display.display();
}
