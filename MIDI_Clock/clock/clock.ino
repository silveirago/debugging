#include <MIDIUSB.h>

// Define o tempo (batidas por minuto)
const int bpm = 120;
const int pulsesPerQuarterNote = 24;
const long msPerMinute = 60000;  // Usando 'long' para evitar overflow
const long interval = msPerMinute / (bpm * pulsesPerQuarterNote);

unsigned long lastClockTime = 0;

void setup() {
  Serial.begin(115200);

  // Espera até que a comunicação serial esteja estabelecida
  while (!Serial) {
    ; // Espera aqui até a comunicação serial ser inicializada
  }
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastClockTime >= interval) {
    // Envio do clock MIDI
    sendMIDIClock();

    // Atualiza o tempo do último clock enviado
    lastClockTime = currentTime;
  }
}

void sendMIDIClock() {
  midiEventPacket_t clock = {0x0F, 0xF8, 0x00, 0x00};
  MidiUSB.sendMIDI(clock);
  MidiUSB.flush();
}
