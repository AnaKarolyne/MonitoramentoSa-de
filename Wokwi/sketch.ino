#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>

// Pinos dos componentes
const int DHT_PIN = 15;       // Pino ao qual o sensor DHT22 está conectado
const int ledBpmPin = 2;      // Pino ao qual o LED vermelho está conectado
const int ledOxityPin = 5;     // Pino ao qual o LED amarelo está conectado

DHTesp dht; 

// Configurações de rede MQTT
const char* ssid = "Wokwi-ANA";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

// Cliente WiFi e cliente MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis de controle
unsigned long lastMsg = 0;

void setup_wifi() {
  delay(100);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Callback chamada quando uma mensagem MQTT é recebida
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  
  // Exibe o conteúdo da mensagem
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();

  // Ligar ou desligar o LED com base na mensagem recebida
  if ((char)payload[0] == '1') {
    digitalWrite(2, LOW);   // Ligar o LED (LOW é o nível de voltagem)
  } else {
    digitalWrite(2, HIGH);  // Desligar o LED (HIGH é o nível de voltagem)
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    
    // Gerar um ID de cliente único para a conexão MQTT
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    // Tentar se conectar ao broker MQTT
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");
      
      // Publicar uma mensagem de anúncio após a conexão
      client.publish("/saude/monitoramento/mqtt", "Indobot");
      
      // Se inscrever novamente nos tópicos desejados
      client.subscribe("/saude/monitoramento/mqtt");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(1000);
    }
  }
}

void setup() {
  // Inicializar pinos como saída
  pinMode(2, OUTPUT);  // LED vermelho
  pinMode(5, OUTPUT);  // LED amarelo
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  // Inicializar comunicação com o sensor DHT22
  dht.setup(DHT_PIN, DHTesp::DHT22);
}

// Função para controlar o LED com base na frequência
void controlarLED(int pin, int frequencia) {
  digitalWrite(pin, HIGH);
  delay(frequencia);
  digitalWrite(pin, LOW);
  delay(frequencia);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  
  // Publicar dados a cada segundo
  if (now - lastMsg > 1000) {
    lastMsg = now;
    
    // Obter dados do sensor DHT22
    TempAndHumidity  data = dht.getTempAndHumidity();

    // Publicar temperatura
    String bpm = String(data.temperature, 2);
    client.publish("/saude/monitoramento/bpm", bpm.c_str());
    
    // Publicar umidade
    String spo2 = String(data.humidity, 1);
    client.publish("/saude/monitoramento/spo2", spo2.c_str());

    // Exibir dados no monitor serial
    Serial.print("Oxigenação: ");
    Serial.println(spo2);
    Serial.print("Frequência Cardíaca: ");
    Serial.println(bpm);

    // Controle do LED com base na temperatura
    if (data.temperature > 35) {
      int frequenciaBpmLED = map(data.temperature, -40, 80, 50, 500);
      controlarLED(ledBpmPin, frequenciaBpmLED);

      // Publicar mensagem dependendo da temperatura
      if (data.temperature > 40) {
        client.publish("/saude/monitoramento/alertabpm", "Temperatura muito alta!");
      } else {
        client.publish("/saude/monitoramento/alertabpm", "Temperatura elevada.");
      }
    }

    // Controle do LED com base na umidade
    if (data.humidity < 35) {
      int frequenciaOxityLED = map(data.humidity, 0, 30, 10, 100);
      controlarLED(ledOxityPin, frequenciaOxityLED);
    
      // Publicar mensagem dependendo da umidade
      if (data.humidity < 20) {
        client.publish("/saude/monitoramento/alertaoxity", "Umidade muito baixa!");
      } else {
        client.publish("/saude/monitoramento/alertaoxity", "Umidade baixa.");
      }
    }
  }
}
