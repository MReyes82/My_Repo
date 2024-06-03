package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;

public class VentanaDetallesAlumnos extends JFrame {
    private Alumno alumno;

    public VentanaDetallesAlumnos(Alumno alumno) {
        this.alumno = alumno;

        setTitle("Detalles del Alumno");
        setSize(400, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panelAlumno = new JPanel();
        panelAlumno.setLayout(new GridLayout(8, 2, 10, 10));
        panelAlumno.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        panelAlumno.add(new JLabel("Nombre:"));
        panelAlumno.add(new JLabel(alumno.getNombre()));

        panelAlumno.add(new JLabel("Edad:"));
        panelAlumno.add(new JLabel(String.valueOf(alumno.getEdad())));

        panelAlumno.add(new JLabel("Matricula:"));
        panelAlumno.add(new JLabel(String.valueOf(alumno.getMatricula())));

        panelAlumno.add(new JLabel("Facultad:"));
        panelAlumno.add(new JLabel(alumno.getFacultad()));

        panelAlumno.add(new JLabel("Carrera:"));
        panelAlumno.add(new JLabel(alumno.getCarrera()));

        panelAlumno.add(new JLabel("Promedio:"));
        panelAlumno.add(new JLabel(String.valueOf(alumno.getPromedio())));

        panelAlumno.add(new JLabel("Semestre:"));
        panelAlumno.add(new JLabel(String.valueOf(alumno.getSemestre())));

        JButton btnMostrarMaterias = new JButton("Mostrar Materias");
        btnMostrarMaterias.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnMostrarMaterias.setBackground(new Color(0, 153, 204));
        btnMostrarMaterias.setForeground(Color.WHITE);
        btnMostrarMaterias.addActionListener(e -> new MostrarMaterias(this, alumno));

        JButton btnMostrarActividades = new JButton("Mostrar Actividades");
        btnMostrarActividades.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnMostrarActividades.setBackground(new Color(0, 153, 204));
        btnMostrarActividades.setForeground(Color.WHITE);
        btnMostrarActividades.addActionListener(e -> new MostrarActividades(this, alumno));

        JButton btnCerrar = new JButton("Cerrar");
        btnCerrar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCerrar.setBackground(new Color(204, 0, 0));
        btnCerrar.setForeground(Color.WHITE);
        btnCerrar.addActionListener(e -> dispose());

        JPanel panelBotones = new JPanel();
        panelBotones.setLayout(new FlowLayout(FlowLayout.CENTER));
        panelBotones.add(btnMostrarMaterias);
        panelBotones.add(btnMostrarActividades);
        panelBotones.add(btnCerrar);

        add(panelAlumno, BorderLayout.CENTER);
        add(panelBotones, BorderLayout.SOUTH);

        setVisible(true);
    }
}
