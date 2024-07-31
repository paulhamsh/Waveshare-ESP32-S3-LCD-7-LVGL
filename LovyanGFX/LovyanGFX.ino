


const char* title = "Hello World";

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Initialising...");

  //  TouchInit();
  ExpanderInit();
  LgfxInit();
  Serial.println("Lgfx initialised");
}

void loop() {
  LgfxDoTouch();
  delay(5);
}
