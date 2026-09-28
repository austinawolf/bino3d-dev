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
    if (GamePad.isUpPressed())       return GamePadButton::UP;
    if (GamePad.isDownPressed())     return GamePadButton::DOWN;
    if (GamePad.isLeftPressed())     return GamePadButton::LEFT;
    if (GamePad.isRightPressed())    return GamePadButton::RIGHT;
    if (GamePad.isSquarePressed())   return GamePadButton::SQUARE;
    if (GamePad.isCirclePressed())   return GamePadButton::CIRCLE;
    if (GamePad.isCrossPressed())    return GamePadButton::CROSS;
    if (GamePad.isTrianglePressed()) return GamePadButton::TRIANGLE;
    if (GamePad.isStartPressed())    return GamePadButton::START;
    if (GamePad.isSelectPressed())   return GamePadButton::SELECT;

    return GamePadButton::NONE;
}

const char* buttonName(GamePadButton button)
{
    switch (button) {
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
        default:                      return "NONE";
    }
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

    static GamePadButton previousButton = GamePadButton::NONE;

    GamePadButton currentButton = getGamePadButton();

    // Key was just depressed
    if (currentButton != GamePadButton::NONE &&
        currentButton != previousButton) {

        Serial.print("PRESSED: ");
        Serial.println(buttonName(currentButton));
    }

    // Key was just released
    if (currentButton == GamePadButton::NONE &&
        previousButton != GamePadButton::NONE) {

        Serial.print("RELEASED: ");
        Serial.println(buttonName(previousButton));
    }

    previousButton = currentButton;
}
