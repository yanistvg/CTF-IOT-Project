package brutforceDoor;

import javacard.framework.APDU;
import javacard.framework.Applet;
import javacard.framework.ISO7816;
import javacard.framework.ISOException;

public class BrutforceDoor extends Applet {
	
	private final static byte code_lock_id[] = {(byte)0x01, (byte)0x02, (byte)0x03, (byte)0x04};
	private final static byte code_reste_id[] = {(byte)0x04, (byte)0x03, (byte)0x02, (byte)0x01};
	
	private final static byte ID_CARD_CLA =(byte)0x80;
	
	private static final byte VALIDATE_PIN_INS = 0x22;
	private static final byte GET_ID_INS       = 0x23;

	private final static short SW_OK_PASSE_TOUT_VA_BIEN = (short)0x9000;
	
	byte[] id = {0x00}; // id de la carte qui serat donné au reader et changé par itération
	boolean lockId = false;

	private BrutforceDoor() {
	}

	public static void install(byte bArray[], short bOffset, byte bLength) throws ISOException {
		new BrutforceDoor().register();
	}

	public void process(APDU apdu) throws ISOException {
		byte[] buffer = apdu.getBuffer();
		
		if(this.selectingApplet()) return;

		if (buffer[ISO7816.OFFSET_CLA] != ID_CARD_CLA) // quitter si mauvais CLA
			ISOException.throwIt(ISO7816.SW_CLA_NOT_SUPPORTED);
		
		switch(buffer[ISO7816.OFFSET_INS]){
			case VALIDATE_PIN_INS:
				validatePin(apdu); break;
			case GET_ID_INS:
				getId(apdu); break;
			default: ISOException.throwIt(ISO7816.SW_INS_NOT_SUPPORTED);
		}
	}
	
	public void validatePin(APDU apdu) {
		byte[] buffer = apdu.getBuffer();
		byte[] code = {0x00, 0x00, 0x00, 0x00};
		short i;
		
		for (i=0; i < 4; i++)
			code[(short)i] = (byte)buffer[(short)((short)ISO7816.OFFSET_CDATA + (short)i)];
		
		if ((byte)code[0] == (byte)code_lock_id[0] &&
			(byte)code[1] == (byte)code_lock_id[1] &&
			(byte)code[2] == (byte)code_lock_id[2] &&
			(byte)code[3] == (byte)code_lock_id[3])
			lockId = true;
		
		if ((byte)code[0] == (byte)code_reste_id[0] &&
			(byte)code[1] == (byte)code_reste_id[1] &&
			(byte)code[2] == (byte)code_reste_id[2] &&
			(byte)code[3] == (byte)code_reste_id[3]) {
				lockId = false;
				id[0] = (byte)0x00;
		}
		
		ISOException.throwIt(SW_OK_PASSE_TOUT_VA_BIEN);
	}
	
	public void getId(APDU apdu) {
		if (!lockId)
			id[0] = (byte)((byte)id[0] + (byte)1);
		
		apdu.setOutgoing();
		apdu.setOutgoingLength((short) 1);
		apdu.sendBytesLong((byte[]) id, (short) 0, (short) 1);
	}

}
