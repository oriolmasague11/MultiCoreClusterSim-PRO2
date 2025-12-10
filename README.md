# Multiprocessor Cluster Simulation  
*A multiprocessor cluster simulation for the PRO2 course (UPC)*

## Overview
MultiCoreClusterSim is a C++ simulator of a multiprocessor architecture where processors are arranged as a binary-tree cluster.  
Each processor owns a private memory space and can run multiple processes concurrently.  
A global waiting area stores pending processes, ordered by configurable priority categories.

The simulator supports:
- Cluster creation and modification  
- Priority and process management  
- Best-fit memory allocation without fragmentation  
- Time advancement and automatic removal of completed processes  
- Memory compaction (per processor or cluster-wide)  
- Structured reporting of processors, the cluster, and the waiting area  

This project is based on the specification from the PRO2 course (UPC, 2023).

---

## Features
- **Binary-tree processor cluster** with unique processor identifiers  
- **Waiting area with priorities**, sorted lexicographically  
- **Process model** including ID, memory required, and execution time  
- **Best-fit allocation strategy** within each processor  
- **Scheduling strategy** for sending pending processes to the cluster  
- **Time simulation** with process completion handling  
- **Memory compaction** for individual processors or the entire cluster  
- **Error handling** for invalid operations (as defined in the assignment)

---

## Command Summary

| Command | Abbrev. | Description |
|--------|---------|-------------|
| `configurar_cluster` | `cc` | Initialize or replace the cluster. |
| `modificar_cluster` | `mc` | Replace a processor with a new cluster. |
| `alta_prioridad` | `ap` | Add a new priority to the waiting area. |
| `baja_prioridad` | `bp` | Remove a priority (only if empty). |
| `alta_proceso_espera` | `ape` | Add a process to the waiting area. |
| `alta_proceso_procesador` | `app` | Add a process directly to a processor. |
| `baja_proceso_procesador` | `bpp` | Remove a process from a processor. |
| `enviar_procesos_cluster` | `epc` | Attempt to insert *n* waiting processes. |
| `avanzar_tiempo` | `at` | Advance time and remove finished processes. |
| `imprimir_prioridad` | `ipri` | Print processes of a priority + statistics. |
| `imprimir_area_espera` | `iae` | Print all priorities and their pending processes. |
| `imprimir_procesador` | `ipro` | Print details of a processor. |
| `imprimir_procesadores_cluster` | `ipc` | Print all processors sorted by ID. |
| `imprimir_estructura_cluster` | `iec` | Print binary-tree structure of the cluster. |
| `compactar_memoria_procesador` | `cmp` | Compact memory of a processor. |
| `compactar_memoria_cluster` | `cmc` | Compact memory in all processors. |
| `fin` | — | End program execution. |

---


## Compilation

The project uses `g++` with the following compilation flags:

```-D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11```


### **Build the program**

```make```

This produces an executable:
```program.exe```


### Clean object files and executables
```make clean```


### Generate a .tar file for submission
```make tar```

---

## Usage
Run the executable and provide commands through standard input:

```./program.exe < input.txt```

---

## Requirements
- **C++11 compiler**
- Linux/Unix environment recommended (for Makefile & tar support)

---

## Author

Project developed by Oriol Masagué as part of the PRO2 (Programming 2) course at UPC.
Implementation, debugging, and design follow the course specifications.

---

## 📄 License

This project is provided for academic purposes.
Feel free to reference or adapt it, but please follow your institution’s academic integrity rules.
