package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;

public class MostrarMaterias extends JFrame {
    private Alumno alumno;

    public MostrarMaterias(JFrame parent, Alumno alumno) {
        this.alumno = alumno;

        setTitle("Materias del Alumno");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(parent);

        JPanel panelMaterias = new JPanel();
        panelMaterias.setLayout(new BorderLayout());
        panelMaterias.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        JLabel lblMaterias = new JLabel("Materias:");
        lblMaterias.setFont(new Font("Tahoma", Font.PLAIN, 15));
        panelMaterias.add(lblMaterias, BorderLayout.NORTH);

        JTextArea textArea = new JTextArea();
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea);
        panelMaterias.add(scrollPane, BorderLayout.CENTER);

        String[] materias = alumno.getMaterias();
        if (materias == null || materias.length == 0) {
            textArea.setText("No hay materias");
        } else {
            StringBuilder materiasText = new StringBuilder();
            for (String materia : materias) {
                materiasText.append(materia).append("\n");
            }
            textArea.setText(materiasText.toString());
        }

        JButton btnCerrar = new JButton("Cerrar");
        btnCerrar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCerrar.setBackground(new Color(204, 0, 0));
        btnCerrar.setForeground(Color.WHITE);
        btnCerrar.addActionListener(e -> dispose());

        JPanel panelBotones = new JPanel();
        panelBotones.setLayout(new FlowLayout(FlowLayout.CENTER));
        panelBotones.add(btnCerrar);

        add(panelMaterias, BorderLayout.CENTER);
        add(panelBotones, BorderLayout.SOUTH);

        setVisible(true);
    }
}
