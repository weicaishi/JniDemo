package jniDemo;

public class JniDll {
	//jobject type convert
	public native void init();
	public native void put(byte[] buf, int size);
	public native byte[] get();
	public native void callback(byte[] buf, int size);
	
	static{
        System.loadLibrary("JniDll");
    }
	
	public static void main(String[] args) {
    	String sPath=System.getProperty("java.library.path");
    	System.out.println(sPath);
    	
    	JniDll jd1=new JniDll();
    	jd1.init();
    	
    	String sBuf="welcome jni.....";
    	jd1.put(sBuf.getBytes(), sBuf.getBytes().length);
    	
    	byte[] btBuf=jd1.get();
    	sBuf= new String(btBuf);
    	
    	jd1.callback(sBuf.getBytes(), sBuf.getBytes().length);
    	System.out.println("get() :"+sBuf);
	}

	public void callbackProc(byte[] buf, int size) {
		String sBuf= new String(buf);
    	System.out.println("callbackProc:\t"+sBuf);
	}
	
}
