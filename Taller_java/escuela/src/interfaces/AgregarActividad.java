package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Map;

public class AgregarActividad extends JFrame {
    private JTextField fechaField;
    private JTextField actividadField;
    private Maestro maestro;

    public AgregarActividad(Maestro maestro) {
        this.maestro = maestro;

        // Configuración de la ventana
        setTitle("Agregar Actividad");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        // Crear el panel principal
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 2, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Crear y añadir los componentes al panel
        panel.add(new JLabel("Fecha:"));
        fechaField = new JTextField();
        panel.add(fechaField);

        panel.add(new JLabel("Actividad:"));
        actividadField = new JTextField();
        panel.add(actividadField);

        JButton aceptarButton = new JButton("Aceptar");
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

        JButton cancelarButton = new JButton("Cancelar");
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
        String fecha = fechaField.getText();
        String actividad = actividadField.getText();

        if (fecha.isEmpty() || actividad.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Por favor, complete todos los campos", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        maestro.agregarActividad(fecha, actividad);
        JOptionPane.showMessageDialog(this, "Actividad agregada exitosamente", "Éxito", JOptionPane.INFORMATION_MESSAGE);
        dispose();
    }
}
