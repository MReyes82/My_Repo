package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class BuscarGrupo extends JFrame {
    private JTextField numeroField;
    private JLabel messageLabel;

    public BuscarGrupo() {
        // Configuración del JFrame
        setTitle("Buscar Grupo");
        setSize(454, 250);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        // Crear panel para los componentes
        JPanel panel = new JPanel();
        panel.setLayout(null); // Uso de null layout para posicionamiento absoluto

        // Campo de texto para ingresar el número de grupo
        numeroField = new JTextField();
        numeroField.setFont(new Font("Tahoma", Font.PLAIN, 12));
        numeroField.setBounds(69, 90, 300, 25); // Posición y tamaño
        panel.add(numeroField);

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
        JLabel lblInstruccion = new JLabel("Ingrese el número del grupo");
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
            String numero = numeroField.getText().trim();
            if (!numero.isEmpty()) {
                try {
                    int numeroGrupo = Integer.parseInt(numero);
                    Grupo grupo = Control.buscarGrupoPorNumero(numeroGrupo);
                    if (grupo != null) {
                        new VentanaDetallesGrupo(grupo);
                        dispose();
                    } else {
                        JOptionPane.showMessageDialog(BuscarGrupo.this, "No se encontró el grupo.");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(BuscarGrupo.this, "Por favor, ingrese un número válido.");
                }
            } else {
                JOptionPane.showMessageDialog(BuscarGrupo.this, "Por favor, ingrese un número.");
            }
        }
    }
}
