package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class VentanaEditarMaestro extends JFrame {
    private JTextField nombreField;
    private JTextField edadField;
    private JTextField matriculaField;
    private JTextField facultadField;
    private JTextField tituloField;
    private JButton aceptarButton;
    private JButton cancelarButton;

    private Maestro maestro;

    public VentanaEditarMaestro(Maestro maestro) {
        this.maestro = maestro;

        // Configuración de la ventana
        setTitle("Editar Maestro");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        // Crear el panel principal
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Crear y añadir los componentes al panel
        panel.add(new JLabel("Nombre:"));
        nombreField = new JTextField(maestro.getNombre());
        panel.add(nombreField);

        panel.add(new JLabel("Edad:"));
        edadField = new JTextField(String.valueOf(maestro.getEdad()));
        panel.add(edadField);

        panel.add(new JLabel("Matricula:"));
        matriculaField = new JTextField(String.valueOf(maestro.getMatricula()));
        matriculaField.setEditable(false);
        panel.add(matriculaField);

        panel.add(new JLabel("Facultad:"));
        facultadField = new JTextField(maestro.getFacultad());
        panel.add(facultadField);

        panel.add(new JLabel("Título:"));
        tituloField = new JTextField(maestro.getTituloAcademico());
        panel.add(tituloField);

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
            String titulo = tituloField.getText();

            // Validación básica
            if (nombre.isEmpty() || facultad.isEmpty() || titulo.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Todos los campos deben estar llenos", "Error", JOptionPane.ERROR_MESSAGE);
            } else if (edad < 0) {
                JOptionPane.showMessageDialog(this, "La edad debe ser un valor positivo", "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                // Actualizar los datos del maestro
                maestro.setNombre(nombre);
                maestro.setEdad(edad);
                maestro.setFacultad(facultad);
                maestro.setTituloAcademico(titulo);

                // Mostrar mensaje de éxito
                JOptionPane.showMessageDialog(this, "Maestro actualizado con éxito", "Éxito", JOptionPane.INFORMATION_MESSAGE);
                dispose();
            }
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "La edad debe ser un número válido", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
