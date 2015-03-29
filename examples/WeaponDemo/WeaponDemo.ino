/*
 * IRtag: WeaponDemo - Weapon for "laser tag" style IR shooters
 * Connect an IR LED to the transmitter pin. Please look at IRtagInt.h to find out
 * which pin this is; it depends on the Arduino model. For an ATmega8 based board,
 * pin D9 is used. Connect a normal LED to LED_PIN if you want to have a visual
 * indication that the weapon was fired.
 *
 * Use the serial terminal to fire the weapon:
 *
 * <SPACE>    Fire weapon
 *    +       Increase weapon damage
 *    -       Decrease weapon damage
 *    t       Change team
 */

#include <IRtag.h>

// flash LED on this pin to get a visual indication that the weapon was fired
#define LED_PIN      13

// number of teams
#define NUM_TEAMS    4

// maximum power
#define MAX_POWER    8

// IR transmitter instance
IRsend irsend;

volatile int power = 2;    // current weapon power
volatile int team;         // current team

unsigned long  teams[NUM_TEAMS] = {LS_TEAM_BLUE, LS_TEAM_RED, LS_TEAM_YELLOW, LS_TEAM_GREEN};
const    char* names[NUM_TEAMS] = {"blue", "red", "yellow", "green"};

void printTeam()
{
  Serial.print("Team ");
  Serial.println(names[team]);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  printTeam();
}

void loop()
{
  char ch;

  if (Serial.available() > 0)
  {
    ch = Serial.read();

    switch (ch)
    {
      case ' ':
        /* fire weapon */
        digitalWrite(LED_PIN, HIGH);
        Serial.print("* ");
        Serial.println(power, DEC);
        irsend.send(teams[team] | LS_WPN_CODE_RFL_LASER_STRIKE | (unsigned long)power);
        digitalWrite(LED_PIN, LOW);
        break;
        
      case '+':
        /* increase firepower */
        if (power < MAX_POWER)
          power++;
        Serial.println(power, DEC);
        break;
        
      case '-':
        /* decrease firepower */
        if (power > 1)
          power--;
        Serial.println(power, DEC);
        break;
  
      case 't':
        /* cycle through the teams */
        team++;
        if (team >= NUM_TEAMS)
          team = 0;
        printTeam();
        break;
        
      default:
        /* do nothing */
        break;
    }
  }
}

