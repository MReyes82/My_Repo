package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;

public class VentanaDetallesGrupo extends JFrame {
    private Grupo grupo;

    public VentanaDetallesGrupo(Grupo grupo) {
        this.grupo = grupo;

        setTitle("Detalles del Grupo");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panelGrupo = new JPanel();
        panelGrupo.setLayout(new GridLayout(4, 2, 10, 10));
        panelGrupo.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        panelGrupo.add(new JLabel("Número de Grupo:"));
        panelGrupo.add(new JLabel(String.valueOf(grupo.getNumeroDeGrupo())));

        panelGrupo.add(new JLabel("Cantidad Máxima de Alumnos:"));
        panelGrupo.add(new JLabel(String.valueOf(grupo.getCantidadMaxAlumnos())));

        panelGrupo.add(new JLabel("Maestro:"));
        panelGrupo.add(new JLabel(grupo.getProfesor().getNombre()));

        JButton btnVerAlumnos = new JButton("Ver Listado de Alumnos");
        btnVerAlumnos.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnVerAlumnos.setBackground(new Color(0, 153, 204));
        btnVerAlumnos.setForeground(Color.WHITE);
        btnVerAlumnos.addActionListener(e -> new VentanaListadoAlumnos(grupo));

        JButton btnCerrar = new JButton("Cerrar");
        btnCerrar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCerrar.setBackground(new Color(204, 0, 0));
        btnCerrar.setForeground(Color.WHITE);
        btnCerrar.addActionListener(e -> dispose());

        JPanel panelBotones = new JPanel();
        panelBotones.setLayout(new FlowLayout(FlowLayout.CENTER));
        panelBotones.add(btnVerAlumnos);
        panelBotones.add(btnCerrar);

        add(panelGrupo, BorderLayout.CENTER);
        add(panelBotones, BorderLayout.SOUTH);

        setVisible(true);
    }
}
