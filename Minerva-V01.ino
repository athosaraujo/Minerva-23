#include <Stepper.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
float txValue = 0;
bool convert = false;
String rxString = "";
std::string rxValue;

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0)  {
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
  myStepper.setSpeed(13); // Velocidade de rotação dos motores de passo
  
  // Configuração e inicialização do serviço Bluetooth Low Energy
  BLEDevice::init("J4S0N-V1"); // Nome do Protótipo
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
  if (rxString == "!B11:")      // Apertou Botão 01
  else if (rxString == "!B10;") // Largou Botão 01

  else if (rxString == "!B219") // Apertou Botão 02
  else if (rxString == "!B20:") // Largou Botão 02

  else if (rxString == "!B318") // Apertou Botão 03
  else if (rxString == "!B309") // Largou Botão 03

  else if (rxString == "!B417") // Apertou Botão 04
  else if (rxString == "!B408") // Largou Botão 04

  else if (rxString == "!B516"){ // Seta do controle apontando para cima
      Serial.println("Going foward");
      while(rxString == "!B516"){
      myStepper.step(10);
      }}
  else if (rxString == "!B507") // Largou a seta apontando pra cima

  else if (rxString == "!B615"){ // Seta do controle apontando para baixo
    Serial.println("Going Backwards");
      while(rxString == "!B615"){
      myStepper.step(-10);
      }}
  else if (rxString == "!B606") // Largou a seta apontando pra baixo
    
  else if (rxString == "!B714" // Seta do controle apontando pra esquerda
  else if (rxString == "!B705") // Largou a seta apontando pra esquerda
  
  else if (rxString == "!B813") // Seta do controle apontando pra direita
  else if (rxString == "!B804") // Largou a seta apontando pra direita  
  rxString = "";
}
