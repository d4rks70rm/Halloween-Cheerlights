#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>


#define PixelPin 2
#define PixelNum 12

const char* ssid = "dev";
const char* password = "RatoRoeuRolha";

unsigned long cheerLightsChannelNumber = 1417;

int delayval = 500;

String colorName[] = {"none","red","pink","green","blue","cyan","white","warmwhite","oldlace","purple","magenta","yellow","orange"};

// Map of RGB values for each of the Cheerlight color names
int colorRGB[][3] = {     0,  0,  0,  // "none"
                        255,  0,  0,  // "red"
                        255,192,203,  // "pink"
                          0,255,  0,  // "green"
                          0,  0,255,  // "blue"
                          0,255,255,  // "cyan",
                        255,255,255,  // "white",
                        255,223,223,  // "warmwhite",
                        255,223,223,  // "oldlace",
                        128,  0,128,  // "purple",
                        255,  0,255,  // "magenta",
                        255,255,  0,  // "yellow",
                        255,165,  0}; // "orange"};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PixelNum, PixelPin, NEO_GRB + NEO_KHZ800);
WiFiClient wclient;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.println(".");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Ligado a ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  pixels.begin();
  ThingSpeak.begin(wclient);
}

void loop() {
  String color = ThingSpeak.readStringField(cheerLightsChannelNumber, 1);
  setColor(color);
  //Serial.println(color);

  delay(5000);
}

void setColor(String color)
{
  for(int iColor = 0; iColor <= 12; iColor++)
  {
    if(color == colorName[iColor])
    {
       for(int i=0;i<PixelNum;i++){
        pixels.setPixelColor(i, pixels.Color(colorRGB[iColor][0],colorRGB[iColor][1],colorRGB[iColor][2])); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
      }
      return;
    }
  }
}
