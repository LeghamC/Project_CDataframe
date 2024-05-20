# Project_CDataframe
L1-S2 C project : CDataframe   
Link to repository: https://github.com/LeghamC/Project_CDataframe

Project Idea:

For this CDataFrame project, we aim to develop a framework similar to a spreadsheet, akin to programs like LibreOffice Calc or MS Excel. 
Our goal is to empower users to organize their data directly using operations provided by our program.

To achieve this, our code addresses three main tasks:

First, we worked on the columns to handle various data types, allowing users flexibility in data entry. 
Our dataframe can handle the following data types: UINT, INT, CHAR, FLOAT, DOUBLE, STRING, and VEC, which is a custom structure type we implemented. 
In the vector.c file, we implemented numerous functions to manipulate these vectors.

Secondly, to enhance efficiency, we implemented the CDataFrame with a doubly-linked list instead of an array of columns. 
This change enhances its resemblance to a genuine spreadsheet program. We also added the ability to load data from a .csv file to avoid manual entry of multiple lines of data. 
Additionally, we enabled the contents of a CDataFrame to be stored in a .csv file.

Finally, we added several advanced functionalities, including useful functions to search for specific values and sort columns in various ways, whether they are unsorted or partially sorted.

To test our CDataFrame, it is very simple. 
The user only needs to go to the main file and run the program, as we have already included a scenario that demonstrates how our project works and the functionalities we have added.
