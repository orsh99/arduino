#define THERMISTOR_0_PIN                       A0
#define THERMISTOR_1_PIN                       A1
#define THERMISTOR_NOMINAL_RESISTANCE          50000
#define THERMISTOR_NOMINAL_TEMPERATURE_CELSIUS 25
#define NUMBER_OF_SAMPLES                      5
#define THERMISTOR_BETA_COEFFICIENT            3950  // the beta coefficiency of the thermistor (usually 3000-4000)
#define RESISTOR_RESISTANCE                    50000

int samples[2][NUMBER_OF_SAMPLES];

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t i;
  float averageReading[2];
  float resistance[2];
  float temperature_c[2];

  for (i = 0; i < NUMBER_OF_SAMPLES; i++) {
    samples[0][i] = analogRead(THERMISTOR_0_PIN);
    samples[1][i] = analogRead(THERMISTOR_1_PIN);
    delay(10);
  }

  averageReading[0] = 0;
  averageReading[1] = 0;
  for (i = 0; i < NUMBER_OF_SAMPLES; i++) {
    averageReading[0] += samples[0][i];
    averageReading[1] += samples[1][i];
  }
  averageReading[0] /= NUMBER_OF_SAMPLES;
  averageReading[1] /= NUMBER_OF_SAMPLES;

  Serial.print("Average analog readings: Sensor 0: ");
  Serial.print(averageReading[0]);
  Serial.print(". Sensor 1: ");
  Serial.println(averageReading[1]);

  resistance[0] = RESISTOR_RESISTANCE / (1023 / averageReading[0] - 1);
  resistance[1] = RESISTOR_RESISTANCE / (1023 / averageReading[1] - 1);

  Serial.print("Thermistor resistance: Sensor 0: ");
  Serial.print(resistance[0]);
  Serial.print(". Sensor 1: ");
  Serial.println(resistance[1]);

  temperature_c[0] = steinhart(resistance[0]);
  temperature_c[1] = steinhart(resistance[1]);

  Serial.print("Temperature: Sensor 0: ");
  Serial.print(temperature_c[0]);
  Serial.print("º C. Sensor 1: ");
  Serial.print(temperature_c[1]);
  Serial.println("º C");

  delay(1000);
}

float steinhart(float averageResistance) {
  float result;
  result = averageResistance / THERMISTOR_NOMINAL_RESISTANCE;
  result = log(result);
  result /= THERMISTOR_BETA_COEFFICIENT;
  result += 1.0 / (THERMISTOR_NOMINAL_TEMPERATURE_CELSIUS + 273.15);
  result = 1.0 / result;
  result -= 273.15;

  return result;
}