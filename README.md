# Documentação Técnica - Monitoramento de Saúde com ESP32 e MQTT
## Introdução
Este código implementa um sistema de monitoramento de saúde usando o microcontrolador ESP32, sensores DHT22 (temperatura e umidade), LEDs indicadores e comunicação MQTT para a troca de dados.

<br>

## Componentes
1. ESP32: Microcontrolador responsável por coletar dados do sensor e controlar os LEDs.
2. DHT22: Sensor de temperatura e umidade utilizado para medir as condições ambientais.
3. LEDs: Dois LEDs (vermelho e amarelo) indicam alertas com base nas leituras do sensor.

<br>
   
## Configurações Iniciais
Rede Wi-Fi
O ESP32 se conecta a uma rede Wi-Fi configurada no código, fornecendo acesso à internet para comunicação MQTT.

cpp
Copy code
const char* ssid = "Sua-Rede-WiFi";
const char* password = "Sua-Senha";

<br>

## MQTT
As configurações do servidor MQTT são definidas no código. Certifique-se de substituir esses valores pelos do seu servidor.

cpp
Copy code
const char* mqtt_server = "seu.mqtt.servidor";

<br>

## Setup
A função setup() é executada uma vez no início do programa e realiza as seguintes operações:

1. Configuração dos pinos: Define os pinos como saída para os LEDs.
2. Inicialização da comunicação serial: Para debug e visualização de mensagens no monitor serial.
3. Configuração da rede Wi-Fi: Conecta o ESP32 à rede Wi-Fi.
4. Configuração do cliente MQTT: Estabelece a conexão com o servidor MQTT.
5. Configuração do sensor DHT22: Inicializa a comunicação com o sensor de temperatura e umidade.

<br>
   
## Loop Principal
A função loop() é executada continuamente e realiza as seguintes operações:
1. Reconexão MQTT: Verifica se o cliente MQTT está conectado. Se não estiver, tenta reconectar.
2. Leitura de Dados: Obtém dados do sensor DHT22 (temperatura e umidade).
3. Publicação MQTT: Publica os dados no tópico MQTT correspondente.
4. Controle dos LEDs: Controla o piscar dos LEDs com base nas condições de temperatura e umidade.
5. Publicação de Alertas: Publica alertas MQTT com base nas condições de temperatura e umidade.

<br>

## Controle dos LEDs
A função controlarLED() é responsável por controlar o LED indicador. Recebe o pino do LED e a frequência de piscamento como parâmetros.

cpp
Copy code
void controlarLED(int pin, int frequencia) {
  digitalWrite(pin, HIGH);
  delay(frequencia);
  digitalWrite(pin, LOW);
  delay(frequencia);
}

<br>

## Comunicação MQTT
A função callback() é chamada quando uma mensagem MQTT é recebida. Ela interpreta a mensagem e controla o estado do LED.

cpp
Copy code
void callback(char* topic, byte* payload, unsigned int length) {
  // Lógica para interpretar e reagir à mensagem MQTT recebida
}

<br>

## Links
### Youtube
- Sensor de Monitoramento de Saúde:

<br>

## Autores
| Nome               | RM     |
| ------------------ | ------ |
| Ana Karolyne       | RM93668    |
| Alan Araujo        | RM95355    |
| Iago Coelho        | RM95683    |
| João Marcelo       | RM94983    |
| Valentina Fuzaro   | RM95741    |

<br>

## Considerações Finais
Este código fornece uma estrutura básica para monitoramento de saúde usando ESP32, DHT22 e MQTT. Personalize conforme necessário para atender aos requisitos específicos do seu projeto.
