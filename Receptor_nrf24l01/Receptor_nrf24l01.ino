//Librerias utilizadas
#include <RF24.h>           //Transceptor nRF20L01+
#include <LiquidCrystal.h>  //Pantalla LCD

//Objeto del transceptor de radio
RF24 radio(48, 49);

//Objeto de la pantalla LCD
LiquidCrystal lcd(34, 32, 30, 28, 26, 24, 22);

//Estructura con el paquete de datos
struct PAQUETE {
  float temperatura;
  float humedad;
};

//Instancia de la estructura con los datos a recibir
PAQUETE datos;

//Direccion de recepction de datos
const uint8_t dirLect[5] = { 0x00, 0x00, 0x00, 0x00, 0x01, };

void setup() {
  //Inicializa el puerto serie
  Serial.begin(9600);

  //Inicializa la pantalla LCD
  lcd.begin(16, 2);

  //Imprime en la pantalla los elementos fijos de texto
  lcd.setCursor(0, 0);
  lcd.print("RH:");
  lcd.setCursor(9, 0);
  lcd.print("T:");
  lcd.setCursor(6, 1);
  lcd.print("RCD0");

  //Inicializa el transceptor nRF24L01+ y lo coloca en modo de
  //recepcion
  radio.begin();
  radio.openReadingPipe(1, dirLect);
  radio.startListening();
}

void loop() {
  char numero[16];

  //Verifica si han llegado datos al transceptor
  if (radio.available()) {
    //Si hay datos, los lee. Para ello se pasa la direccion de
    //la estructura de datos y su longitud.
    radio.read(&datos, sizeof(datos));

    //Imprime en la terminal serie los datos recibidos
    Serial.print("T = ");
    Serial.print(datos.temperatura);
    Serial.print("   H = ");
    Serial.println(datos.humedad);

    //Imprime en la pantalla LCD la humedad relativa
    lcd.setCursor(4, 0);
    sprintf(numero, "%3d%%", int(datos.humedad));
    lcd.print(numero);

    //Imprime en la pantalla la temperatura
    lcd.setCursor(12, 0);
    sprintf(numero, "%2d" "\xDF" "C", int(datos.temperatura));
    lcd.print(numero);
  }
}

