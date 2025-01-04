const int piezoPin = A0;       // Piezoelektrik sensörün bağlı olduğu pin
const int speakerPin = 8;      // Hoparlör için dijital pin
const int ledGreen = 5;        // Yeşil LED
const int ledYellow = 6;       // Sarı LED
const int resetButton = 2;     // Sıfırlama butonu

int thresholdLow = 500;        // Orta risk eşiği
int thresholdHigh = 800;       // Yüksek risk eşiği

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(resetButton, INPUT_PULLUP);  // Buton için dahili pull-up direnci etkinleştir

  Serial.begin(9600);  // Seri monitör için
}

void loop() {
  int vibration = analogRead(piezoPin);  // Sensör değerini oku

  // Seri monitörde titreşim seviyesini görüntüle
  Serial.print("Titresim Seviyesi: ");
  Serial.println(vibration);
  delay(100);

  // Titreşim değerine göre uyarı seviyesi belirle
  if (vibration > thresholdLow) {
    triggerAlert(ledYellow);
  } else {
    normalOperation();
  }

  // Sıfırlama butonuna basıldığında tüm uyarıları kapat
  if (digitalRead(resetButton) == LOW) {
    resetSystem();
  }

  delay(1000);  // Sensör okuma hızını kontrol etmek için kısa gecikme
}

void triggerAlert(int ledPin) {
  // Yalnızca belirtilen LED'i yak, diğerlerini söndür
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledPin, HIGH);

  // Hoparlörü aktif et
  digitalWrite(speakerPin, HIGH);

  // Risk seviyesini seri monitöre yazdır
  Serial.print("Titresim var");
  Serial.println();
}

void normalOperation() {
  // Normal durumda yeşil LED açık, diğerleri kapalı
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(speakerPin, LOW);
  Serial.println("Titresim yok");
}

void resetSystem() {
  // Tüm LED'leri ve hoparlörü kapat
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(speakerPin, LOW);

  Serial.println("System Reset!");
}