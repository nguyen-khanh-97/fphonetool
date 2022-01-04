//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package org.qtproject.qt5.android.extras;

import android.os.Binder;
import android.os.Parcel;

public class QtAndroidBinder extends Binder {
    private long m_id;

    public QtAndroidBinder(long var1) {
        this.m_id = var1;
    }

    public void setId(long var1) {
        synchronized(this) {
            this.m_id = var1;
        }
    }

    protected boolean onTransact(int var1, Parcel var2, Parcel var3, int var4) {
        synchronized(this) {
            return QtNative.onTransact(this.m_id, var1, var2, var3, var4);
        }
    }
}
