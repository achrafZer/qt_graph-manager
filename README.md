# QT Graph Manager

QT Graph Manager is a C++ project that uses the Qt library to display randomly generated or imported matrix data in the form of a graph. The graph summarizes the data with nodes representing the distinct values in the matrix and edges representing the belonging of data to the same row. It also does it the other way, by taking a graph as an input and generating its matrix data

## Installation
To use this project, you will need to have the Qt library installed. You can download it from the [official website](https://www.qt.io/download)

##Usage
Once you have downloaded and installed Qt, you can compile and run the program by opening the project file (matrix-graph.pro) in Qt Creator and building the project.

When the application is launched, it will display the data in a tabular format. For each column, the density of each value will be calculated, providing weighting for the distinct values. The user can modify the graph by moving a node or edge. The size of the nodes and edges depends on the number of distinct values of the element considered.

If the graph is too dense for a good visibility, the user can group multiple nodes to transform them into a meta-node. The user can also choose various color schemes for the nodes and edges. Finally, an export of the image in bitmap (PNG, BMP...) and/or in vectorial (SVG) will be appreciated, accompanied by the description of the data (file name, number of rows and columns, number of nodes and edges, date of the export...)

##Contributing
If you find any bugs or have suggestions for improving the project, please feel free to open an issue or submit a pull request.
