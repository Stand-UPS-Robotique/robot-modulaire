// https://github.com/controlwear/virtual-joystick-android

package fr.standups.robotmodulaire.activities;

import android.annotation.SuppressLint;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.widget.SeekBar;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import fr.standups.robotmodulaire.R;
import fr.standups.robotmodulaire.com.BluetoothCommunication;
import io.github.controlwear.virtual.joystick.android.JoystickView;

public class ControlActivity extends AppCompatActivity {

    private SeekBar seekBar1, seekBar2;
    private int joyX, joyY, sliderX, sliderY;

    @SuppressLint("SourceLockedOrientationActivity")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        setContentView(R.layout.activity_control);

        seekBar1 = findViewById(R.id.seekBar1);
        seekBar1.setMax(255);

        seekBar2 = findViewById(R.id.seekBar2);
        seekBar2.setMax(255);

        JoystickView joystickView = findViewById(R.id.joystick);
        joystickView.setOnMoveListener((angle, strength) -> {
            joyX = (int) (Math.cos(Math.PI * (double) angle / 180.0) * (double) strength * 1.28) + 127;
            joyY = (int) (Math.sin(Math.PI * (double) angle / 180.0) * (double) strength * 1.28) + 127;
        });

        seekBar1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                sliderX = progress;
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
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        Thread t = new Thread() {
            @Override
            public void run() {
                while(true)
                {
                    assert BluetoothCommunication.getInstance() != null;
                    BluetoothCommunication.getInstance().write(getDataString());
                    System.out.println(getDataString());
                }
            }
        };
        t.start();
    }

    public String getDataString() {
        StringBuilder bob = new StringBuilder();
        bob.append(joyX);
        bob.append(",");
        bob.append(joyY);
        bob.append(",");
        bob.append(sliderX);
        bob.append(",");
        bob.append(sliderY);
        bob.append("\n");
        return bob.toString();
    }
}
