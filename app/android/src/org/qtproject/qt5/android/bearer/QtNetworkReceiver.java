//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package org.qtproject.qt5.android.bearer;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;

public class QtNetworkReceiver {
    private static final String LOG_TAG = "QtNetworkReceiver";
    private static QtNetworkReceiver.BroadcastReceiverPrivate m_broadcastReceiver = null;
    private static final Object m_lock = new Object();

    private static native void activeNetworkInfoChanged();

    private QtNetworkReceiver() {
    }

    public static void registerReceiver(Context var0) {
        synchronized(m_lock) {
            if (m_broadcastReceiver == null) {
                m_broadcastReceiver = new QtNetworkReceiver.BroadcastReceiverPrivate();
                IntentFilter var2 = new IntentFilter("android.net.conn.CONNECTIVITY_CHANGE");
                var0.registerReceiver(m_broadcastReceiver, var2);
            }

        }
    }

    public static void unregisterReceiver(Context var0) {
        synchronized(m_lock) {
            if (m_broadcastReceiver != null) {
                var0.unregisterReceiver(m_broadcastReceiver);
            }
        }
    }

    public static ConnectivityManager getConnectivityManager(Context var0) {
        return (ConnectivityManager)var0.getSystemService("connectivity");
    }

    private static class BroadcastReceiverPrivate extends BroadcastReceiver {
        private BroadcastReceiverPrivate() {
        }

        public void onReceive(Context var1, Intent var2) {
            QtNetworkReceiver.activeNetworkInfoChanged();
        }
    }
}
