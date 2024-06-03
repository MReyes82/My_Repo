package interfaces;

import escuelaClases.*;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AltaAlumno extends JFrame {
    private JPanel contentPane;
    private JTextField nombreField;
    private JTextField edadField;
    private JTextField matriculaField;
    private JTextField facultadField;
    private JTextField carreraField;
    private JTextField promedioField;
    private JTextField semestreField;
    private int cantidadMaterias;
    private JTable tableMaterias;

    public AltaAlumno() {
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 800, 550);
        contentPane = new JPanel();
        contentPane.setBackground(new Color(240, 240, 240));
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        JLabel lblTitulo = new JLabel("Alta de Alumno");
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

        JLabel lblCarrera = new JLabel("Carrera:");
        lblCarrera.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblCarrera.setBounds(250, 240, 120, 20);
        contentPane.add(lblCarrera);

        carreraField = new JTextField();
        carreraField.setBounds(400, 239, 200, 25);
        contentPane.add(carreraField);
        carreraField.setColumns(10);

        JLabel lblPromedio = new JLabel("Promedio:");
        lblPromedio.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblPromedio.setBounds(250, 280, 120, 20);
        contentPane.add(lblPromedio);

        promedioField = new JTextField();
        promedioField.setBounds(400, 279, 200, 25);
        contentPane.add(promedioField);
        promedioField.setColumns(10);

        JLabel lblSemestre = new JLabel("Semestre:");
        lblSemestre.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblSemestre.setBounds(250, 320, 120, 20);
        contentPane.add(lblSemestre);

        semestreField = new JTextField();
        semestreField.setBounds(400, 319, 200, 25);
        contentPane.add(semestreField);
        semestreField.setColumns(10);

        JLabel lblCantidadMaterias = new JLabel("Cantidad de Materias:");
        lblCantidadMaterias.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblCantidadMaterias.setBounds(250, 360, 180, 20);
        contentPane.add(lblCantidadMaterias);

        JTextField cantidadMateriasField = new JTextField();
        cantidadMateriasField.setBounds(436, 359, 164, 25);
        contentPane.add(cantidadMateriasField);
        cantidadMateriasField.setColumns(10);

        JButton btnMaterias = new JButton("Siguiente");
        btnMaterias.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnMaterias.setBackground(new Color(0, 153, 0));
        btnMaterias.setForeground(Color.WHITE);
        btnMaterias.setBounds(250, 446, 150, 35);
        btnMaterias.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    cantidadMaterias = Integer.parseInt(cantidadMateriasField.getText());
                    if (cantidadMaterias <= 0) {
                        mostrarMensajeError("La cantidad de materias debe ser mayor a 0");
                        return;
                    }
                    mostrarVentanaMaterias();
                } catch (NumberFormatException ex) {
                    mostrarMensajeError("Por favor, ingrese un número válido");
                }
            }
        });
        contentPane.add(btnMaterias);

        JButton btnCancelar = new JButton("Cancelar");
        btnCancelar.setFont(new Font("Tahoma", Font.BOLD, 16));
        btnCancelar.setBackground(new Color(204, 0, 0));
        btnCancelar.setForeground(Color.WHITE);
        btnCancelar.setBounds(450, 445, 150, 35);
        btnCancelar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (nombreField.getText().isEmpty() && edadField.getText().isEmpty() &&
                    matriculaField.getText().isEmpty() && facultadField.getText().isEmpty() &&
                    carreraField.getText().isEmpty() && promedioField.getText().isEmpty() &&
                    semestreField.getText().isEmpty() && cantidadMateriasField.getText().isEmpty()) {
                    dispose();
                } else {
                    limpiarCampos();
                }
            }
        });
        contentPane.add(btnCancelar);
    }

    private void mostrarVentanaMaterias() {
        JDialog dialog = new JDialog(this, "Materias", true);
        dialog.setBounds(100, 100, 450, 400);
        JPanel panel = new JPanel();
        panel.setBorder(new EmptyBorder(5, 5, 5, 5));
        dialog.setContentPane(panel);
        panel.setLayout(null);

        JLabel lblMaterias = new JLabel("Ingrese los nombres de las materias");
        lblMaterias.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblMaterias.setBounds(32, 11, 358, 20);
        panel.add(lblMaterias);

        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setBounds(32, 41, 358, 220);
        panel.add(scrollPane);

        tableMaterias = new JTable();
        tableMaterias.setModel(new DefaultTableModel(
                new Object[cantidadMaterias][1],
                new String[] {
                        "Materia"
                }
        ) {
            boolean[] columnEditables = new boolean[] {
                    true
            };
            public boolean isCellEditable(int row, int column) {
                return columnEditables[column];
            }
        });
        scrollPane.setViewportView(tableMaterias);

        JButton btnRegistrar = new JButton("Registrar");
        btnRegistrar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnRegistrar.setBackground(new Color(0, 153, 0));
        btnRegistrar.setForeground(Color.WHITE);
        btnRegistrar.setBounds(50, 300, 120, 35);
        btnRegistrar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (registrarAlumno()) {
                    dialog.dispose();
                    dispose();
                }
            }
        });
        panel.add(btnRegistrar);

        JButton btnCancelarMaterias = new JButton("Cancelar");
        btnCancelarMaterias.setFont(new Font("Tahoma", Font.BOLD, 16));
        btnCancelarMaterias.setBackground(new Color(204, 0, 0));
        btnCancelarMaterias.setForeground(Color.WHITE);
        btnCancelarMaterias.setBounds(250, 300, 120, 35);
        btnCancelarMaterias.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
            }
        });
        panel.add(btnCancelarMaterias);

        dialog.setVisible(true);
    }

    private boolean registrarAlumno() {
        if (validarDatos()) {
            String nombre = nombreField.getText();
            int edad = Integer.parseInt(edadField.getText());
            int matricula = Integer.parseInt(matriculaField.getText());
            String facultad = facultadField.getText();
            String carrera = carreraField.getText();
            float promedio = Float.parseFloat(promedioField.getText());
            int semestre = Integer.parseInt(semestreField.getText());

            DefaultTableModel model = (DefaultTableModel) tableMaterias.getModel();
            int rowCount = model.getRowCount();
            String[] materias = new String[rowCount];
            for (int i = 0; i < rowCount; i++) {
                materias[i] = (String) model.getValueAt(i, 0);
            }

            Alumno nuevo = new Alumno(nombre, edad, matricula, facultad, promedio, carrera, materias, semestre);
            Control.agregarAlumnos(nuevo);
            JOptionPane.showMessageDialog(this, "Alumno registrado exitosamente", "Registro exitoso", JOptionPane.INFORMATION_MESSAGE);
            return true;
        }
        return false;
    }

    private boolean validarDatos() {
        if (nombreField.getText().isEmpty() || edadField.getText().isEmpty() ||
            matriculaField.getText().isEmpty() || facultadField.getText().isEmpty() ||
            carreraField.getText().isEmpty() || promedioField.getText().isEmpty() ||
            semestreField.getText().isEmpty()) {
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

        try {
            Float.parseFloat(promedioField.getText());
        } catch (NumberFormatException e) {
            mostrarMensajeError("El promedio debe ser un número decimal válido");
            return false;
        }

        try {
            Integer.parseInt(semestreField.getText());
        } catch (NumberFormatException e) {
            mostrarMensajeError("El semestre debe ser un número entero válido");
            return false;
        }

        DefaultTableModel model = (DefaultTableModel) tableMaterias.getModel();
        int rowCount = model.getRowCount();
        for (int i = 0; i < rowCount; i++) {
            if (model.getValueAt(i, 0) == null || ((String) model.getValueAt(i, 0)).trim().isEmpty()) {
                mostrarMensajeError("Por favor, complete todos los campos de materias");
                return false;
            }
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
        carreraField.setText("");
        promedioField.setText("");
        semestreField.setText("");
    }
}
