
 // Pines
const int boton = 2;
const int botonEspacio = 7;
const int led = 13;
const int buzzer = 8;

// Configuracion del buzzer
const int frecuenciaBuzzer = 500;
const int unidadMorse = 200;

// Variables de tiempo
unsigned long tiempoInicio = 0;
unsigned long tiempoLiberacion = 0;

// Tiempos de deteccion
const unsigned long umbral = 300;
const unsigned long pausaLetra = 1200;
const unsigned long debounce = 50;

// Estados del boton Morse
bool presionado = false;
bool haySimbolos = false;

int lecturaAnteriorMorse = HIGH;
int estadoEstableMorse = HIGH;
unsigned long ultimoCambioMorse = 0;

// Cadenas de texto
String codigoMorse = "";
String mensaje = "";

// Estados del boton de espacio
int lecturaAnteriorEspacio = HIGH;
int estadoEstableEspacio = HIGH;
unsigned long ultimoCambioEspacio = 0;


// Estructura de equivalencias
struct Equivalencia {
  const char* codigo;
  char letra;
};


// Tabla Morse
Equivalencia tablaMorse[] = {
  {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'},
  {"-..", 'D'}, {".", 'E'}, {"..-.", 'F'},
  {"--.", 'G'}, {"....", 'H'}, {"..", 'I'},
  {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
  {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
  {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},
  {"...", 'S'}, {"-", 'T'}, {"..-", 'U'},
  {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
  {"-.--", 'Y'}, {"--..", 'Z'},

  {"-----", '0'}, {".----", '1'},
  {"..---", '2'}, {"...--", '3'},
  {"....-", '4'}, {".....", '5'},
  {"-....", '6'}, {"--...", '7'},
  {"---..", '8'}, {"----.", '9'},

  {".-.-.-", '.'}, {"--..--", ','},
  {"..--..", '?'}, {"---...", ':'},
  {".----.", '\''}, {"-....-", '-'}
};


void LED() {
  if (presionado || estadoEstableEspacio == LOW) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}


// Decodifica Morse
char decoMorse(String codigo) {
  for (int i = 0; i < 42; i++) {
    if (codigo == tablaMorse[i].codigo) {
      return tablaMorse[i].letra;
    }
  }

  return '?';
}


// Busca el codigo
const char* buscarCodigo(char letra) {
  for (int i = 0; i < 42; i++) {
    if (tablaMorse[i].letra == letra) {
      return tablaMorse[i].codigo;
    }
  }

  return "";
}


void setup() {
  pinMode(boton, INPUT_PULLUP);
  pinMode(botonEspacio, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("Traductor iniciado");
}


void loop() {

  // Recibir caracteres desde la computadora
  if (Serial.available() > 0) {
    char letraRecibida = Serial.read();

    Serial.print("Recibido desde PC: ");
    Serial.println(letraRecibida);

    if (letraRecibida == ' ') {
      noTone(buzzer);
      delay(unidadMorse * 7);
    }
    else {
      reproducirMorse(letraRecibida);
    }
  }


  // Antirrebote del boton Morse
  int lecturaMorse = digitalRead(boton);

  if (lecturaMorse != lecturaAnteriorMorse) {
    ultimoCambioMorse = millis();
    lecturaAnteriorMorse = lecturaMorse;
  }

  if (millis() - ultimoCambioMorse >= debounce) {

    if (lecturaMorse != estadoEstableMorse) {
      estadoEstableMorse = lecturaMorse;

      if (estadoEstableMorse == LOW && !presionado) {
        presionado = true;
        tiempoInicio = millis();

        LED();
      }

      else if (estadoEstableMorse == HIGH && presionado) {
        presionado = false;

        unsigned long duracion = millis() - tiempoInicio;
        tiempoLiberacion = millis();

        LED();

        if (duracion < umbral) {
          codigoMorse += ".";
          Serial.println("Punto registrado");
        } else {
          codigoMorse += "-";
          Serial.println("Raya registrada");
        }

        haySimbolos = true;
      }
    }
  }


  // Detectar final de una letra
  if (haySimbolos && !presionado &&
      millis() - tiempoLiberacion >= pausaLetra) {

    Serial.print("Codigo Morse: ");
    Serial.println(codigoMorse);

    char letra = decoMorse(codigoMorse);

    mensaje += letra;

    Serial.print("CARACTER:");
    Serial.println(letra);

    Serial.print("Mensaje: ");
    Serial.println(mensaje);

    codigoMorse = "";
    haySimbolos = false;

    Serial.println("----------------");
  }


  // Antirrebote del boton de espacio
  int lecturaEspacio = digitalRead(botonEspacio);

  if (lecturaEspacio != lecturaAnteriorEspacio) {
    ultimoCambioEspacio = millis();
    lecturaAnteriorEspacio = lecturaEspacio;
  }

  if (millis() - ultimoCambioEspacio >= debounce) {

    if (lecturaEspacio != estadoEstableEspacio) {
      estadoEstableEspacio = lecturaEspacio;

      if (estadoEstableEspacio == LOW) {

        LED();

        if (!haySimbolos && !presionado) {
          mensaje += " ";

          Serial.println("ESPACIO");

          Serial.print("Mensaje: ");
          Serial.println(mensaje);
        }
      }

      else {
        LED();
      }
    }
  }
}


// Reproduce una letra mediante el buzzer
void reproducirMorse(char letra) {

  const char* codigo = buscarCodigo(letra);

  if (codigo[0] == '\0') {
    return;
  }

  for (int i = 0; codigo[i] != '\0'; i++) {

    tone(buzzer, frecuenciaBuzzer);

    if (codigo[i] == '.') {
      delay(unidadMorse);
    }
    else if (codigo[i] == '-') {
      delay(unidadMorse * 3);
    }

    noTone(buzzer);

    if (codigo[i + 1] != '\0') {
      delay(unidadMorse);
    }
  }
}
