// https://github.com/controlwear/virtual-joystick-android

package fr.standups.robotmodulaire.activities;

import android.annotation.SuppressLint;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.Log;
import android.widget.SeekBar;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import fr.standups.robotmodulaire.R;
import fr.standups.robotmodulaire.com.BluetoothCommunication;
import io.github.controlwear.virtual.joystick.android.JoystickView;

public class ControlActivity extends AppCompatActivity {

    private SeekBar seekBar1, seekBar2;
    private int joyX, joyY, sliderX, sliderY;
    private JoystickView joystickView;
    private BluetoothCommunication bluetoothComInstance;

    @SuppressLint("SourceLockedOrientationActivity")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        setContentView(R.layout.activity_control);

        bluetoothComInstance = BluetoothCommunication.getInstance();

        seekBar1 = findViewById(R.id.seekBar1);
        seekBar1.setMax(255);

        seekBar2 = findViewById(R.id.seekBar2);
        seekBar2.setMax(255);

        joystickView = findViewById(R.id.joystick);
        joystickView.setOnMoveListener((angle, strength) -> {
            joyX = (int) (Math.cos(Math.PI * (double) angle / 180.0) * (double) strength * 1.28) + 127;
            joyY = (int) (Math.sin(Math.PI * (double) angle / 180.0) * (double) strength * 1.28) + 127;

            bluetoothComInstance.write(getDataString());
        });

        seekBar1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                sliderX = progress;
                bluetoothComInstance.write(getDataString());
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {}

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        seekBar2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                sliderY = progress;
                bluetoothComInstance.write(getDataString());
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    public String getDataString() {
        StringBuilder bob = new StringBuilder();
        bob.append(int2fixStr(joyX));
        bob.append(",");
        bob.append(int2fixStr(joyY));
        bob.append(",");
        bob.append(int2fixStr(sliderX));
        bob.append(",");
        bob.append(int2fixStr(sliderY));
        bob.append("\n");
        return bob.toString();
    }

    private String int2fixStr(int a) {
        if(a < 10) {
            return "00" + a;
        }
        else if(a < 100)
        {
            return "0" + a;

        } else {
            return Integer.toString(a);
        }
    }
}
