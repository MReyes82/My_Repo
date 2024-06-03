package interfaces;

import escuelaClases.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class MostrarMaestros extends JFrame {
    private JTable tablaMaestros;
    private DefaultTableModel modeloTabla;

    public MostrarMaestros() {
        setTitle("Lista de Maestros");
        setSize(800, 550);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        inicializarComponentes();
    }

    private void inicializarComponentes() {
        JPanel panelPrincipal = new JPanel(new BorderLayout());

        // Etiqueta arriba de la tabla
        JLabel lblTitulo = new JLabel("Lista de maestros registrados");
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

        tablaMaestros = new JTable(modeloTabla);
        JScrollPane scrollPane = new JScrollPane(tablaMaestros);

        // Llenar la tabla con los datos de los maestros
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
                int selectedRow = tablaMaestros.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un maestro primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de ver detalles
                    Maestro maestroSeleccionado = obtenerMaestroSeleccionado(selectedRow);
                    new VentanaDetallesMaestro(maestroSeleccionado);
                }
            }
        });

        JButton btnEditar = new JButton("Editar");
        btnEditar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnEditar.setBackground(new Color(0, 153, 204));
        btnEditar.setForeground(Color.WHITE);
        btnEditar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int selectedRow = tablaMaestros.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un maestro primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de edición
                    Maestro maestroSeleccionado = obtenerMaestroSeleccionado(selectedRow);
                    new VentanaEditarMaestro(maestroSeleccionado);
                }
            }
        });

        JButton btnAgregarActividad = new JButton("Agregar Actividad");
        btnAgregarActividad.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnAgregarActividad.setBackground(new Color(0, 153, 204));
        btnAgregarActividad.setForeground(Color.WHITE);
        btnAgregarActividad.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int selectedRow = tablaMaestros.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un maestro primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de agregar actividad
                    Maestro maestroSeleccionado = obtenerMaestroSeleccionado(selectedRow);
                    new AgregarActividad(maestroSeleccionado);
                }
            }
        });

        JButton btnEliminar = new JButton("Eliminar");
        btnEliminar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnEliminar.setBackground(new Color(204, 0, 0));
        btnEliminar.setForeground(Color.WHITE);
        btnEliminar.addActionListener(new ActionListener() 
        {
            public void actionPerformed(ActionEvent e) 
            {
                int selectedRow = tablaMaestros.getSelectedRow();
                if (selectedRow == -1) 
                {
                    JOptionPane.showMessageDialog(null, "Selecciona un maestro primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de eliminación
                    Maestro maestroSeleccionado = obtenerMaestroSeleccionado(selectedRow);
                    int confirmacion = JOptionPane.showConfirmDialog(null, 
                        "¿Está seguro de que desea eliminar al maestro " + maestroSeleccionado.getNombre() + "?", 
                        "Confirmar eliminación", JOptionPane.YES_NO_OPTION);
                    if (confirmacion == JOptionPane.YES_OPTION) {
                        Control.getProfesores().remove(maestroSeleccionado);
                        modeloTabla.removeRow(selectedRow);
                        JOptionPane.showMessageDialog(null, "Maestro eliminado con éxito");
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
        List<Maestro> todosMaestros = Control.getProfesores();

        for (Maestro maestro : todosMaestros) {
            Object[] fila = {
                    maestro.getNombre(),
                    maestro.getEdad(),
                    maestro.getMatricula(),
                    maestro.getFacultad()
            };
            modeloTabla.addRow(fila);
        }
    }

    private Maestro obtenerMaestroSeleccionado(int selectedRow) {
        List<Maestro> todosMaestros = Control.getProfesores();
        return todosMaestros.get(selectedRow);
    }
}
