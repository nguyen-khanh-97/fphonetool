package org.qtproject.fphonetool.service;

import android.util.DisplayMetrics;
import android.util.Size;
import android.view.WindowManager;
import android.accessibilityservice.AccessibilityService;
import android.view.accessibility.AccessibilityEvent;
import android.view.accessibility.AccessibilityNodeInfo;
import android.view.accessibility.AccessibilityWindowInfo;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import java.util.List;
import android.provider.Settings;
import android.content.res.Configuration;
import android.os.IBinder;
import org.qtproject.qt5.android.bindings.QtApplication;
import org.qtproject.qt5.android.bindings.QtServiceLoader;
import org.qtproject.qt5.android.bindings.QtService;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import android.content.pm.PackageManager;
import androidx.core.content.FileProvider;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.widget.Toast;
import android.os.Handler;
import android.os.Looper;
import android.widget.TextView;
import android.graphics.Color;
import android.view.Gravity;
import android.graphics.drawable.Drawable;
import android.content.res.Resources;
import org.qtproject.fphonetool.R;

public class QAccessibilityService extends AccessibilityService{

    private final static String TAG = "QAccessibilityService";
    QtServiceLoader m_loader = new QtServiceLoader(this, QAccessibilityService.class);
    private static Context context;
    private static Handler handler = new Handler(Looper.getMainLooper());
    private static TextView toastView;
    private static Toast toast;

    protected void onCreateHook() {
        m_loader.onCreate();
    }

    @Override
    public void onCreate() {
        context = this;
        Log.d(TAG, " ----- Created  QAccessibilityService ----");
        super.onCreate();
        onCreateHook();
    }

    @Override
    protected void onServiceConnected() {
        Log.d(TAG, " ---- ServiceConnected ----");
        startNative();

        Intent intent = getPackageManager().getLaunchIntentForPackage(getPackageName());
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK|Intent.FLAG_ACTIVITY_CLEAR_TASK|Intent.FLAG_ACTIVITY_CLEAR_TOP|Intent.FLAG_FROM_BACKGROUND);
        startActivity(intent);
    }

    @Override
    public void onInterrupt() {
        Log.d(TAG, "onInterrupt!");
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, " ----- Destroyed  QAccessibilityService ----");
        super.onDestroy();
        QtApplication.invokeDelegate();
    }

    @Override
    public void onAccessibilityEvent(AccessibilityEvent event) {
        onQAccessibilityEvent(event);
    }

    //---------------------------------------------------------------------------

    @Override
    public void onConfigurationChanged(Configuration newConfig){
        if (!QtApplication.invokeDelegate(newConfig).invoked)
            super.onConfigurationChanged(newConfig);
    }

    public void super_onConfigurationChanged(Configuration newConfig){
        super.onConfigurationChanged(newConfig);
    }
    //---------------------------------------------------------------------------

    @Override
    public void onLowMemory()
    {
        if (!QtApplication.invokeDelegate().invoked)
            super.onLowMemory();
    }
    //---------------------------------------------------------------------------

    @Override
    public int onStartCommand(Intent intent, int flags, int startId){
        QtApplication.InvokeResult res = QtApplication.invokeDelegate(intent, flags, startId);
        if (res.invoked)
            return (Integer) res.methodReturns;
        else
            return super.onStartCommand(intent, flags, startId);
    }

    public int super_onStartCommand(Intent intent, int flags, int startId){
        return super.onStartCommand(intent, flags, startId);
    }
    //---------------------------------------------------------------------------

    @Override
    public void onTaskRemoved(Intent rootIntent){
        if (!QtApplication.invokeDelegate(rootIntent).invoked)
            super.onTaskRemoved(rootIntent);
    }

    public void super_onTaskRemoved(Intent rootIntent){
        super.onTaskRemoved(rootIntent);
    }
    //---------------------------------------------------------------------------

    @Override
    public void onTrimMemory(int level){
        if (!QtApplication.invokeDelegate(level).invoked)
            super.onTrimMemory(level);
    }

    public void super_onTrimMemory(int level){
        super.onTrimMemory(level);
    }
    //---------------------------------------------------------------------------

    @Override
    public boolean onUnbind(Intent intent){
        QtApplication.InvokeResult res = QtApplication.invokeDelegate(intent);
        if (res.invoked)
            return (Boolean) res.methodReturns;
        else
            return super.onUnbind(intent);
    }

    public boolean super_onUnbind(Intent intent){
        return super.onUnbind(intent);
    }
    //---------------------------------------------------------------------------

    public Size getScreenSize() {
        WindowManager wmgr = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        DisplayMetrics metrics = new DisplayMetrics();
        wmgr.getDefaultDisplay().getRealMetrics(metrics);
        return new Size(metrics.widthPixels, metrics.heightPixels);
    }

    public static String readFile(String filePath){
        StringBuilder contentBuilder = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(filePath));
            String line;
            while ((line = reader.readLine()) != null){
                contentBuilder.append(line).append("\n");
            }
            reader.close();
            return contentBuilder.toString();
        } catch (Exception e) {
            Log.d("VDLogger",e.toString());
        }
        return null;
    }

    public static boolean isPackageInstalled(String packageName) {
        try {
            context.getPackageManager().getPackageInfo(packageName, 0);
            return true;
        } catch (PackageManager.NameNotFoundException e) {
            return false;
        }
    }

    public static void openUnknownApp(){
        context.startActivity(new Intent(Settings.ACTION_MANAGE_UNKNOWN_APP_SOURCES)
                                            .setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_FROM_BACKGROUND)
                                            .setData(Uri.parse(String.format("package:%s", context.getPackageName()))));
    }

    public static void openInstallAPK(String filePath){
        File fileLocal = new File(filePath);
        if(fileLocal.exists()){
            Uri apkUri = FileProvider.getUriForFile(context,context.getPackageName() + ".provider", fileLocal);
            Intent intent_update = new Intent(Intent.ACTION_VIEW);
            intent_update.setDataAndType(apkUri, "application/vnd.android.package-archive");
            intent_update.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS | Intent.FLAG_ACTIVITY_NO_HISTORY | Intent.FLAG_GRANT_READ_URI_PERMISSION);
            List<ResolveInfo> resInfoList = context.getPackageManager().queryIntentActivities(intent_update, PackageManager.MATCH_DEFAULT_ONLY);
            for (ResolveInfo resolveInfo : resInfoList) {
                String packageName = resolveInfo.activityInfo.packageName;
                context.grantUriPermission(packageName, apkUri, Intent.FLAG_GRANT_WRITE_URI_PERMISSION | Intent.FLAG_GRANT_READ_URI_PERMISSION);
            }
            context.startActivity(intent_update);
        }
    }

    public static void showToast(final String message){
        handler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (toastView == null) {
                            toastView = new TextView(context);
                            toastView.setHeight(150);
                            toastView.setWidth(Resources.getSystem().getDisplayMetrics().widthPixels - 200);
                            toastView.setBackgroundResource(R.drawable.ic_css_toast);
                            toastView.setTextColor(Color.WHITE);
                            toastView.setGravity(Gravity.CENTER);
                        }
                        toastView.setText(message);

                        if (toast != null){
                            toast.cancel();
                            toast = null;
                        }
                        toast = new Toast(context);
                        toast.setDuration(1500);
                        toast.setView(toastView);
                        toast.show();
                    }
                });
    }

    public native void onQAccessibilityEvent(AccessibilityEvent event);
    public native void startNative();
}
