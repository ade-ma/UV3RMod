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

#include <MC81F8816/MC81F8816.h>
#include <hms800.h>
#include "uv3r.h"
#include "uart.h"
#include "rda.h"

struct RadioSettings radioSettings;

void initRadioSettings()
{
  radioSettings.rxFreqM = 145;
  radioSettings.rxFreqK = 525;

  radioSettings.txFreqM = 145;
  radioSettings.txFreqK = 525;

  radioSettings.offset = 0;

  radioSettings.rssi = 0;
  radioSettings.vssi = 0;
  radioSettings.dtmf = 0;
  radioSettings.flags = 0;

  radioSettings.ctcss = 0;


  radioSettings.txDTMF[0] = 0x01;
  radioSettings.txDTMF[1] = 0x02;
  radioSettings.txDTMF[2] = 0x03;
  radioSettings.txDTMF[3] = 0x10; //Blank
  radioSettings.txDTMF[4] = 0x10; //Blank
  radioSettings.txDTMF[5] = 0x10; //Blank

  radioSettings.transmitting = FALSE;
  radioSettings.txTime = 0;

}

int main()
{
  //Pin 31 is R10
  initIOPorts();

  msDelay(100);

  initRadioSettings();

  msDelay(100); //Show startup screen for 1 second

  //Initial RDA settings
  rda1846Init();
  rda1846RX(1); //Go into rx mode


  uartInit();

  while(1)
  {
    WDTR	= 0xFF;
    if (uartAvailable() > 0) processSerialCommand();
  }

  return 0;
}
