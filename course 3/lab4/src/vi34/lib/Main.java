package vi34.lib;

import Arith.ArithParser;
import com.mxgraph.layout.hierarchical.mxHierarchicalLayout;
import com.mxgraph.swing.mxGraphComponent;
import com.mxgraph.util.mxConstants;
import com.mxgraph.view.mxGraph;
import com.mxgraph.view.mxStylesheet;

import javax.swing.*;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by vi34 on 21/03/16.
 */
public class Main {
    static int cnt = 0;
    public static void main(String[] args) throws FileNotFoundException {
        Parser parser = null;
        //parser = new PostfixParser();
        parser = new ArithParser();

        try {
            Tree res = parser.parse(new FileInputStream("tests/input.txt"));
            mxGraph graph = new mxGraph();
            Object parent = graph.getDefaultParent();
            createStyles(graph);
            graph.getModel().beginUpdate();
            try
            {
                Object v1 = graph.insertVertex(parent, null, res.toString(), 300, 300, 80, 30, "ROUNDED");
                dfs(graph, v1, res);
                mxHierarchicalLayout layout = new mxHierarchicalLayout(graph);
                layout.setIntraCellSpacing(40);
                layout.execute(parent);
            }
            finally
            {
                graph.getModel().endUpdate();
            }
            mxGraphComponent graphComponent = new mxGraphComponent(graph);


            JFrame frame = new JFrame("Simple Graph View");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.getContentPane().add(graphComponent);
            frame.pack();
            frame.setVisible(true);
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    private static void createStyles(mxGraph graph) {
        mxStylesheet stylesheet = graph.getStylesheet();
        Map<String, Object> style = new HashMap<>();
        style.put(mxConstants.STYLE_SHAPE, mxConstants.SHAPE_ELLIPSE);
        style.put(mxConstants.STYLE_OPACITY, 50);
        style.put(mxConstants.STYLE_FONTCOLOR, "#000000");
        style.put(mxConstants.STYLE_FILLCOLOR, "#0099ff");
        stylesheet.putCellStyle("ROUNDED", style);

        Map<String, Object> style2 = new HashMap<>();
        style2.put(mxConstants.STYLE_SHAPE, mxConstants.SHAPE_ELLIPSE);
        style2.put(mxConstants.STYLE_OPACITY, 50);
        style2.put(mxConstants.STYLE_FONTCOLOR, "#000000");
        style2.put(mxConstants.STYLE_FILLCOLOR, "#00ff00");
        stylesheet.putCellStyle("LEAF", style2);

        Map<String, Object> style3 = new HashMap<>();
        style3.put(mxConstants.STYLE_SHAPE, mxConstants.SHAPE_ELLIPSE);
        style3.put(mxConstants.STYLE_OPACITY, 10);
        style3.put(mxConstants.STYLE_FONTCOLOR, "#000000");
        style3.put(mxConstants.STYLE_FILLCOLOR, "#999999");
        stylesheet.putCellStyle("EPS", style3);
    }

    private static void dfs(mxGraph graph, Object par, Tree tree) {
        if (tree.getChildren() == null) return;
        for (Tree child: tree.getChildren()) {
            String style = "ROUNDED";
            if (child.getNode().equals("EPS")) {
                style = "EPS";
            } else if (child.getChildren().size() == 0) {
                style = "LEAF";
            }

            Object created = graph.insertVertex(
                    graph.getDefaultParent(), null, child.toString(), 0, 0, 50, 50, style);
            graph.insertEdge(graph.getDefaultParent(), null, null, par, created);
            dfs(graph, created, child);
        }
    }

}
