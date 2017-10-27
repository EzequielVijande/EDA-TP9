#pragma once

//Inicializa el FTDI y el LCD
FT_HANDLE * lcdInit(int iDevice);

//Escribe un byte al IR
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);

//Escribe un byte al DR
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);
