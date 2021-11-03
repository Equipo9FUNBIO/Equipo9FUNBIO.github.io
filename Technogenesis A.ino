# define entrada 2
# define audio1 8
# define audio2 9

void setup() {
pinMode (entrada, INPUT);
pinMode (audio1, OUTPUT);
pinMode (audio2, OUTPUT);
}

void loop() {
int v_entrada = digitalRead(entrada);
if(v_entrada==1){
  tone(audio1,80,1000 ); // (PIN, FRECUENCIA, DURACIÓN).
  tone(audio2,80,1000 );
 }
}
