// Define the pins for the LED and the button
const int ledPin = 23;
const int buttonPin = 22;

// Variables to store the game state
unsigned long startTime; // When the LED turns on
unsigned long reactionTime; // The calculated reaction time
bool gameRunning = false; // Flag to check if we are waiting for a button press

void setup() {
  // Initialize Serial Communication at 115200 baud rate
  Serial.begin(115200);

  // Set the pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Initialize the random seed
  randomSeed(analogRead(0));

  // Game instructions
  Serial.println("--- ESP32 Reaction Game ---");
  Serial.println("Press the button as fast as you can when the LED turns on.");
  Serial.println("Starting a new game...");
}

void loop() {
  // Check if a game is NOT currently running
  if (!gameRunning) {
    // Generate a random delay between 2 and 7 seconds (2000-7000 milliseconds)
    int randomDelay = random(2000, 7000);
    Serial.print("Get ready... The LED will turn on in ");
    Serial.print(randomDelay / 1000.0);
    Serial.println(" seconds.");
    
    // Wait for the random delay time
    delay(randomDelay);

    // --- Start the reaction test ---
    digitalWrite(ledPin, HIGH); // Turn the LED ON
    startTime = millis();       // Record the start time
    gameRunning = true;         // Set the game state to running
  }

  // Check if the game IS running and the button has been pressed
  if (gameRunning && digitalRead(buttonPin) == HIGH) {
    // --- Calculate and display the reaction time ---
    reactionTime = millis() - startTime; // Calculate the difference
    digitalWrite(ledPin, LOW);           // Turn the LED OFF

    // Print the result to the Serial Monitor
    Serial.print("Your reaction time: ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    Serial.println("\nStarting a new game...");
    
    gameRunning = false; // Reset the game state for the next round
    delay(1000); // A short pause before the next round starts
  }
}