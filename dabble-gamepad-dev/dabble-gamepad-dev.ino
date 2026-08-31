#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <Dabble.h>

// HM-10:
//   TX -> Nano D2 (RX)
//   RX -> Nano D3 (TX)
SoftwareSerial hm10(2, 3);

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

GamePadButton getGamePadButton()
{
    GamePadButton button = GamePadButton::NONE;

    if (GamePad.isUpPressed()) {
        button = GamePadButton::UP;
    }
    else if (GamePad.isDownPressed()) {
        button = GamePadButton::DOWN;
    }
    else if (GamePad.isLeftPressed()) {
        button = GamePadButton::LEFT;
    }
    else if (GamePad.isRightPressed()) {
        button = GamePadButton::RIGHT;
    }
    else if (GamePad.isSquarePressed()) {
        button = GamePadButton::SQUARE;
    }
    else if (GamePad.isCirclePressed()) {
        button = GamePadButton::CIRCLE;
    }
    else if (GamePad.isCrossPressed()) {
        button = GamePadButton::CROSS;
    }
    else if (GamePad.isTrianglePressed()) {
        button = GamePadButton::TRIANGLE;
    }
    else if (GamePad.isStartPressed()) {
        button = GamePadButton::START;
    }
    else if (GamePad.isSelectPressed()) {
        button = GamePadButton::SELECT;
    }

    if (button != GamePadButton::NONE) {
        Serial.print("Button: ");

        switch (button) {
            case GamePadButton::UP:
                Serial.println("UP");
                break;
            case GamePadButton::DOWN:
                Serial.println("DOWN");
                break;
            case GamePadButton::LEFT:
                Serial.println("LEFT");
                break;
            case GamePadButton::RIGHT:
                Serial.println("RIGHT");
                break;
            case GamePadButton::SQUARE:
                Serial.println("SQUARE");
                break;
            case GamePadButton::CIRCLE:
                Serial.println("CIRCLE");
                break;
            case GamePadButton::CROSS:
                Serial.println("CROSS");
                break;
            case GamePadButton::TRIANGLE:
                Serial.println("TRIANGLE");
                break;
            case GamePadButton::START:
                Serial.println("START");
                break;
            case GamePadButton::SELECT:
                Serial.println("SELECT");
                break;
            default:
                break;
        }
    }

    return button;
}

void setup()
{
    Serial.begin(115200);

    hm10.begin(9600);

    // Tell Dabble to use the HM-10 serial connection.
    Dabble.begin(hm10);

    Serial.println("Dabble GamePad ready");
}

void loop()
{
    Dabble.processInput();

    GamePadButton button = getGamePadButton();

    // Handle button here
    switch (button) {
        case GamePadButton::UP:
            // Move forward
            break;

        case GamePadButton::DOWN:
            // Move backward
            break;

        case GamePadButton::LEFT:
            // Turn left
            break;

        case GamePadButton::RIGHT:
            // Turn right
            break;

        case GamePadButton::NONE:
            // Nothing pressed
            break;

        default:
            break;
    }
}