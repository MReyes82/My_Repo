package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;

public class BuscarPersona extends JFrame {
    public BuscarPersona() {
        setTitle("Buscar Persona");
        setSize(300, 200);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(3, 2));

        JTextField nombreField = new JTextField();

        add(new JLabel("Nombre:"));
        add(nombreField);

        JButton submitButton = new JButton("Buscar");
        submitButton.addActionListener(e -> {
            String nombre = nombreField.getText().trim();
            if (!nombre.isEmpty()) {
                Alumno alumno = Control.buscarAlumnoPorNombre(nombre);
                if (alumno != null) {
                    JOptionPane.showMessageDialog(this, alumno.toString());
                } else {
                    Maestro maestro = Control.buscarMaestroPorNombre(nombre);
                    if (maestro != null) {
                        JOptionPane.showMessageDialog(this, maestro.toString());
                    } else {
                        JOptionPane.showMessageDialog(this, "No se encontró la persona.");
                    }
                }
            } else {
                JOptionPane.showMessageDialog(this, "Por favor, ingrese un nombre.");
            }
        });
        add(submitButton);

        JButton cancelButton = new JButton("Cancelar");
        cancelButton.addActionListener(e -> dispose());
        add(cancelButton);

        setVisible(true);
    }
}

