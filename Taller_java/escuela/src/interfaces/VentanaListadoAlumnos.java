package interfaces;

import escuelaClases.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.List;

public class VentanaListadoAlumnos extends JFrame {
    private JTable tablaAlumnos;
    private DefaultTableModel modeloTabla;

    public VentanaListadoAlumnos(Grupo grupo) {
        setTitle("Listado de Alumnos");
        setSize(800, 550);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        inicializarComponentes(grupo);
    }

    private void inicializarComponentes(Grupo grupo) {
        JPanel panelPrincipal = new JPanel(new BorderLayout());

        // Etiqueta arriba de la tabla
        JLabel lblTitulo = new JLabel("Alumnos del grupo " + grupo.getNumeroDeGrupo());
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

        // Llenar la tabla con los datos de los alumnos del grupo
        llenarTabla(grupo);

        // Panel para la tabla
        JPanel panelTabla = new JPanel();
        panelTabla.setLayout(new BorderLayout());
        panelTabla.setPreferredSize(new Dimension(700, 400));
        panelTabla.add(scrollPane, BorderLayout.CENTER);

        JButton btnCerrar = new JButton("Cerrar");
        btnCerrar.setFont(new Font("Times New Roman", Font.BOLD, 16));
        btnCerrar.setBackground(new Color(204, 0, 0));
        btnCerrar.setForeground(Color.WHITE);
        btnCerrar.addActionListener(e -> dispose());

        // Panel para los botones
        JPanel panelBotones = new JPanel();
        panelBotones.setLayout(new FlowLayout(FlowLayout.CENTER));
        panelBotones.add(btnCerrar);

        // Agregar los paneles al panel principal
        panelPrincipal.add(panelTabla, BorderLayout.CENTER);
        panelPrincipal.add(panelBotones, BorderLayout.SOUTH);

        getContentPane().add(panelPrincipal);
        setVisible(true);
    }

    private void llenarTabla(Grupo grupo) {
        List<Alumno> alumnos = List.of(grupo.getAlumnos());

        for (Alumno alumno : alumnos) {
            if (alumno != null) {
                Object[] fila = {
                        alumno.getNombre(),
                        alumno.getEdad(),
                        alumno.getMatricula(),
                        alumno.getFacultad()
                };
                modeloTabla.addRow(fila);
            }
        }
    }
}
