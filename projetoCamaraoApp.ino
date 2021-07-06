
/*
 * UFRPE
 * Nome: David Luan Santos de Carvalho
 * Curso: Lic. em Commputação
 * 
 * Projeto de Iniciação científica em IoT:
 * Carcincultura - Monitoramento de qualidade de água para camarões em cativeiro.
 * Professor Dr.: Obionor Nóbrega.
 * 
 * Resumo:
 * O desafio é criar um sistema IoT que monitora a temperatura a cada 1 segundo
 * e ativa um led na plataforma caso o limiar mínimo/máximo sejam ultrapassados.
 * 
 * Fluxograma:
 * 1.(MODO DE LEITURA)
 * O sistema inicia o monitoramento da temperatura já pré-configuradas nas variáveis globais.
 * tempMin e tempMax.
 * Caso o valor da tempCount ultrapasse tempMin e tempMax, acende um led.
 * Caso não, continua monitorando a temp e apaga o led.
 * 
 * 2.(MODO DE CONFIGURAÇÃO)
 * Se o botão do app seja pressionado (1ª vez), entra no menu de configuração da tempMin.
 * o usuário utiliza o potenciômetro no app para ajustar esse valor que entra na variável potCount.
 * Após clicar com o botão novamente (2ª vez), esse valor de potCount é incluído no tempMin.
 * E logo inicia novamente a leitura em tempo real do valor do potCount para o usuário ajustar qual
 * será a tempMax.
 * Quando o usuário pressionar o botão (3ª vez), o valor de potCount entra na variável tempMax.
 * As temperaturas são configuradas e mostra na tela:
 * 
 * 1.potCount - Valor atual do potenciômetro
 * 2 tempCount - Valor atual do sensor de temperatura
 * 3.tempMin -  Valor atual da temperatura mínima configurada
 * 4.tempMax -  Valor atual da temperatura máxima configurada
 * 
 * V0 = Button
 * V1 = Bar
 * V2 = Led Red
 * V3 = Display
 * V4 = Superchart (Gráfico)
 * V5 - Led Blue
 */

//LIBRARIES
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal.h>
BlynkTimer timer;

//NETWORKING CONFIGURATIONS
char auth[] = "wyCXst8z1d8iLRjQYNz93dliSH5dy3LP";
char ssid[] = "KAKA Coliseu";
char pass[] = "Demario186";

//LCD IN DEVICE
LiquidCrystal lcd(D3, D4, D5, D6, D7, D8);

//TEMPSENSOR IN DEVICE
int tempSensor = A0;
float tempCount;
int tempMin = 28;
int tempMax = 35;

//LED IN DEVICE
int ledRed = D0;
int ledBlue = D1;

//BUZZER IN DEVICE
int buzzer = D2;

//BUTTON IN APP
int button = D1;
int buttonCount;

//POTENCIOMETER IN APP
int potCount;

//LED IN APP
WidgetLED led1(V2);
WidgetLED led2(V5);

//TIMER EVENT
void myTimerEvent(){
  Blynk.virtualWrite(V3, millis() / 1000); //Display
  Blynk.virtualWrite(V4, millis() / 1000); //Gráfico
  
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(tempSensor,INPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledBlue,OUTPUT);
  pinMode(buzzer,OUTPUT);
  timer.setInterval(2000L, myTimerEvent);
  lcd.begin(16, 2);
  welcome();
}

//BUTTON IN APP READING
BLYNK_WRITE(V0){
  if (param.asInt()==1){
    buttonCount = buttonCount + 1;
    //Serial.println(buttonCount);
  }
}

/*
//SUPERCHART IN APP READING
BLYNK_WRITE(V0){
  potCount = param.asInt();
}*/

//POTENCIOMETER IN APP READING
BLYNK_WRITE(V1){
  potCount = param.asInt();
}

//TEMP VERIFICATION
void verifyTemp(){
  tempCount = (float(analogRead(tempSensor))*3.300/(1023))/0.01;
  //Serial.println("Temperatura atual: ");
  //Serial.println(tempCount);
  delay(1000);
}

//ON ALERT TEMPERATURE MIN
void alertOnMin(){
  led2.on();
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledBlue,LOW);
  digitalWrite(buzzer,HIGH);
}

//ON ALERT TEMPERATURE MAX
void alertOnMax(){
  led1.on();
  digitalWrite(ledRed,LOW);
  digitalWrite(ledBlue,HIGH);
  digitalWrite(buzzer,HIGH);
}

//OFF ALERT TEMPERATURE
void alertOff(){
  led2.off();
  led1.off();
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledBlue,HIGH);
  digitalWrite(buzzer,LOW);
}

//LCD WELCOME
void welcome(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Camarao App");
  delay(3000);
  lcd.clear();
  lcd.print("Autor:");
  lcd.setCursor(0,1);
  lcd.print("David Carvalho");
  delay(3000);
  lcd.clear();
}

//LCD TEMP MONITORING
void lcdMonitor(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp Atual: ");
  lcd.setCursor(0,1);
  lcd.print(tempCount);
  lcd.print(" oC");
}

//LCD CONFIG TEMP MIN
void lcdConfigTempMin(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp Minima: ");
  lcd.setCursor(0,1);
  lcd.print(potCount);
  lcd.print(" oC");
  tempMin = potCount;
}
//LCD CONFIG TEMP MAX
void lcdConfigTempMax(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp Maxima: ");
  lcd.setCursor(0,1);
  lcd.print(potCount);
  lcd.print(" oC");
}
//LCD CONFIGURATIONS
void lcdConfigurations(){
  tempMax = potCount;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp Min: ");
  lcd.print(tempMin);
  lcd.print(" oC");
  lcd.setCursor(0,1);
  lcd.print("Temp Max: ");
  lcd.print(tempMax);
  lcd.print(" oC");
  delay(5000);
  lcd.clear();
  buttonCount = 0;
}

void loop() {
  
  Blynk.run();
  //timer.run();
  Blynk.virtualWrite (V3,tempCount);
  Blynk.virtualWrite (V4,tempCount);

  //CONFIGURATION TEMP MIN
  if(buttonCount == 1){
    alertOff();
    lcdConfigTempMin();
  }
  
  //CONFIGURATION TEMP MAX
  else if(buttonCount == 2){
    lcdConfigTempMax();
  }
  
  //CONFIRMATION OF CONFIGURATIONS
  else if (buttonCount == 3){
    lcdConfigurations();
  }
  
  //TEMP MONITORING
  else{
     verifyTemp();
     lcdMonitor();
     
     if((tempCount > tempMax) and (buttonCount == 0)){
      alertOnMax();
     }
     
     else if((tempCount < tempMin) and (buttonCount == 0)){
      alertOnMin();
     }
     
     else{
        alertOff();
     }
  }
}
