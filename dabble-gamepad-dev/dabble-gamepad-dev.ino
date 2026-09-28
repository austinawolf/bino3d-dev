#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <Dabble.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// HM-10:
//   TX -> Nano D2 (RX)
//   RX -> Nano D3 (TX)
SoftwareSerial hm10(2, 3);


// --------------------------------------------------
// Motor control outputs
// --------------------------------------------------
const int LEFT_MOTOR_A  = 4;
const int LEFT_MOTOR_B  = 5;
const int RIGHT_MOTOR_A = 6;
const int RIGHT_MOTOR_B = 7;


// --------------------------------------------------
// Servo
// --------------------------------------------------
const int SERVO_PIN = 9;
const int SERVO_RIGHT_LIMIT = 45;
const int SERVO_LEFT_LIMIT = 135;
const int SERVO_CENTER = 135;
Servo headServo;

static int currentServoPosition = 0;

// --------------------------------------------------
// Button events
// --------------------------------------------------
enum class GamePadButton {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SQUARE,
    CIRCLE,
    CROSS,
    TRIANGLE,
    START,
    SELECT
};


// --------------------------------------------------
// Get GamePad button
// --------------------------------------------------

GamePadButton getGamePadButton()
{
    if (GamePad.isUpPressed())
        return GamePadButton::UP;

    if (GamePad.isDownPressed())
        return GamePadButton::DOWN;

    if (GamePad.isLeftPressed())
        return GamePadButton::LEFT;

    if (GamePad.isRightPressed())
        return GamePadButton::RIGHT;

    if (GamePad.isSquarePressed())
        return GamePadButton::SQUARE;

    if (GamePad.isCirclePressed())
        return GamePadButton::CIRCLE;

    if (GamePad.isCrossPressed())
        return GamePadButton::CROSS;

    if (GamePad.isTrianglePressed())
        return GamePadButton::TRIANGLE;

    if (GamePad.isStartPressed())
        return GamePadButton::START;

    if (GamePad.isSelectPressed())
        return GamePadButton::SELECT;

    return GamePadButton::NONE;
}


// --------------------------------------------------
// Rover functions
// --------------------------------------------------

void roverForward()
{
    digitalWrite(LEFT_MOTOR_A, HIGH);
    digitalWrite(LEFT_MOTOR_B, LOW);

    digitalWrite(RIGHT_MOTOR_A, HIGH);
    digitalWrite(RIGHT_MOTOR_B, LOW);
}

void roverReverse()
{
    digitalWrite(LEFT_MOTOR_A, LOW);
    digitalWrite(LEFT_MOTOR_B, HIGH);

    digitalWrite(RIGHT_MOTOR_A, LOW);
    digitalWrite(RIGHT_MOTOR_B, HIGH);
}

void roverRight()
{
    digitalWrite(LEFT_MOTOR_A, HIGH);
    digitalWrite(LEFT_MOTOR_B, LOW);

    digitalWrite(RIGHT_MOTOR_A, LOW);
    digitalWrite(RIGHT_MOTOR_B, HIGH);
}

void roverLeft()
{
    digitalWrite(LEFT_MOTOR_A, LOW);
    digitalWrite(LEFT_MOTOR_B, HIGH);

    digitalWrite(RIGHT_MOTOR_A, HIGH);
    digitalWrite(RIGHT_MOTOR_B, LOW);
}

void roverIdle()
{
    digitalWrite(LEFT_MOTOR_A, LOW);
    digitalWrite(LEFT_MOTOR_B, LOW);

    digitalWrite(RIGHT_MOTOR_A, LOW);
    digitalWrite(RIGHT_MOTOR_B, LOW);
}

// --------------------------------------------------
// Servo functions
// --------------------------------------------------
void servoCenter()
{
    currentServoPosition = SERVO_CENTER;
    headServo.write(SERVO_CENTER);
}

void servoLeft()
{
    if (currentServoPosition == 0)
    {
        return;
    }

    headServo.write(--currentServoPosition);
}

void servoRight()
{
    if (currentServoPosition == 0)
    {
        return;
    }

    headServo.write(++currentServoPosition);
}


// --------------------------------------------------
// Button event handler
// --------------------------------------------------

void onButtonEvent(GamePadButton event)
{
    switch (event)
    {
        case GamePadButton::UP:
            roverForward();
            break;
        case GamePadButton::DOWN:
            roverReverse();
            break;
        case GamePadButton::RIGHT:
            roverRight();
            break;
        case GamePadButton::LEFT:
            roverLeft();
            break;
        case GamePadButton::NONE:
            roverIdle();
            break;
        case GamePadButton::SQUARE:
            servoLeft();
            break;
        case GamePadButton::CIRCLE:
            servoRight();
            break;
        case GamePadButton::CROSS:
            break;
        case GamePadButton::TRIANGLE:
            servoCenter();
            break;
        case GamePadButton::START:
            break;
        case GamePadButton::SELECT:
            break;
    }
}

// --------------------------------------------------
// Util
// --------------------------------------------------

const char* getButtonName(GamePadButton event)
{
    switch (event)
    {
        case GamePadButton::NONE:     return "NONE";
        case GamePadButton::UP:       return "UP";
        case GamePadButton::DOWN:     return "DOWN";
        case GamePadButton::LEFT:     return "LEFT";
        case GamePadButton::RIGHT:    return "RIGHT";
        case GamePadButton::SQUARE:   return "SQUARE";
        case GamePadButton::CIRCLE:   return "CIRCLE";
        case GamePadButton::CROSS:    return "CROSS";
        case GamePadButton::TRIANGLE: return "TRIANGLE";
        case GamePadButton::START:    return "START";
        case GamePadButton::SELECT:   return "SELECT";
    }

    return "UNKNOWN";
}

void logButtonEvent(GamePadButton event)
{
    static GamePadButton previousEvent = GamePadButton::NONE;

    if (event != previousEvent)
    {
        Serial.print("Button event: ");
        Serial.println(getButtonName(event));

        previousEvent = event;
    }
}

// --------------------------------------------------
// Setup
// --------------------------------------------------
void setup()
{
    pinMode(LEFT_MOTOR_A, OUTPUT);
    pinMode(LEFT_MOTOR_B, OUTPUT);

    pinMode(RIGHT_MOTOR_A, OUTPUT);
    pinMode(RIGHT_MOTOR_B, OUTPUT);

    hm10.begin(9600);
    
    Serial.begin(115200); 
    
    Dabble.begin(hm10);

    headServo.attach(SERVO_PIN);

    Serial.println("Ready.");
}

// --------------------------------------------------
// Main loop
// --------------------------------------------------

void loop()
{
    Dabble.processInput();

    GamePadButton event = getGamePadButton();

    // log the event if its changed
    logButtonEvent(event);

    // take action on button event
    onButtonEvent(event);
}

