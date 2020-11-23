#define posicion_manzana 0
#define posicion_naranja 120
#define posicion_pera 240

int GradoActual = 0;
int GradoDeseado = 0;

const int BotonIzquierda = 16;
const int BotonDerecha = 17;

const int P_Step = 19;
const int P_Dir = 18;
const int led_estado = 13;
const int led_pera = 12;
const int led_naranja = 14;
const int led_manzana = 27;


void setup() {
  pinMode(P_Step, OUTPUT);
  pinMode(P_Dir, OUTPUT);
  pinMode(led_estado, OUTPUT);
  pinMode(led_pera, OUTPUT);
  pinMode(led_naranja, OUTPUT);
  pinMode(led_manzana, OUTPUT);
  pinMode(BotonIzquierda, INPUT);
  pinMode(BotonDerecha, INPUT);
  Serial.begin(9600);
}

void loop() {
  DetectarMensaje();
  ActualizarPosicionMotores();
  ActualizarBotones();
}

void ActualizarPosicionMotores() {
  Serial.print(GradoActual);
  Serial.print("-");
  Serial.print(GradoDeseado);
  Serial.println();
  if (GradoActual < GradoDeseado) {
    SubirGrado();
  }
  else if ( GradoActual > GradoDeseado) {
    BajarGrado();
  }
}

void SubirGrado() {
  Serial.println("Moviendo Abajo");
  GradoActual++;
  MoverMotor(1);
}

void BajarGrado() {
  Serial.println("Moviendo Abajo");
  GradoActual--;
  MoverMotor(-1);
}

void MoverMotor(int Pasos) {
  if (Pasos > 0) {
    digitalWrite(P_Dir, HIGH);
  } else {
    digitalWrite(P_Dir, LOW);
    Pasos = -Pasos;
  }
  for (int i = 0; i < Pasos; i++) {
    digitalWrite(P_Step, HIGH);
    delay(10);
    digitalWrite(P_Step, LOW);
    delay(10);
  }
}

void DetectarMensaje() {
  if (Serial.available()) {
    char Letra = Serial.read();
    digitalWrite(led_estado, 0);
    if (Letra == 'M') {
      GradoDeseado = posicion_manzana;
      Serial.println("Cambiando a Manzana");
      digitalWrite(led_manzana,HIGH);
      digitalWrite(led_pera,LOW);
      digitalWrite(led_naranja,LOW);
    }
    else if (Letra == 'J') {
      GradoDeseado = posicion_naranja;
      Serial.println("Cambiando a Naranja");
      digitalWrite(led_naranja,HIGH);
      digitalWrite(led_pera,LOW);
      digitalWrite(led_manzana,LOW);
    } else if (Letra == 'P') {
      GradoDeseado = posicion_pera;
      Serial.println("Cambiando a Pera");
      digitalWrite(led_pera,HIGH);
      digitalWrite(led_naranja,LOW);
      digitalWrite(led_manzana,LOW);
    }
  }
}
void ActualizarBotones() {
  if (digitalRead(BotonIzquierda)) {
    Serial.println("Reiniciando hacia la izquierda");
    MoverMotor(1);
    GradoActual = 0;
    GradoDeseado = 0;
    digitalWrite(led_pera,LOW);
    digitalWrite(led_naranja,LOW);
    digitalWrite(led_manzana,LOW);
  }
  if (digitalRead(BotonDerecha)) {
    Serial.println("Reiniciando hacia la derecha");
    MoverMotor(-1);
    GradoActual = 0;
    GradoDeseado = 0;
    digitalWrite(led_pera,LOW);
    digitalWrite(led_naranja,LOW);
    digitalWrite(led_manzana,LOW);
  }
}
