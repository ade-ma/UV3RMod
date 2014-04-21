/*
 * This file is part of the uv3r firmware
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
//Functions related to control the radio remotly
#include <MC81F8816/MC81F8816.h>
#include <hms800.h>
#include "uv3r.h"
#include "uart.h"
#include "rda.h"

void updateRDA1846Freq(unsigned short freqM, unsigned short freqK){
  //Convert from DCB to binary of freqM and freqK while using short (2 byte) numbers
  //The rda1846 keeps the freq in 1khz/8 steps
  //so: 32Bit val = freqM*8000 + freqK*8
  //since 8000 can be broken down into 125*64 we can first

  unsigned short freqKs = freqK;

  //Since freqK is a fraction of 1000,
  //convert it into a whole number
  if (freqK > 0 && freqK < 10)
    freqKs = freqK*100;
  else if (freqK >= 10 && freqK < 100)
    freqKs = freqK*10;

  unsigned short tmp = freqM*125;
  unsigned short highWord = (tmp >> 10); //Get the top 4 bits
  tmp = (tmp << 6); //Just get the lower bits

  unsigned short lowWord =  tmp + (freqK<<3); //tmp + freqK*8
  if (lowWord < tmp)
    highWord += 1; //Overflow

  rda1846SetFreq(highWord, lowWord);
}


void getFreqFromSerial(unsigned short* freqM, unsigned short* freqK)
{

  *freqM  = getChar()&0xFF;
  *freqM  <<= 8;
  *freqM  |= getChar()&0xFF;

  *freqK  = getChar()&0xFF;
  *freqK  <<= 8;
  *freqK  |= getChar()&0xFF;

  if(getChar() == '\r' && getChar() == '\n')
  {
    uartSendMsg("Set freqM: ");
    uartSendNum(*freqM, 10);
    uartSendMsg("\r\n");

    uartSendMsg("Set freqM: ");
    uartSendNum(*freqK, 10);
    uartSendMsg("\r\n");
  }

  return;


}

void setReg(unsigned char addr, short data)
{
  uartSendMsg("Set2: ");
  uartSendNum(addr, 16);
  uartSendMsg(" to ");
  uartSendNum(data, 16);
  uartSendMsg("\r\n");

  //SPI(0x3C, 0x0958 ); //00000001 00010001
  //SPI(addr, data);
  SPI(addr, data );
}

void processSerialCommand()
{
  uartSendMsg("Check start\r\n");
  if (getChar() != 0xAA || getChar() != 0x55)
    return;
  uartSendMsg("Got start\r\n");
  unsigned char cmd = getChar();
  uartSendMsg("Got Command ");
  uartSendNum(cmd, 10);
  uartSendMsg("\r\n");

  switch(cmd)
  {
    case 'F':
      getFreqFromSerial(&radioSettings.rxFreqM, &radioSettings.rxFreqK);
      updateRDA1846Freq(radioSettings.rxFreqM, radioSettings.rxFreqK);
      break;
    case 'G':
       uartSendNum(radioSettings.rxFreqM, 10);
       uartSendMsg(" ");
       uartSendNum(radioSettings.rxFreqK, 10);
       uartSendMsg("\r\n");
       break;
    case 'T':
      if (getChar() == '\r' && getChar() == '\n')
        rda1846TX();
      break;
    case 'R':
      if(getChar() == '\r' && getChar() == '\n')
        rda1846RX(1);
      break;
    case 'D':
      if(getChar() == '\r' && getChar() == '\n')
        rda1846TXDTMF(radioSettings.txDTMF, 6, 1000);
      break;
    case 'd':
      {
        uartSendMsg("Send Digital RTTY\n");

        unsigned char data = getChar()&0xFF;

        short time = getChar()&0xFF;
        time <<= 8;
        time |= getChar()&0xFF;

        if(getChar() == '\r' && getChar() == '\n')
          rda1846TXDigital(data, time,
              5796, //Mark 1.415Khz
              6492 //space 1.585Khz
              );
        uartSendMsg("Send Digital Done\n");
      }
      break;
    case 'S':
      {
        unsigned char addr = getChar()&0xFF;

        short data = getChar()&0xFF;
        data <<= 8;
        data |= getChar()&0xFF;

        if(getChar() == '\r' && getChar() == '\n')
        {
          uartSendMsg("Set: ");
          uartSendNum(addr, 16);
          uartSendMsg(" to ");
          uartSendNum(data, 16);
          uartSendMsg("\r\n");

          rda1846SetReg(addr, data); //, data);
        }
      }
      break;
  }

}

