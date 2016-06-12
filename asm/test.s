.text
add r1, r2, r3
rsub r1, r2, r3
addc r1, r2, r3
rsubc r1, r2, r3
addk r1, r2, r3
rsubk r1, r2, r3
cmp r1, r2, r3
cmpu r1, r2, r3
addkc r1, r2, r3
rsubkc r1, r2, r3
addi r1, r2, 0x1234
rsubi r1, r2, 0x1234
addic r1, r2, 0x1234
rsubic r1, r2, 0x1234
addik r1, r2, 0x1234
rsubik r1, r2, 0x1234
addikc r1, r2, 0x1234
rsubikc r1, r2, 0x1234
mul r1, r2, r3
mulh r1, r2, r3
mulhu r1, r2, r3
mulhsu r1, r2, r3
bsra r1, r2, r3
bsll r1, r2, r3
idiv r1, r2, r3
idivu r1, r2, r3
tneagetd r1, r2
tnaputd r1
tnecagetd r1, r2
tncaputd r1
fadd r1, r2, r3
frsub r1, r2, r3
fmul r1, r2, r3
fdiv r1, r2, r3
fcmp.un r1, r2, r3
fcmp.lt r1, r2, r3
fcmp.eq r1, r2, r3
fcmp.le r1, r2, r3
fcmp.gt r1, r2, r3
fcmp.ne r1, r2, r3
fcmp.ge r1, r2, r3
flt r1, r2
fint r1, r2
fsqrt r1, r2
muli r1, r2, 0x1234
bsrli r1, r2, 0x1f
bsrai r1, r2, 0x1f
bslli r1, r2, 0x1f
tneaget r1, rfsl2
tnaput r1
tnecaget r1, rfsl2
tncaput r1
or r1, r2, r3
pcmpbf r1, r2, r3
and r1, r2, r3
xor r1, r2, r3
pcmpeq r1, r2, r3
andn r1, r2, r3
pcmpne r1, r2, r3
sra r1, r2
src r1, r2
srl r1, r2
sext8 r1, r2
sext16 r1, r2
wic r1, r2
wdc r1, r2
mts rmsr, r1
mfs r1, rmsr
msrclr r1, 0x1234
msrset r1, 0x1234
br r1
brd r1
brld r1, r2
bra r1
brad r1
brald r1, r2
brk r1, r2
beq r1, r2
bne r1, r2
blt r1, r2
ble r1, r2
bgt r1, r2
bge r1, r2
beqd r1, r2
bned r1, r2
bltd r1, r2
bled r1, r2
bgtd r1, r2
bged r1, r2
ori r1, r2, 0x1234
andi r1, r2, 0x1234
xori r1, r2, 0x1234
andni r1, r2, 0x1234
ori r1, r2, 0x12345678
rtsd r1, 0x1234
rtid r1, 0x1234
rtbd r1, 0x1234
rted r1, 0x1234
bri 0x0000
brid 0x0000
brlid r1, 0x0000
brai 0x1234
braid 0x1234
bralid r1, 0x1234
brki r1, 0x1234
beqi r1, 0x0000
bnei r1, 0x0000
blti r1, 0x0000
blei r1, 0x0000
bgti r1, 0x0000
bgei r1, 0x0000
beqid r1, 0x0000
bneid r1, 0x0000
bltid r1, 0x0000
bleid r1, 0x0000
bgtid r1, 0x0000
bgeid r1, 0x0000
lbu r1, r2, r3
lhu r1, r2, r3
lw r1, r2, r3
sb r1, r2, r3
sh r1, r2, r3
sw r1, r2, r3
lbui r1, r2, 0x1234
lhui r1, r2, 0x1234
lwi r1, r2, 0x1234
sbi r1, r2, 0x1234
shi r1, r2, 0x1234
swi r1, r2, 0x1234
