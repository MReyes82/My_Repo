package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AgregarActividadAlumno extends JFrame {
    private Alumno alumno;
    private JTextField fechaField;
    private JTextField actividadField;

    public AgregarActividadAlumno(Alumno alumno) {
        this.alumno = alumno;

        setTitle("Agregar Actividad para Alumno");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 2, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        panel.add(new JLabel("Fecha:"));
        fechaField = new JTextField();
        panel.add(fechaField);

        panel.add(new JLabel("Actividad:"));
        actividadField = new JTextField();
        panel.add(actividadField);

        JButton btnAgregar = new JButton("Agregar");
        btnAgregar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnAgregar.setBackground(new Color(0, 153, 0));
        btnAgregar.setForeground(Color.WHITE);
        btnAgregar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                agregarActividad();
            }
        });
        panel.add(btnAgregar);

        JButton btnCancelar = new JButton("Cancelar");
        btnCancelar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCancelar.setBackground(new Color(204, 0, 0));
        btnCancelar.setForeground(Color.WHITE);
        btnCancelar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });
        panel.add(btnCancelar);

        getContentPane().add(panel);
        setVisible(true);
    }

    private void agregarActividad() {
        String fecha = fechaField.getText().trim();
        String actividad = actividadField.getText().trim();

        if (fecha.isEmpty() || actividad.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Por favor, complete todos los campos", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        alumno.agregarActividad(fecha, actividad);
        JOptionPane.showMessageDialog(this, "Actividad agregada exitosamente", "Éxito", JOptionPane.INFORMATION_MESSAGE);
        dispose();
    }
}
