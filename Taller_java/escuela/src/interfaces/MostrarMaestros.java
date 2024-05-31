package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class MostrarMaestros extends JFrame 
{
    public MostrarMaestros() {
        setTitle("Mostrar Maestros");
        setSize(600, 400);
        setLocationRelativeTo(null);

        String[] columnNames = {"Nombre", "Edad", "Matricula", "Facultad", "Titulo"};
        List<Maestro> maestros = Control.getProfesores();
        String[][] data = new String[maestros.size()][5];
        for (int i = 0; i < maestros.size(); i++) {
            Maestro maestro = maestros.get(i);
            data[i][0] = maestro.getNombre();
            data[i][1] = String.valueOf(maestro.getEdad());
            data[i][2] = String.valueOf(maestro.getMatricula());
            data[i][3] = maestro.getFacultad();
            data[i][4] = maestro.getTituloAcademico();
        }

        JTable table = new JTable(data, columnNames);
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);

        setVisible(true);
    }
}
