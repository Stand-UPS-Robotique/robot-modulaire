// https://github.com/controlwear/virtual-joystick-android

package fr.standups.robotmodulaire.activities;

import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import fr.standups.robotmodulaire.R;
import io.github.controlwear.virtual.joystick.android.JoystickView;

public class ControlActivity extends AppCompatActivity {

    private int joyX, joyY, sliderX, sliderY;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);

        JoystickView joystickView = findViewById(R.id.joystick);
        joystickView.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                joyX = (int) (Math.cos(Math.PI * (double) angle / 180.0) * (double) strength * 1.28) + 127;
                joyY = (int) (Math.sin(Math.PI * (double) angle / 180.0) * (double) strength * 1.28) + 127;

                System.out.println(joyX + ", " + joyY);
            }
        });
    }
}
