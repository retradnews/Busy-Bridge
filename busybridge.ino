#include <Arduino.h>
#include "USB.h"
#include "USBHID.h"

const char* FW_VERSION = "KuandEmu v0.3.2";

USBHID HID;

static const uint8_t hidReportDescriptor[] = {
  0x06, 0x00, 0xFF,
  0x09, 0x01,
  0xA1, 0x01,

  0x19, 0x40,
  0x29, 0x40,

  0x15, 0x00,
  0x26, 0xFF, 0x00,

  0x75, 0x08,
  0x95, 0x40,

  0x81, 0x00,

  0x19, 0x40,
  0x29, 0x40,

  0x15, 0x00,
  0x26, 0xFF, 0x00,

  0x75, 0x08,
  0x95, 0x40,

  0x91, 0x00,

  0xC0
};

volatile uint8_t currentR = 0;
volatile uint8_t currentG = 0;
volatile uint8_t currentB = 0;

volatile bool blinkEnabled = false;

bool blinkState = false;
uint32_t lastBlinkToggle = 0;

void setColor(uint8_t r, uint8_t g, uint8_t b)
{
  analogWrite(18, 255 - r);
  analogWrite(17, 255 - g);
  analogWrite(16, 255 - b);
}

void rainbowFade()
{
  for (int i = 0; i < 256; i++)
  {
    setColor(255 - i, i, 0);
    delay(5);
  }

  for (int i = 0; i < 256; i++)
  {
    setColor(0, 255 - i, i);
    delay(5);
  }

  for (int i = 0; i < 256; i++)
  {
    setColor(i, 0, 255 - i);
    delay(5);
  }

  setColor(0, 0, 0);
}

class BusyLightDevice : public USBHIDDevice
{
public:

  BusyLightDevice()
  {
  }

  void begin()
  {
    HID.addDevice(this, sizeof(hidReportDescriptor));
  }

  uint16_t _onGetDescriptor(uint8_t *buffer) override
  {
    memcpy(
      buffer,
      hidReportDescriptor,
      sizeof(hidReportDescriptor)
    );

    return sizeof(hidReportDescriptor);
  }

  void sendIdentity()
  {
    uint8_t report[64] = {0};

    memcpy(&report[0],  "PLENOM",   6);
    memcpy(&report[8],  "DASAN",    5);
    memcpy(&report[16], "20150528", 8);

    HID.SendReport(0, report, 64);
  }

  void _onOutput(uint8_t report_id,
                 const uint8_t *buffer,
                 uint16_t len) override
  {
    (void)report_id;

    if (len == 0)
    {
      sendIdentity();
      return;
    }

    //
    // Keepalive / Poll Reports ignorieren
    //
    if (buffer[0] == 0x8F)
    {
      sendIdentity();
      return;
    }

    if (buffer[0] == 0x8A)
    {
      sendIdentity();
      return;
    }

    if (len >= 7)
    {
      currentR = buffer[2];
      currentG = buffer[3];
      currentB = buffer[4];

      blinkEnabled =
        (buffer[5] == 0x05) &&
        (buffer[6] == 0x05);

      if (!blinkEnabled)
      {
        setColor(
          currentR,
          currentG,
          currentB
        );
      }
    }

    sendIdentity();
  }
};

BusyLightDevice busy;

void setup()
{
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);

  setColor(0, 0, 0);

  rainbowFade();

  setColor(0, 0, 0);

  USB.VID(0x27BB);
  USB.PID(0x3BCA);

  USB.productName("BUSYLIGHT");
  USB.manufacturerName("PLENOM APS");

  busy.begin();

  HID.begin();
  USB.begin();

  delay(1000);

  busy.sendIdentity();
}

void loop()
{
  if (blinkEnabled)
  {
    if (millis() - lastBlinkToggle >= 125)
    {
      lastBlinkToggle = millis();

      blinkState = !blinkState;

      if (blinkState)
      {
        setColor(
          currentR,
          currentG,
          currentB
        );
      }
      else
      {
        setColor(0, 0, 0);
      }
    }
  }

  delay(10);
}
