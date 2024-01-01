package com.ghinhara.ryuuka;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.content.res.AssetManager;
import android.util.Base64;
import androidx.multidex.MultiDexApplication;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.lang.ref.WeakReference;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.Map;

public class ApkKiller extends MultiDexApplication implements InvocationHandler {
	
	private static String c = "";

    private static Signature[] d;
	
    private Object a;

    private File b = null;
	
	
	public void attachBaseContext(Context context) {
		
		try {
			DataInputStream dataInputStream = new DataInputStream(new ByteArrayInputStream(Base64.decode("AQAABYowggWGMIIDbqADAgECAhQyqrtXJgd9m5QfO9cdtEMvIb5/8TANBgkqhkiG9w0BAQsFADB0MQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNTW91bnRhaW4gVmlldzEUMBIGA1UEChMLR29vZ2xlIEluYy4xEDAOBgNVBAsTB0FuZHJvaWQxEDAOBgNVBAMTB0FuZHJvaWQwHhcNMTkxMTA4MDUxNTQ3WhcNNDkxMTA4MDUxNTQ3WjB0MQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNTW91bnRhaW4gVmlldzEUMBIGA1UEChMLR29vZ2xlIEluYy4xEDAOBgNVBAsTB0FuZHJvaWQxEDAOBgNVBAMTB0FuZHJvaWQwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCf9krbyyJcWqKhvClSV7Ak3P30zUFudg62RdU+NdMyMbETbzMVn/ZsMfL/XBg46V7cULI4IvjcwRSVqTVWDb8AqajDFU8aXqLLrn9DedtuExiJsD8lkZN0lMsHwLfjf/NJscW8jBxpN0CtIcWSHg25ZofxyKlRoMoLbHtzDOnH6htUzPgnW6GWknOccQasuKQs3j+CT8bXDIvREKPKuRDDS03hfkddmdp9tBX6rBrbNNw2FOz5/NKAnsw+sm4lKg73XL/Alo7/PdPMVDc1VKd496JMmzggDzukTHfJGzH5WMPQa1JNZ1dTpVytjx0mD5SP0nqzBg/IVLAeEgP3gJror3zAACaFvUYKbqgEQ7YVOq8mOmezYDobiyhsiLCCySejiARPE7accbfjfFg4sr9EKIKnY0dJbVuhliEN1oWYSPXCj82aqcu5vD5S0vexMmOsSKsxuUWXWitNKmlQU+plOd8qoX/KBpktchEZvnQxExvQBwzyCKLGageE6WFuqwSB61mdMPVH10TA7C9gL2Y2IPZBqW15I4m4quPi0YwYfK1NKdrf663ARlLY0WBJ8xtkQBt27btwru/pjVYzCJlcFqnNOGwUNfDom0ba4k5JX6d/BFpVOQHrkrKAwPrUyCko+GrBoXxxeCj3sgDMnUbHVGvlytvBdTzDtDiJnlFViQIDAQABoxAwDjAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBCwUAA4ICAQBhPCT3s3RU7bPlDnO3RzZViv4Uw0vTKiPesdbxonbf6ABcnK1C6JjiOZtGSuCSqdosnxhGmXwN4h74Eaeg2AqV0AU9l7jVZwmwJ3IwsdDL9MaUupSJxYjheGghqaf7HXPIMgAwkfOEhuRI0Oqj71aNOKZSPDl87a0vDZ8Qn3Du2TvsL9t/UWz8s5n3rtttwb+rqh8wWTinWzRxgWxr6dXjKaGn/OuZvDCrJp1t1LD+2/A/mpoWqS4Rl82vKMe4ePpxF3mgHD7CbiBK5eWSAgZEWDNXEvKgqh7nntWQR67/RUqCAffTHf3/zLBN53n1X1bT24JpI4dAxyJoHsrUV2pm/xLxGWBMyBuptXTE2v92fa1CHvVsDVFkYJ8lh6VUr0F4J5q5oU6K8m1vBBOW5E5k5Xu4L8EkJEmDg+KGuG8E3vm/eKULUb8wdewivrr0ty0BWlJTfTplJpfajqoT76OXDmyXwQKx0t3pmIUBtlfgkztLdpceJ8ZuInVdWfm+mwNe//zwKu8XhkpDPWkJuCraRrkYTlnTpahVg10dUya1dwPVtJZam7Rdj6jXnkazZvyxSISSiHpV/o1mLcHWp7gL/nqNjZ2nsXRNWYOTrFodSMrjwXL2Aw61SOK5JeB5xX+a9JTik6aWJ2IoEIqXYfjsJLW5AunQUF2OTItcMBoWvg==", 0)));
			int read = dataInputStream.read() & 255;
			byte[][] bArr = new byte[read][];
			for (int i = 0; i < read; i++) {
                bArr[i] = new byte[dataInputStream.readInt()];
                dataInputStream.readFully(bArr[i]);
            }
			
            if (d == null) {
                d = new Signature[read];
                int i2 = 0;
                while (true) {
                    Signature[] signatureArr = d;
                    if (i2 >= signatureArr.length) {
                        break;
                    }
                    signatureArr[i2] = new Signature(bArr[i2]);
                    i2++;
                }
            }
            Class<?> cls = Class.forName("android.app.ActivityThread");
            Object invoke = cls.getDeclaredMethod("currentActivityThread", new Class[0]).invoke((Object) null, new Object[0]);
            Field declaredField = cls.getDeclaredField("sPackageManager");
            declaredField.setAccessible(true);
            Object obj = declaredField.get(invoke);
            Class<?> cls2 = Class.forName("android.content.pm.IPackageManager");
            this.a = obj;
            c = context.getPackageName();
            Object newProxyInstance = Proxy.newProxyInstance(cls2.getClassLoader(), new Class[]{cls2}, this);
            declaredField.set(invoke, newProxyInstance);
            PackageManager packageManager = context.getPackageManager();
            Field declaredField2 = packageManager.getClass().getDeclaredField("mPM");
            declaredField2.setAccessible(true);
            declaredField2.set(packageManager, newProxyInstance);
        } catch (Throwable th) {
            th.printStackTrace();
        }
        try {
            String name = new File(context.getApplicationInfo().sourceDir).getName();
            File file = (File) context.getClass().getMethod("getFileStreamPath", new Class[]{String.class}).invoke(context, new Object[]{name});
            this.b = file;
            if (!file.exists()) {
                AssetManager assetManager = (AssetManager) context.getClass().getMethod("getAssets", (Class[]) null).invoke(context, (Object[]) null);
                InputStream inputStream = (InputStream) assetManager.getClass().getMethod("open", new Class[]{String.class}).invoke(assetManager, new Object[]{"sjhks"});
                FileOutputStream fileOutputStream = new FileOutputStream(this.b);
                byte[] bArr2 = new byte[1024];
                for (int i3 = 0; i3 != -1; i3 = inputStream.read(bArr2)) {
                    fileOutputStream.write(bArr2, 0, i3);
                    fileOutputStream.flush();
                }
                inputStream.close();
                fileOutputStream.close();
            }
            File file2 = this.b;
            if (file2 != null && file2.exists()) {
                String path = this.b.getPath();
                Field declaredField3 = ClassLoader.getSystemClassLoader().loadClass("android.app.ActivityThread").getDeclaredField("sCurrentActivityThread");
                declaredField3.setAccessible(true);
                Object obj2 = declaredField3.get((Object) null);
                Field declaredField4 = obj2.getClass().getDeclaredField("mPackages");
                declaredField4.setAccessible(true);
                Object obj3 = ((WeakReference) ((Map) declaredField4.get(obj2)).get(context.getPackageName())).get();
                
				Field declaredField5 = obj3.getClass().getDeclaredField("mAppDir");
                declaredField5.setAccessible(true);
                declaredField5.set(obj3, path);
                
				Field declaredField6 = obj3.getClass().getDeclaredField("mApplicationInfo");
                declaredField6.setAccessible(true);
                
				ApplicationInfo applicationInfo = (ApplicationInfo) declaredField6.get(obj3);
                applicationInfo.publicSourceDir = path;
                applicationInfo.sourceDir = path;
            }
        } catch (Throwable th2) {
            th2.printStackTrace();
        }
		super.attachBaseContext(context);
    }
	
	public Object invoke(Object obj, Method method, Object[] objArr) throws Throwable {
        if (method != null && "getPackageInfo".equals(method.getName())) {
           // String str = objArr[0];
            if (/*(objArr[1].intValue() & 64) != 0 && */c.equals(objArr[0])) {
                PackageInfo packageInfo = (PackageInfo) method.invoke(this.a, objArr);
                Signature[] signatureArr = d;
                Signature[] signatureArr2 = new Signature[signatureArr.length];
                packageInfo.signatures = signatureArr2;
                System.arraycopy(signatureArr, 0, signatureArr2, 0, signatureArr.length);
                return packageInfo;
            }
        }
        if (method == null || !"getApplicationInfo".equals(method.getName()) || !c.equals(objArr[0])) {
            return new String(new byte[]{103, 101, 116, 73, 110, 115, 116, 97, 108, 108, 101, 114, 80, 97, 99, 107, 97, 103, 101, 78, 97, 109, 101}).equals(method.getName()) ? "com.android.vending" : method.invoke(this.a, objArr);
        }
		
        ApplicationInfo applicationInfo = (ApplicationInfo) method.invoke(this.a, objArr);
        applicationInfo.sourceDir = this.b.getPath();
        applicationInfo.publicSourceDir = this.b.getPath();
        return applicationInfo;
    }
}
