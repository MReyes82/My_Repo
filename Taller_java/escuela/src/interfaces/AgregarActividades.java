package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;

//TODO: RESOLVER METODOS 

public class AgregarActividades extends JFrame {
    public AgregarActividades() {
        setTitle("Agregar Actividades");
        setSize(300, 200);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(4, 2));

        JTextField nombreField = new JTextField();
        JTextField actividadField = new JTextField();

        add(new JLabel("Nombre:"));
        add(nombreField);
        add(new JLabel("Actividad:"));
        add(actividadField);

        JButton submitButton = new JButton("Agregar");
        submitButton.addActionListener(e -> {
            String nombre = nombreField.getText().trim();
            String actividad = actividadField.getText().trim();
            if (!nombre.isEmpty() && !actividad.isEmpty()) {
                Alumno alumno = Control.buscarAlumnoPorNombre(nombre);
                if (alumno != null) {
                    //alumno.agregarActividadExtracurricular(actividad);
                    JOptionPane.showMessageDialog(this, "Actividad agregada con éxito.");
                    dispose();
                } else {
                    Maestro maestro = Control.buscarMaestroPorNombre(nombre);
                    if (maestro != null) {
                        //maestro.agregarActividadExtracurricular(actividad);
                        JOptionPane.showMessageDialog(this, "Actividad agregada con éxito.");
                        dispose();
                    } else {
                        JOptionPane.showMessageDialog(this, "No se encontró la persona.");
                    }
                }
            } else {
                JOptionPane.showMessageDialog(this, "Por favor, complete todos los campos.");
            }
        });
        add(submitButton);

        JButton cancelButton = new JButton("Cancelar");
        cancelButton.addActionListener(e -> dispose());
        add(cancelButton);

        setVisible(true);
    }
}

