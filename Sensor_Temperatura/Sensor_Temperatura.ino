int sensorPin = A0;
int contador = 0;

String data;
int sizeOfData;
String entrada;
String dataDEC = "";
char functionCode;
String sDataDEC;
String sDataS;
char sDataC;
String fCode;

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
      int aux = (int)data.charAt(i);
      dataDEC +=String(aux,DEC);
      
      if(i != (sizeOfData-1)){
        dataDEC += " ";
      }
    }

    functionCode = entrada.charAt(4);

    sDataS = String(sizeOfData);
    sDataC = sDataS.charAt(0);
    
    sDataDEC = String(sDataC,DEC);
    fCode = String(functionCode,DEC);

    switch (functionCode){
      
      case '1':{
        
        if (Serial.availableForWrite()){
           Serial.print(fCode+" "+sDataDEC+" "+dataDEC);
        }
      }

      case 'A':{
        if (Serial.availableForWrite()){
          //Serial.print(functionCode);
        }
      }
      
      default:{
        }
    }
  }
  dataDEC = "";
}
