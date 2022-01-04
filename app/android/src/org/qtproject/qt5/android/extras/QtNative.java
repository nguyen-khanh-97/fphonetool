//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package org.qtproject.qt5.android.extras;

import android.os.IBinder;
import android.os.Parcel;

public class QtNative {
    public QtNative() {
    }

    public static native boolean onTransact(long var0, int var2, Parcel var3, Parcel var4, int var5);

    public static native void onServiceConnected(long var0, String var2, IBinder var3);

    public static native void onServiceDisconnected(long var0, String var2);
}
