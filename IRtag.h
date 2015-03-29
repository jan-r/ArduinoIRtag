/*
 * IRtag - Library to interface Arduino with infrared laser tag toys
 * 
 * Based on the IRremote library written by Ken Shirriff et al.
 * For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
 *
 */

#ifndef IRtag_h
#define IRtag_h

#include <inttypes.h>

// The following are compile-time library options.
// If you change them, recompile the library.
// If DEBUG is defined, a lot of debugging output will be printed during decoding.
// TEST must be defined for the IRtest unittests to work.  It will make some
// methods virtual, which will be slightly slower, which is why it is optional.
// #define DEBUG
// #define TEST

// Results returned from the decoder
class decode_results
{
public:
  unsigned long value; // Decoded value
  int bits; // Number of bits in decoded value
  volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
  int rawlen; // Number of records in rawbuf.
};

// main class for receiving IR
class IRrecv
{
public:
  IRrecv(int recvpin);
  void blink13(int blinkflag);
  uint8_t decode(decode_results *results);
  void enableIRIn();
  void resume();
private:
  // These are called by decode
  int getRClevel(decode_results *results, int *offset, int *used, int t1);
  uint8_t decodeIRtag(decode_results *results);
  int compare(unsigned int oldval, unsigned int newval);
};

// Only used for testing; can remove virtual for shorter code
#ifdef TEST
#define VIRTUAL virtual
#else
#define VIRTUAL
#endif

class IRsend
{
public:
  IRsend() {}
  void send(unsigned long data);
  void enableIROut(int khz);
  VIRTUAL void mark(int usec);
  VIRTUAL void space(int usec);
}
;

// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100

/*
 * Team color codes
 */
#define LS_TEAM_OFFSET  24U

#define LS_TEAM_RED     (4UL << LS_TEAM_OFFSET)
#define LS_TEAM_YELLOW  (5UL << LS_TEAM_OFFSET)
#define LS_TEAM_GREEN   (6UL << LS_TEAM_OFFSET)
#define LS_TEAM_BLUE    (7UL << LS_TEAM_OFFSET)
#define LS_TEAM_MEDIC   (8UL << LS_TEAM_OFFSET)


/*
 * Weapon codes
 */
#define LS_WPN_CODE_OFFSET      8U
// from pistol
#define LS_WPN_CODE_LASER_STRIKE        (1U << LS_WPN_CODE_OFFSET)
#define LS_WPN_CODE_STEALTH_STRIKE      (2U << LS_WPN_CODE_OFFSET)
#define LS_WPN_CODE_PULSE_STRIKE        (3U << LS_WPN_CODE_OFFSET)
#define LS_WPN_CODE_SONIC_STRIKE        (4U << LS_WPN_CODE_OFFSET)
// from rifle
#define LS_WPN_CODE_RFL_LASER_STRIKE    (5U << LS_WPN_CODE_OFFSET)
#define LS_WPN_CODE_RFL_STEALTH_STRIKE  (6U << LS_WPN_CODE_OFFSET)
#define LS_WPN_CODE_RFL_PULSE_STRIKE    (7U << LS_WPN_CODE_OFFSET)
#define LS_WPN_CODE_RFL_RAIL_STRIKE     (8U << LS_WPN_CODE_OFFSET)
#define LS_WPN_CODE_RFL_SONIC_STRIKE    (9U << LS_WPN_CODE_OFFSET)
// medic
#define LS_WPN_CODE_MEDIC               (8U << LS_WPN_CODE_OFFSET)
// bomb
#define LS_WPN_CODE_BOMB                (14U << LS_WPN_CODE_OFFSET)
// sentry
#define LS_WPN_CODE_SENTRY              (15U << LS_WPN_CODE_OFFSET)


/*
 * Weapon damage
 */
// Pistol
#define LS_WPN_DMG_PST_LASER_STRIKE     2U
#define LS_WPN_DMG_PST_STEALTH_STRIKE   2U
#define LS_WPN_DMG_PST_PULSE_STRIKE     3U
#define LS_WPN_DMG_PST_SONIC_STRIKE     6U
// Assault rifle
#define LS_WPN_DMG_RFL_LASER_STRIKE     2U
#define LS_WPN_DMG_RFL_STEALTH_STRIKE   2U
#define LS_WPN_DMG_RFL_PULSE_STRIKE     3U
#define LS_WPN_DMG_RFL_RAIL_STRIKE      6U
#define LS_WPN_DMG_RFL_SONIC_STRIKE     8U
// Bomb
#define LS_WPN_DMG_BOMB                 24U
// Sentry
#define LS_WPN_DMG_SENTRY               8U


/*
 * Official weapon shot definitions (weapon code + damage)
 */
// Assault rifle
#define LS_SHOT_RFL_LASER_STRIKE    (LS_WPN_CODE_RFL_LASER_STRIKE   | LS_WPN_DMG_RFL_LASER_STRIKE)
#define LS_SHOT_RFL_STEALTH_STRIKE  (LS_WPN_CODE_RFL_STEALTH_STRIKE | LS_WPN_DMG_RFL_STEALTH_STRIKE)
#define LS_SHOT_RFL_PULSE_STRIKE    (LS_WPN_CODE_RFL_PULSE_STRIKE   | LS_WPN_DMG_RFL_PULSE_STRIKE)
#define LS_SHOT_RFL_RAIL_STRIKE     (LS_WPN_CODE_RFL_RAIL_STRIKE    | LS_WPN_DMG_RFL_RAIL_STRIKE)
#define LS_SHOT_RFL_SONIC_STRIKE    (LS_WPN_CODE_RFL_SONIC_STRIKE   | LS_WPN_DMG_RFL_SONIC_STRIKE)

// Pistol
#define LS_SHOT_PST_LASER_STRIKE    (LS_WPN_CODE_PST_LASER_STRIKE   | LS_WPN_DMG_PST_LASER_STRIKE)
#define LS_SHOT_PST_STEALTH_STRIKE  (LS_WPN_CODE_PST_STEALTH_STRIKE | LS_WPN_DMG_PST_STEALTH_STRIKE)
#define LS_SHOT_PST_PULSE_STRIKE    (LS_WPN_CODE_PST_PULSE_STRIKE   | LS_WPN_DMG_PST_PULSE_STRIKE)
#define LS_SHOT_PST_SONIC_STRIKE    (LS_WPN_CODE_PST_SONIC_STRIKE   | LS_WPN_DMG_PST_SONIC_STRIKE)

// Bomb
#define LS_SHOT_BOMB                (LS_WPN_CODE_BOMB               | LS_WPN_DMG_BOMB)

// Sentry
#define LS_SHOT_SENTRY              (LS_WPN_CODE_SENTRY             | LS_WPN_DMG_SENTRY)


/*
 * Full 32-bit code for a "heal" shot (medic)
 */
#define LS_HEAL_TEAM(_team)     (LS_TEAM_MEDIC | LS_WPN_CODE_MEDIC | ((_team) >> LS_TEAM_OFFSET))

#endif

