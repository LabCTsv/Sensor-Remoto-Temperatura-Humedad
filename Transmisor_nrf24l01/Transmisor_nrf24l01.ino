//Librerias utilizadas
#include <RF24.h>     //Transceptor nRF20L01+
#include <DHT_U.h>    //Sensor de temperatura (libreria universal)
#include <DHT.h>      //Semsor de temperatura

//Objeto del transceptor de radio
RF24 radio(49, 53);
//Objeto del sensor de temperatura
DHT dht(22, DHT22);

//Estructura con el paquete de datos
struct PAQUETE {
  float temperatura;
  float humedad;
};

//Instancia de la estructura con los datos a enviar
PAQUETE datos;

//Direccion de transmision de datos
const uint8_t dirEscr[5] = { 0x00, 0x00, 0x00, 0x00, 0x01, };

void setup() {
  //Inicializa el puerto serie
  Serial.begin(9600);

  //Inicializa el transceptor nRF24L01+ y lo coloca en modo de
  //transmision
  radio.begin();
  radio.openWritingPipe(dirEscr);

  //Inicializa la libreria del sensor de humedad/temperatura
  dht.begin();
}

void loop() {
  //Prepara la estructura con los datos del sensor antes de
  //enviarla
  datos.temperatura = dht.readTemperature();
  datos.humedad = dht.readHumidity();

  //Imprime los datos en la terminal serie antes de enviarlos
  Serial.print("T = ");
  Serial.print(datos.temperatura);
  Serial.print("   H = ");
  Serial.println(datos.humedad);

  //Envia la estructura mediante el transceptor. Para ello se
  //pasa la direccion de la estructura y su longitud.
  radio.write(&datos, sizeof(datos));

  //Espera un segundo antes de volver a transmitir.
  delay(1000);
}

