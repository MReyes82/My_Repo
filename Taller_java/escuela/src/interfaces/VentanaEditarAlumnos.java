package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class VentanaEditarAlumnos extends JFrame {
    private JTextField nombreField;
    private JTextField edadField;
    private JTextField matriculaField;
    private JTextField facultadField;
    private JTextField carreraField;
    private JTextField promedioField;
    private JTextField semestreField;
    private JButton aceptarButton;
    private JButton cancelarButton;

    private Alumno alumno;

    public VentanaEditarAlumnos(Alumno alumno) {
        this.alumno = alumno;

        // Configuración de la ventana
        setTitle("Editar Alumno");
        setSize(400, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        // Crear el panel principal
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(8, 2, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Crear y añadir los componentes al panel
        panel.add(new JLabel("Nombre:"));
        nombreField = new JTextField(alumno.getNombre());
        panel.add(nombreField);

        panel.add(new JLabel("Edad:"));
        edadField = new JTextField(String.valueOf(alumno.getEdad()));
        panel.add(edadField);

        panel.add(new JLabel("Matricula:"));
        matriculaField = new JTextField(String.valueOf(alumno.getMatricula()));
        matriculaField.setEditable(false);
        panel.add(matriculaField);

        panel.add(new JLabel("Facultad:"));
        facultadField = new JTextField(alumno.getFacultad());
        panel.add(facultadField);

        panel.add(new JLabel("Carrera:"));
        carreraField = new JTextField(alumno.getCarrera());
        panel.add(carreraField);

        panel.add(new JLabel("Promedio:"));
        promedioField = new JTextField(String.valueOf(alumno.getPromedio()));
        panel.add(promedioField);

        panel.add(new JLabel("Semestre:"));
        semestreField = new JTextField(String.valueOf(alumno.getSemestre()));
        panel.add(semestreField);

        aceptarButton = new JButton("Aceptar");
        aceptarButton.setFont(new Font("Tahoma", Font.BOLD, 14));
        aceptarButton.setBackground(new Color(0, 153, 0));
        aceptarButton.setForeground(Color.WHITE);
        aceptarButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                aceptarCambios();
            }
        });
        panel.add(aceptarButton);

        cancelarButton = new JButton("Cancelar");
        cancelarButton.setFont(new Font("Tahoma", Font.BOLD, 14));
        cancelarButton.setBackground(new Color(204, 0, 0));
        cancelarButton.setForeground(Color.WHITE);
        cancelarButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });
        panel.add(cancelarButton);

        // Añadir el panel a la ventana
        getContentPane().add(panel);

        // Hacer visible la ventana
        setVisible(true);
    }

    private void aceptarCambios() {
        try {
            String nombre = nombreField.getText();
            int edad = Integer.parseInt(edadField.getText());
            String facultad = facultadField.getText();
            String carrera = carreraField.getText();
            float promedio = Float.parseFloat(promedioField.getText());
            int semestre = Integer.parseInt(semestreField.getText());

            // Validación básica
            if (nombre.isEmpty() || facultad.isEmpty() || carrera.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Todos los campos deben estar llenos", "Error", JOptionPane.ERROR_MESSAGE);
            } else if (edad < 0 || promedio < 0 || semestre < 0) {
                JOptionPane.showMessageDialog(this, "Edad, Promedio y Semestre deben ser valores positivos", "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                // Actualizar los datos del alumno
                alumno.setNombre(nombre);
                alumno.setEdad(edad);
                alumno.setFacultad(facultad);
                alumno.setCarrera(carrera);
                alumno.setPromedio(promedio);
                alumno.setSemestre(semestre);

                // Mostrar mensaje de éxito
                JOptionPane.showMessageDialog(this, "Alumno actualizado con éxito", "Éxito", JOptionPane.INFORMATION_MESSAGE);
                dispose();
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Edad, Promedio y Semestre deben ser números válidos", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
