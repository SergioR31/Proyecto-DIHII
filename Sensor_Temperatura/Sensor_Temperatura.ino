int sensorPin = A0;
int contador = 0;

String entrada;

String address;
String functionCode;
String quantity;
int sizeOfData;
String data;
String dataHex = "";


void setup(){
  Serial.begin (9600);
}

void loop(){
  int value = analogRead(sensorPin);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10;
  
  data = String(celsius);
  
  sizeOfData = (sizeof(String(celsius)))-1;
  
  if(Serial.available()){

    entrada = Serial.readString();

    for (int i=0;i<sizeOfData;i++){
      dataHex += String(data.charAt(i),HEX);
      if(i != (sizeOfData-1)){
        dataHex += " ";
      }
    }

    address = entrada.substring(0,2);
    functionCode = entrada.substring(3,5);
    quantity = entrada.substring(6,8);

    switch (functionCode.substring(1,2).toInt()){
      
      case 1:{
        
        if (Serial.availableForWrite()){
          if(sizeOfData < 10){
            Serial.print(functionCode+" 0"+sizeOfData+" "+dataHex);
          }else{
            Serial.print(functionCode+" "+sizeOfData+" "+dataHex);
          }
        }
      }
      default:{
        }
    }
  }
  dataHex = "";
}
