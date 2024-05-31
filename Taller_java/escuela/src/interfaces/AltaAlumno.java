package interfaces;

import escuelaClases.*;
import javax.swing.*;
import java.awt.*;

public class AltaAlumno extends JFrame {
    public AltaAlumno() {
        setTitle("Alta Alumno");
        setSize(400, 400);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(8, 2));

        JTextField nombreField = new JTextField();
        JTextField edadField = new JTextField();
        JTextField matriculaField = new JTextField();
        JTextField facultadField = new JTextField();
        JTextField carreraField = new JTextField();
        JTextField promedioField = new JTextField();
        JTextField semestreField = new JTextField();
        JTextField cantidadMateriasField = new JTextField();

        add(new JLabel("Nombre:"));
        add(nombreField);
        add(new JLabel("Edad:"));
        add(edadField);
        add(new JLabel("Matricula:"));
        add(matriculaField);
        add(new JLabel("Facultad:"));
        add(facultadField);
        add(new JLabel("Carrera:"));
        add(carreraField);
        add(new JLabel("Promedio:"));
        add(promedioField);
        add(new JLabel("Semestre:"));
        add(semestreField);
        add(new JLabel("Cantidad de Materias:"));
        add(cantidadMateriasField);

        JButton submitButton = new JButton("Submit");
        submitButton.addActionListener(e -> {
            if (validateTextField(nombreField) && validateIntegerField(edadField) &&
                validateIntegerField(matriculaField) && validateTextField(facultadField) &&
                validateTextField(carreraField) && validateFloatField(promedioField) &&
                validateIntegerField(semestreField) && validateIntegerField(cantidadMateriasField)) {
                String[] materias = new String[Integer.parseInt(cantidadMateriasField.getText())];
                for (int i = 0; i < materias.length; i++) {
                    materias[i] = JOptionPane.showInputDialog("Materia " + (i + 1) + ":");
                }
                Alumno nuevo = new Alumno(
                        nombreField.getText(),
                        Integer.parseInt(edadField.getText()),
                        Integer.parseInt(matriculaField.getText()),
                        facultadField.getText(),
                        Float.parseFloat(promedioField.getText()),
                        carreraField.getText(),
                        materias,
                        Integer.parseInt(semestreField.getText())
                );
                Control.agregarAlumnos(nuevo);
                dispose();
                JOptionPane.showMessageDialog(this, "Alumno agregado con éxito.");
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

    public boolean validateFloatField(JTextField textField) {
        try {
            Float.parseFloat(textField.getText().trim());
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}
