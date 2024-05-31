package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.stream.Collectors;

public class OrdenarPorNombre extends JFrame {
    public OrdenarPorNombre() {
        setTitle("Ordenar por Nombre");
        setSize(600, 400);
        setLocationRelativeTo(null);

        String[] columnNames = {"Tipo", "Nombre", "Edad"};
        List<Object[]> data = Control.getProfesores().stream()
                .sorted((a, b) -> a.getNombre().compareToIgnoreCase(b.getNombre()))
                .map(maestro -> new Object[]{"Maestro", maestro.getNombre(), maestro.getEdad()})
                .collect(Collectors.toList());
        data.addAll(Control.getEstudiantes().stream()
                .sorted((a, b) -> a.getNombre().compareToIgnoreCase(b.getNombre()))
                .map(alumno -> new Object[]{"Alumno", alumno.getNombre(), alumno.getEdad()})
                .collect(Collectors.toList()));

        String[][] dataArray = data.stream()
                .map(row -> new String[]{(String) row[0], (String) row[1], String.valueOf(row[2])})
                .toArray(String[][]::new);

        JTable table = new JTable(dataArray, columnNames);
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);

        setVisible(true);
    }
}

