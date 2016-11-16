//Librerias utilizadas
#include <RF24.h>     //Transceptor nRF20L01+

//Objeto del transceptor de radio
RF24 radio(49, 53);

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

  //Inicializa el transceptor nRF24L01+ y lo coloca en modo de
  //recepcion
  radio.begin();
  radio.openReadingPipe(1, dirLect);
  radio.startListening();
}

void loop() {
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
  }
}

