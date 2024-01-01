package com.ghinhara.ryuuka;

import android.os.Parcel;
import java.security.Signature;

public class FakeSign {
	static native long Hash_1();
	static native long Hash_2();
	
	public static String a = "";
	public static boolean b;
	
	public static void s(Parcel parcel) {
		int readInt = parcel.readInt();
		String readString = parcel.readString();
		int dataPosition = parcel.dataPosition();
		
		if (readInt == 1) {
			parcel.setDataPosition(dataPosition);
			parcel.writeInt(0);
            if (readString != null) {
				long currentTimeMillis = System.currentTimeMillis();
				String[] split = readString.split(new String(new byte[]{(byte) 92, (byte) 124}));
				split[0] = new String(new byte[]{(byte) 48});
                
				StringBuilder stringBuilder = new StringBuilder();
                long j = Hash_1() + currentTimeMillis;
                stringBuilder.append(j);
                stringBuilder.append(new String(new byte[]{(byte) 58, (byte) 71, (byte) 82, (byte) 61, (byte) 49, (byte) 48, (byte) 38, (byte) 86, (byte) 84, (byte) 61}));
                stringBuilder.append(j + 1);
                stringBuilder.append(new String(new byte[]{(byte) 38, (byte) 71, (byte) 84, (byte) 61}));
				stringBuilder.append(currentTimeMillis + Hash_2());
                split[5] = stringBuilder.toString();
                String str = "";
				
				for (int i = 0; i < split.length; i++) {
					if (i < split.length - 1) {
                        stringBuilder.append(str);
                        stringBuilder.append(split[i]);
                        stringBuilder.append(new String(new byte[]{(byte) 124}));
                        str = stringBuilder.toString();
                    } else {
                        stringBuilder = new StringBuilder();
                        stringBuilder.append(str);
                        stringBuilder.append(split[i]);
                        str = stringBuilder.toString();
                    }
                }
                readString = str;
            }
            a = readString;
            parcel.writeString(readString);
            parcel.setDataPosition(dataPosition);
            return;
        }
        parcel.setDataPosition(dataPosition);
    }
	
	public static void enforceInterface(Parcel parcel, String str) {
		if (str.equals(new String(new byte[]{(byte) 99, (byte) 111, (byte) 109, (byte) 46, (byte) 97, (byte) 110, (byte) 100, (byte) 114, (byte) 111, (byte) 105, (byte) 100, (byte) 46, (byte) 118, (byte) 101, (byte) 110, (byte) 100, (byte) 105, (byte) 110, (byte) 103, (byte) 46, (byte) 108, (byte) 105, (byte) 99, (byte) 101, (byte) 110, (byte) 115, (byte) 105, (byte) 110, (byte) 103, (byte) 46, (byte) 73, (byte) 76, (byte) 105, (byte) 99, (byte) 101, (byte) 110, (byte) 115, (byte) 101, (byte) 82, (byte) 101, (byte) 115, (byte) 117, (byte) 108, (byte) 116, (byte) 76, (byte) 105, (byte) 115, (byte) 116, (byte) 101, (byte) 110, (byte) 101, (byte) 114}))) {
			try {
				parcel.getClass().getMethod(new String(new byte[]{(byte) 101, (byte) 110, (byte) 102, (byte) 111, (byte) 114, (byte) 99, (byte) 101, (byte) 73, (byte) 110, (byte) 116, (byte) 101, (byte) 114, (byte) 102, (byte) 97, (byte) 99, (byte) 101}), new Class[]{String.class}).invoke(parcel, new Object[]{0});
			} catch (Throwable th) {
				th.printStackTrace();
			}
			s(parcel);
			return;
		} try {
			parcel.getClass().getMethod(new String(new byte[]{(byte) 101, (byte) 110, (byte) 102, (byte) 111, (byte) 114, (byte) 99, (byte) 101, (byte) 73, (byte) 110, (byte) 116, (byte) 101, (byte) 114, (byte) 102, (byte) 97, (byte) 99, (byte) 101}), new Class[]{String.class}).invoke(parcel, new Object[]{0});
		} catch (Throwable th2) {
			th2.printStackTrace();
		}
		
	}

    public static void update(Signature signature, byte[] bArr) throws Throwable {
        if (a.equals("") || !new String(bArr).equals(a)) {
            b = false;
        } else {
            b = true;
        }
        signature.getClass().getMethod(new String(new byte[]{(byte) 117, (byte) 112, (byte) 100, (byte) 97, (byte) 116, (byte) 101}), new Class[]{byte[].class}).invoke(signature, new Object[]{bArr});
    }

    public static boolean verify(Signature signature, byte[] bArr) throws Throwable {
        if (b) {
            return true;
        }
        return ((Boolean) signature.getClass().getMethod(new String(new byte[]{(byte) 118, (byte) 101, (byte) 114, (byte) 105, (byte) 102, (byte) 121}), new Class[]{byte[].class}).invoke(signature, new Object[]{bArr})).booleanValue();
    }
}
