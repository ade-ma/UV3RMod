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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA	02110-1301 USA
 */
//Functions related to control the radio remotly
#include <MC81F8816/MC81F8816.h>
#include <hms800.h>
#include "uv3r.h"
#include "uart.h"
#include "rda.h"
#include "spi.h"

void processSerialCommand()
{
	if (getChar() != 0xAA || getChar() != 0x55) {
		return;
	}
	uartSendMsg("Got start\r\n");
	unsigned char cmd = getChar();
	uartSendMsg("Got Command ");
	uartSendNum(cmd, 10);
	uartSendMsg("\r\n");

	switch(cmd)
	{
	case 'D':
		if(getChar() == '\r' && getChar() == '\n')
		rda1846TXDTMF(radioSettings.txDTMF, 6, 1000);
		break;
	case 'd':
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
			short out = SPI(addr, data);
			uartSendNum(out, 16);
			uartSendMsg("\r\n");
		}
		}
		break;
	}
}

