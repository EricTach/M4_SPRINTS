#define B1 4
#define B2 2
#define LEDAM 5 
#define LEDAZ 18
#define LEDVERMELHO 19
#define LEDVERDE 21
#define LDR 25
#define BUZZ 14
int salvo = 0;
int nota = 0;
double freq[15] = {2093, 2349.32, 2637.02, 2793.83, 3135.96, 3520.00, 3951.07, 4186.01	, 4698.63	, 5274.04, 5587.65, 6271.93, 7040.00, 7902.13};
int cho[50] = {};
int nsalva = 0;
void setup() {
 Serial.begin(115200);
  pinMode(LEDAM, OUTPUT);
  pinMode(LEDAZ, OUTPUT);
  pinMode(LEDVERMELHO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
}
void seq(int numero) {
  
  digitalWrite(LEDAM, numero & 0b0001);
  digitalWrite(LEDAZ, numero & 0b0010);
  digitalWrite(LEDVERMELHO, numero & 0b0100);
  digitalWrite(LEDVERDE, numero & 0b1000);
  
  tone(BUZZ, freq[numero], 500);
  
  delay(500);
}


void loop() {

  int leit = analogRead(LDR);
  int esc = map(leit, 32, 4063, 0, 15); 
  Serial.println(esc);

  if (salvo != esc){
    seq(esc);
    salvo = esc;
    nota = esc;
  }
  
  if (digitalRead(B1) == LOW) {
    cho[nsalva] = nota;
    nsalva++;
    Serial.println("escolhida: ");
    Serial.println(cho[nsalva]);
  }

  if (digitalRead(B2) == LOW) {
    for (int i =0; i <= nsalva; i++){
      seq(cho[i]);
    }
    cho[50] = {};
    nsalva = 0;    
  }
  
  delay(300);
}
