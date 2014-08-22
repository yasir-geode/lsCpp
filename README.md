The program takes a parameter on the command line which is a directory name.  It does a recursive traversal

of the subdirectories under the directory, printing a line for each node (file, directory, etc.) in the directory. 

The results should contain Files and directories strictly in the format below.

Program should be named <your email alias>_quiz.exe (E.g. John Doe’s Program: jdoe_quiz.exe).

 

Input:

Take directory as command line argument.

 

Usage:

jdoe_quiz.exe <inputDirectory>

 

 

Output:

The result should be printed in the following format:

<Full path of the file>,<F or D – File or Directory>,<Size of the file in bytes (if no size, then print ‘0’)>,<Modified time in Unix time format>

Note that there should not be any spaces between the output fields. File/Directory names can contain spaces.

Directories do not have any size. So display ‘0’ for size.

 

Example:

If the directory structure is as follows:

/export/home/apache/folder1/file2.dat

/export/home/apache/file1.dat

/export/home/apache/file2.dat

 

If the input is: jdoe_quiz “/export/home”

Then the output should be something like:

/export/home/apache,D,0,915148678

/export/home/apache/file1.dat,F,8812,915147128

/export/home/apache/file2.dat,F,1020401,915148801

/export/home/apache/folder1,D,0,915148801

/export/home/apache/folder1/file2.dat,F,6677,915148801

 

 

Requirements:

(1) Make sure that it works on a large directory tree

    (like C:\ or D:\ in Windows, / or /usr in Unix)

(2) If program stops due to a permissions problem, skip that subtree and continue.

 
