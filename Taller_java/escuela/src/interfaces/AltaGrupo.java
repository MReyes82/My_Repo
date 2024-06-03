package interfaces;

import escuelaClases.*;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class AltaGrupo extends JFrame {
    private JPanel contentPane;
    private JTextField numField;
    private JTextField cantidadField;

    public AltaGrupo() {
        setResizable(false);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 800, 550);
        contentPane = new JPanel();
        contentPane.setBackground(new Color(240, 240, 240));
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);

        JLabel lblTitulo = new JLabel("Alta de Grupo");
        lblTitulo.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitulo.setFont(new Font("Times New Roman", Font.BOLD, 24));
        lblTitulo.setBounds(200, 20, 400, 30);
        contentPane.add(lblTitulo);

        JLabel lblNumero = new JLabel("Número del grupo:");
        lblNumero.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblNumero.setBounds(250, 213, 150, 20);
        contentPane.add(lblNumero);

        numField = new JTextField();
        numField.setBounds(400, 213, 200, 25);
        contentPane.add(numField);
        numField.setColumns(10);

        JLabel lblCantidad = new JLabel("Cantidad de alumnos\r\n:");
        lblCantidad.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblCantidad.setBounds(250, 271, 150, 20);
        contentPane.add(lblCantidad);

        cantidadField = new JTextField();
        cantidadField.setBounds(400, 271, 200, 25);
        contentPane.add(cantidadField);
        cantidadField.setColumns(10);

        JButton btnRegistrar = new JButton("Registrar");
        btnRegistrar.setFont(new Font("Tahoma", Font.BOLD, 16));
        btnRegistrar.setBackground(new Color(0, 153, 0));
        btnRegistrar.setForeground(Color.WHITE);
        btnRegistrar.setBounds(250, 446, 150, 35);
        btnRegistrar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (validateIntegerField(numField) && validateIntegerField(cantidadField)) {
                    int num = Integer.parseInt(numField.getText());
                    int cantidad = Integer.parseInt(cantidadField.getText());

                    if (num < 0 || cantidad < 0) {
                        JOptionPane.showMessageDialog(AltaGrupo.this, "ERROR: valor inválido ingresado.");
                        return;
                    }

                    Maestro profesorDelGrupo = seleccionarMaestro();
                    if (profesorDelGrupo == null) {
                        JOptionPane.showMessageDialog(AltaGrupo.this, "No se seleccionó un maestro válido.");
                        return;
                    }

                    List<Alumno> alumnosDelGrupo = seleccionarAlumnos(cantidad);
                    if (alumnosDelGrupo.isEmpty()) {
                        JOptionPane.showMessageDialog(AltaGrupo.this, "No se seleccionaron alumnos válidos.");
                        return;
                    }

                    Grupo nuevoGrupo = new Grupo(num, cantidad, profesorDelGrupo);
                    nuevoGrupo.setAlumnos(alumnosDelGrupo.toArray(new Alumno[0]));

                    Control.agregarGrupo(nuevoGrupo);
                    JOptionPane.showMessageDialog(AltaGrupo.this, "Grupo agregado exitosamente.");
                    dispose();
                } else {
                    JOptionPane.showMessageDialog(AltaGrupo.this, "ERROR: valor inválido ingresado.");
                }
            }
        });
        contentPane.add(btnRegistrar);

        JButton btnCancelar = new JButton("Cancelar");
        btnCancelar.setFont(new Font("Tahoma", Font.BOLD, 16));
        btnCancelar.setBackground(new Color(204, 0, 0));
        btnCancelar.setForeground(Color.WHITE);
        btnCancelar.setBounds(450, 446, 150, 35);
        btnCancelar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (numField.getText().isEmpty() && cantidadField.getText().isEmpty()) {
                    dispose();
                } else {
                    limpiarCampos();
                }
            }
        });
        contentPane.add(btnCancelar);
    }

    private Maestro seleccionarMaestro() {
        List<Maestro> maestros = Control.getProfesores();
        String[] columnas = {"Nombre", "Edad", "Matricula", "Facultad", "Título"};
        DefaultTableModel model = new DefaultTableModel(columnas, 0);

        for (Maestro maestro : maestros) {
            model.addRow(new Object[]{maestro.getNombre(), maestro.getEdad(), maestro.getMatricula(), maestro.getFacultad(), maestro.getTituloAcademico()});
        }

        JTable table = new JTable(model);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setBounds(32, 41, 358, 220);

        JDialog dialog = new JDialog(this, "Seleccione un Maestro", true);
        dialog.setBounds(100, 100, 450, 400);
        JPanel panel = new JPanel();
        panel.setBorder(new EmptyBorder(5, 5, 5, 5));
        dialog.setContentPane(panel);
        panel.setLayout(null);

        panel.add(scrollPane);

        JLabel lblSeleccionar = new JLabel("Seleccione un maestro:");
        lblSeleccionar.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblSeleccionar.setBounds(32, 11, 200, 20);
        panel.add(lblSeleccionar);

        JButton btnSeleccionar = new JButton("Seleccionar");
        btnSeleccionar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnSeleccionar.setBackground(new Color(0, 153, 0));
        btnSeleccionar.setForeground(Color.WHITE);
        btnSeleccionar.setBounds(50, 300, 120, 35);
        btnSeleccionar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
            }
        });
        panel.add(btnSeleccionar);

        JButton btnCancelar = new JButton("Cancelar");
        btnCancelar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCancelar.setBackground(new Color(204, 0, 0));
        btnCancelar.setForeground(Color.WHITE);
        btnCancelar.setBounds(250, 300, 120, 35);
        btnCancelar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
            }
        });
        panel.add(btnCancelar);

        dialog.setVisible(true);

        int selectedRow = table.getSelectedRow();
        if (selectedRow >= 0) {
            return maestros.get(selectedRow);
        } else {
            return null;
        }
    }

    private List<Alumno> seleccionarAlumnos(int cantidad) {
        List<Alumno> alumnosSeleccionados = new ArrayList<>();
        List<Alumno> alumnosDisponibles = Control.getEstudiantes();
        String[] columnas = {"Nombre", "Edad", "Matricula", "Facultad", "Promedio", "Carrera", "Semestre"};
        DefaultTableModel model = new DefaultTableModel(columnas, 0);

        for (Alumno alumno : alumnosDisponibles) {
            model.addRow(new Object[]{alumno.getNombre(), alumno.getEdad(), alumno.getMatricula(), alumno.getFacultad(), alumno.getPromedio(), alumno.getCarrera(), alumno.getSemestre()});
        }

        JTable table = new JTable(model);
        table.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setBounds(32, 41, 358, 220);

        JDialog dialog = new JDialog(this, "Seleccione Alumnos", true);
        dialog.setBounds(100, 100, 450, 400);
        JPanel panel = new JPanel();
        panel.setBorder(new EmptyBorder(5, 5, 5, 5));
        dialog.setContentPane(panel);
        panel.setLayout(null);

        panel.add(scrollPane);

        JLabel lblSeleccionar = new JLabel("Seleccione alumnos:");
        lblSeleccionar.setFont(new Font("Tahoma", Font.PLAIN, 15));
        lblSeleccionar.setBounds(32, 11, 200, 20);
        panel.add(lblSeleccionar);

        JButton btnSeleccionar = new JButton("Seleccionar");
        btnSeleccionar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnSeleccionar.setBackground(new Color(0, 153, 0));
        btnSeleccionar.setForeground(Color.WHITE);
        btnSeleccionar.setBounds(50, 300, 120, 35);
        btnSeleccionar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
            }
        });
        panel.add(btnSeleccionar);

        JButton btnCancelar = new JButton("Cancelar");
        btnCancelar.setFont(new Font("Tahoma", Font.BOLD, 14));
        btnCancelar.setBackground(new Color(204, 0, 0));
        btnCancelar.setForeground(Color.WHITE);
        btnCancelar.setBounds(250, 300, 120, 35);
        btnCancelar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
            }
        });
        panel.add(btnCancelar);

        dialog.setVisible(true);

        int[] selectedRows = table.getSelectedRows();
        for (int i : selectedRows) {
            alumnosSeleccionados.add(alumnosDisponibles.get(i));
        }

        if (alumnosSeleccionados.size() > cantidad) {
            JOptionPane.showMessageDialog(this, "Se seleccionaron más alumnos de los permitidos.");
            return new ArrayList<>();
        }

        return alumnosSeleccionados;
    }

    private boolean validateIntegerField(JTextField textField) {
        try {
            Integer.parseInt(textField.getText().trim());
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    private void limpiarCampos() {
        numField.setText("");
        cantidadField.setText("");
    }
}
