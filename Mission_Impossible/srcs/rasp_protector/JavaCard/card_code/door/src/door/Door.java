package door;

import javacard.framework.*;

import javacard.framework.APDU;
import javacard.framework.Applet;
import javacard.framework.ISOException;

public class Door extends Applet {
	
	private final static byte ID_CARD_CLA =(byte)0x80;
	
	private static final byte VALIDATE_PIN_INS = 0x22;
	private static final byte GET_ID_INS       = 0x23;
	
	final static byte PIN_TRY_LIMIT = (byte) 0x03;
	final static byte MAX_PIN_SIZE = (byte) 0x08;
	private final static byte PIN_SIZE =(byte)0x04;
	
	private final static short SW_VERIFICATION_FAILED = 0x6300;
	private final static short SW_PIN_VERIFICATION_REQUIRED = 0x6301;
	
	OwnerPIN pin;
	byte[] id = {0x24}; // id de la carte qui serat donné au reader

	private Door() {
		// initialisation du code pin de la carte
		pin = new OwnerPIN(PIN_TRY_LIMIT, MAX_PIN_SIZE);
		pin.update(new byte[]{0x01,0x05,0x08,0x03},(short) 0, PIN_SIZE);
		register();
	}

	public static void install(byte bArray[], short bOffset, byte bLength) throws ISOException {
		new Door().register();
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
		if(buffer[ISO7816.OFFSET_LC]==PIN_SIZE){
			apdu.setIncomingAndReceive();
			if(pin.check(buffer, ISO7816.OFFSET_CDATA,PIN_SIZE)==false)
				ISOException.throwIt(SW_VERIFICATION_FAILED);
		}else ISOException.throwIt(ISO7816.SW_WRONG_LENGTH);
	}
	
	public void getId(APDU apdu) {
		if(!pin.isValidated()) ISOException.throwIt(SW_PIN_VERIFICATION_REQUIRED);

		apdu.setOutgoing();
		apdu.setOutgoingLength((short) 1);
		apdu.sendBytesLong((byte[]) id, (short) 0, (short) 1);
	}

}
