package interfaces;

import escuelaClases.Persona;

import javax.swing.*;
import java.awt.*;

public class MostrarActividades extends JDialog {
    public MostrarActividades(Frame owner, Persona persona) {
        super(owner, "Actividades de " + persona.getNombre(), true);
        setSize(400, 300);
        setLocationRelativeTo(owner);

        JPanel panelActividades = new JPanel();
        panelActividades.setLayout(new BorderLayout(10, 10));
        panelActividades.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        JTextArea textArea = new JTextArea();
        textArea.setEditable(false);
        textArea.setText(persona.muestraActividad());

        JScrollPane scrollPane = new JScrollPane(textArea);
        panelActividades.add(scrollPane, BorderLayout.CENTER);

        JButton btnCerrar = new JButton("Cerrar");
        btnCerrar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCerrar.setBackground(new Color(204, 0, 0));
        btnCerrar.setForeground(Color.WHITE);
        btnCerrar.addActionListener(e -> dispose());

        JPanel panelBotones = new JPanel();
        panelBotones.setLayout(new FlowLayout(FlowLayout.CENTER));
        panelBotones.add(btnCerrar);

        add(panelActividades, BorderLayout.CENTER);
        add(panelBotones, BorderLayout.SOUTH);

        setVisible(true);
    }
}
