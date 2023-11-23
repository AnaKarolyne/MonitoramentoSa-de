# Documentação Técnica - Monitoramento de Saúde com ESP32 e MQTT
## 🚀 Introdução
O projeto "Monitoramento de Saúde com ESP32 e MQTT" tem como objetivo criar uma solução eficaz para o acompanhamento contínuo e em tempo real das condições ambientais e de saúde. Utilizando o microcontrolador ESP32, um sensor DHT22 para medição de temperatura e umidade, LEDs indicadores e comunicação MQTT, a iniciativa busca oferecer uma ferramenta versátil e acessível para diversos cenários de monitoramento de saúde.

<br>

## 🎯 Objetivo do Projeto

A ideia central é proporcionar às pessoas um meio de monitorar, de maneira intuitiva, as condições ambientais que podem impactar sua saúde. O sensor de temperatura permite a detecção precoce de febre, enquanto o sensor de umidade amplia a compreensão do ambiente, sendo útil em situações como cuidados respiratórios, prevenção de doenças e garantia de conforto dermatológico.

O uso de LEDs vermelho e amarelo como indicadores visuais oferece uma forma imediata de alertar para condições anormais, proporcionando uma resposta rápida diante de situações críticas. A comunicação MQTT, integrada ao projeto, possibilita o envio de alertas para dispositivos externos, permitindo que familiares, cuidadores ou profissionais de saúde recebam notificações em tempo real.

O projeto é flexível e pode ser adaptado para uma variedade de cenários, desde o monitoramento domiciliar até ambientes clínicos e locais de trabalho. A personalização do código permite ajustar limiares de temperatura, frequências de alerta e tópicos MQTT, tornando-o uma solução versátil para atender às necessidades específicas de cada aplicação.

Com uma abordagem abrangente que considera tanto a temperatura quanto a umidade, o "Monitoramento de Saúde com ESP32 e MQTT" representa uma iniciativa inovadora no campo da saúde conectada, proporcionando uma resposta proativa e eficiente para situações que exigem atenção imediata.


<br>

## 💯 Benefícios para os Usuários
1. **Detecção de Febre:** O sensor de temperatura (DHT22) possibilita a detecção de febre, indicando um aumento na temperatura ambiente.
2. **Monitoramento da Umidade:** O sensor de umidade permite monitorar os níveis de umidade ambiental, sendo benéfico em situações como cuidados respiratórios, prevenção de doenças respiratórias e conforto dermatológico.
3. **Alerta Visual com LEDs:** O uso de LEDs vermelho e amarelo fornece alertas visuais imediatos, permitindo uma identificação rápida e intuitiva de condições anormais.
4. **Comunicação MQTT:** A integração com o protocolo MQTT possibilita o envio de alertas para dispositivos externos, como smartphones ou computadores, permitindo que pessoas responsáveis ou profissionais de saúde recebam notificações em tempo real.

<br>

## 🏠 Cenários de Uso
1. **Monitoramento Domiciliar:** Pode ser utilizado em casa para monitorar a saúde de familiares, especialmente crianças e idosos.
2. **Ambientes Clínicos:** Em ambientes clínicos, pode ser implementado para monitorar a temperatura e umidade em salas de espera, consultórios médicos, entre outros.
3. **Locais de Trabalho:** Em locais de trabalho, o sistema pode ser empregado para monitorar as condições ambientais e de saúde dos funcionários.

<br>

## 🛠️ Pré-Requisitos
1. Simulador de eletrônica online, como por exemplo o Wokwi (https://wokwi.com/);
2. Node-Red - Ferramenta de programação visual;
3. Módulo node-red-dashboard;
4. Broker - Intermediário entre a máquina e o protocolo;

<br>

## 📋 Componentes físicos do sensor
1. ESP32: Microcontrolador responsável por coletar dados do sensor e controlar os LEDs.
2. DHT22: Sensor de temperatura e umidade utilizado para medir as condições ambientais.
3. LEDs: Dois LEDs (vermelho e amarelo) indicam alertas com base nas leituras do sensor.
4. Protoboard: plataforma versátil que permite a conexão temporária dos componentes eletrônicos.

<br>

## ⚙️ Executando os testes
Para realizar o teste do programa, segue os passos necessários em ordem de execução:
1. Clone o repositório para o seu ambiente local, ou crie um novo dentro do seu simulador online.
2. Execute o programa e verifique se a conexão está sendo feita corretamente.
3. Abra o Node-RED configurado localmente.
4. Configure as conexões necessárias com o dashboard escolhido.
5. Implemente o seu fluxo Node-RED.
6. Acesse o Node-RED dashboard, por meio do seu endereço local e a sigla "ui" no final do seu link.

<br>

## 🪄 Configurações Personalizadas
O código fornecido é um ponto de partida e pode ser personalizado conforme as necessidades específicas de cada aplicação. É possível ajustar limiares de temperatura, frequências de alerta e tópicos MQTT para atender aos requisitos particulares.

<br>

## 🔌Configurações de Rede e Broker

### Rede Wi-Fi
O ESP32 se conecta a uma rede Wi-Fi configurada no código, fornecendo acesso à internet para comunicação MQTT.

```
const char* ssid = "Wokwi-ANA";
const char* password = "";
```

<br>

### MQTT
Configuração do broker online conforme documentação técnica do mosquitto.
```
const char* mqtt_server = "test.mosquitto.org";
```
<br>

## 📝 Código

### Setup
A função setup() é executada uma vez no início do programa e realiza as seguintes operações:

1. Configuração dos pinos: Define os pinos como saída para os LEDs.
2. Inicialização da comunicação serial: Para debug e visualização de mensagens no monitor serial.
3. Configuração da rede Wi-Fi: Conecta o ESP32 à rede Wi-Fi.
4. Configuração do cliente MQTT: Estabelece a conexão com o servidor MQTT.
5. Configuração do sensor DHT22: Inicializa a comunicação com o sensor de temperatura e umidade.

<br>
   
### Loop Principal
A função loop() é executada continuamente e realiza as seguintes operações:
1. Reconexão MQTT: Verifica se o cliente MQTT está conectado. Se não estiver, tenta reconectar.
2. Leitura de Dados: Obtém dados do sensor DHT22 (temperatura e umidade).
3. Publicação MQTT: Publica os dados no tópico MQTT correspondente.
4. Controle dos LEDs: Controla o piscar dos LEDs com base nas condições de temperatura e umidade.
5. Publicação de Alertas: Publica alertas MQTT com base nas condições de temperatura e umidade.

<br>

### Controle dos LEDs
A função controlarLED() é responsável por controlar o LED indicador. Recebe o pino do LED e a frequência de piscamento como parâmetros.

```
void controlarLED(int pin, int frequencia) {
  digitalWrite(pin, HIGH);
  delay(frequencia);
  digitalWrite(pin, LOW);
  delay(frequencia);
}
```

<br>

## 🖇️ Links
### 📽️ Youtube
- Sensor de Monitoramento de Saúde:
### 💡 Wonki
- Projeto Wokwi ESP32_FrequenciaCardiaca_MQTT: https://wokwi.com/projects/381419262223450113

<br>

## ✒️ Autores
| Nome               | RM     |
| ------------------ | ------ |
| Ana Karolyne       | RM93668    |
| Alan Araujo        | RM95355    |
| Iago Coelho        | RM95683    |
| João Marcelo       | RM94983    |
| Valentina Fuzaro   | RM95741    |

<br>

## 🎁 Considerações Finais
Este código fornece uma estrutura básica para monitoramento de saúde usando ESP32, DHT22 e MQTT. Espera-se que este projeto forneça uma solução prática e eficiente para o monitoramento de saúde, contribuindo para a detecção precoce de condições adversas e melhorando a resposta a situações de emergência.
