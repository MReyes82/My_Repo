package interfaces;

import escuelaClases.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class MostrarAlumnos extends JFrame {
    private JTable tablaAlumnos;
    private DefaultTableModel modeloTabla;

    public MostrarAlumnos() {
        setTitle("Lista de Alumnos");
        setSize(800, 550);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        inicializarComponentes();
    }

    private void inicializarComponentes() {
        JPanel panelPrincipal = new JPanel(new BorderLayout());

        // Etiqueta arriba de la tabla
        JLabel lblTitulo = new JLabel("Lista de alumnos registrados");
        lblTitulo.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitulo.setFont(new Font("Times New Roman", Font.BOLD, 24));
        panelPrincipal.add(lblTitulo, BorderLayout.NORTH);

        // Columnas de la tabla
        String[] columnas = {"Nombre", "Edad", "Matricula", "Facultad"};

        // Modelo de la tabla
        modeloTabla = new DefaultTableModel(columnas, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false; // Hacer las celdas no editables
            }
        };

        tablaAlumnos = new JTable(modeloTabla);
        JScrollPane scrollPane = new JScrollPane(tablaAlumnos);

        // Llenar la tabla con los datos de los alumnos
        llenarTabla();

        // Panel para la tabla
        JPanel panelTabla = new JPanel();
        panelTabla.setLayout(new BorderLayout());
        panelTabla.setPreferredSize(new Dimension(700, 400));
        panelTabla.add(scrollPane, BorderLayout.CENTER);

        // Botones "Ver Detalles", "Editar", "Agregar Actividad", "Eliminar" y "Cerrar"
        JButton btnVerDetalles = new JButton("Ver Detalles");
        btnVerDetalles.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnVerDetalles.setBackground(new Color(0, 153, 204));
        btnVerDetalles.setForeground(Color.WHITE);
        btnVerDetalles.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int selectedRow = tablaAlumnos.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un alumno primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de ver detalles
                    Alumno alumnoSeleccionado = obtenerAlumnoSeleccionado(selectedRow);
                    new VentanaDetallesAlumnos(alumnoSeleccionado);
                }
            }
        });

        JButton btnEditar = new JButton("Editar");
        btnEditar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnEditar.setBackground(new Color(0, 153, 204));
        btnEditar.setForeground(Color.WHITE);
        btnEditar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int selectedRow = tablaAlumnos.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un alumno primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de edición
                    Alumno alumnoSeleccionado = obtenerAlumnoSeleccionado(selectedRow);
                    new VentanaEditarAlumnos(alumnoSeleccionado);
                }
            }
        });

        JButton btnAgregarActividad = new JButton("Agregar Actividad");
        btnAgregarActividad.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnAgregarActividad.setBackground(new Color(0, 153, 204));
        btnAgregarActividad.setForeground(Color.WHITE);
        btnAgregarActividad.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int selectedRow = tablaAlumnos.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un alumno primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de agregar actividad
                    Alumno alumnoSeleccionado = obtenerAlumnoSeleccionado(selectedRow);
                    new AgregarActividadAlumno(alumnoSeleccionado);
                }
            }
        });

        JButton btnEliminar = new JButton("Eliminar");
        btnEliminar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnEliminar.setBackground(new Color(204, 0, 0));
        btnEliminar.setForeground(Color.WHITE);
        btnEliminar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int selectedRow = tablaAlumnos.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un alumno primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de eliminación
                    Alumno alumnoSeleccionado = obtenerAlumnoSeleccionado(selectedRow);
                    int confirmacion = JOptionPane.showConfirmDialog(null, 
                        "¿Está seguro de que desea eliminar al alumno " + alumnoSeleccionado.getNombre() + "?", 
                        "Confirmar eliminación", JOptionPane.YES_NO_OPTION);
                    if (confirmacion == JOptionPane.YES_OPTION) {
                        Control.getEstudiantes().remove(alumnoSeleccionado);
                        modeloTabla.removeRow(selectedRow);
                        JOptionPane.showMessageDialog(null, "Alumno eliminado con éxito");
                    }
                }
            }
        });

        JButton btnCerrar = new JButton("Cerrar");
        btnCerrar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnCerrar.setBackground(new Color(204, 0, 0));
        btnCerrar.setForeground(Color.WHITE);
        btnCerrar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        // Panel para los botones
        JPanel panelBotones = new JPanel();
        panelBotones.setLayout(new FlowLayout(FlowLayout.CENTER));
        panelBotones.add(btnVerDetalles);
        panelBotones.add(btnEditar);
        panelBotones.add(btnAgregarActividad);
        panelBotones.add(btnEliminar);
        panelBotones.add(btnCerrar);

        // Agregar los paneles al panel principal
        panelPrincipal.add(panelTabla, BorderLayout.CENTER);
        panelPrincipal.add(panelBotones, BorderLayout.SOUTH);

        getContentPane().add(panelPrincipal);
    }

    private void llenarTabla() {
        List<Alumno> todosAlumnos = Control.getEstudiantes();

        for (Alumno alumno : todosAlumnos) {
            Object[] fila = {
                    alumno.getNombre(),
                    alumno.getEdad(),
                    alumno.getMatricula(),
                    alumno.getFacultad()
            };
            modeloTabla.addRow(fila);
        }
    }

    private Alumno obtenerAlumnoSeleccionado(int selectedRow) {
        List<Alumno> todosAlumnos = Control.getEstudiantes();
        return todosAlumnos.get(selectedRow);
    }
}
