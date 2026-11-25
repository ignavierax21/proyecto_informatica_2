
import processing.serial.*;

Serial puerto;
String mensaje = "";

// Caracteres disponibles
char[] caracteres = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z',
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9',
  '.', ',', '?', ':'
};

// Distribución de la grilla
int columnas = 8;
int teclaAncho = 38;
int teclaAlto = 38;
int separacion = 5;

int inicioX = 620;
int inicioY = 125;

void setup() {
  size(1000, 600);
  surface.setTitle("Codigo Morse");

  println(Serial.list());
  puerto = new Serial(this, "COM3", 9600);
}

void draw() {
  leerArduino();
  
  background(235);

  // Titulo
  fill(30);
  textAlign(CENTER);
  textSize(28);
  text("CODIGO MORSE", width / 2, 45);

  // Panel del mensaje
  fill(255);
  rect(30, 80, 550, 480, 12);
  // Mostrar mensaje recibido
  
  fill(30);
  textAlign(LEFT, TOP);
  textSize(20);
  text(mensaje, 55, 115, 500, 420);

  // Panel de caracteres
  fill(255);
  rect(610, 80, 360, 480, 12);

  // Titulo del teclado
  fill(30);
  textSize(18);
  text("CARACTERES", 740, 100);

  dibujarTeclado();
}

void dibujarTeclado() {

  textAlign(CENTER, CENTER);
  textSize(16);

  for (int i = 0; i < caracteres.length; i++) {

    int columna = i % columnas;
    int fila = i / columnas;

    int x = inicioX + columna * (teclaAncho + separacion);
    int y = inicioY + fila * (teclaAlto + separacion);

    fill(225);
    stroke(160);
    rect(x, y, teclaAncho, teclaAlto, 6);

    fill(30);
    text(caracteres[i], x + teclaAncho / 2,
         y + teclaAlto / 2);
  }

  // Tecla ESPACIO
  int filaEspacio = 5;
  int x = inicioX;
  int y = inicioY + filaEspacio * (teclaAlto + separacion);

  fill(210);
  stroke(160);
  rect(x, y, columnas * teclaAncho +
       (columnas - 1) * separacion, teclaAlto, 6);

  fill(30);
  text("ESPACIO", x + 170, y + teclaAlto / 2);
}


void mousePressed() {

  for (int i = 0; i < caracteres.length; i++) {

    int columna = i % columnas;
    int fila = i / columnas;

    int x = inicioX + columna * (teclaAncho + separacion);
    int y = inicioY + fila * (teclaAlto + separacion);

    if (mouseX >= x && mouseX <= x + teclaAncho &&
        mouseY >= y && mouseY <= y + teclaAlto) {

      char letra = caracteres[i];

      println("Caracter seleccionado: " + letra);

      // Enviar el caracter al Arduino
      puerto.write(letra);
    }
  }

  // Detectar clic en ESPACIO
  int xEspacio = inicioX;
  int yEspacio = inicioY + 5 * (teclaAlto + separacion);

  int anchoEspacio = columnas * teclaAncho +
                     (columnas - 1) * separacion;

  if (mouseX >= xEspacio && mouseX <= xEspacio + anchoEspacio &&
      mouseY >= yEspacio && mouseY <= yEspacio + teclaAlto) {

    println("Espacio seleccionado");

    puerto.write(' ');
  }
}

void leerArduino() {

  while (puerto.available() > 0) {

    String dato = puerto.readStringUntil('\n');

    if (dato != null) {

      dato = trim(dato);

      if (dato.startsWith("CARACTER:")) {

       String letra = dato.substring(9);
       mensaje += letra;

        println("Recibido desde Arduino: " + letra);
      }
    }
  }
}
