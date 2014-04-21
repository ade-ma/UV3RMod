/*
 * This program is used to flash the MC81F8616L chip which is part of the uv3r ham radio
 * More info at www.liorelazary.com
 *
 * Created by Lior Elazary (KK6BWA) Copyright (C) 2013 <lior at elazary dot com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

//Protocol
//   CMD            Param               Description
//   S                                  Enter ISP mode
//   C                                  Exit  ISP mode
//   I                                  Get Chip ID
//   F              HH                  Flash config register with hex HH
//   E                                  Erase flash memory
//   P              AAAA LL DDDD...     Program memory with starting at address AAAA length LL and data DDDDDD (2char hex code)
//   R              SSSS EEEE           Read memory from address SSSS to EEEE
//On success return OK
//On failure return ERR


#include <avr/io.h>

//Programming pin out
#define MC_SCK 7
#define MC_SDA 6
#define MC_VPP 5

#define LED 13

#define FALSE 0
#define TRUE 1

unsigned char flashData[256]; // global block storage

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(38400);

  // initialize the digital pin as an output.
  pinMode(MC_SCK, OUTPUT);
  pinMode(MC_SDA, OUTPUT);
  pinMode(MC_VPP, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(MC_SCK, LOW);
  digitalWrite(MC_SDA, LOW);
  digitalWrite(MC_VPP, HIGH);
  digitalWrite(LED, LOW);


}


unsigned char waitForACK()
{
  unsigned char gotData = FALSE;
  int i;
  pinMode(MC_SDA, INPUT);

  for(i=0; i<30000; i++)
  {
    if (!digitalRead(MC_SDA)) //Wait until we get a response
    {
      break;
      gotData = TRUE;
    }
    delayMicroseconds(100);
  }
  pinMode(MC_SDA, OUTPUT);
  digitalWrite(MC_SDA, HIGH);

  return gotData;
}

void spiTX(unsigned char data)
{
  pinMode(MC_SDA, OUTPUT);
  int counter;
  for(counter=8; counter  ; counter--)
  {
    //Place the data on the line
    if (data & 0x01)
      digitalWrite(MC_SDA, HIGH);
    else
      digitalWrite(MC_SDA, LOW);

    //Clock the data
    digitalWrite(MC_SCK, LOW);
    //delayMicroseconds(4);

    //Set data/read
    digitalWrite(MC_SCK, HIGH);
    //delayMicroseconds(8);

    data >>= 1; //next bit
  }

}

unsigned char spiRX()
{
  unsigned char data;
  pinMode(MC_SDA, INPUT);

  int counter;
  for(counter=0; counter<8  ; counter++)
  {
    data >>= 1;
    digitalWrite(MC_SCK, LOW);
    delayMicroseconds(4);
    //Set data/read
    digitalWrite(MC_SCK, HIGH);
    if (digitalRead(MC_SDA))
      data |= 0x80;
    delayMicroseconds(8);

  }

  pinMode(MC_SCK, OUTPUT);
  digitalWrite(MC_SDA, HIGH);
  return data;
}

void enterISP()
{
  //Enter
  digitalWrite(MC_SCK, HIGH);
  digitalWrite(MC_SDA, HIGH);
  digitalWrite(MC_VPP, LOW);
  delay(240);
  digitalWrite(LED, HIGH);
}

void exitISP()
{
  delay(200);
  digitalWrite(MC_SCK, LOW);
  digitalWrite(MC_SDA, LOW);
  digitalWrite(MC_VPP, HIGH);
  digitalWrite(LED, LOW);
}

void sendData(unsigned char* data, int length)
{
  int i=0;
  for(i=0; i<length; i++)
  {
    spiTX(data[i]);  //10101010
    delayMicroseconds(40);
    waitForACK();
  }
}

uint8_t getch() {
  while(!Serial.available());
  return Serial.read();
}

void chipSetup()
{
  spiTX(0x55);
  delayMicroseconds(40);
  waitForACK();

  spiTX(0xAA);
  delayMicroseconds(40);
  spiTX(0x5A);
  delayMicroseconds(40);
  spiTX(0xA5);
  delayMicroseconds(40);
}

unsigned char modeSetup(unsigned char mode)
{
  spiTX(0x01);
  delayMicroseconds(40);
  waitForACK();

  spiTX(0x00);
  delayMicroseconds(40);
  waitForACK();

  spiTX(0x00);
  delayMicroseconds(40);
  waitForACK();

  spiTX(0x05);
  delayMicroseconds(40);
  waitForACK();

  spiTX(mode);
  delayMicroseconds(40);
  waitForACK();
  digitalWrite(MC_SDA, LOW);
  delay(1);

  unsigned char val = spiRX();

  return val;

}

unsigned char getChipID()
{
  chipSetup();
  unsigned char val = modeSetup(0x00);


  Serial.print("Chip id: ");
  Serial.println(val, HEX);

  if (val == 0x82)
    return TRUE; //Success
  else
    return FALSE; //Fail to get ID

}

void setMode()
{
  //unsigned char data[] =
  //{ 0x55, 0xAA, 0x5A, 0xA5, 0x01, 0x00, 0x00, 0x05 , 0x08};
  //sendData(data, 9);

  //Read chip ID
  //delay(1); //waitForACK();
  //unsigned char val = spiRX();
  //Serial.print("Mode: ");
  //Serial.println(val, HEX);

  chipSetup();
  unsigned char val = modeSetup(0x08);

  //Serial.print("Mode2: ");
  //Serial.println(val, HEX);
  //Return 1
}

void setRegister()
{
  unsigned char data[] =
  { 0x55, 0xAA, 0x5A, 0xA5, 0x02, 0x00, 0x00, 0x03 , 0x05,
   0x02}; //Register 20FF value to 0x00
  sendData(data, 10);

  //Read chip ID
  delay(1); //waitForACK();
  unsigned char val = spiRX();
  Serial.print("register: ");
  Serial.println(val, HEX);
}

void setFlashAddr(unsigned short addr, unsigned char len)
{
  unsigned char addrU = (addr >> 8) & 0xFF;
  unsigned char addrL = addr & 0xFF;
  chipSetup();

  spiTX(len);
  delayMicroseconds(40);
  waitForACK();

  spiTX(addrU);
  delayMicroseconds(40);
  waitForACK();

  spiTX(addrL);
  delayMicroseconds(40);
  waitForACK();

  spiTX(0x00);
  delayMicroseconds(40);
  waitForACK();

}

void setEraseMode()
{
  unsigned char data[] =
  { 0x55, 0xAA, 0x5A, 0xA5, 0x01, 0x00, 0x00, 0x03 , 0x01};
  sendData(data, 9);

  //Read chip ID
  delay(1); //waitForACK();
  unsigned char val = spiRX();
  Serial.print("Erase Mode: ");
  Serial.println(val, HEX);

}

unsigned char eraseFlash()
{
  if (!getChipID())
  {
    Serial.println("Failed to get chip ID");
    return FALSE;
  }
  delay(30);
  setEraseMode();

  waitForACK();

  delay(2000);
  setRegister();
  delay(30);

  return TRUE;

}

void setFastClock()
{

 DDRD = 0xFF;
  while(1) {
    PORTD ^= 0xFF;
  }
}

unsigned char programFuse()
{
  if (!getChipID())
  {
    Serial.println("Failed to get chip ID");
    return FALSE;
  }
  delay(30);
  setMode();
  delay(30);
  setRegister();
  delay(30);

  return TRUE;
}

unsigned char enterProgramMode()
{
  if (!getChipID())
  {
    Serial.println("Failed to get chip ID");
    return FALSE;
  }
  delay(15);
  setMode();

  return TRUE;
}

unsigned char programFlash(unsigned short addr, unsigned char len)
{
  setFlashAddr(addr, len);

  int i=0;
  for(i=0; i<len; i++)
  {
    spiTX(flashData[i]);
    delayMicroseconds(40);
    waitForACK();
  }
  digitalWrite(MC_SDA, HIGH);
  delay(1);


  pinMode(MC_SDA, INPUT);

  //Wait for data to go low and the high again
  for(i=0; i<30000; i++)
    if (digitalRead(MC_SDA)) //Wait until we get a response
      break;
  for(i=0; i<30000; i++)
    if (!digitalRead(MC_SDA)) //Wait until we get a response
      break;


  unsigned char val = spiRX();
  Serial.print("Program result: ");
  Serial.println(val, HEX);

  return val;
}

void setReadRange(unsigned short startAddr, unsigned short endAddr)
{
/*
  unsigned char data[] =
  { 0x55, 0xAA, 0x5A, 0xA5, 0x05, 0x00, 0x00, 0x04 ,
   0xC0, 0x00,
   0xC0, 0xFF, 0x00};

   data[8] = (startAddr >> 8) & 0xFF;
   data[9] = startAddr & 0xFF;
   data[10] = (endAddr >> 8) & 0xFF;
   data[11] = endAddr & 0xFF;
   sendData(data, 13);
  */

   unsigned char startAddrU = (startAddr >> 8) & 0xFF;
   unsigned char startAddrL = startAddr & 0xFF;
   unsigned char endAddrU = (endAddr >> 8) & 0xFF;
   unsigned char endAddrL = endAddr & 0xFF;
   chipSetup();

   spiTX(05);
   delayMicroseconds(40);
   waitForACK();

   spiTX(0x00);
   delayMicroseconds(40);
   waitForACK();

   spiTX(0x00);
   delayMicroseconds(40);
   waitForACK();

   spiTX(0x04);
   delayMicroseconds(40);
   waitForACK();

   spiTX(startAddrU);
   delayMicroseconds(40);
   waitForACK();

   spiTX(startAddrL);
   delayMicroseconds(40);
   waitForACK();

   spiTX(endAddrU);
   delayMicroseconds(40);
   waitForACK();

   spiTX(endAddrL);
   delayMicroseconds(40);
   waitForACK();

   spiTX(0x00);
   delayMicroseconds(40);
   waitForACK();

}


unsigned char readFlash(unsigned short startAddr, unsigned short endAddr)
{
  int i=0;
  unsigned short len = endAddr - startAddr;

  if (len > 255)
  {
    Serial.println("Only 255 byte can be returned at a time");
    return FALSE;
  }

  //Set flashData to 0
  for(int i=0; i<256; i++)
    flashData[i] = 0;

  setReadRange(startAddr, endAddr);

  //waitForACK();
  delay(1);

  for(i=0; i<len; i++)
    flashData[i] = spiRX();

  setMode();
  //delay(30);


  return TRUE;
}

byte getVal(char c)
{
   if(c >= '0' && c <= '9')
     return (byte)(c - '0');
   else
     return (byte)(c-'A'+10);
}

int mcuisp()
{

  uint8_t ch = getch();

  switch (ch) {
    case 'S': //Enter ISP mode
      enterISP();
      Serial.println("Enter ISP");
      Serial.println("OK");
      return 1;
      break;
    case 'C': //Close ISP mode
      Serial.println("Exit ISP");
      exitISP();
      Serial.println("OK");
      return 1;
      break;
    case 'I': //Get chip ID
      if (getChipID())
      {
        Serial.println("OK");
        return TRUE;
      } else {
        Serial.println("ERR:Failed to get chip ID");
        return FALSE;
      }
      break;
    case 'F':
      {
        unsigned char bits = getVal(getch()) << 4;
        bits |= getVal(getch());

        Serial.print("Config Device with ");
        Serial.println(bits, HEX);
        if (programFuse())
        {
          Serial.println("OK");
          return TRUE;
        } else {
          Serial.println("ERR:Failed to config chip");
          return FALSE;
        }
        break;
      }
    case 'E':
      {
        Serial.println("Erasing chip");
        if (eraseFlash())
        {
          Serial.println("OK");
          return TRUE;
        } else {
          Serial.println("ERR:Failed to erase chip");
          return FALSE;
        }
        break;
      }
    case 'M':
      {
        //Serial.println("Enter Program Mode");
        enterProgramMode();
        Serial.println("OK");
        //if (enterProgramMode())
        //{
        //  Serial.println("OK");
        //  return TRUE;
        //} else {
        //  Serial.println("ERR:Failed to enter program mode");
        //  return FALSE;
        //}
	return TRUE;
      }
    case 'P':
      {
        unsigned short addr = getVal(getch()) << 12;
        addr |= getVal(getch()) << 8;
        addr |= getVal(getch()) << 4;
        addr |= getVal(getch());

        getch(); //skip space

        unsigned char len = getVal(getch()) << 4;
        len |= getVal(getch());

        getch(); //skip space

        for (int i = 0; i < len; i++)
        {
          unsigned char data = getVal(getch()) << 4;
          data |= getVal(getch());
          flashData[i] = data;
        }

        if (len > 0)
        {
          Serial.print("Program Flash at: ");
          Serial.print(addr, HEX);
          Serial.print(" Len: ");
          Serial.println(len, HEX);
          unsigned char val = programFlash(addr, len);
          if (val)
          {
            Serial.print("OK:");
            Serial.println(val, HEX);
            return TRUE;
          } else {
            Serial.println("ERR:Failed to program flash");
            return FALSE;
          }
        } else {
          Serial.println("ERR: Can not flash with no data");
          return FALSE;
        }

        break;
      }
    case 'R':
      {
        unsigned short startAddr = getVal(getch()) << 12;
        startAddr |= getVal(getch()) << 8;
        startAddr |= getVal(getch()) << 4;
        startAddr |= getVal(getch());

        getch(); //skip space

        unsigned short endAddr = getVal(getch()) << 12;
        endAddr |= getVal(getch()) << 8;
        endAddr |= getVal(getch()) << 4;
        endAddr |= getVal(getch());

        Serial.println("Reading ");
        Serial.print(startAddr, HEX);
        Serial.print(" ");
        Serial.println(endAddr, HEX);
        unsigned short len = endAddr - startAddr;
        char format[2];
        if (readFlash(startAddr, endAddr))
        {
          Serial.print("OK:");
          for(int i=0; i<len; i++)
          {
            sprintf(format, "%0.2X", flashData[i]);
            Serial.print(format);
          }
          Serial.println();

          return TRUE;
        } else {
          Serial.println("ERR:Failed to readflash");
          return FALSE;
        }
        break;
      }

    default:
      Serial.print("Unknown Command ");
      Serial.println(ch);
  }
}


void loop(void)
{
  if (Serial.available())
    mcuisp();
}
