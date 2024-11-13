#include <ESP32Servo.h>

#define DATA_PIN 5   // Pino conectado ao DS do 74HC595
#define LATCH_PIN 22 // Pino conectado ao STCP do 74HC595
#define CLOCK_PIN 23 // Pino conectado ao SHCP do 74HC595
#define EXTRA_PIN 18 // Pino extra para indicar efiencia completa

const int ldr1Pin = 35;  // Pino do LDR 1 no ESP32
const int ldr2Pin = 34;  // Pino do LDR 2 no ESP32
const int servoPin = 13; // Pino do servo no ESP32

const int numLeds = 8; // Número de LEDs no LED bar graph controlado pelo 74HC595

Servo servoMotor;      // Cria o objeto Servo
int posicaoServo = 90; // Posição inicial do servo (meio)

// Inicializando o valor global de luminosidade
int totalLuminosity = 0;

void setup()
{
    initSerial();
    servoSetup();
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(EXTRA_PIN, OUTPUT);   // Pino para indicar efiencia energetica maxima
    digitalWrite(EXTRA_PIN, LOW); // Inicializa a indicação de efiencia energetica maxima como desligada
}

void loop()
{
    handleSolarLight();
    updateLeds(); // Atualiza os LEDs com base no nível de carga
    delay(2000);  // Aguarda 2 segundos antes da próxima leitura
}

void initSerial()
{
    Serial.begin(115200);
    delay(1000);
}

void servoSetup()
{
    servoMotor.attach(servoPin, 500, 2400); // Configuração dos pulsos para ESP32
    servoMotor.write(posicaoServo);         // Define posição inicial do servo
}

void handleSolarLight()
{
    // Lê a intensidade de luz dos LDRs e utiliza a função map
    int luminosity1 = map(analogRead(ldr1Pin), 0, 4095, 100, 0);
    int luminosity2 = map(analogRead(ldr2Pin), 0, 4095, 100, 0);

    // Exibe os valores dos LDRs no monitor serial
    Serial.println("----=()=----");
    Serial.print("Luz LDR 1: ");
    Serial.println(luminosity1);
    Serial.print("Luz LDR 2: ");
    Serial.println(luminosity2);

    // Movimenta o servo para o lado que recebe mais luz solar
    if (luminosity1 > luminosity2 + 5) // Ajuste de 5% para evitar pequenas variacões
    {                                              
        posicaoServo = min(posicaoServo + 5, 180); // Move para a direita
        servoMotor.write(posicaoServo);
        Serial.println("Correção para a direita");
    }
    else if (luminosity2 > luminosity1 + 5)
    {
        posicaoServo = max(posicaoServo - 5, 0); // Move para a esquerda
        servoMotor.write(posicaoServo);
        Serial.println("Correção para a esquerda");
    }
    else
    {
        Serial.println("Nenhuma mudança de correção");
    }

    // Atualiza o nível de carga com a média das leituras
    totalLuminosity = (luminosity1 + luminosity2) / 2;
    Serial.print("Eficiência: ");
    Serial.print(totalLuminosity);
    Serial.println("%");
}

// Função para atualizar os LEDs conforme o nível de efiencia energetica
void updateLeds()
{
    // Mapeia o nível de carga para o número de LEDs a serem acesos
    int ledsToLight = map(totalLuminosity, 0, 100, 0, numLeds);

    // Variável para armazenar o padrão dos LEDs
    byte ledPattern = 0;

    // Define os bits de `ledPattern` para acender os LEDs necessários
    for (int i = 0; i < ledsToLight; i++)
    {
        ledPattern |= (1 << i); // Liga os LEDs até o índice `ledsToLight`
    }

    // Envia o padrão para o shift register
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, ledPattern); // Envia o padrão de bits
    digitalWrite(LATCH_PIN, HIGH);

    // Se todos os LEDs estiverem acesos, indica que aeficiencia energética está no máximo
    if (ledsToLight == numLeds)
    {
        digitalWrite(EXTRA_PIN, HIGH); // Liga a indicação de eficiencia energética máxima
    }
    else
    {
        digitalWrite(EXTRA_PIN, LOW); // Desliga a indicação de eficiencia energética máxima
    }
}
