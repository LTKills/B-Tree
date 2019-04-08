# File Organization Project

## What is this

This repo contains a project to the Files' Organization class from our
university. As we think (and hope) this can be helpful to other computer
science undergraduates, we decided to open the project.

This project explores different record fitting techniques (Best, Worst
and First-fit) as well as index files searching (in this project we only
implemented one primary index file).

### Already done from previous project

1. Interface and data display
2. Read input file and treat it
3. Remove from the three output files with correct logic
4. Display statistics about the index files and about the removed records


### Things we've done

1. Generate the 3 output files (with Worst, Best or First-fit).

2. Create one primary index **per output file** by the field *ticket*
    - Note here that each file has it index (files 1, 2, 3 have respective 
      indexes 1, 2 and 3). Also, index files MUST be generated IMMEDIATLY AFTER
      the output files. e.g: file 1 generated -> index 1 generated -> file 2 
      generated -> index 2 generated...
    
3. **Logic remotion:** user should type a value and we should
    - Search the record in **each of the 3 files USING THE INDEX FILES**.
    - **Logic remove** the record (See FAQ for explaining).
    - Physically remove the record **from the index files** (See FAQ).
    - Display a message saying whether it was or not successfully removed. 
  
4. **Insertion:** insertion should be done using logic removed spaces
  (dynamic reuse of space).
    - For output file 1 (first-fit) WITHOUT ORDERING: list of removed
    records with treatment of intern fragmentation WITHOUT concatenation
    of available spaces.

    - For output file 2 (best-fit) WITH INCREASING ORDERING: list of removed
    records with treatment of intern fragmentation WITHOUT concatenation
    of available spaces.

    - For output file 2 (worst-fit) WITH DECREASING ORDERING: list of removed
    records with treatment of intern fragmentation WITHOUT concatenation
    of available spaces.

    - **Input:** the user should type the record to be inserted, then we should
      insert the record IN EACH OF THE THREE FILES, update de INDEX FILE and 
      display a message saying whether it was or not successfully inserted.
    
 5. **Statistics about the index file:** This functionality should display
 a TABLE that contains the *number of records* associated to each of the index
 files.
  
 6. **Statistics about the removed records:** This option shows how many removed
 records there are and displays the queue formed in the file in a cute way.
  

---------------------------------------------------------------------------
## File Structuring
  The file structure will be identical as the first project. Fixed-size
  fields should be grouped before variable ones following the order:
  
**FIXED**

  1. ticket
  2. documento
  3. dataHoraCadastro
  4. dataHoraAtualiza

**VARIABLE**

  5. dominio
  6. nome
  7. uf
  8. cidade
  

**Fixed fields come all together on the beginning of the record**,
followed by the variable fields.

Fixed fields do not need any type of indicators, they are always there. 
Variable fields should have **size indicators** before them. 
Records should have **delimiters** at the end of them.

---------------------------------------------------------------------------
## Restrictions
- All files shoud be written and read in *binary mode*
- Data should be read *field by field*
- Index files shoud be in the disk, but they should be loaded in RAM
  during the program's execution.
- The program should compile in *gcc 4.8.2* or newer.
---------------------------------------------------------------------------

## Contributing

We really hope this can help you understand and even implement yourself
files' different structures, organizations and algorithms.


If you'd like to contribute, these are some things we've not implemented
due to time restriction:

- Graphical user interface (GUI)
- Further testing (memory allocation, border cases,...)
- Implement to more input files (other than CSV format)
- Enhance statistics about the removed records (with GUI)
