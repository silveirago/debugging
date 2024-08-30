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
  
  Serial.println("MIDI Clock Iniciado");

  // Verifica o valor do intervalo calculado
  Serial.print("Intervalo calculado: ");
  Serial.println(interval);
}

void loop() {
  unsigned long currentTime = millis();

  // Adiciona mais prints para verificar o andamento do loop
  Serial.println("Loop em execução...");

  if (currentTime - lastClockTime >= interval) {
    Serial.println("Condição do clock atingida, enviando MIDI Clock...");

    // Envio do clock MIDI
    sendMIDIClock();

    // Atualiza o tempo do último clock enviado
    lastClockTime = currentTime;

    Serial.print("MIDI Clock enviado. Intervalo: ");
    Serial.print(interval);
    Serial.println(" ms");
  }

  // Atraso curto para não sobrecarregar o monitor serial
  delay(100); 
}

void sendMIDIClock() {
  midiEventPacket_t clock = {0x0F, 0xF8, 0x00, 0x00};
  MidiUSB.sendMIDI(clock);
  MidiUSB.flush();
  Serial.println("Mensagem de Clock MIDI enviada: 0xF8");
}
