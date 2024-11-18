#include <SPI.h>
#include <Adafruit_SHT31.h>
#include <MS5611.h>

// Inisialisasi sensor SHT31 dan MS5611
Adafruit_SHT31 sht31 = Adafruit_SHT31();
MS5611 ms5611;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Inisialisasi I2C

  // Inisialisasi SHT31
  if (!sht31.begin(0x44)) { // 0x44 adalah alamat default SHT31
    Serial.println("Gagal mendeteksi sensor SHT31!");
    while (1);
  } else {
    Serial.println("SHT31 berhasil diinisialisasi.");
  }

  // Inisialisasi MS5611
  if (!ms5611.begin()) { // Alamat I2C default MS5611
    Serial.println("Gagal mendeteksi sensor MS5611!");
    while (1);
  } else {
    Serial.println("MS5611 berhasil diinisialisasi.");
  }
  ms5611.setOversampling(OSR_ULTRA_HIGH);
}

void loop() {
  // Membaca data dari SHT31
  float suhu_sht31 = sht31.readTemperature(); // SHT31 suhu
  float kelembapan = sht31.readHumidity();    // SHT31 kelembapan

  if (!isnan(suhu_sht31) && !isnan(kelembapan)) {
    Serial.print("SHT31 - Suhu: ");
    Serial.print(suhu_sht31);
    Serial.print(" °C, Kelembapan: ");
    Serial.print(kelembapan);
    Serial.println(" %");
  } else {
    Serial.println("Gagal membaca data dari SHT31!");
  }

  // Membaca data dari MS5611
  if (ms5611.read() == MS5611_READ_OK) {
    float suhu_ms5611 = ms5611.getTemperature(); // MS5611 suhu
    float tekanan = ms5611.getPressure();        // MS5611 tekanan

    Serial.print("MS5611 - Suhu: ");
    Serial.print(suhu_ms5611);
    Serial.print(" °C, Tekanan: ");
    Serial.print(tekanan);
    Serial.println(" hPa");
  } else {
    Serial.println("Gagal membaca data dari MS5611!");
  }

  delay(2000); // Tunggu 2 detik sebelum pembacaan berikutnya
}
