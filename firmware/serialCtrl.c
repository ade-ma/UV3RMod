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
#include "spi.h"

void processSerialCommand()
{
	if (getChar() != 0xAA || getChar() != 0x55) {
		return;
	}
	uartSendMsg("Got start\r\n");
	unsigned char cmd = getChar();
	uartSendMsg("Got Command ");
	uartSendNum(cmd, 16);
	uartSendMsg("\r\n");

	switch(cmd)
	{
	case 'E':
		{
		short reg = getChar()&0xff;
		reg <<= 8;
		reg |= getChar()&0xff;
		if (getChar() == '\r' && getChar() == '\n')
		{
			unsigned char val = *((char *)reg);
			uartSendNum(val, 16);
			uartSendMsg("\r\n");
		}
		}
		break;
	case 'O':
		{
		short reg = getChar()&0xFF;
		reg <<= 8;
		reg |= getChar()&0xFF;
		char val = getChar()&0xFF;
		if(getChar() == '\r' && getChar() == '\n')
		{
			*((char *) reg) = val;
			uartSendNum(val, 16);
			uartSendMsg("\r\n");
		}
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
			short out = SPI(addr, data);
			uartSendNum(out, 16);
			uartSendMsg("\r\n");
		}
		}
		break;
	}
}

