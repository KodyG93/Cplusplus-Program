#Kody Greenberg for CS 210 12/7/2022 PythonFile.py
import re
import string
from collections import Counter #Used to count frequency of words in included file

# ReadFile is used to read the input file - option 1
def ReadFile():
    # Each product is counted and printed to the console
    # Object to open the text file
    ticket = open("CS210_Project_Three_Input_File.txt") 
    # Creates an object to hold each line from ticket
    products = ticket.read().split() 
    unique_Product = sorted(set(products))
    for word in unique_Product:
        print(word, ": ", products.count(word))
        print("------------------------------------")
        # Ticket object must be closed to prevent memory issues
        ticket.close() 

# A string is entered from C++ code - option 2
# This object then searches through the text file to count quantity of the string
def SelectItem(v):
    ticket = open("CS210_Project_Three_Input_File.txt")
    # Object to split and organize each line from ticket
    products = ticket.read().split() 
    # Sorts the items from the text file
    unique_Product = sorted(set(products)) 
    ticket.close() # closed to prevent memory issues 
    tot = 0
    tot_inventory = 0
    tot_inventory_count = 0
    # Used to get total amount of items in the list
    for word in unique_Product: 
        tot_inventory_count += 1
    for word in unique_Product:
        temp_String = word
        tot_inventory += 1
        if (temp_String.lower() == v.lower()):
            tot = products.count(word)
            # This is used to ensure the string entered from user exists in the file, otherwise an error is produced
            tot_inventory -= 1 
        if (temp_String != v and tot_inventory == tot_inventory_count):
            return -1
    return tot

# Information from the text file is translate to frequency.dat file - OPTION 3
def CreateFile():
    # Each product is sorted and counted, then displayed in a histogram

    ticket = open("CS210_Project_Three_Input_File.txt")
    # Creates the frequency.dat file
    data = open("frequency.dat", "w")

    products = ticket.read().split()
    unique_Product = sorted(set(products))
    #writes the data to the .dat file
    for word in unique_Product:
        data.write(word)
        data.write(" ")
        # Converts the products to string to write to the .dat file
        data.write(str(products.count(word))) 
        data.write("\n")
    data.close()
        
    # After frequency.dat file is created,this object reads the file
    histo_data = open("frequency.dat", "r") 
    product_data = histo_data.readlines()

    temp_freq = 0
    temp_product = ""

    # Reads data from the .dat file for histogram
    for line in product_data:
        temp_int = 0
        # Product name and frequency must be split for proper output 
        temp_string = line.split() 

        for word in temp_string:
            temp_int += 1
            if (temp_int == 1):
                temp_product = word
                print(temp_product, end = " ")
            if (temp_int == 2):
                temp_freq = int(word)