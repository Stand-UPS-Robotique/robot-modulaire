package fr.standups.robotmodulaire.activities;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import fr.standups.robotmodulaire.R;

public class SetupActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_setup);
    }

    /* called when a bluetooth socket is created */
    private void changeActivity(View view) {
        Intent intent = new Intent(this, ControlActivity.class);
//        intent.putExtra()
        startActivity(intent);
    }
}
