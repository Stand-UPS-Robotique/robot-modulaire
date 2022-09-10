package fr.standups.robotmodulaire.com;

import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import java.io.IOException;
import java.io.OutputStream;


public class BluetoothCommunication {
    private static BluetoothCommunication INSTANCE;

    private final BluetoothSocket mmSocket;
    private final OutputStream mmOutStream;
    private final Handler mHandler;

    private BluetoothCommunication(BluetoothSocket socket, Handler handler) {
        mmSocket = socket;
        mHandler = handler;
        OutputStream tmpOut = null;

        // Get the input and output streams, using temp objects because
        // member streams are final
        try {
            tmpOut = socket.getOutputStream();
        } catch (IOException e) { }

        mmOutStream = tmpOut;
    }

    public static BluetoothCommunication getInstance(BluetoothSocket socket, Handler handler) {
        if(INSTANCE == null) {
            INSTANCE = new BluetoothCommunication(socket, handler);
        }
        return INSTANCE;
    }

    /* Call this from the main activity to send data to the remote device */
    public void write(String input) {
        byte[] bytes = input.getBytes();           //converts entered String into bytes
        try {
            mmOutStream.write(bytes);
        } catch (IOException e) { }
    }

    /* Call this from the main activity to shutdown the connection */
    public void cancel() {
        try {
            mmSocket.close();
        } catch (IOException e) { }
    }
}