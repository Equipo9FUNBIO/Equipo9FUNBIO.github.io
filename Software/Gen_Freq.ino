// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Definir pines
int pinUp = 6;int pinDown = 7;
int pinOK=8;int pinFreq1=10;int pinLED=13;
int op=0;int c=0;int i=0; int pot=0; int vol=0;int time1=0; int segundos=0;
int minutos=0; int opciones=0;
int segu=59;
int tiempo=1;//Tiempo de duracion en minutos de la onda mayor a 1 minuto
int minu=tiempo-1;
unsigned long contador = 0;
int Freq[]={20,30,40,50,60,70};
int n=sizeof(Freq)/sizeof(Freq[0]);

//Definir variables
boolean estadoActualB1 = false;
boolean estadoAnteriorB1 = false;
boolean estadoActualB2 = false;
boolean estadoAnteriorB2 = false;

void setup(){
  lcd.begin(16, 2); //(columnas, filas)
  //Definir I/O
  pinMode(pinUp, INPUT);  pinMode(pinDown, INPUT);
  //pinMode(pinMENU, INPUT);
  pinMode(pinOK,INPUT);  pinMode(pinLED,OUTPUT);  pinMode(pinFreq1,OUTPUT);
  
  //Escribir en lcd
  lcd.setCursor(0, 0); lcd.print("PROYECTO");
  lcd.setCursor(0, 1);lcd.print("GEN. FRECUENCIA");
  //Retardo
  delay(1000);
  
  //Borrar lcd
  lcd.clear();
}

boolean efectoRebote(boolean estadoAnterior, int pin){ boolean estadoActual = digitalRead(pin);
  if(estadoAnterior != estadoActual){delay(5);estadoActual = digitalRead(pin);
  }
  return estadoActual;
}


void loop() {

pot=map(analogRead(A0),0,1023,0,20);
  
if(digitalRead(pinOK)==HIGH&&c==1&&vol==pot){ digitalWrite(pinLED,HIGH);  contador=millis();  delay(1);  tone(pinFreq1,Freq[op]);
}
if(vol!=pot&&c==1){c=0; lcd.clear();
}

if(digitalRead(pinUp)==HIGH||digitalRead(pinDown)==HIGH){
  c=0; lcd.clear();  SelecFREQ();
}
  
  if(c==1){contar();
    InputMENU();if(minutos==tiempo){lcd.clear();c=0;
    }
  }else{segundos=0;minutos=0;
    digitalWrite(pinLED,LOW); noTone(pinFreq1);SelecFREQ();
  }

}

void InputMENU(){
 
  lcd.setCursor(0, 0); if(minu-minutos<10){lcd.print("0");}lcd.print(minu-minutos); lcd.print(":"); if(segu-segundos<10){lcd.print("0");} lcd.print(segu-segundos);
  lcd.setCursor(9, 0);lcd.print("Vol: ");if(pot<10){lcd.print("0");} lcd.print(pot);
  lcd.setCursor(0, 1);lcd.print("Freq ");lcd.print(opciones+1);lcd.print(": ");lcd.print(Freq[opciones]);lcd.print(" Hz");

}

void SelecFREQ(){
  estadoActualB1 = efectoRebote(estadoAnteriorB1, pinUp);
  if(!estadoAnteriorB1 && estadoActualB1){opciones++;
    if(opciones>n-1){ opciones = 0;
    }
  }
  estadoAnteriorB1 = estadoActualB1;
  
  estadoActualB2 = efectoRebote(estadoAnteriorB2, pinDown);
  if(!estadoAnteriorB2 && estadoActualB2){opciones--;
    if(opciones<0){opciones = n-1;
    }
  }
  estadoAnteriorB2 = estadoActualB2;
        
      lcd.setCursor(9, 0);lcd.print("Vol: ");if(pot<10){lcd.print("0");} lcd.print(pot);
      lcd.setCursor(0, 1);lcd.print("Freq ");lcd.print(opciones+1);lcd.print(": ");lcd.print(Freq[opciones]);lcd.print(" Hz");     
      CheckLCD();
}
  
void contar(){
  
  if ((millis() - contador) > 999) { //incremento de segundos usando millis
    contador = millis();segundos++;
    //estado_punto^=1; //cambiar cada segundo el punto de ON a OFF
  }
  if (segundos > 59) {segundos = 0; minutos++;
  }
}

void CheckLCD(){
        if(op!=opciones){
      lcd.setCursor(14, 1);
      lcd.print("  "); 
      } else{
         lcd.setCursor(14, 1);//lcd.print((char)223);
         lcd.print("<<"); 
       }
      
      if(digitalRead(pinOK)==HIGH){op=opciones;c=1;vol=pot;lcd.clear();
      }
}
  
