#include <ESP8266WiFi.h>
#include <DNSServer.h>             // Import Layberaries to used in the code.
#include <ESP8266WebServer.h>


IPAddress apIP(192, 168, 8, 1); 
IPAddress gaIP(255, 255, 255, 0);    // IP Adresses for the network and the ESP8266.
DNSServer dnsServer;
ESP8266WebServer webServer(80);

void handleReq0(){ webServer.send(200,"text",String(5*digitalRead(LED_BUILTIN))+".00"); }    // If the reqest is 0.
void handleReq1(){ reqOut(1,0); }    // If the reqest is 1.

void handleNotFound(){              // If request is not identified.
  String message = "";              
  message = webServer.uri();                  
  if (message=="/favicon.ico") {     
    webServer.send(0,"","");        // Send Empty messege to unknown requists.
    }                               
}                                    

void reqOut(boolean stateOut,int delayTime){
  webServer.send(200,"html",F("<!DOCTYPE html><html><head><style>table { border-collapse: collapse;}td, th {border: 1px solid #dddddd;text-align: center;}body { text-align: center;}table.center {margin-left: auto;margin-right: auto;}.button {background-color: #4caf50;border: none;color: white;padding: 10px 20px;display: inline-block;font-size: 16px;margin: 10px 2px;cursor: pointer;}</style></head><body><h1 id=\"val\">0V</h1><button id=\"myTa\" class=\"button\" onclick=\"ToCSV('DMM2')\">Download .xls</button><table id=\"tbl\" class=\"center\"><tr><th>Time</th><th>Value</th><th>Unit</th></table><script>setInterval(function() {upd();}, 250);</script><script>function upd() {var xhttp = new XMLHttpRequest();xhttp.onreadystatechange = function() {if(this.responseText.length > 0){document.getElementById(\"val\").innerHTML = this.responseText + ' V ';}};xhttp.open(\"GET\", \"/2\", true);xhttp.send();var table = document.getElementById(\"tbl\");if ( table.rows.length > 100) {document.getElementById(\"tbl\").deleteRow(100);}var row = table.insertRow(1);var cell1 = row.insertCell(0);var cell2 = row.insertCell(1);var cell3 = row.insertCell(2);cell1.innerHTML = new Date().toLocaleTimeString();cell2.innerHTML = document.getElementById(\"val\").innerHTML.slice(0, 4);cell3.innerHTML = \"V\"; }function ToCSV(filename = '') {var csv = [];var rows = document.querySelectorAll(\"table tr\");for (var i = 0; i < rows.length; i++) {var row = [], cols = rows[i].querySelectorAll(\"td, th\");for (var j = 0; j < cols.length; j++) row.push(cols[j].innerText);csv.push(row.join(\",\"));}var csvFile;var downloadLink;csvFile = new Blob([csv.join(\"\\n\")], {type: \"text/csv\"});downloadLink = document.createElement(\"a\");document.body.appendChild(downloadLink);downloadLink.href = window.URL.createObjectURL(csvFile);downloadLink.download = filename +'.csv' ;downloadLink.click();}</script></body></html>"));  // Send the HTML page to the user.
//  delay(delayTime);                                            // Wait for some time.                                                                                                                                                                                                                                                                                                                             
//  digitalWrite(LED_BUILTIN, stateOut);                            // Change output state as given.
}

void setup() {
  pinMode(LED_BUILTIN, INPUT);                // Define Outpu Pin.

  
  WiFi.mode(WIFI_AP);                          // Wi-Fi mode: Access Point.
  WiFi.softAPConfig(apIP, apIP, gaIP);         // Set IPs for the Access Point.
  WiFi.softAP("WiFi_Relay_[1]");   // Set SSID and password.

  dnsServer.start(53, "esp.iot", apIP);        // Set Address of the Web Page on the Local Network.
  webServer.onNotFound(handleNotFound);        // When user requiest is not found: Do nothing.
  webServer.on("/2", handleReq0);              // When user requiest is 0: Set output to Low.
  webServer.on("/1", handleReq1);              // When user requiest is 1: Set output to High.     
  webServer.begin();                           // Begin the Access point.
}

void loop() {
  dnsServer.processNextRequest();             // Wait for a request.
  webServer.handleClient();                   // Proccess incoming requiest.
}
