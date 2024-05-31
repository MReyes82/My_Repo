package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.stream.Collectors;

// TODO: ARREGLAR LO COMENTADO

public class MostrarGrupos extends JFrame 
{
    public MostrarGrupos() {
        setTitle("Mostrar Grupos");
        setSize(600, 400);
        setLocationRelativeTo(null);

        String[] columnNames = {"Numero del Grupo", "Cantidad Maxima de Alumnos", "Profesor", "Alumnos"};
        List<Grupo> grupos = Control.getGrupos();
        String[][] data = new String[grupos.size()][4];
        for (int i = 0; i < grupos.size(); i++) {
            Grupo grupo = grupos.get(i);
            data[i][0] = String.valueOf(grupo.getNumeroDeGrupo());
            data[i][1] = String.valueOf(grupo.getCantidadMaxAlumnos());
            data[i][2] = grupo.getProfesor().getNombre();
            //data[i][3] = grupo.getAlumnos().stream().map(Alumno::getNombre).collect(Collectors.joining(", "));
            // PENDIENTE DE ARREGLAR
        }

        JTable table = new JTable(data, columnNames);
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane);

        setVisible(true);
    }
}

