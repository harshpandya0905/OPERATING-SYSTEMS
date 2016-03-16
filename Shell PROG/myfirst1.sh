#!/bin/bash


DisplayOP()
{
cd Folder
echo " Redirection of O/P :"

ls # Contents inside Folder1
echo " Redirecting O/P to a file :"
ls > file1 # O/P is saved in the file named List
cat file1 # Display contents inside List file
echo " Adding the same information to the file i.e. creating duplicate values "
ls >> file1 # Append duplicate entries
cat file1
}

RecieveINP()
{
cd Folder
echo " Redirection of Input"
echo " Input text "
read text # Reading from Terminal
echo " Text You Entered is : $text "
echo " Reading a file, sorting and saving it in a newly created file named file2 "
sort < file1 > file2 # Read from File sort and then save it to file2
cat file2
}

showPipes()
{
# Pipes are also used as Filters

echo " After using PIPES which acts as a filter where here is used as a UNIQ function that removes the DUPLICATE entries"

cat file2 | uniq

# '|' pipes the output of Newlist to 'uniq'- which deletes all the repeated entries.
}


#Execution starts

DisplayOP&
echo showOutput_PID = $! # Prints the Process ID of the executed Child Process
wait
# Suspends execution of the calling process till the created child thread or the O/P method terminates.
echo " Output Shown " # Displayed after the child process completion

RecieveINP # get call to the Input
echo " Inout Obtained "

showPipes& # show use of pipes
echo showPipes_PID = $!
wait
echo " Program is now Completed "
