import csv

#Add all data from all CSV into one single CSV file with correct labels
with open('Car_Hacking_Dataset_All_multiclass.csv', 'w', newline='') as output_file:
    writer = csv.writer(output_file)
    with open('Car_Hacking_Dataset/DoS_dataset.csv', 'r') as input_file:
        reader = csv.reader(input_file)
        
        for row in reader:
            
            length_byte = int(row[2])
            combined_column = ' '.join(row[3:3+length_byte])  # Combine the first 8 columns with whitespace in between
            combined_column = combined_column.upper()
            
            if row[3+length_byte] == "R":
                row[3+length_byte] = "Normal"
            else:
                continue
            writer.writerow([row[1],combined_column,row[3+length_byte]])
    
    with open('Car_Hacking_Dataset/Fuzzy_dataset.csv', 'r') as input_file:
        reader = csv.reader(input_file)
        
        for row in reader:
            
            length_byte = int(row[2])
            combined_column = ' '.join(row[3:3+length_byte])  # Combine the first 8 columns with whitespace in between
            combined_column = combined_column.upper()
            
            if row[3+length_byte] == "R":
                row[3+length_byte] = "Normal"
            else:
                row[3+length_byte] = "Fuzzy"
            writer.writerow([row[1],combined_column,row[3+length_byte]])
    
    with open('Car_Hacking_Dataset/gear_dataset_2_new.csv', 'r') as input_file:
        reader = csv.reader(input_file)
        
        for row in reader:
            
            length_byte = int(row[2])
            combined_column = ' '.join(row[3:3+length_byte])  # Combine the first 8 columns with whitespace in between
            combined_column = combined_column.upper()
            
            if row[3+length_byte] == "R":
                row[3+length_byte] = "Normal"
            else:
                row[3+length_byte] = "Spoofing"
            writer.writerow([row[1],combined_column,row[3+length_byte]])
    
    with open('Car_Hacking_Dataset/RPM_dataset_new.csv', 'r') as input_file:
        reader = csv.reader(input_file)
        
        for row in reader:
            
            length_byte = int(row[2])
            combined_column = ' '.join(row[3:3+length_byte])  # Combine the first 8 columns with whitespace in between
            combined_column = combined_column.upper()
            
            if row[3+length_byte] == "R":
                row[3+length_byte] = "Normal"
            else:
                row[3+length_byte] = "Spoofing"
            writer.writerow([row[1],combined_column,row[3+length_byte]])

#Remove all the duplicates
input_file = "Car_Hacking_Dataset_All_multiclass.csv"
output_file = "Car_Hacking_Dataset_no_duplicates.csv"
with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
    seen_rows = set() # set for fast O(1) amortized lookup
    reader = csv.reader(infile)
    writer = csv.writer(outfile)

    for row in reader:
        if tuple(row) not in seen_rows:
            seen_rows.add(tuple(row))
            writer.writerow(row)