//Code made by @ElectroVilla :- https://www.youtube.com/@ElectroVilla

// Watch Full Tutorial:- https://youtu.be/aK4KOQaEzp0?si=GrkzrxUdeEGXg4G3

#include <ESP8266WiFi.h>  // including the required libraries and header files!
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "Your SSID";  // Wifi Credentials
const char* pass = "Password";

const int Switch_1 = 0, Switch_2 = 2, Switch_3 = 14, Switch_4 = 12;  // Outputs

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Connect I2C Display SCL & SDA with D1 and D2

ESP8266WebServer server(80);  // assigning the port for the server (port 80 for http)

void setup() {                // initialising all the IO and states (predefined)
  pinMode(Switch_1, OUTPUT);  //Defining OUTPUTS
  pinMode(Switch_2, OUTPUT);
  pinMode(Switch_3, OUTPUT);
  pinMode(Switch_4, OUTPUT);
  pinMode(Switch_3, OUTPUT);

  // The Relay Module & LAN_Status_LED is "Active-LOW" giving default value 1 to turn them OFF by default!
  digitalWrite(Switch_1, 1);
  digitalWrite(Switch_2, 1);
  digitalWrite(Switch_3, 1);
  digitalWrite(Switch_4, 1);

  WiFi.begin(ssid, pass);
  WiFi.hostname("Home-automation-System");

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting......");
  //Checking for WiFi connection at boot!
  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
  }
  server.begin();

  lcd.clear();
  lcd.print("Connected, IP:-");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());  // view IP in I2C Display
  delay(5000);
  lcd.clear();

  server.on("/", HTTP_GET, handle_WebPage_Root);           //hhtp get req for the esp LAN server!
  server.on("/Switch1_state", HTTP_POST, handle_Switch1);  //calling funtion to toggle relays through xml post req!
  server.on("/Switch2_state", HTTP_POST, handle_Switch2);  //calling funtion to toggle relays through xml post req!
  server.on("/Switch3_state", HTTP_POST, handle_Switch3);  //calling funtion to toggle relays through xml post req!
  server.on("/Switch4_state", HTTP_POST, handle_Switch4);  //calling funtion to toggle relays through xml post req!
}

void handle_Switch1() {  // function toggle Switch-1
  digitalWrite(Switch_1, !digitalRead(Switch_1));
  lcd.setCursor(0, 0);
  if (digitalRead(Switch_1) == 1) {
    lcd.print("S1: OFF");
  } else {
    lcd.print("S1: ON ");
  }
}

void handle_Switch2() {  // function toggle Switch-2
  digitalWrite(Switch_2, !digitalRead(Switch_2));
  lcd.setCursor(9, 0);
  if (digitalRead(Switch_2) == 1) {
    lcd.print("S2: OFF");
  } else {
    lcd.print("S2: ON ");
  }
}

void handle_Switch3() {  // function toggle Switch-3
  digitalWrite(Switch_3, !digitalRead(Switch_3));
  lcd.setCursor(0, 1);
  if (digitalRead(Switch_3) == 1) {
    lcd.print("S3: OFF");
  } else {
    lcd.print("S3: ON ");
  }
}

void handle_Switch4() {  // function toggle Switch-4
  digitalWrite(Switch_4, !digitalRead(Switch_4));
  lcd.setCursor(9, 1);
  if (digitalRead(Switch_4) == 1) {
    lcd.print("S4: OFF");
  } else {
    lcd.print("S4: ON ");
  }
}

void handle_WebPage_Root() {
  const char* WebPage = R"(
    <!DOCTYPE html>
    <html lang="eng" data-bs-theme="dark">

    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>WiFi-Home-Automation</title>
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet"
            integrity="sha384-KK94CHFLLe+nY2dmCWGMq91rCGa5gtU4mk92HdvYe+M/SXH301p5ILy+dN9+nJOZ" crossorigin="anonymous">
        <style>
            .btns_default_color {
                font-weight: bold;
                font-size: large;
                background-color: red;
                padding: 10px 20px;
                font-size: 16px;
                cursor: pointer;
                border-radius: 100px;
                border: white 1px solid;
            }

            header {
                color: whitesmoke;
                background-color: #660066;
            }

            footer {
                background-color: #660066;
                position: sticky;
                text-align: center;
                height: 10vh;
                width: 100%;
                margin-top: 100%;
            }

            footer>a {
                text-decoration: none;
            }

            #btn1 {
                margin-top: 30px;
            }
        </style>
    </head>

    <body>
        <header class="navbar navbar-expand-lg bd-navbar sticky-top">
            <nav class=" container-xxl bd-gutter flex-wrap flex-lg-nowrap" aria-label="Main navigation">
                <div class="container">
                    <h1 class="h1 text-center">
                        WiFi-Home Automation
                    </h1>
                </div>
            </nav>
        </header>
        <div class="container text-center mb-4">
            <div class="col d-grid gap-2  mb-4">
                <button type="button" class="btns_default_color" id="btn1">Switch 1 OFF</button>
            </div>
            <div class="col d-grid gap-2 mb-4">
                <button type="button" class="btns_default_color" id="btn2">Switch 2 OFF</button>
            </div>

            <div class="col d-grid gap-2 mb-4">
                <button type="button" class="btns_default_color" id="btn3">Switch 3 OFF</button>
            </div>

            <div class="col d-grid gap-2 mb-4">
                <button type="button" class="btns_default_color" id="btn4">Switch 4 OFF</button>
            </div>
        </div>
        <footer>
            &copy; Made by ElectroVilla
            <a href="https://www.youtube.com/@ElectroVilla" target="_blank">Visit YouTube
                Channel</a>
        </footer>

        <script>

            // Functions For Switch 1 ON and OFF
            let State_Switch1 = 0;
            btn1.addEventListener("click", () => {
                State_Switch1 = !State_Switch1;
                const xhr_btn1 = new XMLHttpRequest();
                if (State_Switch1 == 1) {
                    xhr_btn1.open('POST', '/Switch1_state', true);
                    xhr_btn1.send();
                    document.getElementById("btn1").innerHTML = "Switch 1 ON"
                    document.getElementById("btn1").style = "background-color: green"
                }
                else if (State_Switch1 != 1) {
                    xhr_btn1.open('POST', '/Switch1_state', true);
                    xhr_btn1.send();
                    document.getElementById("btn1").innerHTML = "Switch 1 OFF"
                    document.getElementById("btn1").style = "background-color: red"
                }
            })
            // Functions For Switch 2 ON and OFF
            let State_Switch2 = 0;
            btn2.addEventListener("click", () => {
                const xhr_btn2 = new XMLHttpRequest();
                State_Switch2 = !State_Switch2;
                if (State_Switch2) {
                    xhr_btn2.open('POST', '/Switch2_state', true);
                    xhr_btn2.send();
                    document.getElementById("btn2").innerHTML = "Switch 2 ON"
                    document.getElementById("btn2").style = "background-color: green"
                }
                else {
                    xhr_btn2.open('POST', '/Switch2_state', true);
                    xhr_btn2.send();
                    document.getElementById("btn2").innerHTML = "Switch 2 OFF"
                    document.getElementById("btn2").style = "background-color: red"
                }
            })

            // Functions For Switch 3 ON and OFF
            let State_Switch3 = 0;
            btn3.addEventListener("click", ()=>{
                const xhr_btn3 = new XMLHttpRequest();
                State_Switch3 = !State_Switch3;
                if (State_Switch3) {
                    xhr_btn3.open('POST', '/Switch3_state', true);
                    xhr_btn3.send();
                    document.getElementById("btn3").innerHTML = "Switch 3 ON"
                    document.getElementById("btn3").style = "background-color: green"
                }
                else {
                    xhr_btn3.open('POST', '/Switch3_state', true);
                    xhr_btn3.send();
                    document.getElementById("btn3").innerHTML = "Switch 3 OFF"
                    document.getElementById("btn3").style = "background-color: red"
                }
            })

            // Functions For Switch 4 ON and OFF
            let State_Switch4 = 0;
            btn4.addEventListener("click", ()=>{
                const xhr_btn4 = new XMLHttpRequest();
                State_Switch4 = !State_Switch4;
                if (State_Switch4) {
                    xhr_btn4.open('POST', '/Switch4_state', true);
                    xhr_btn4.send();
                    document.getElementById("btn4").innerHTML = "Switch 4 ON"
                    document.getElementById("btn4").style = "background-color: green"
                }
                else {
                    xhr_btn4.open('POST', '/Switch4_state', true);
                    xhr_btn4.send();
                    document.getElementById("btn4").innerHTML = "Switch 4 OFF"
                    document.getElementById("btn4").style = "background-color: red"
                }
            })
        </script>
        <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
    </body>

    </html>
  )";
  server.send(200, "text/html", WebPage);
}

void loop() {  // Check for WiFi connectivity in loop!
  server.handleClient();
}
