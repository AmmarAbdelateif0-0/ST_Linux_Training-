# Disk Partition Reader

This C program reads the Master Boot Record (MBR) from a disk image file and displays information about the primary partitions and any extended partitions found within the disk image. The program is designed to work with disk images formatted with the MBR partitioning scheme.

## Table of Contents

- [Description](#description)
- [Usage](#usage)

## Description

The program performs the following tasks:

1. **Open Disk Image**: Opens the specified disk image file in read-only mode.

2. **Read MBR**: Reads the first 512 bytes of the disk image to obtain the Master Boot Record (MBR).

3. **Parse Partitions**: Extracts partition information from the MBR, identifying primary partitions and detecting any extended partitions.

4. **Display Partitions**: Prints a table summarizing the partition information, including:
   
   - **Device**: Specifies the disk image file and partition index.
   - **Boot**: Indicates whether the partition is bootable (* if yes).
   - **Start**: Shows the starting Logical Block Address (LBA) of the partition.
   - **End**: Shows the ending LBA of the partition.
   - **Sectors**: Displays the total number of sectors in the partition.
   - **Size**: Provides the size of the partition in gigabytes.
   - **Id**: Lists the partition type ID.
   - **Type**: Describes the partition type, such as Extended or Linux.

   For extended partitions, the program reads the extended partition table to provide additional details.

## Usage

To use the program, compile it and run it with the path to the disk image file as an argument. 

1. **Clone the Repository**

   ```sh
   git clone https://github.com/username/repository.git
   ```
- *Navigate to the Project Directory* :     
    ```sh
   cd <project-directory>
    ```    
- then
    ```sh
        make
    ```
- when you run this program must used sudo replace x by you      MBR   partition.
    ```sh
        sudo ./mydisk /dev/sd[x]
    ```

## example :
    
```sh
        sudo ./mydisk /dev/sdb
   ```
### output
```sh
Device     Boot     Start           End            Sectors         Size     Id     Type
/dev/sdb1           2048            41945087       41943040        20G      05      Extended
/dev/sdb2           41945088        50333695       8388608         4G      83      Linux
/dev/sdb3           0               4294967295     0               0G      00      Linux
/dev/sdb4           0               4294967295     0               0G      00      Linux
/dev/sdb5           4096            10489855       10485760        5G      83      Linux
/dev/sdb6           0               4294967295     0               0G      00      Linux


   ```


---------------------------------