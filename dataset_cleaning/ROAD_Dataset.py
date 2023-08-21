import os
import csv

# Function to get all filenames containing a keyword in given directory 
def find_files(root_dir, keyword):
    matches = []
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if keyword in file:
                matches.append(os.path.join(root, file))
    return matches

# Function to combine all the given log files into a single log file
def combine_log_files(matched_files, dest_file):
    # Create a list of all .log files in the specified directory
    log_files = matched_files
    
    # Open the destination file in write mode
    with open(dest_file, 'w') as outfile:
        for log in sorted(log_files):
            with open(log, 'r') as infile:
                # Write contents of each log file to the destination file
                outfile.write(infile.read())
                # Optionally, add a newline between files
                outfile.write('\n')

#Function to combine all the CSV files into one
def combine_csv_files(matched_files, dest_file):
    # Get a list of all .csv files in the specified directory
    csv_files = matched_files
    
    # Initialize a list to hold all rows
    all_rows = []
    
    # Read each csv file and append its rows to the all_rows list
    for file in csv_files:
        with open(file, 'r') as infile:
            reader = csv.reader(infile)
            all_rows.extend(row for idx, row in enumerate(reader) if idx > 0 or not all_rows)
            
    # Write all rows to the destination file
    with open(dest_file, 'w', newline='') as outfile:
        writer = csv.writer(outfile)
        writer.writerows(all_rows)

# Get all masquarade log file names
directory_to_search = 'road/attacks' # replace with your directory path
keyword = 'masq'
matched_files = find_files(directory_to_search, keyword)
matched_files = sorted(matched_files)

#Remove the data points having "FFF#0000000000000000"
matched_files_temp = []
for input_file in matched_files:
    input_file_path = input_file
    filename = os.path.basename(input_file_path)
    output_file_path = "road/"+filename
    
    matched_files_temp.append(output_file_path)
    # Step 1: Read the file line by line
    with open(input_file_path, 'r') as infile, open(output_file_path, 'w') as outfile:
        for line in infile:
            # Step 2: Check if the string "FFF#0000000000000000" exists in the line
            if "FFF#0000000000000000" not in line:
                # Step 3: Write to the temporary file
                outfile.write(line)
matched_files = matched_files_temp

#Combine all the log files of Masquerade
src_dir = matched_files  # replace with your directory path
dest_log_file = 'combined_masq_attacks.log'  # replace with your desired output file name
combine_log_files(src_dir, dest_log_file)

# Get all the filenames of CSV having Masquarade attacks
directory_to_search = 'road/signal_extractions/attacks' # replace with your directory path
keyword = 'masq'
matched_files = find_files(directory_to_search, keyword)
matched_files = sorted(matched_files)
print(matched_files)

#Combine all the CSV files of Masquarade into one
src_dir = matched_files  # replace with your directory path
dest_csv_file = 'combined_masq_attacks.csv' # replace with your desired output file name
combine_csv_files(src_dir, dest_csv_file)

# Read the log file and extract data
with open('combined_masq_attacks.log', 'r') as log_file:  # replace 'log.txt' with your log file name
    lines = log_file.readlines()

# Extract required parts of data having ID and data frame
i = 0
extracted_data = []
for line in lines:
    if len(line.split(' '))>1:
        extracted_data.append(line.split(' ')[2].split('#'))
extracted_data = [[item[0], item[1].rstrip('\n')] for item in extracted_data]

# Write the extracted data into a new CSV file
with open('new_attacks_masq.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)
    writer.writerows(extracted_data)

# Read another CSV file and extract the 'label' header field
label_data = []
with open('combined_masq_attacks.csv', 'r') as csv_file:  # replace 'another_file.csv' with your other csv file name
    reader = csv.DictReader(csv_file)
    for row in reader:
        if len(row)>0:
            label_data.append(row['Label'])
print(len(label_data))

# Add the extracted field to the previously created CSV file
with open('new_attacks_masq.csv', 'r') as in_file:
    reader = csv.reader(in_file)
    all_rows = [row for row in reader]

# Add label_data to all_rows (ignoring headers)
for i, label in enumerate(label_data): 
    all_rows[i].append(label)

# Now, write the modified data back to the csv file
with open('new_attacks_masq.csv', 'w', newline='') as out_file:
    writer = csv.writer(out_file)
    writer.writerows(all_rows[1:])

# Read the CSV file and change all labels '0' to 'Normal' and '1' to 'Masquerade'
rows = []
with open('new_attacks_masq.csv', 'r') as csv_file:
    reader = csv.reader(csv_file)
    for row in reader:
        if len(row)>2:
            if row[2] == '0':  # Assuming Labels column is the 3rd column (index 2)
                row[2] = 'Normal'
            elif row[2] == '1':
                row[2] = 'Masquerade'
            rows.append(row)

# Remove all the duplicates
input_file = "new_attacks_masq.csv"
output_file = "Road_Dataset_no_duplicates.csv"
with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
    seen_rows = set() # set for fast O(1) amortized lookup
    reader = csv.reader(infile)
    writer = csv.writer(outfile)

    for row in reader:
        if tuple(row) not in seen_rows:
            seen_rows.add(tuple(row))
            writer.writerow(row)
