#include <FastLED.h>
#include <string.h>

int ultimoA = 0;
int ultimoPush = 0;
int DATOS = 0;
char buffer[64];
int posicion = 0;

CRGB LED[1];

struct Notificacion {
    char source [5];
    int priority;
    char texto[65];
};

Notificacion actual;

bool urgente = false;

void setup()
{
    Serial.begin(9600);
    pinMode(7, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);

    ultimoA = digitalRead(7); // primera lectura real, ya con los pines configurados
    ultimoPush = digitalRead(5);

    FastLED.addLeds<WS2812B, A0, GRB>(LED, 1);
    LED[0] = CRGB::Red;
    FastLED.show();
}

void loop()
{
    int actualA = digitalRead(7);

    // Solo nos importan las transiciones de A. B nunca dispara nada por su
    // cuenta -- se lee solo como referencia, en el instante exacto en que A cambia.
    if (actualA != ultimoA) {
        int actualB = digitalRead(4);

        // La direccion esta en la RELACION entre el nuevo valor de A y B,
        // no en un valor fijo de B. Si terminan iguales, es una direccion;
        // si terminan distintos, es la otra. Esto es consistente en las
        // dos transiciones de A por cada click del encoder.
        if (actualA == actualB) {
            Serial.println("Direccion 1");
        } else {
            Serial.println("Direccion 2");
        }

        ultimoA = actualA; // actualizo la memoria para la proxima vuelta de loop()
    }

    int actualPush = digitalRead(5);

    if(actualPush != ultimoPush && actualPush == LOW){
        Serial.println("Push");
        urgente = false;

        ultimoPush = actualPush;
    }

    while(Serial.available()>0){
        DATOS=Serial.read();    
        if(DATOS != '\n'){
            buffer[posicion] = DATOS;
            posicion = posicion + 1;
        }else{
            buffer[posicion] = '\0';
            Serial.println(buffer);
            posicion = 0;
            char* primero = strtok(buffer, "|");
            char* segundo = strtok(NULL, "|");

            if(strcmp(primero, "C") == 0){
                //es C
            }else{
                char* tercero = strtok(NULL, "|");
                char* cuarto = strtok(NULL, "|");
                Serial.println(segundo);
                Serial.println(tercero);
                Serial.println(cuarto);
                    
                int prioridad = atoi(tercero);
                Serial.println(prioridad);

                if(!urgente || prioridad == 2) {
                    strcpy(actual.source, segundo);
                    strcpy(actual.texto, cuarto);
                    actual.priority = prioridad;

                    if(prioridad == 2) {
                    urgente = true;
                    };                    
                };
            };

        };  
    };

    
}

// Nota: "Direccion 1" / "Direccion 2" son etiquetas genericas -- una vez que
// tengas el encoder real conectado, giralo para un lado, fijate cual mensaje
// sale, y ahi renombralo a CW/CCW (o izquierda/derecha) segun corresponda.
