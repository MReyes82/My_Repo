package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class BuscarPersona extends JFrame {
    private JTextField nombreField;
    private JLabel messageLabel;

    public BuscarPersona() {
        // Configuración del JFrame
        setTitle("Buscar Persona");
        setSize(454, 250);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        // Crear panel para los componentes
        JPanel panel = new JPanel();
        panel.setLayout(null); // Uso de null layout para posicionamiento absoluto

        // Campo de texto para ingresar el nombre
        nombreField = new JTextField();
        nombreField.setFont(new Font("Tahoma", Font.PLAIN, 12));
        nombreField.setBounds(69, 90, 300, 25); // Posición y tamaño
        panel.add(nombreField);

        // Etiqueta para mostrar mensajes
        messageLabel = new JLabel("", JLabel.CENTER);
        messageLabel.setBounds(50, 70, 300, 25); // Posición y tamaño
        panel.add(messageLabel);

        // Botón para buscar
        JButton submitButton = new JButton("Buscar");
        submitButton.setFont(new Font("Tahoma", Font.BOLD, 14));
        submitButton.setBackground(new Color(0, 153, 204));
        submitButton.setForeground(Color.WHITE);
        submitButton.setBounds(97, 138, 100, 30); // Posición y tamaño
        submitButton.addActionListener(new SubmitButtonListener());
        panel.add(submitButton);

        // Etiqueta de instrucciones
        JLabel lblInstruccion = new JLabel("Ingrese el nombre de la persona");
        lblInstruccion.setHorizontalAlignment(SwingConstants.CENTER);
        lblInstruccion.setFont(new Font("Tahoma", Font.PLAIN, 16));
        lblInstruccion.setBounds(85, 48, 268, 25);
        panel.add(lblInstruccion);

        // Botón para cancelar
        JButton btnCancelar = new JButton("Cancelar");
        btnCancelar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCancelar.setBackground(new Color(204, 0, 0));
        btnCancelar.setForeground(Color.WHITE);
        btnCancelar.setBounds(239, 139, 100, 30); // Posición y tamaño
        btnCancelar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });
        panel.add(btnCancelar);

        // Añadir panel al JFrame
        getContentPane().add(panel);
        setVisible(true);
    }

    public class SubmitButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String nombre = nombreField.getText().trim();
            if (!nombre.isEmpty()) {
                Alumno alumno = Control.buscarAlumnoPorNombre(nombre);
                if (alumno != null) {
                    new VentanaDetallesAlumnos(alumno);
                    dispose();
                } else {
                    Maestro maestro = Control.buscarMaestroPorNombre(nombre);
                    if (maestro != null) {
                        new VentanaDetallesMaestro(maestro);
                        dispose();
                    } else {
                        JOptionPane.showMessageDialog(BuscarPersona.this, "No se encontró la persona.");
                    }
                }
            } else {
                JOptionPane.showMessageDialog(BuscarPersona.this, "Por favor, ingrese un nombre.");
            }
        }
    }
}
