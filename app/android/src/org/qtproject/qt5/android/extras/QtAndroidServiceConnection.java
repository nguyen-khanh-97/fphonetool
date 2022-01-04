//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package org.qtproject.qt5.android.extras;

import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.IBinder;

public class QtAndroidServiceConnection implements ServiceConnection {
    private long m_id;

    public QtAndroidServiceConnection(long var1) {
        this.m_id = var1;
    }

    public void setId(long var1) {
        synchronized(this) {
            this.m_id = var1;
        }
    }

    public void onServiceConnected(ComponentName var1, IBinder var2) {
        synchronized(this) {
            QtNative.onServiceConnected(this.m_id, var1.flattenToString(), var2);
        }
    }

    public void onServiceDisconnected(ComponentName var1) {
        synchronized(this) {
            QtNative.onServiceDisconnected(this.m_id, var1.flattenToString());
        }
    }
}
