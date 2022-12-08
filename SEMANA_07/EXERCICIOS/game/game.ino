#include <WiFi.h>

const char* ssid     = "FITOSP";
const char* password = "tata1312";

WiFiServer server(80);

#define LED_CARA 2
#define LED_COROA 5



void setup()
{
    Serial.begin(115200);

    pinMode(LED_CARA, OUTPUT);      // LED Vermelho -> CARA
    pinMode(LED_COROA, OUTPUT);      // LED Azul (direito)

    delay(12);

    // Conecte-se à rede Wi-FI

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listener para os clientes

  if (client) {                             // se uma cliente se conectar,
    Serial.println("New Client.");           // imprima mensagem na porta serial
    String currentLine = "";                // String para armazenar dados do cliente
    while (client.connected()) {            // loop enquanto cliente estiver conectado
      if (client.available()) {             // se houver bytes para ler do cliente,
        char c = client.read();             // leia o byte, então
        Serial.write(c);                    // o imprima no monitor serial
        if (c == '\n') {                    // se o byte é um caractere de nova linha

          // se a linha atual for branca, há dois caracterés de nova linha na sequência
          // isso é o final da requsição HTTP, envie uma resposta:
          if (currentLine.length() == 0) {
            // Os cabeçalhos HTTP sempre começam com um código de resposta (por exemplo, HTTP/1.1 200 OK)
            // e um tipo de conteúdo para que o cliente saiba o que está por vir e, em seguida, uma linha em branco:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Mostrar a pagina HTML em si
            client.println("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Cara ou coroa!</title></head><body><div id='main'><h1>Cara ou coroa!?</h1><button onclick='caracoroa()'>Girar a moeda</button><p id='moed'></p><img id='caramoeda' src='https://i.pinimg.com/originals/75/90/c0/7590c002386d1107c5b5c5b0b333994a.png' alt='caramoeda' style='display: none;' ><img id='coroamoeda' src='https://i.pinimg.com/originals/66/13/d2/6613d23bff61c8cb0c03885415bd1e9d.png' alt='coroamoeda' style='display: none;'></div><script>function caracoroa() {var moeda = Math.floor(Math.random() * 2);if (moeda == 0) {document.getElementById('moed').innerHTML = 'Cara';document.getElementById('caramoeda').style.display = 'block';document.getElementById('coroamoeda').style.display = 'none';} else {document.getElementById('moed').innerHTML = 'Coroa';document.getElementById('coroamoeda').style.display = 'block';document.getElementById('caramoeda').style.display = 'none'; }}</script><style>#coroamoeda{width: 350px;height: 350px;margin-left: -20px;margin-top: -20px;}#main{position: absolute;top: 3%;left: 40%;width: 350px;height: 350px;}</style></body></html>");
            

            // a resposta HTTP termina com outra linha em branco:
            client.println();
            // saia do loop while:
            break;

    // feche a conexão:
    client.stop();
    Serial.println("Client Disconnected.");
    }
