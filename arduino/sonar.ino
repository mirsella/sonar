#include <Servo.h>
Servo monServomoteur;
int position = 0;
int step = 5;
int motion = step;

/* Constantes pour les broches */
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO

/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

/** Fonction setup() */
void setup() {
  // met le servo a 0
  monServomoteur.write(position);

  /* Initialise le port série */
  Serial.begin(9600);

  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);

  monServomoteur.attach(9);
}

/** Fonction loop() */
void loop() {
  if (position >= 180) {
    motion = -step;
  } else if (position <= 0) {
    motion = step;
  }

  position += motion;
  monServomoteur.write(position);

  delay(200); // laisse le moteur le temps de tourner pour pas qu'il pompe tout le courant

  int first = mesure();
  delay(100);
  int second = mesure();
  delay(100);
  int third = mesure();
  int mesures[3] = {first, second, third};
  int mesures_length = sizeof(mesures) / sizeof(mesures[0]);
  qsort(mesures, mesures_length, sizeof(mesures[0]), sort_desc);


  Serial.print(position);
  Serial.print(",");
  Serial.print(mesures[1]);

  /* Affiche les résultats en mm, cm et m */

  //  Serial.print(F("Distance: "));
  //  Serial.print(round(distance_mm));
  //  Serial.print(F("mm ("));
  //  Serial.print(distance_mm) / 10.0, 2);
  //  Serial.print(F("cm, "));
  //  Serial.print(distance_mm / 1000.0, 2);
  //  Serial.println(F("m)"));

  Serial.print(".");
}

int mesure() {
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);

  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  int Idistance_cm = distance_mm / 10 + 0.5;
  return Idistance_cm;
}

// qsort requires you to create a sort function
int sort_desc(const void *cmp1, const void *cmp2)
{
  // Need to cast the void * to int *
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  // The comparison
  return a > b ? -1 : (a < b ? 1 : 0);
  // A simpler, probably faster way:
  //return b - a;
}
