# MultiCoreClusterSim  
*A multiprocessor cluster simulation for the PRO2 course (UPC)*

## 📌 Overview
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

## 🧩 Features
- **Binary-tree processor cluster** with unique processor identifiers  
- **Waiting area with priorities**, sorted lexicographically  
- **Process model** including ID, memory required, and execution time  
- **Best-fit allocation strategy** within each processor  
- **Scheduling strategy** for sending pending processes to the cluster  
- **Time simulation** with process completion handling  
- **Memory compaction** for individual processors or the entire cluster  
- **Error handling** for invalid operations (as defined in the assignment)

---

## 🛠️ Compilation

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

## ▶️ Usage
Run the executable and provide commands through standard input:

```./program.exe < input.txt```

The command interpreter supports:

- Cluster configuration (```configurar_cluster```, ```cc```)
- Priority and process management (```ap```, ```bp```, ```ape```)
- Sending processes to the cluster (```epc```)
- Time advancement (```at```)
- Memory compaction (```cmp```, ```cmc```)
- Printing detailed system state (```ipri```, ```iae```, ```ipro```, ```ipc```, ```iec```)
- And more (full list available in the assignment)

---

## 📚 Requirements
- **C++11 compiler**
- Linux/Unix environment recommended (for Makefile & tar support)

---

## 👤 Author

Project developed by Oriol Masagué as part of the PRO2 (Programming 2) course at UPC.
Implementation, debugging, and design follow the course specifications.

---

## 📄 License

This project is provided for academic purposes.
Feel free to reference or adapt it, but please follow your institution’s academic integrity rules.
