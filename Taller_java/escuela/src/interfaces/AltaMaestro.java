//package escuelaClases;
package interfaces;

import escuelaClases.*;	 

import javax.swing.*;
import java.awt.*;

public class AltaMaestro extends JFrame {
    public AltaMaestro() {
        setTitle("Alta Maestro");
        setSize(400, 300);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(6, 2));

        JTextField nombreField = new JTextField();
        JTextField edadField = new JTextField();
        JTextField matriculaField = new JTextField();
        JTextField facultadField = new JTextField();
        JTextField tituloField = new JTextField();

        add(new JLabel("Nombre:"));
        add(nombreField);
        add(new JLabel("Edad:"));
        add(edadField);
        add(new JLabel("Matricula:"));
        add(matriculaField);
        add(new JLabel("Facultad:"));
        add(facultadField);
        add(new JLabel("Titulo:"));
        add(tituloField);

        JButton submitButton = new JButton("Submit");
        submitButton.addActionListener(e -> {
            if (validateTextField(nombreField) && validateIntegerField(edadField) &&
                validateIntegerField(matriculaField) && validateTextField(facultadField) &&
                validateTextField(tituloField)) {
                Maestro nuevo = new Maestro(
                        nombreField.getText(),
                        Integer.parseInt(edadField.getText()),
                        Integer.parseInt(matriculaField.getText()),
                        facultadField.getText(),
                        tituloField.getText()
                );
                Control.agregarMaestro(nuevo);
                dispose();
                JOptionPane.showMessageDialog(this, "Maestro agregado con éxito.");
            } else {
                JOptionPane.showMessageDialog(this, "Por favor, complete todos los campos correctamente.");
            }
        });
        add(submitButton);

        JButton cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(e -> dispose());
        add(cancelButton);
    }

    public boolean validateTextField(JTextField textField) {
        return textField.getText() != null && !textField.getText().trim().isEmpty();
    }

    public boolean validateIntegerField(JTextField textField) {
        try {
            Integer.parseInt(textField.getText().trim());
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}
