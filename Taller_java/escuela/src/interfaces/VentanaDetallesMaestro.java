package interfaces;

import escuelaClases.Maestro;
import escuelaClases.Persona;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class VentanaDetallesMaestro extends JFrame {
    private Maestro maestro;

    public VentanaDetallesMaestro(Maestro maestro) {
        this.maestro = maestro;

        setTitle("Detalles del Maestro");
        setSize(400, 350);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panelMaestro = new JPanel();
        panelMaestro.setLayout(new GridLayout(6, 2, 10, 10));
        panelMaestro.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        panelMaestro.add(new JLabel("Nombre:"));
        panelMaestro.add(new JLabel(maestro.getNombre()));

        panelMaestro.add(new JLabel("Edad:"));
        panelMaestro.add(new JLabel(String.valueOf(maestro.getEdad())));

        panelMaestro.add(new JLabel("Matricula:"));
        panelMaestro.add(new JLabel(String.valueOf(maestro.getMatricula())));

        panelMaestro.add(new JLabel("Facultad:"));
        panelMaestro.add(new JLabel(maestro.getFacultad()));

        panelMaestro.add(new JLabel("Título:"));
        panelMaestro.add(new JLabel(maestro.getTituloAcademico()));

        JButton btnMostrarActividades = new JButton("Mostrar Actividades");
        btnMostrarActividades.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnMostrarActividades.setBackground(new Color(0, 153, 204));
        btnMostrarActividades.setForeground(Color.WHITE);
        btnMostrarActividades.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new MostrarActividades(VentanaDetallesMaestro.this, maestro);
            }
        });

        JButton btnCerrar = new JButton("Cerrar");
        btnCerrar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCerrar.setBackground(new Color(204, 0, 0));
        btnCerrar.setForeground(Color.WHITE);
        btnCerrar.addActionListener(e -> dispose());

        JPanel panelBotones = new JPanel();
        panelBotones.setLayout(new FlowLayout(FlowLayout.CENTER));
        panelBotones.add(btnMostrarActividades);
        panelBotones.add(btnCerrar);

        add(panelMaestro, BorderLayout.CENTER);
        add(panelBotones, BorderLayout.SOUTH);

        setVisible(true);
    }
}
