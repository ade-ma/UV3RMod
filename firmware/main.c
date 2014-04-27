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

int main()
{
  //Pin 31 is R10
  initIOPorts();

  //msDelay(100);

  //initRadioSettings();

  //msDelay(100); //Show startup screen for 1 second

  //Initial RDA settings
//  rda1846Init();


  uartInit();

  while(1)
  {
    WDTR	= 0xFF;
    if (uartAvailable() > 0) processSerialCommand();
  }

  return 0;
}
