
//#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display

Adafruit_SSD1306 display(128, 64);  // Create display

//#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
//#include <Fonts/FreeMono9pt7b.h>  // Add a custom font

byte midiCh = 1;

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

  display.clearDisplay();  // Clear the display so we can refresh
  display.setTextSize(4);
  //  display.setFont(&FreeMonoBold12pt7b);  // Set a custom font
  //display.setFont(&FreeMono9pt7b);  // Set a custom font
  //display.setFont(&FreeSansBoldOblique9pt7b);  // Set a custom font
  // Print variable with left alignment:
  display.setCursor(0, 0);  // posição onde vai começar a ser mostrado na tela (x,y)
  //display.println(Variable1);  // Text or value to print
  display.print(midiCh);  // Text or value to print
  display.display();  // Print everything we set previously


}

void loop() {
  // put your main code here, to run repeatedly:

}

/////////////////////////////////////////////
// imprime o valor no display
void printChannel(int n) {

  display.setCursor(0, 60);  // posição onde vai começar a ser mostrado na tela (x,y)
  display.clearDisplay();  // Clear the display so we can refresh

  if (n < 10) {
    display.print("0"); // insere um zero se for menor que 10
    //display.display();
  }

  // Print text:
  display.print(n);  // Imprime no display
  display.display();


}
