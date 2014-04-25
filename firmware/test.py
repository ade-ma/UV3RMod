import glob, serial, time

s = serial.Serial(glob.glob("/dev/ttyUSB*")[0], 9600)

def poke (addr, value):
	s.write("\xAA\x55S"+chr(addr)+chr(value>>8)+chr(value&0xff)+"\r\n")
	(map(lambda x:hex(ord(x)),"\xAA\x55S"+chr(addr)+chr(value>>8)+chr(value&0xff)+"\r\n"))
	print s.readline()+s.readline()+s.readline()+s.readline()

def setf (freq):
	x = int(freq*8000)
	poke(0x29, x>>16)
	poke(0x2a, x&0xffff)


#setf(145.525)

init = [
 ( 0x30, 0x0001 ),
 ( 0x30, 0x0004 ),
 ( 0x04, 0x0FD0 ),
 ( 0x0B, 0x1A10 ),
 ( 0x2B, 0x32C8 ),
 ( 0x2C, 0x1964 ),
 ( 0x32, 0x627C ),
 ( 0x33, 0x0AF2 ),
 ( 0x47, 0x2C2F ),
 ( 0x4E, 0x293A ),
 ( 0x54, 0x1D4C ),
 ( 0x56, 0x0652 ),
 ( 0x6E, 0x062D ),
 ( 0x70, 0x1029 ),
 ( 0x7F, 0x0001 ),
 ( 0x05, 0x001F ),
 ( 0x7F, 0x0000 ),
 ( 0x30, 0x3006 ),
 ( 0x0A, 0x0400 ), #PA Bias 0000 0100 '00 00' 0000
 ( 0x1F, 0x0000 ), #GPIO selection 0001 1110 1011 1001
 ( 0x30, 0x3006 ),
 ( 0x0F, 0x6be4 ),
 ( 0x29, 0x0011 ), #145.550
 ( 0x2A, 0xC470 ), #145.550
 ( 0x48, 0x03FF ), #0000 0011 1111 0000
 ( 0x49, 0x01b3 ), #0003
 ( 0x3C, 0x0958 ), #0000 1001 0101 1000
 ( 0x43, 0x1F1F ),
 ( 0x30, 0x3006 ),
 ( 0x36, 0x1000 )
]

#[poke(x,y) for (x,y) in init]
setf(145.550)
[poke(x,y) for (x,y) in [(0x3c, 0x958), (0x1f, 0xc000), (0x30, 0x3046)]]

poke(0x0a, 0x0410)

raw_input()

[poke(x,y) for (x,y) in [(0x1f, 0x0), (0x30, 0x302E)]]
