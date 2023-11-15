#ifdef WIN32
	#undef UNICODE
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
	#include <PCSC/winscard.h>
	#include <PCSC/wintypes.h>
#else
	#include <winscard.h>
#endif

#ifdef WIN32
	static char *pcsc_stringify_error(LONG rv) {
		static char out[20];
		sprintf_s(out, sizeof(out), "0x%08X", rv);

		return out;
	}
#endif

#define CHECK(f, rv) \
	if (SCARD_S_SUCCESS != rv) \
	{ \
		printf(f ": %s\n", pcsc_stringify_error(rv)); \
		return -1; \
	}

int main(void)
{
	LONG rv;

	SCARDCONTEXT hContext;
	LPTSTR mszReaders;
	SCARDHANDLE hCard;
	DWORD dwReaders, dwActiveProtocol, dwRecvLength;

	SCARD_IO_REQUEST pioSendPci;
	BYTE pbRecvBuffer[258];

	BYTE APDU_select_applet[] = {0x00, 0xA4, 0x04, 0x00, 0x0b, 0x01, 0x02,
	                           0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
	                           0x00, 0x01, 0x7F};

	BYTE APDU_verify_pin[10] = {0x80, 0x22, 0x00, 0x00, 0x04, 0x01, 0x05, 0x08, 0x03, 0x7F};
	//                          CLA   INS   P1    P2    LC    --------- PIN --------  LE

	BYTE APDU_get_id[] = {0x80, 0x23, 0x00, 0x00, 0x7F};
	//                    CLA   INS   P1    P2    LE

	unsigned int i;

	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
	CHECK("SCardEstablishContext", rv)

	#ifdef SCARD_AUTOALLOCATE
		dwReaders = SCARD_AUTOALLOCATE;

		rv = SCardListReaders(hContext, NULL, (LPTSTR)&mszReaders, &dwReaders);
		CHECK("SCardListReaders", rv)
	#else
		rv = SCardListReaders(hContext, NULL, NULL, &dwReaders);
		CHECK("SCardListReaders", rv)

		mszReaders = calloc(dwReaders, sizeof(char));
		rv = SCardListReaders(hContext, NULL, mszReaders, &dwReaders);
		CHECK("SCardListReaders", rv)
	#endif
	
	printf("reader name: %s\n", mszReaders);

	rv = SCardConnect(hContext, mszReaders, SCARD_SHARE_SHARED, 
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
	CHECK("SCardConnect", rv)

	switch(dwActiveProtocol) {
		case SCARD_PROTOCOL_T0:
			pioSendPci = *SCARD_PCI_T0; break;
		case SCARD_PROTOCOL_T1:
			pioSendPci = *SCARD_PCI_T1; break;
	}
	
	dwRecvLength = sizeof(pbRecvBuffer);
	rv = SCardTransmit(hCard, &pioSendPci, APDU_select_applet, sizeof(APDU_select_applet),
		NULL, pbRecvBuffer, &dwRecvLength);
	CHECK("SCardTransmit", rv)

	printf("response de la selection de l'applet: ");
	for(i=0; i < dwRecvLength; i++)
		printf("%02X ", pbRecvBuffer[i]);
	printf("\n");

	dwRecvLength = sizeof(pbRecvBuffer);
	rv = SCardTransmit(hCard, &pioSendPci, APDU_verify_pin, sizeof(APDU_verify_pin),
		NULL, pbRecvBuffer, &dwRecvLength);
	CHECK("SCardTransmit", rv)

	printf("response de la verifiaction du pin: ");
	for(i=0; i<dwRecvLength; i++)
		printf("%02X ", pbRecvBuffer[i]);
	printf("\n");

	dwRecvLength = sizeof(pbRecvBuffer);
	rv = SCardTransmit(hCard, &pioSendPci, APDU_get_id, sizeof(APDU_get_id),
		NULL, pbRecvBuffer, &dwRecvLength);
	CHECK("SCardTransmit", rv)

	printf("response de la recuperation de l'id: ");
	for(i=0; i < dwRecvLength; i++)
		printf("%02X ", pbRecvBuffer[i]);
	printf("\n");

	rv = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
	CHECK("SCardDisconnect", rv)

	#ifdef SCARD_AUTOALLOCATE
		rv = SCardFreeMemory(hContext, mszReaders);
		CHECK("SCardFreeMemory", rv)
	#else
		free(mszReaders);
	#endif

	rv = SCardReleaseContext(hContext);

	CHECK("SCardReleaseContext", rv)

	return 0;
}