#include <Stepper.h>
#include "ESP32_Servo.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

Servo myHatch;
Servo myShovel;

int pos = 0;
bool openH = false;
bool shovelDown = false;


BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
float txValue = 0;
bool convert = false;
String rxString = "";
std::string rxValue;

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0) {
      convert = true;
      Serial.println(" ");
      Serial.print("Received data: ");
      for (int i = 0; i < rxValue.length(); i++) {
        Serial.print(rxValue[i]);
        rxString = rxString + rxValue[i];
      }
    }
  }
};

Stepper myStepper(2048, 18, 22, 19, 23);
// (passosPorRevolução, Ini1, Ini3, Ini2, Ini4);

void setup() {
  Serial.begin(115200);
  myStepper.setSpeed(13);  // Velocidade de rotação dos motores de passo
  myHatch.attach(4);
  myShovel.attach(2);

  // Configuração e inicialização do serviço Bluetooth Low Energy
  BLEDevice::init("J4S0N-V1");  // Nome do Protótipo
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_TX,
    BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX,
    BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Esperando conexão com cliente para notificar...");
  Serial.println(" ");
}

// Código a ser rodado
void loop() {
  if (deviceConnected) {
    if (convert) convertControlpad();
  }
  delay(50);
}

// ************************* CONVERT CONTROLPAD CODE ************************
void convertControlpad() {
  convert = false;
  Serial.print("      ");
  if (rxString == "!B11:") {
    while (rxString == "!B11:") {
      if (openH == false) {
        openH = true;
        for (int i = 0; i <= 180; i++) {
          myHatch.write(i);
        }
      }
    }
    if (openH == true) {
      openH = false;
      for (int i = 180; i >= 0; i--) {
        myHatch.write(i);
      }
    }
  }  // Apertou Botão 01

  else if (rxString == "!B10;") {Serial.println("Largou botão 01");} 

  else if (rxString == "!B219"){
    while (rxString == "!B219") {
      if (shovelDown == false) {
        shovelDown = true;
        for (int i = 0; i >= -90; i--) {
          myShovel.write(i);
        }
      }
    }
    if (shovelDown == true) {
      shovelDown = false;
      for (int i = -90; i <= 0; i++) {
        myShovel.write(i);
      }
    }
  }  // Apertou Botão 02
  
  else if (rxString == "!B20:") {Serial.println("Largou botão 02");}

  else if (rxString == "!B318") {Serial.println("Apertou botão 03");} 
  else if (rxString == "!B309") {Serial.println("Largou botão 03");}

  else if (rxString == "!B417") {Serial.println("Apertou botão 04");} 
  else if (rxString == "!B408") {Serial.println("Largou botão 04");}

  else if (rxString == "!B516") {  // Seta do controle apontando para cima
    Serial.println("Going foward");
    while (rxString == "!B516") {
      myStepper.step(10);
      }
    } 
  else if (rxString == "!B507") Serial.println("Largou seta cima");

  else if (rxString == "!B615") {  // Seta do controle apontando para baixo
    Serial.println("Going Backwards");
    while (rxString == "!B615") {
      myStepper.step(10);
      }
    } 
  else if (rxString == "!B606") {Serial.println("Largou seta baixo");}

  else if (rxString == "!B714") {Serial.println("Apertou seta esquerda");}
  else if (rxString == "!B705") {Serial.println("Largou seta esquerda");}

  else if (rxString == "!B813") {Serial.println("Apertou seta direita");}
  else if (rxString == "!B804") {Serial.println("Largou seta direita");}
  rxString = "";
}
