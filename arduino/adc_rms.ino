#define ReadType unsigned long

int adcPin = 0;
ReadType measure;
int R2 = 10000;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(115200);
}

ReadType RMS(int n){
  ReadType acc = 0;
  ReadType val = 0;
  for(int i = 0; i < n; i++)
  {
    val = analogRead(adcPin);
    acc += val*val;
  }
  return sqrt(acc/n);
}

void loop()  {
  measure = RMS(50);
  double R1 = ceil(R2*( 1023.0 / measure - 1.0 ));
  double TC = ( 1.0 / (c1 + c2*log(R1) + c3*log(R1)*log(R1)*log(R1)) ) - 273.15; //STEINHART
  
  Serial.print("Steinhart: ");
  Serial.println(TC);
}


