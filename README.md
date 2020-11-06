# Self-Database
## Introduction
This is my try to build my own simple database which is based on db_tutorial
## Config
```
gcc 7.5.0
GNU make 4.1
```
## Setup
First, you need to clone this project into your Linux machine because my programme is written and run on the Linux operating system.
```
git clone https://github.com/KuangjuX/Self-Database.git
cd Self-Database/database
```
In this project, I provide a Makefile file , hoping to help our database programme compile and run easily. \
So you can compile and run by executing the following commands in your terminal:
```
make
make run
```
And if you want to compile the programme again:, you can execute `make clean` to delete exist executable file.
## Use
When you execute this programme, you will see a signal `db > `  , which prints a prompt to the user. We do this before reading each line of input. \
We assuse a structer of data table, only including id, user and email. So you can test by enter a line like this: `insert qcx qcx@tju.ecu.com` to insert a row to this table. \
Similarly， you can also enter a line `select` to get all of data in this table.
