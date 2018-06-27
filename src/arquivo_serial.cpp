//============================================================================
// Name        : arquivo_serial.cpp
// Author      : apenaz
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <iostream>
using namespace std;
// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
	char com[6], port[15],filename[15];
	printf("Digite a porta serial que deseja salvar conteudo:\n");
	scanf("%s", com);
	sprintf(port, "\\\\.\\%s", com);
	sprintf(filename, "%s.dat", com);



	FILE *file;
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial(port);    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected\n\n");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	int dataLength = 255;
	int readResult = 0;

	// TESTES DE ABERTURA DO ARQUIVO
	file = fopen(filename, "a");
	if (file == NULL) {
	       printf ("Houve um erro ao abrir o arquivo.\n\n");
	       system("PAUSE");
	       return 1;
	}
	fclose(file);

	//COMUNICAÇÃO
	while(SP->IsConnected())
	{
		file = fopen(filename, "a");
		readResult = SP->ReadData(incomingData,dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
            incomingData[readResult] = 0;
            printf("%s",incomingData);
            fprintf(file, "%s", incomingData);
            fclose(file);
	}

	system("PAUSE");
	return 0;
}
