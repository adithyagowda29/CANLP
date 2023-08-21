import csv
import random

#Add all Fuzzy attack CSV files into one single CSV file with correct labels
with open('Attack_IV_Fuzzy_multiclass.csv', 'w', newline='') as output_file:
    writer = csv.writer(output_file)
    with open('In-Vehicle_Network_Intrusion_Detection/Fuzzy_CHEVROLET_Spark_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Fuzzy"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Fuzzy_HYUNDAI_Sonata_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:
            if len(row):
                if row[4] == "R":
                    row[4] = "Normal"
                else:
                    row[4] = "Fuzzy"
                writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Fuzzy_KIA_Soul_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Fuzzy"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Fuzzy_dataset_HY_Sonata_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Fuzzy"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Fuzzy_dataset_KIA_Soul_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Fuzzy"
            writer.writerow([row[1],row[3],row[4]])

#Add all Malfunction attack CSV files into one single CSV file with correct labels
with open('Attack_IDS_Malfunction_multiclass.csv', 'w', newline='') as output_file:
    writer = csv.writer(output_file)
    with open('In-Vehicle_Network_Intrusion_Detection/Malfunction_1st_dataset_HY_Sonata_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:
            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Malfunction"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Malfunction_1st_dataset_KIA_Soul_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Malfunction"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Malfunction_2nd_HY_Sonata_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Malfunction"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Malfunction_2nd_KIA_Soul_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Malfunction"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Malfunction_CHEVROLET_Spark_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Malfunction"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Malfunction_HYUNDAI_Sonata_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Malfunction"
            writer.writerow([row[1],row[3],row[4]])

    with open('In-Vehicle_Network_Intrusion_Detection/Malfunction_KIA_Soul_train.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:

            if row[4] == "R":
                row[4] = "Normal"
            else:
                row[4] = "Malfunction"
            writer.writerow([row[1],row[3],row[4]])

# Split data field into 2 bytes of data each column in Malfunction
input_file = "Attack_IDS_Malfunction_multiclass.csv"
output_file = "Attack_IDS_Malfunction_multiclass_data_split.csv"

with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
    reader = csv.reader(infile)
    writer = csv.writer(outfile)
    for row in reader:
        data_split = row[1].split()
        row_list = []
        row_list.append(row[0])
        row_list += data_split
        row_list.append(row[2])
        writer.writerow(row_list)

# Add random data using data from specific IDs by selecting 3 random bytes and inserting random data into it
input_file_path = "Attack_IDS_Malfunction_multiclass_data_split.csv"
output_file_path = "Attack_IDS_Malfunction_multiclass_new.csv"
# Columns to check in 'ID' column
Target_ID = ['0018', '0140', '018F', '0080', '0110', '0260', '0517', '04F1', '059B', '05A2']
# Read data from CSV
original_rows = []
with open(input_file_path, 'r') as infile:
    reader = csv.reader(infile, delimiter=',')
    for row in reader:
        original_rows.append(row)
# Process rows and generate new modified rows
new_rows = []
for row in original_rows:
    if row[0] in Target_ID:
        modified_row = row.copy()  # Create a copy of the row to modify
        # Randomly choose 3 columns from col 4-11 (Python indices 3-10) 
        random_indices = random.sample(range(1, len(row)-2), min(3,len(row)-3))
        # Randomize the byte values
        for idx in random_indices:
            modified_row[idx] = str(format(random.randint(0, 255), '02x')).upper()  # Random byte as hex
        # Flip the last column from R to T
        modified_row[-1] = "Malfunction"
        new_rows.append(modified_row)
# Combine original and new rows
combined_rows = new_rows + original_rows        
# Write data to new CSV
with open(output_file_path, 'w', newline='') as outfile:
    writer = csv.writer(outfile, delimiter=',')
    writer.writerows(combined_rows)

#Combine all the data columns into one data column
with open("Attack_IDS_Malfunction_multiclass_data_combined.csv", 'w', newline='') as output_file:
    writer = csv.writer(output_file)
    with open("Attack_IDS_Malfunction_multiclass_new.csv", 'r') as input_file:
        reader = csv.reader(input_file)
        
        for row in reader:
            
            length_byte = len(row) - 2
            combined_column = ' '.join(row[1:1+length_byte])  # Combine the first 8 columns with whitespace in between
            combined_column = combined_column.upper()

            writer.writerow([row[0],combined_column,row[-1]])

#Combine all the CSV files(Fuzzy and Malfunction) into one
with open('Attack_IDS_all_multiclass.csv', 'w', newline='') as output_file:
    writer = csv.writer(output_file)
    with open('Attack_IDS_Malfunction_multiclass_data_combined.csv', 'r') as input_file:
        reader = csv.reader(input_file)
        for row in reader:
            writer.writerow(row)
    with open('Attack_IV_Fuzzy_multiclass.csv', 'r') as input_file:
        reader = csv.reader(input_file)

        for row in reader:
            writer.writerow(row)

#Remove all the duplicates
input_file = "Attack_IDS_all_multiclass.csv"
output_file = "Attack_IDS_all_multiclass_no_duplicates.csv"
with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
    seen_rows = set() # set for fast O(1) amortized lookup
    reader = csv.reader(infile)
    writer = csv.writer(outfile)

    for row in reader:
        if tuple(row) not in seen_rows:
            seen_rows.add(tuple(row))
            writer.writerow(row)