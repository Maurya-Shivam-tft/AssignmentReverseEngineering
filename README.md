# C++ DLL Automation & Reverse Engineering Assignment

## Objective
Non-Admin Requirement.
Important: The entire solution must work without Administrator privileges.

Create a C++ application that automates changing the default search engine in Microsoft Edge.

## Assignment

### 1. Create a C++ EXE and DLL

The solution must contain:

* A C++ EXE
* A C++ DLL

### 2. EXE Responsibilities

The EXE should only:

* Load and execute the DLL.
* Write logs in the AppData folder.
* Log:

  * Start Time
  * End Time
  * Status (Success/Failure)
  * Total Time Taken

The EXE should run by simply double-clicking it.

### 3. DLL Responsibilities

The DLL should:

* Automate the manual steps required to change the default search engine in Microsoft Edge from **Bing** to **Yahoo** without requiring any user interaction.
* Return a Success/Failure status to the EXE once the automation is complete.
* Ensure the change persists after restarting Microsoft Edge.

### 4. Reverse Engineering Task

Using **Ghidra** or **IDA**, reverse engineer the DLL and modify its behavior so that it changes the default search engine from **Yahoo** to **DuckDuckGo**.

**Allowed Tools:**

* Ghidra
* IDA Free
* IDA Pro

### 5. Verification

After modifying the DLL:

* Run the EXE again.
* Verify that the search engine changes to **DuckDuckGo**.
* Verify that the change persists after restarting Microsoft Edge.

## Video Recording

Record a video using **Bandicam (Free Version)** showing:

* Original EXE execution.
* Search engine changing from Bing to Yahoo.
* DLL analysis using Ghidra or IDA.
* DLL modification.
* Running the EXE again.
* Search engine changing from Bing to DuckDuckGo.

### Recording Guidelines

* The recording must be continuous and unedited.
* The recording must not exceed **10 minutes**.

## Deliverables

* EXE source code
* DLL source code
* Compiled EXE
* Compiled DLL
* Modified DLL
* Screen recording video
* Brief explanation of the implementation and reverse-engineering approach
