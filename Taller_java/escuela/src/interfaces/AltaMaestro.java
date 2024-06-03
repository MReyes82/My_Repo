package interfaces;

import escuelaClases.*;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AltaMaestro extends JFrame {
    private JPanel contentPane;
    private JTextField nombreField;
    private JTextField edadField;
    private JTextField matriculaField;
    private JTextField facultadField;
    private JTextField tituloField;

    public AltaMaestro() {
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 800, 550);
        contentPane = new JPanel();
        contentPane.setBackground(new Color(240, 240, 240));
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        JLabel lblTitulo = new JLabel("Alta de Maestro");
        lblTitulo.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitulo.setFont(new Font("Times New Roman", Font.BOLD, 24));
        lblTitulo.setBounds(200, 20, 400, 30);
        contentPane.add(lblTitulo);

        JLabel lblNombre = new JLabel("Nombre:");
        lblNombre.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblNombre.setBounds(250, 80, 120, 20);
        contentPane.add(lblNombre);

        nombreField = new JTextField();
        nombreField.setBounds(400, 79, 200, 25);
        contentPane.add(nombreField);
        nombreField.setColumns(10);

        JLabel lblEdad = new JLabel("Edad:");
        lblEdad.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblEdad.setBounds(250, 120, 120, 20);
        contentPane.add(lblEdad);

        edadField = new JTextField();
        edadField.setBounds(400, 119, 200, 25);
        contentPane.add(edadField);
        edadField.setColumns(10);

        JLabel lblMatricula = new JLabel("Matricula:");
        lblMatricula.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblMatricula.setBounds(250, 160, 120, 20);
        contentPane.add(lblMatricula);

        matriculaField = new JTextField();
        matriculaField.setBounds(400, 159, 200, 25);
        contentPane.add(matriculaField);
        matriculaField.setColumns(10);

        JLabel lblFacultad = new JLabel("Facultad:");
        lblFacultad.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblFacultad.setBounds(250, 200, 120, 20);
        contentPane.add(lblFacultad);

        facultadField = new JTextField();
        facultadField.setBounds(400, 199, 200, 25);
        contentPane.add(facultadField);
        facultadField.setColumns(10);

        JLabel lblTituloAcademico = new JLabel("Titulo Academico:");
        lblTituloAcademico.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblTituloAcademico.setBounds(250, 240, 120, 20);
        contentPane.add(lblTituloAcademico);

        tituloField = new JTextField();
        tituloField.setBounds(400, 239, 200, 25);
        contentPane.add(tituloField);
        tituloField.setColumns(10);

        JButton btnRegistrar = new JButton("Registrar");
        btnRegistrar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnRegistrar.setBackground(new Color(0, 153, 0));
        btnRegistrar.setForeground(Color.WHITE);
        btnRegistrar.setBounds(250, 446, 150, 35);
        btnRegistrar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (registrarMaestro()) {
                    dispose();
                }
            }
        });
        contentPane.add(btnRegistrar);

        JButton btnCancelar = new JButton("Cancelar");
        btnCancelar.setFont(new Font("Tahoma", Font.BOLD, 16));
        btnCancelar.setBackground(new Color(204, 0, 0));
        btnCancelar.setForeground(Color.WHITE);
        btnCancelar.setBounds(450, 445, 150, 35);
        btnCancelar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (nombreField.getText().isEmpty() && edadField.getText().isEmpty() &&
                    matriculaField.getText().isEmpty() && facultadField.getText().isEmpty() &&
                    tituloField.getText().isEmpty()) {
                    dispose();
                } else {
                    limpiarCampos();
                }
            }
        });
        contentPane.add(btnCancelar);
    }

    private boolean registrarMaestro() {
        if (validarDatos()) {
            String nombre = nombreField.getText();
            int edad = Integer.parseInt(edadField.getText());
            int matricula = Integer.parseInt(matriculaField.getText());
            String facultad = facultadField.getText();
            String titulo = tituloField.getText();

            Maestro nuevo = new Maestro(nombre, edad, matricula, facultad, titulo);
            Control.agregarMaestro(nuevo);
            JOptionPane.showMessageDialog(this, "Maestro registrado exitosamente", "Registro exitoso", JOptionPane.INFORMATION_MESSAGE);
            return true;
        }
        return false;
    }

    private boolean validarDatos() {
        if (nombreField.getText().isEmpty() || edadField.getText().isEmpty() ||
            matriculaField.getText().isEmpty() || facultadField.getText().isEmpty() ||
            tituloField.getText().isEmpty()) {
            mostrarMensajeError("Por favor, complete todos los campos");
            return false;
        }

        try {
            Integer.parseInt(edadField.getText());
        } catch (NumberFormatException e) {
            mostrarMensajeError("La edad debe ser un número entero válido");
            return false;
        }

        try {
            Integer.parseInt(matriculaField.getText());
        } catch (NumberFormatException e) {
            mostrarMensajeError("La matrícula debe ser un número entero válido");
            return false;
        }

        return true;
    }

    private void mostrarMensajeError(String mensaje) {
        JOptionPane.showMessageDialog(this, mensaje, "Error de validación", JOptionPane.ERROR_MESSAGE);
    }

    private void limpiarCampos() {
        nombreField.setText("");
        edadField.setText("");
        matriculaField.setText("");
        facultadField.setText("");
        tituloField.setText("");
    }
}
