package interfaces;

import escuelaClases.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class MostrarGrupos extends JFrame {
    private JTable tablaGrupos;
    private DefaultTableModel modeloTabla;

    public MostrarGrupos() {
        setTitle("Lista de Grupos");
        setSize(800, 550);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        inicializarComponentes();
    }

    private void inicializarComponentes() {
        JPanel panelPrincipal = new JPanel(new BorderLayout());

        // Etiqueta arriba de la tabla
        JLabel lblTitulo = new JLabel("Lista de grupos registrados");
        lblTitulo.setHorizontalAlignment(SwingConstants.CENTER);
        lblTitulo.setFont(new Font("Times New Roman", Font.BOLD, 24));
        panelPrincipal.add(lblTitulo, BorderLayout.NORTH);

        // Columnas de la tabla
        String[] columnas = {"Número", "Cantidad de alumnos", "Maestro"};

        // Modelo de la tabla
        modeloTabla = new DefaultTableModel(columnas, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false; // Hacer las celdas no editables
            }
        };

        tablaGrupos = new JTable(modeloTabla);
        JScrollPane scrollPane = new JScrollPane(tablaGrupos);

        // Llenar la tabla con los datos de los grupos
        llenarTabla();

        // Panel para la tabla
        JPanel panelTabla = new JPanel();
        panelTabla.setLayout(new BorderLayout());
        panelTabla.setPreferredSize(new Dimension(700, 400));
        panelTabla.add(scrollPane, BorderLayout.CENTER);

        // Botones "Ver Listado de Alumnos" y "Cerrar"
        JButton btnVerListado = new JButton("Ver Listado de Alumnos");
        btnVerListado.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnVerListado.setBackground(new Color(0, 153, 204));
        btnVerListado.setForeground(Color.WHITE);
        btnVerListado.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                int selectedRow = tablaGrupos.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Selecciona un grupo primero", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    // Acción de ver listado de alumnos
                    Grupo grupoSeleccionado = obtenerGrupoSeleccionado(selectedRow);
                    new VentanaListadoAlumnos(grupoSeleccionado);
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
        panelBotones.add(btnVerListado);
        panelBotones.add(btnCerrar);

        // Agregar los paneles al panel principal
        panelPrincipal.add(panelTabla, BorderLayout.CENTER);
        panelPrincipal.add(panelBotones, BorderLayout.SOUTH);

        getContentPane().add(panelPrincipal);
    }

    private void llenarTabla() {
        List<Grupo> todosGrupos = Control.getGrupos();

        for (Grupo grupo : todosGrupos) {
            Object[] fila = {
                    grupo.getNumeroDeGrupo(),
                    grupo.getCantidadMaxAlumnos(),
                    grupo.getProfesor().getNombre()
            };
            modeloTabla.addRow(fila);
        }
    }

    private Grupo obtenerGrupoSeleccionado(int selectedRow) {
        List<Grupo> todosGrupos = Control.getGrupos();
        return todosGrupos.get(selectedRow);
    }
}
