#define B1 37
#define B2 45
#define LEDAM 15 
#define LEDAZ 18
#define LEDVERMELHO 9
#define LEDVERDE 12
#define LDR 1
#define BUZZ 2

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
void seq(int num) {
  
  digitalWrite(LEDAM, num & 0b0001);
  digitalWrite(LEDAZ, num & 0b0010);
  digitalWrite(LEDVERMELHO, num & 0b0100);
  digitalWrite(LEDVERDE, num & 0b1000);
  
  tone(BUZZ, freq[num], 500);
  
  delay(500);
}


void loop() {

  int read = analogRead(LDR);
  int select = map(read, 32, 4063, 0, 15); 

  if (salvo != select){
    seq(select);
    salvo = select;
    nota = select;
  }
  
  if (digitalRead(B1) == LOW) {
    cho[nsalva] = nota;
    nsalva++;

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



