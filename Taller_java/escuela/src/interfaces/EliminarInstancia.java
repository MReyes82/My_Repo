package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;

public class EliminarInstancia extends JFrame {
    public EliminarInstancia() {
        setTitle("Eliminar Instancia");
        setSize(300, 200);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(3, 2));

        JTextField nombreField = new JTextField();

        add(new JLabel("Nombre:"));
        add(nombreField);

        JButton submitButton = new JButton("Eliminar");
        submitButton.addActionListener(e -> {
            String nombre = nombreField.getText().trim();
            if (!nombre.isEmpty()) {
                if (Control.eliminarMaestroPorNombre(nombre) || Control.eliminarAlumnoPorNombre(nombre)) {
                    JOptionPane.showMessageDialog(this, "Instancia eliminada con éxito.");
                } else {
                    JOptionPane.showMessageDialog(this, "No se encontró la instancia.");
                }
                dispose();
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

