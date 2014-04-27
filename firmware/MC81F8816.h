/******************************************************************************* 
   Title            : Control registers' definitions of MC81F8816
   File Name        : MC81F8816.h
   Release Date     : 2009. 5. 6.
   Revision No.     : 1.0
   Programmer       : NW MA
   Cross Checker    : NW MA
*******************************************************************************/

/******************************************************************************* 
   Copyright (c) 2009, ABOV Semiconductor Co. Ltd
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. 
********************************************************************************/

#ifndef	_MC81F8816_H_
#define	_MC81F8816_H_ 1

sfr	I2CMR	  = 0x90          ; // [R/W] I2C Mode control Register 
sbit  I2CEA   = I2CMR^7       ; //       I2C Enable
sbit  WREL    = I2CMR^5       ; //       release SCL to High
sbit  STPIE   = I2CMR^4       ; //       Stop detected 
sbit  WTIM    = I2CMR^3       ; //       I2C Interrupt Pending time ACK or 8th clock 
sbit  ACKE    = I2CMR^2       ; //       ACK enable
sbit  STT     = I2CMR^1       ; //       Start generate
sbit  SPT     = I2CMR^0       ; //       Stop  generate

sfr	I2CSR	  = 0x91          ; // [R/W] I2C Status Register 
sbit  MSTS    = I2CSR^7       ; //       Master device state
sbit  ALD     = I2CSR^6       ; // [R/W] Arbitration Lost
sbit  EXC     = I2CSR^5       ; // [R/W] General Call
sbit  COI     = I2CSR^4       ; // [R/W] Selected as Slave 
sbit  TRC     = I2CSR^3       ; //       Transmit
sbit  ACKD    = I2CSR^2       ; //       Acknowledge detected 
sbit  STD     = I2CSR^1       ; //       Start Condition Detected 
sbit  SPD     = I2CSR^0       ; //       Stop  Condition Detected 

sfr	I2CCR	  = 0x92          ; // [R/W] I2C Clock control Register 
sbit  FM      = I2CCR^7       ; //       Fast mode fscl=400 kHz

sfr	I2CPR	  = 0x93          ; // [R/W] I2C Pipe and Shift Register 
sfr	I2CAR	  = 0x94          ; // [R/W] I2C Slave Address Register 

sfr	XPLLCR  = 0x9A          ; // [R/W] PLL Control Register 
sbit  FXTS    = XPLLCR^1      ; //       fxt select
sbit  XPLLE   = XPLLCR^0      ; //       Oscillator PLLenable 

sfr	XPLLDAT = 0x9B          ; // [R/W] PLL Data Register 
sbit  XPLLFD2 = XPLLDAT^5     ; //       PLL Feedback divider 
sbit  XPLLFD1 = XPLLDAT^4     ; //               
sbit  XPLLFD0 = XPLLDAT^3     ; //                 
sbit  XPLLPS2 = XPLLDAT^2     ; //       PLL Post-Scaler Control 
sbit  XPLLPS1 = XPLLDAT^1     ; //                
sbit  XPLLPS0 = XPLLDAT^0     ; //                

sfr   R0OD    = 0xA0		; // [W]   R0 Open Drain Control Register
sfr   R1OD    = 0xA1		; // [W]   R1 Open Drain Control Register
sfr   R2OD    = 0xA2		; // [W]   R2 Open Drain Control Register
sfr   R3OD    = 0xA3		; // [W]   R3 Open Drain Control Register
sfr   R4OD    = 0xA4		; // [W]   R4 Open Drain Control Register

sfr	R0PU	  = 0xA5          ; // [W]   R0 Pull up Register
sfr	R1PU    = 0xA6          ; // [W]   R1 Pull up Register
sfr	R2PU    = 0xA7          ; // [W]   R2 Pull up Register
sfr	R3PU    = 0xA8          ; // [W]   R3 Pull up Register
sfr	R4PU    = 0xA9          ; // [W]   R4 Pull up Register

sfr   R0PSR   = 0xAA          ; // [W]   R0 Port Function select Register
sfr   R1PSR	  = 0xAB          ; // [W]   R1 Port Function select Register

sfr	R5PSR   = 0xAC          ; // [R/W] R5/LCD Port Selection Register
sbit  R5PS7   = R5PSR^7       ; //       
sbit  R5PS6	  = R5PSR^6       ; //       
sbit  R5PS5	  = R5PSR^5	      ; //       
sbit  R5PS4	  = R5PSR^4       ; //       
sbit  R5PS3	  = R5PSR^3	      ; //       
sbit  R5PS2	  = R5PSR^2       ; //       
sbit  R5PS1	  = R5PSR^1       ; //       
sbit  R5PS0	  = R5PSR^0       ; //       

sfr   R6PSR	  = 0xAD          ; // [R/W] R6/LCD Port Selection Register
sbit  R6PS7	  = R6PSR^7	      ; //       
sbit  R6PS6	  = R6PSR^6       ; //       
sbit  R6PS5	  = R6PSR^5       ; //       
sbit  R6PS4	  = R6PSR^4       ; //       
sbit  R6PS3	  = R6PSR^3       ; //       
sbit  R6PS2	  = R6PSR^2       ; //       
sbit  R6PS1	  = R6PSR^1       ; //       
sbit  R6PS0	  = R6PSR^0       ; //       

sfr   R7PSR   = 0xAE          ; // [R/W] R7/LCD Port Selection Register
sbit  R7PS7	  = R7PSR^7	      ; //       
sbit  R7PS6	  = R7PSR^6	      ; //       
sbit  R7PS5	  = R7PSR^5	      ; //       
sbit  R7PS4	  = R7PSR^4	      ; //       
sbit  R7PS3	  = R7PSR^3	      ; //       
sbit  R7PS2	  = R7PSR^2	      ; //       
sbit  R7PS1	  = R7PSR^1	      ; //       
sbit  R7PS0	  = R7PSR^0	      ; //       

sfr   R7      = 0xB0          ; // [R/W] R7 Data Register
sbit  R77     = R7^7          ; //       
sbit  R76     = R7^6          ; //       
sbit  R75     = R7^5          ; //       
sbit  R74     = R7^4          ; //       
sbit  R73     = R7^3          ; //       
sbit  R72     = R7^2          ; //       
sbit  R71     = R7^1          ; //       
sbit  R70     = R7^0          ; //       

sfr   LCR     = 0xB2          ; // [R/W] LCD Control Register
sbit  SCKD    = LCR^7         ; //       Sub Clock Disable[1]
sbit  LCDEN	  = LCR^5         ; //       LCD Display Enable
sbit  LCDD0	  = LCR^3         ; //       LCD Duty Selection 1/4 or 1/8
sbit  LCK1    = LCR^1         ; //       LCD Clock Source Selection
sbit  LCK0    = LCR^0         ; //

sfr   LBCR    = 0xB3          ; // [W]   LCDBias Control Register
sbit  CTRS    = LBCR^7        ; //       Bias Control Select
sbit  CTRDS3  = LBCR^6        ; //       LCD Contrast Control 
sbit  CTRDS2  = LBCR^5        ; //        
sbit  CTRDS1  = LBCR^4        ; //
sbit  CTRDS0  = LBCR^3        ; //        
sbit  SYSBIR1 = LBCR^2        ; //       Reset/Freeze Selection after BOD  
sbit  SYSBIR0 = LBCR^1        ; //        
sbit  BIF     = LBCR^0        ; //       Brown Out detected? 

sfr   R7IO    = 0xB4          ; // [W]   R7 Direction Register

sfr   SPIM	  = 0xB6          ; // [R/W] SIO Mode Control Register
sbit  POL     = SPIM^7        ; //       Serial Clock Polarity Selection
sbit  IOSW    = SPIM^6        ; //       Serial Input Pin Selection
sbit  SM1     = SPIM^5        ; //       SIO Operation Mode Selection
sbit  SM0     = SPIM^4        ; //
sbit  SCK1    = SPIM^3        ; //       SIO Clock Selection
sbit  SCK0    = SPIM^2        ; //
sbit  SIOST	  = SPIM^1        ; //       SIO Start
sbit  SIOSF	  = SPIM^0        ; //       SIO Status

sfr   SPIR    = 0xB7          ; // [R/W] SIO Data Shift Register

sfr   ASIMR0  = 0xB8          ; // [R/W] Asynchronus Serial Interface Mode Register0
sbit  TX0M    = ASIMR0^7	; //       Operation Mode
sbit  RX0M    = ASIMR0^6	; //
sbit  PS01    = ASIMR0^5	; //       Parity Bit Selection
sbit  PS00    = ASIMR0^4	; //
sbit  SL0     = ASIMR0^2	; //       Stop Bit Length
sbit  ISRM0   = ASIMR0^1	; //       Receive Completion Interrupt Request

sfr   ASISR0  = 0xB9          ; // [R]   Asynchronus Serial Interface Status Register0
sbit  PE0     = ASISR0^2      ; //       Parity Error
sbit  FE0     = ASISR0^1      ; //       Framing Error
sbit  OVE0    = ASISR0^0      ; //       Overrun Error
 
sfr   BRGCR0  = 0xBA          ; // [R/W] BAUD Rate Generate Control Register0
sbit  TPS02	  = BRGCR0^6	; //       Source Clock Selection for 5-Bit Counter
sbit  TPS01	  = BRGCR0^5	; //       
sbit  TPS00	  = BRGCR0^4	; //       
sbit  MDL03	  = BRGCR0^3	; //       Source Clock Selection for 5-Bit Counter
sbit  MDL02	  = BRGCR0^2	; //       
sbit  MDL01	  = BRGCR0^1      ; //       
sbit  MDL00	  = BRGCR0^0      ; //       

sfr   RXBR	  = 0xBB          ; // [R]   Receiver Buffer Register0
sfr   TXSR	  = 0xBB          ; // [W]   Transmit Shift Register0

sfr   R0      = 0xC0          ; // [R/W] R0 Port Data Register
sbit  R07     = R0^7          ; //       
sbit  R06     = R0^6          ; //       
sbit  R05     = R0^5          ; //       
sbit  R04     = R0^4          ; //       
sbit  R03     = R0^3          ; //       
sbit  R02     = R0^2          ; //       
sbit  R01     = R0^1          ; //       
sbit  R00     = R0^0          ; //       

sfr   R0IO    = 0xC1          ; // [W]   R0 Port Direction Register

sfr   R1      = 0xC2          ; // [R/W] R1 Port Data Register
sbit  R17     = R1^7          ; //       
sbit  R16     = R1^6          ; //       
sbit  R15     = R1^5          ; //       
sbit  R14     = R1^4          ; //       
sbit  R13     = R1^3          ; //       
sbit  R12     = R1^2          ; //       
sbit  R11     = R1^1          ; //       
sbit  R10     = R1^0          ; //       

sfr   R1IO    = 0xC3          ; // [W]   R1 Port Direction Register

sfr   R2      = 0xC4          ; // [R/W] R2 Port Data Register
sbit  R27     = R2^7          ; //       
sbit  R26     = R2^6          ; //       
sbit  R25     = R2^5          ; //       
sbit  R24     = R2^4          ; //       
sbit  R23     = R2^3          ; //       
sbit  R22     = R2^2          ; //       
sbit  R21     = R2^1          ; //       
sbit  R20     = R2^0          ; //       

sfr   R2IO    = 0xC5          ; // [W]   R2 Port Direction Register

sfr   R4      = 0xC8          ; // [R/W] R4 Port Data Register
sbit  R47     = R4^7          ; //       
sbit  R46     = R4^6          ; //       
sbit  R45     = R4^5          ; //       
sbit  R44     = R4^4          ; //       
sbit  R43     = R4^3          ; //       
sbit  R42     = R4^2          ; //       
sbit  R41     = R4^1          ; //       
sbit  R40     = R4^0          ; //       

sfr   R4IO    = 0xC9          ; // [W]   R4 Port Direction Register

sfr   R5      = 0xCA          ; // [R/W] R5 Port Data Register
sbit  R57     = R5^7          ; //       
sbit  R56     = R5^6          ; //       
sbit  R55     = R5^5          ; //       
sbit  R54     = R5^4          ; //       
sbit  R53     = R5^3          ; //       
sbit  R52     = R5^2          ; //       
sbit  R51     = R5^1          ; //       
sbit  R50     = R5^0          ; //       

sfr   R5IO    = 0xCB          ; // [W]   R5 Port Direction Register

sfr   R6      = 0xCC          ; // [R/W] R6 Port Data Register
sbit  R67     = R6^7          ; //       
sbit  R66     = R6^6          ; //       
sbit  R65     = R6^5          ; //       
sbit  R64     = R6^4          ; //       
sbit  R63     = R6^3          ; //       
sbit  R62     = R6^2          ; //       
sbit  R61     = R6^1          ; //       
sbit  R60     = R6^0          ; //       

sfr   R6IO    = 0xCD          ; // [W]   R6 Port Direction Register

sfr   BUZR    = 0xCE          ; // [W]   Buzzer Driver Register
sbit  BUCK1   = BUZR^7        ; //       Buzzer Clock Source
sbit  BUCK0   = BUZR^6        ; //       
sbit  BUR5    = BUZR^5        ; //       
sbit  BUR4    = BUZR^4        ; //       
sbit  BUR3    = BUZR^3        ; //       
sbit  BUR2    = BUZR^2        ; //       
sbit  BUR1    = BUZR^1        ; //       
sbit  BUR0    = BUZR^0        ; //       

sfr   RPR     = 0xCF          ; // [R/W] RAM Page Register
sbit  RPR2    = RPR^2         ; //       
sbit  RPR1    = RPR^1         ; //       
sbit  RPR0    = RPR^0         ; //       

sfr   TM0     = 0xD0          ; // [R/W] Timer0 Mode Control Register 
sbit  CAP0    = TM0^5         ; //       Capture Mode Selection
sbit  T0CK2   = TM0^4         ; //       Count Clock
sbit  T0CK1   = TM0^3         ; //
sbit  T0CK0   = TM0^2         ; //
sbit  T0CN    = TM0^1         ; //       Continue
sbit  T0ST    = TM0^0         ; //       Start

sfr   T0      = 0xD1          ; // [R]   Timer0 Register
sfr   TDR0    = 0xD1          ; // [W]   Timer0 Data Register
sfr   CDR0    = 0xD1          ; // [R]   Timer0 Capture Data Register

sfr   TM1     = 0xD2          ; // [R/W] Timer1 Mode Control Register 
sbit  POL1    = TM1^7         ; //       PWM Polarity Selection
sbit  T16B1   = TM1^6         ; //       16Bit Mode Selection
sbit  PWM0E   = TM1^5         ; //       PWM Enable Selection
sbit  CAP1    = TM1^4         ; //       Capture Mode Selection
sbit  T1CK1   = TM1^3         ; //       Count Clock
sbit  T1CK0   = TM1^2         ; //
sbit  T1CN    = TM1^1         ; //       Continue
sbit  T1ST    = TM1^0         ; //       Start

sfr   TDR1    = 0xD3          ; // [W]   Timer1 Data Register
sfr   T1PPR   = 0xD3          ; // [W]   Timer1 PWM Period Register

sfr   T1      = 0xD4          ; // [R]   Timer1 Register
sfr   T1PDR   = 0xD4          ; // [R/W] Timer1 PWM Duty Register
sfr   CDR1    = 0xD4          ; // [R]   Timer1 Capture Data Register

sfr   T1PWHR  = 0xD5          ; // [W]   Timer1 PWM High Register

sfr   TM2     = 0xD6          ; // [R/W] Timer2 Mode Control Register
sbit  CAP2    = TM2^5         ; //       Capture Mode Selection
sbit  T2CK2   = TM2^4         ; //       Count Clock
sbit  T2CK1   = TM2^3         ; //
sbit  T2CK0   = TM2^2         ; //
sbit  T2CN    = TM2^1         ; //       Continue 
sbit  T2ST    = TM2^0         ; //       Start

sfr   T2      = 0xD7          ; // [R]   Timer2 Register
sfr   TDR2    = 0xD7          ; // [W]   Timer2 Data Register
sfr   CDR2    = 0xD7          ; // [R]   Timer2 Capture Data Register

sfr   TM3     = 0xD8          ; // [R/W] Timer3 Mode Control Register
sbit  POL3    = TM3^7         ; //       PWM Polarity Selection
sbit  T16B3   = TM3^6         ; //       16Bit Mode Selection
sbit  PWM1E   = TM3^5         ; //       PWM Enable Selection
sbit  CAP3    = TM3^4         ; //       Capture Mode Selection
sbit  T3CK1   = TM3^3         ; //       Count Clock
sbit  T3CK0   = TM3^2         ; //
sbit  T3CN    = TM3^1         ; //       Continue
sbit  T3ST    = TM3^0         ; //       Start

sfr   TDR3    = 0xD9          ; // [W]   Timer3 Data Register
sfr   T3PPR   = 0xD9          ; // [W]   Timer3 PWM Period Register

sfr   T3      = 0xDA          ; // [R]   Timer3 Register
sfr   T3PDR   = 0xDA          ; // [R/W] Timer3 PWM Duty Register
sfr   CDR3    = 0xDA          ; // [R]   Timer3 Capture Data Register

sfr   T3PWHR  = 0xDB          ; // [W]   Timer3 PWM High Register

sfr   ADCM    = 0xE2		; // [R/W] 10-bit ADC Mode Control Register
sbit  ADEN    = ADCM^7        ; //       AD Converter Enable[1]/Disable[0]
sbit  ADCK    = ADCM^6        ; //       AD Converter Clock Source Selection
sbit  ADS3    = ADCM^5        ; //       Analog Input Port Select
sbit  ADS2    = ADCM^4        ; //
sbit  ADS1    = ADCM^3        ; //
sbit  ADS0    = ADCM^2        ; //
sbit  ADST    = ADCM^1        ; //       AD Converter Start
sbit  ADSF    = ADCM^0        ; // [R]   AD Conversion Completed[1]/Busy[1]

sfr   ADCRL   = 0xE3		; // [R]   10-bit ADC Result Register Low
sbit  ADR7    = ADCRL^7	      ; //       
sbit  ADR6    = ADCRL^6	      ; //       
sbit  ADR5    = ADCRL^5       ; //       
sbit  ADR4    = ADCRL^4       ; //       
sbit  ADR3    = ADCRL^3       ; //       
sbit  ADR2    = ADCRL^2       ; //       
sbit  ADR1    = ADCRL^1       ; //       
sbit  ADR0    = ADCRL^0       ; //       

sfr   ADCRH   = 0xE4		; // [W/R] 10-bit ADC Result Register High
sbit  PSSEL1  = ADCRH^7       ; // [W]   AD Converter Clock Selection
sbit  PSSEL0  = ADCRH^6       ; // [W]
sbit  ADC8    = ADCRH^5       ; // [W]   AD Converter Mode Selection(10bit,8bit)
sbit  ADR9    = ADCRH^1       ; // [R]
sbit  ADR8    = ADCRH^0       ; // [R]

sfr   BODR    = 0xE5		; // [R/W] BOD Control Register  
sbit  BODEN   = BODR^7        ; //       Brown Out Detect Enable
sbit  NCSEL   = BODR^6        ; //       Noise Canceller Selection
sbit  ADREF   = BODR^5        ; //       Reference Voltage Check Enable
sbit  TRM1    = BODR^4        ; //       Detection Level Trim select 
sbit	TRM0    = BODR^3        ; //        
sbit	BOD2    = BODR^2        ; //       BOD Level Select 
sbit  BOD1    = BODR^1        ; //        
sbit  BOD0    = BODR^0        ; //        

sfr   BITR    = 0xE6          ; // [R]   Basic Interval Timer Register
sfr   CKCTLR  = 0xE6          ; // [W]   Clock Control Register

sfr   SCMR    = 0xE7          ; // [R/W] System Clock Model Register 
sbit  MCC     = SCMR^2        ; //       Main Clock Oscillation Control
sbit  CS1     = SCMR^1        ; //       System Clock Selection
sbit  CS0     = SCMR^0        ; //

sfr   WDTR    = 0xE8          ; // [W]   Watchdog Timer Register
sfr   WDTDR   = 0xE8          ; // [R]   Watchdog Timer Data Register
sfr   WTR     = 0xE8          ; // [W]   Watch Timer Register

sfr   SSCR    = 0xE9          ; // [W]   Stop & Sleep Mode Control Register

sfr   WTMR    = 0xEA		; // [R/W] Watch Timer Mode Register
sbit  WTEN    = WTMR^7        ; //       Watch Timer enable
sbit  LOADEN  = WTMR^6        ; //       7bit Reload Counter Write Enable
sbit  WTIN1   = WTMR^4        ; //       Interrupt Interval Selection
sbit  WTIN0   = WTMR^3	      ; //
sbit  WTCK2   = WTMR^2        ; //       Clock Source Selection
sbit  WTCK1   = WTMR^1        ; //       
sbit  WTCK0   = WTMR^0        ; //

sfr   INTFH   = 0xF4          ; // [R/W] Interrupt Generation Flag High Register
sbit  IFSPI   = INTFH^4       ; //       SPI  INT Flag
sbit  IFRX0   = INTFH^3       ; //       UART0 RX INT Flag
sbit  IFTX0   = INTFH^2       ; //       UART0 TX INT Flag

sfr   INTFL   = 0xF5		; // [R/W] Interrupt Generation Flag Low Register
sbit  T2F     = INTFL^7       ; //       Timer2 INT Flag
sbit  T3F     = INTFL^6       ; //       Timer3 INT Flag
sbit  I2CF    = INTFL^3       ; //       I2C INT Flag
sbit  ADCF    = INTFL^2       ; //       ADC INT Flag
sbit  WTF     = INTFL^1       ; //       Watch Timer INT Flag
sbit  WDTF    = INTFL^0       ; //       Watchdog Timer INT Flag

sfr   IENH    = 0xF6          ; // [R/W] Interrupt Enable High Register
sbit  INT0E   = IENH^6        ; //       External INT0 Enable
sbit  INT1E   = IENH^5        ; //       External INT1 Enable
sbit  INT2E   = IENH^4        ; //       External INT2 Enable
sbit  RX0E    = IENH^3        ; //       UART0 RX0 INT Enable
sbit  TX0E    = IENH^2        ; //       UART0 TX0 INT Enable

sfr   IENM    = 0xF7          ; // [R/W] Interrupt Enable Middle Register
sbit  T0E     = IENM^7        ; //       Timer/Counter 0 INT Enable
sbit  T1E     = IENM^6        ; //       Timer/Counter 1 INT Enable
sbit  T2E     = IENM^5        ; //       Timer/Counter 2 INT Enable
sbit  T3E     = IENM^4        ; //       Timer/Counter 3 INT Enable
sbit  ADCE    = IENM^0        ; //       ADC INT Enable

sfr   IENL    = 0xF8          ; // [R/W] Interrupt Enable Low Register
sbit  SPIE    = IENL^7        ; //       SPI INT Enable
sbit  BITE    = IENL^6        ; //       Basic Interval Timer INT Enable
sbit  WDTE    = IENL^5        ; //       Watchdog Timer INT Enable
sbit  WTE     = IENL^4        ; //       Watch Timer INT Enable
sbit  INT3E   = IENL^3        ; //       External INT0 Enable
sbit  I2CE    = IENL^2        ; //       I2C INT Enable

sfr   IRQH    = 0xF9          ; // [R/W] Interrupt Request High Register
sbit  INT0IF  = IRQH^6        ; //       External INT0 Request
sbit  INT1IF  = IRQH^5        ; //       External INT1 Request
sbit  INT2IF  = IRQH^4        ; //       External INT2 Request
sbit  RX0IF   = IRQH^3        ; //       UART0 RX0 INT Request
sbit  TX0IF   = IRQH^2        ; //       UART0 TX0 INT Request

sfr   IRQM    = 0xFA          ; // [R/W] Interrupt Request Middle Register
sbit  T0IF    = IRQM^7        ; //       Timer/Counter 0 INT Request
sbit  T1IF    = IRQM^6        ; //       Timer/Counter 1 INT Request
sbit  T2IF    = IRQM^5        ; //       Timer/Counter 2 INT Request
sbit  T3IF    = IRQM^4        ; //       Timer/Counter 3 INT Request
sbit  ADCIF   = IRQM^0        ; //       ADC INT Enable

sfr   IRQL    = 0xFB          ; // [R/W] Interrupt Request Low Register
sbit  SIOIF   = IRQL^7        ; //       SIO INT Request
sbit  BITIF   = IRQL^6        ; //       Basic Interval Timer INT Request
sbit  WDTIF   = IRQL^5        ; //       Watchdog Timer INT Request
sbit  WTIF    = IRQL^4        ; //       Watch Timer INT Request
sbit  INT3IF  = IRQL^3        ; //       External INT3 Request
sbit  I2CIF   = IRQL^2        ; //       I2C INT Request

sfr   IEDS    = 0xFC          ; // [R/W] Interrupt Enable Edge Register 
sbit  IED3H   = IEDS^7        ; //       INT3 Edge Selection
sbit  IED3L   = IEDS^6        ; //
sbit  IED2H   = IEDS^5        ; //       INT2 Edge Selection
sbit  IED2L   = IEDS^4        ; //
sbit  IED1H   = IEDS^3        ; //       INT1 Edge Selection
sbit  IED1L   = IEDS^2        ; //
sbit  IED0H   = IEDS^1        ; //       INT0 Edge Selection
sbit  IED0L   = IEDS^0        ; //

sfr   SEG0    = 0x0460        ; // [R/W] LCD Display Memory
sfr   SEG1    = 0x0461        ; //       
sfr   SEG2    = 0x0462        ; //       
sfr   SEG3    = 0x0463        ; //       
sfr   SEG4    = 0x0464        ; //       
sfr   SEG5    = 0x0465        ; //       
sfr   SEG6    = 0x0466        ; //       
sfr   SEG7    = 0x0467        ; //       

sfr   SEG8    = 0x0468        ; //       
sfr   SEG9    = 0x0469        ; //       
sfr   SEG10   = 0x046A        ; //       
sfr   SEG11   = 0x046B        ; //       
sfr   SEG12   = 0x046C        ; //       
sfr   SEG13   = 0x046D        ; //       
sfr   SEG14   = 0x046E        ; //       
sfr   SEG15   = 0x046F        ; //       

sfr   SEG16   = 0x0470        ; //       
sfr   SEG17   = 0x0471        ; //       
sfr   SEG18   = 0x0472        ; //       
sfr   SEG19   = 0x0473        ; //       
sfr   SEG20   = 0x0474        ; //       
sfr   SEG21   = 0x0475        ; //       
sfr   SEG22   = 0x0476        ; //       
sfr   SEG23   = 0x0477        ; //       

sfr   SEG24   = 0x0478        ; //       
sfr   SEG25   = 0x0479        ; //       
sfr   SEG26   = 0x047A        ; //       
sfr   SEG27   = 0x047B        ; //       
sfr   SEG28   = 0x047C        ; //       
sfr   SEG29   = 0x047D        ; //       
sfr   SEG30   = 0x047E        ; //       
sfr   SEG31   = 0x047F        ; //       

sfr   SEG32   = 0x0480        ; //       
sfr   SEG33   = 0x0481        ; //       
sfr   SEG34   = 0x0482        ; //       
sfr   SEG35   = 0x0483        ; // 36 seg x 8 com = 288 dot

sfr   SEG36   = 0x0484        ; //       
sfr   SEG37   = 0x0485        ; //       
sfr   SEG38   = 0x0486        ; //       
sfr   SEG39   = 0x0487        ; // 40 seg x 4 com = 160 dot 

#endif // _MC81F8816_H_
	
